module.exports = function(RED) {
    "use strict";
    const {
        SerialPort
    } = require('serialport')

    function BatteryInvertNode(n) {
        RED.nodes.createNode(this, n);
        var node = this;
        this.serial = null;
        this.cache = {
            "voltScale": null,
            "amps": null,
            "phaseVoltage": null,
            "watt": null,
            "hertz": null,
            "powerFactor": null,
            "wattHours": null,
            "dcVoltage": null,
            "temperature": null
        };
        this.modbusid = Number("0x" + (n.modbusid || "00").trim());
        this.timer = Number(n.timer || 0) * 1000;
        this.config = {
            baudRate: 57600,
            path: (n.serialport || "").trim(),
            dataBits: 8,
            parity: "none",
            stopBits: 1,
            lock: false, // Hack: Without the this hack, the serial connection is not unlocked in the error/timeout case.
            autoOpen: true
        };
        this.computeCrc = function(oldCrc, data) {
            const v = data;
            var result = ((oldCrc ^ v) | 0xFF00) & (oldCrc | 0x00FF);
            for (var i = 0; i < 8; i++) {
                const leastSignifcantByteSet = result & 0x0001;
                result = result / 2;
                if (leastSignifcantByteSet) result = result ^ 0xA001;
            }
            return result;
        };
        this.getAddressAndLengthFromRegisterType = function(registerType) {
            switch (registerType) {
                case "CommonManufacturer":
                    return {
                        "address": 40004, "length": 16
                    };
                case "CommonModel":
                    return {
                        "address": 40020, "length": 16
                    };
                case "CommonSerialNumber":
                    return {
                        "address": 40052, "length": 16
                    };
                case "CommonDeviceAddress":
                    return {
                        "address": 40068, "length": 1
                    };
                case "InverterAmps":
                    return {
                        "address": 40072, "length": 1
                    };
                case "InverterAmpsPhaseA":
                    return {
                        "address": 40073, "length": 1
                    };
                case "InverterAmpsPhaseB":
                    return {
                        "address": 40074, "length": 1
                    };
                case "InverterAmpsPhaseC":
                    return {
                        "address": 40075, "length": 1
                    };
                case "InverterAmpsScaleFactor":
                    return {
                        "address": 40076, "length": 1
                    };
                case "InverterPhaseVoltageA":
                    return {
                        "address": 40080, "length": 1
                    };
                case "InverterPhaseVoltageB":
                    return {
                        "address": 40081, "length": 1
                    };
                case "InverterPhaseVoltageC":
                    return {
                        "address": 40082, "length": 1
                    };
                case "InverterPhaseVoltageScaleFactor":
                    return {
                        "address": 40083, "length": 1
                    };
                case "InverterWatt":
                    return {
                        "address": 40084, "length": 1
                    };
                case "InverterWattScaleFactor":
                    return {
                        "address": 40085, "length": 1
                    };
                case "InverterHertz":
                    return {
                        "address": 40086, "length": 1
                    };
                case "InverterHertzScaleFactor":
                    return {
                        "address": 40087, "length": 1
                    };
                case "InverterPowerFactor":
                    return {
                        "address": 40092, "length": 1
                    };
                case "InverterPowerFactorScaleFactor":
                    return {
                        "address": 40093, "length": 1
                    };
                case "InverterWattHours":
                    return {
                        "address": 40094, "length": 2
                    };
                case "InverterWattHoursScaleFactor":
                    return {
                        "address": 40096, "length": 1
                    };
                case "InverterDcVoltage":
                    return {
                        "address": 40099, "length": 1
                    };
                case "InverterDcVoltageScaleFactor":
                    return {
                        "address": 40100, "length": 1
                    };
                case "InverterTemperature":
                    return {
                        "address": 40103, "length": 1
                    };
                case "InverterTemperatureScaleFactor":
                    return {
                        "address": 40107, "length": 1
                    };
                case "InverterOperatingState":
                    return {
                        "address": 40108, "length": 1
                    };
                case "NameplateDerType":
                    return {
                        "address": 40124, "length": 1
                    };
                case "ExtendedMesurementsAcWattHours":
                    return {
                        "address": 40187, "length": 2
                    };
                default:
                    return null;
            }
        };
        this.convertRequestToModbus = function(request) {

            function high(value16) {
                return (value16 >> 8) & 0xff;
            };

            function low(value16) {
                return (value16 >> 0) & 0xff;
            };

            function build(array) {
                var buffer = new Uint8Array(array.length + 2);
                var crc = 0xffff;
                for (var i = 0; i < array.length; i++) {
                    buffer[i] = array[i];
                    crc = node.computeCrc(crc, array[i]);
                }
                buffer[array.length + 0] = low(crc);
                buffer[array.length + 1] = high(crc);
                return buffer;
            };
            if (!("type" in request)) throw new Error("Request has no type.");
            switch (request.type) {
                case "factoryValues":
                    return build([node.modbusid, 0x31, 0x01, 0x01]);
                case "readRegister":
                    if (!("value" in request)) throw new Error("Request from type 'readRegister' has no 'value'.");
                    if (!("registerAddress" in request.value)) throw new Error("Request value from type 'readRegister' has no 'registerAddress'.");
                    const addressAndSize = node.getAddressAndLengthFromRegisterType(request.value.registerAddress);
                    if (addressAndSize == null) throw new Error("Request registerAddress '" + request.value.registerAddress + "' unknown.");
                    return build([node.modbusid, 0x03, high(addressAndSize.address), low(addressAndSize.address), 0x00, addressAndSize.length]);
                default:
                    throw new Error("Request type '" + request.type + "' unknown.");
            }
        }
        class Parser {

            constructor(id, request) {
                this.state = 0;
                this.id = id;
                this.crc = 0xffff;
                this.request = request;
            }
            read(byte) {
                this.blub = byte;
                const STATE_ID = 0;
                const STATE_FUNCTION = STATE_ID + 1;
                const STATE_FACTORY_VALUES = STATE_FUNCTION + 1;
                const STATE_READ_REGISTER = STATE_FACTORY_VALUES + 15;
                const STATE_DONE = STATE_READ_REGISTER + 4;

                function jump(state, obj) {
                    obj.state = state;
                    return null;
                };

                function crcAndJump(state, data, obj) {
                    obj.crc = node.computeCrc(obj.crc, data);
                    return jump(state, obj);
                };

                function checkCrcLowAndJump(state, obj) {
                    const low = (obj.crc >> 0) & 0xff;
                    if (low != byte) throw new Error("Expected 0x" + low.toString(16).padStart(2, '0') + " as low crc, but got 0x" + byte.toString(16).padStart(2, '0'));
                    return jump(state, obj);
                };

                function checkCrcHighAndDone(result, obj) {
                    const high = (obj.crc >> 8) & 0xff;
                    if (high != byte) throw new Error("Expected 0x" + high.toString(16).padStart(2, '0') + " as high crc, but got 0x" + byte.toString(16).padStart(2, '0'));
                    return result;
                };
                switch (this.state) {
                    case STATE_ID + 0:
                        if (byte != this.id) throw new Error("Received wrong modbus(" + byte.toString(16).padStart(2, '0') + ") id(0x" + this.id.toString(16).padStart(2, '0') + ")");
                        return crcAndJump(STATE_FUNCTION + 0, byte, this);
                    case STATE_FUNCTION + 0:
                        switch (byte) {
                            case 0x03:
                                if (this.request.type != "readRegister") throw Error("Expected '0x03' as modbus function code for 'readRegister' request, but got " + byte.toString(16).padStart(2, '0'));
                                return crcAndJump(STATE_READ_REGISTER + 0, byte, this);
                            case 0x31:
                                if (this.request.type != "factoryValues") throw Error("Expected '0x31' as modbus function code for 'factoryValues' request, but got " + byte.toString(16).padStart(2, '0'));
                                return crcAndJump(STATE_FACTORY_VALUES + 0, byte, this);
                            default:
                                throw new Error("Received unknown modbus function(0x" + byte.toString(16).padStart(2, '0') + ")");
                        }
                    case STATE_FACTORY_VALUES + 0:
                        if (byte != 0x0c) throw new Error("Expected 0x0c as length for factory values response, but got 0x" + byte.toString(16).padStart(2, '0'));
                        return crcAndJump(STATE_FACTORY_VALUES + 1, byte, this);
                    case STATE_FACTORY_VALUES + 1:
                        this.serialnumber = byte << 8;
                        return crcAndJump(STATE_FACTORY_VALUES + 2, byte, this);
                    case STATE_FACTORY_VALUES + 2:
                        this.serialnumber = this.serialnumber | byte;
                        return crcAndJump(STATE_FACTORY_VALUES + 3, byte, this);
                    case STATE_FACTORY_VALUES + 3:
                        if (byte <= 0 || byte > 31) throw new Error("Expected 1…31 as day for factory values response, but got " + byte.toString());
                        this.day = byte;
                        return crcAndJump(STATE_FACTORY_VALUES + 4, byte, this);
                    case STATE_FACTORY_VALUES + 4:
                        if (byte <= 0 || byte > 12) throw new Error("Expected 1…12 as month for factory values response, but got " + byte.toString());
                        this.month = byte;
                        return crcAndJump(STATE_FACTORY_VALUES + 5, byte, this);
                    case STATE_FACTORY_VALUES + 5:
                        if (byte <= 0 || byte > 99) throw new Error("Expected 1…99 as year for factory values response, but got " + byte.toString());
                        this.year = byte;
                        return crcAndJump(STATE_FACTORY_VALUES + 6, byte, this);
                    case STATE_FACTORY_VALUES + 6:
                        this.hardwareVersion = byte;
                        return crcAndJump(STATE_FACTORY_VALUES + 7, byte, this);
                    case STATE_FACTORY_VALUES + 7:
                        this.firmwareVersion = byte;
                        return crcAndJump(STATE_FACTORY_VALUES + 8, byte, this);
                    case STATE_FACTORY_VALUES + 8:
                        this.bootstrappVersion = byte;
                        return crcAndJump(STATE_FACTORY_VALUES + 9, byte, this);
                    case STATE_FACTORY_VALUES + 9:
                        return crcAndJump(STATE_FACTORY_VALUES + 10, byte, this);
                    case STATE_FACTORY_VALUES + 10:
                        return crcAndJump(STATE_FACTORY_VALUES + 11, byte, this);
                    case STATE_FACTORY_VALUES + 11:
                        return crcAndJump(STATE_FACTORY_VALUES + 12, byte, this);
                    case STATE_FACTORY_VALUES + 12:
                        return crcAndJump(STATE_FACTORY_VALUES + 13, byte, this);
                    case STATE_FACTORY_VALUES + 13:
                        return checkCrcLowAndJump(STATE_FACTORY_VALUES + 14, this);
                    case STATE_FACTORY_VALUES + 14:
                        return checkCrcHighAndDone({
                            "type": "factoryValues",
                            "value": {
                                "serialnumber": this.serialnumber,
                                "productionDate": {
                                    "day": this.day,
                                    "month": this.month,
                                    "year": this.year
                                },
                                "hardwareVersion": this.hardwareVersion,
                                "firmwareVersion": this.firmwareVersion,
                                "bootstrappVersion": this.bootstrappVersion
                            }
                        }, this);
                    case STATE_READ_REGISTER + 0:
                        const addressAndSize = node.getAddressAndLengthFromRegisterType(this.request.value.registerAddress);
                        if (addressAndSize == null) throw new Error("Request registerAddress '" + request.value.registerAddress + "' unknown.");
                        if (addressAndSize.length * 2 != byte) throw new Error("Expected " + (addressAndSize.length * 2).toString() + " as length for readRegister response, but got " + byte + ".");
                        this.data = Array(byte);
                        this.position = 0;
                        return crcAndJump(STATE_READ_REGISTER + 1, byte, this);
                    case STATE_READ_REGISTER + 1:
                        this.data[this.position] = byte;
                        this.position++;
                        return crcAndJump(STATE_READ_REGISTER + (this.position >= this.data.length ? 2 : 1), byte, this);
                    case STATE_READ_REGISTER + 2:
                        return checkCrcLowAndJump(STATE_READ_REGISTER + 3, this);
                    case STATE_READ_REGISTER + 3:
                        function getResult(address, data) {
                            switch (address) {
                                case "CommonManufacturer":
                                case "CommonModel":
                                case "CommonSerialNumber":
                                    function buildString(array) {
                                        var s = "";
                                        for (var i = 0; i < array.length; i++)
                                            if (array[i] >= ' '.charCodeAt(0) && array[i] <= '~'.charCodeAt(0)) s += String.fromCharCode(array[i]);
                                        return s;
                                    };
                                    return (buildString(data));
                                case "InverterAmps":
                                case "InverterAmpsPhaseA":
                                case "InverterAmpsPhaseB":
                                case "InverterAmpsPhaseC":
                                    return {
                                        "quantety": node.cache.amps * (data[0] << 8 | data[1]), "unit": "A"
                                    };
                                case "InverterPhaseVoltageA":
                                case "InverterPhaseVoltageB":
                                case "InverterPhaseVoltageC":
                                    return {
                                        "quantety": node.cache.phaseVoltage * (data[0] << 8 | data[1]), "unit": "V"
                                    };
                                case "InverterWatt":
                                    return {
                                        "quantety": node.cache.watt * (data[0] << 8 | data[1]), "unit": "W"
                                    };
                                case "InverterHertz":
                                    return {
                                        "quantety": node.cache.hertz * (data[0] << 8 | data[1]), "unit": "Hz"
                                    };
                                case "InverterPowerFactor":
                                    return {
                                        "quantety": node.cache.powerFactor * (data[0] << 8 | data[1]), "unit": "%"
                                    };
                                case "InverterWattHours":
                                    return {
                                        "quantety": node.cache.wattHours * (data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3]), "unit": "Wh"
                                    };
                                case "InverterDcVoltage":
                                    return {
                                        "quantety": node.cache.dcVoltage * (data[0] << 8 | data[1]), "unit": "V"
                                    };
                                case "InverterTemperature":
                                    return {
                                        "quantety": node.cache.temperature * (data[0] << 8 | data[1]), "unit": "°C"
                                    };
                                case "CommonDeviceAddress":
                                case "InverterOperatingState":
                                case "NameplateDerType":
                                    return (data[0] << 8 | data[1]);
                                case "ExtendedMesurementsAcWattHours":
                                    return {
                                        "quantety": (data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3]), "unit": "Wh"
                                    };
                                case "InverterAmpsScaleFactor":
                                case "InverterPhaseVoltageScaleFactor":
                                case "InverterWattScaleFactor":
                                case "InverterHertzScaleFactor":
                                case "InverterPowerFactorScaleFactor":
                                case "InverterWattHoursScaleFactor":
                                case "InverterDcVoltageScaleFactor":
                                case "InverterTemperatureScaleFactor":
                                    const v0 = data[0] << 8 | data[1];
                                    const v1 = v0 > 32767 ? v0 - 65536 : v0;
                                    if (v1 < -10 || v1 > 10) throw Error("Scale factor(" + v1.toString() + ") is not in scale [-10,+10]");
                                    return v1;
                                default:
                                    throw Error("Can not handle request register address(" + address + ").");
                            }
                        };
                        const result = getResult(this.request.value.registerAddress, this.data);
                        return checkCrcHighAndDone({
                            "type": "readRegister",
                            "value": {

                                "value": result,
                                "registerAddress": this.request.value.registerAddress
                            }
                        }, this);
                    default:
                        throw new Error("Unexpected state");
                }
            }
        }

        this.setVolt = function(nodeValue) {
            switch (nodeValue.type) {
                case "solar":
                    switch (nodeValue.voltageType) {
                        case 1:
                            nodeValue.voltageType = {
                                "quantety": 12,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.028;
                            break;
                        case 2:
                            nodeValue.voltageType = {
                                "quantety": 17,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.054;
                            break;
                        case 3:
                            nodeValue.voltageType = {
                                "quantety": 35,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.054;
                            break;
                        case 4:
                            nodeValue.voltageType = {
                                "quantety": 50,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.079;
                            break;
                        case 5:
                            nodeValue.voltageType = {
                                "quantety": 70,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.108;
                            break;
                        case 6:
                            nodeValue.voltageType = {
                                "quantety": 90,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.142;
                            break;
                        case 7:
                            nodeValue.voltageType = {
                                "quantety": 120,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.186;
                            break;
                        case 8:
                            nodeValue.voltageType = {
                                "quantety": 160,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.244;
                            break;
                        case 9:
                            nodeValue.voltageType = {
                                "quantety": 240,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.357;
                            break;
                        case 10:
                            nodeValue.voltageType = {
                                "quantety": 320,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.479;
                            break;
                        default:
                            break;
                    }
                    break;
                case "wind":
                    switch (nodeValue.voltageType) {
                        case 1:
                            nodeValue.voltageType = {
                                "quantety": 12,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.028;
                            break;
                        case 2:
                            nodeValue.voltageType = {
                                "quantety": 18,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.054;
                            break;
                        case 3:
                            nodeValue.voltageType = {
                                "quantety": 24,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.054;
                            break;
                        case 4:
                            nodeValue.voltageType = {
                                "quantety": 36,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.079;
                            break;
                        case 5:
                            nodeValue.voltageType = {
                                "quantety": 48,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.108;
                            break;
                        case 6:
                            nodeValue.voltageType = {
                                "quantety": 72,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.142;
                            break;
                        case 7:
                            nodeValue.voltageType = {
                                "quantety": 96,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.186;
                            break;
                        case 8:
                            nodeValue.voltageType = {
                                "quantety": 120,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.244;
                            break;
                        case 9:
                            nodeValue.voltageType = {
                                "quantety": 160,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.357;
                            break;
                        case 10:
                            nodeValue.voltageType = {
                                "quantety": 240,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.479;
                            break;
                        default:
                            break;
                    }
                    break;
                case "battery":
                    switch (nodeValue.voltageType) {
                        case 1:
                            nodeValue.voltageType = {
                                "quantety": 8,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.028;
                            break;
                        case 2:
                            nodeValue.voltageType = {
                                "quantety": 12,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.054;
                            break;
                        case 3:
                            nodeValue.voltageType = {
                                "quantety": 24,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.054;
                            break;
                        case 4:
                            nodeValue.voltageType = {
                                "quantety": 30,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.079;
                            break;
                        case 5:
                            nodeValue.voltageType = {
                                "quantety": 36,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.108;
                            break;
                        case 6:
                            nodeValue.voltageType = {
                                "quantety": 48,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.142;
                            break;
                        case 7:
                            nodeValue.voltageType = {
                                "quantety": 96,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.186;
                            break;
                        case 8:
                            nodeValue.voltageType = {
                                "quantety": 120,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.244;
                            break;
                        case 9:
                            nodeValue.voltageType = {
                                "quantety": 160,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.357;
                            break;
                        case 10:
                            nodeValue.voltageType = {
                                "quantety": 240,
                                "unit": "V"
                            };
                            this.cache.voltScale = 0.479;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        };
        this.updateCache = function(payload) {
            const lookup = [0.028, 0.054, 0.054, 0.079, 0.108, 0.142, 0.186, 0.244, 0.357, 0.479];

            function getIndex(type, quantety) {
                switch (type) {
                    case "solar":
                        switch (quantety) {
                            case 12:
                                return 0;
                            case 17:
                                return 1;
                            case 35:
                                return 2;
                            case 50:
                                return 3;
                            case 70:
                                return 4;
                            case 90:
                                return 5;
                            case 120:
                                return 6;
                            case 160:
                                return 7;
                            case 240:
                                return 8;
                            case 320:
                                return 9;
                            default:
                                return null;
                        }
                    case "wind":
                        switch (quantety) {
                            case 12:
                                return 0;
                            case 18:
                                return 1;
                            case 24:
                                return 2;
                            case 36:
                                return 3;
                            case 48:
                                return 4;
                            case 72:
                                return 5;
                            case 96:
                                return 6;
                            case 120:
                                return 7;
                            case 160:
                                return 8;
                            case 240:
                                return 9;
                            default:
                                return null;
                        }
                    case "battery":
                        switch (quantety) {
                            case 8:
                                return 0;
                            case 12:
                                return 1;
                            case 24:
                                return 2;
                            case 30:
                                return 3;
                            case 36:
                                return 4;
                            case 48:
                                return 5;
                            case 96:
                                return 6;
                            case 120:
                                return 7;
                            case 160:
                                return 8;
                            case 240:
                                return 9;
                            default:
                                return null;
                        }
                    default:
                        return null;
                }
            };

            switch (payload.type) {
                case "readOperatingData3e":
                    const index = getIndex(payload.value.type, payload.value.voltageType.quantety);
                    if (index != null) node.cache.voltScale = lookup[index];
                    break;
                case "readRegister":
                    switch (payload.value.registerAddress) {
                        case "InverterAmpsScaleFactor":
                            node.cache.amps = 10 ** payload.value.value;
                            break;
                        case "InverterPhaseVoltageScaleFactor":
                            node.cache.phaseVoltage = 10 ** payload.value.value;
                            break;
                        case "InverterWattScaleFactor":
                            node.cache.watt = 10 ** payload.value.value;
                            break;
                        case "InverterHertzScaleFactor":
                            node.cache.hertz = 10 ** payload.value.value;
                            break;
                        case "InverterPowerFactorScaleFactor":
                            node.cache.powerFactor = 10 ** payload.value.value;
                            break;
                        case "InverterWattHoursScaleFactor":
                            node.cache.wattHours = 10 ** payload.value.value;
                            break;
                        case "InverterDcVoltageScaleFactor":
                            node.cache.dcVoltage = 10 ** payload.value.value;
                            break;
                        case "InverterTemperatureScaleFactor":
                            node.cache.temperature = 10 ** payload.value.value;
                            break;
                    }
                    break;
            }


        };

        this.preRequest = function(msg) {
            switch (msg.payload.type) {
                case "readOperatingData33":
                    return this.cache.voltScale != null ? null : {
                        "type": "readOperatingData3e",
                        "value": null
                    };
                case "readRegister":
                    switch (msg.payload.value.registerAddress) {
                        case "InverterAmps":
                        case "InverterAmpsPhaseA":
                        case "InverterAmpsPhaseB":
                        case "InverterAmpsPhaseC":
                            return this.cache.amps != null ? null : {
                                "type": "readRegister",
                                "value": {
                                    "registerAddress": "InverterAmpsScaleFactor"
                                }
                            };
                        case "InverterPhaseVoltageA":
                        case "InverterPhaseVoltageB":
                        case "InverterPhaseVoltageC":
                            return this.cache.phaseVoltage != null ? null : {
                                "type": "readRegister",
                                "value": {
                                    "registerAddress": "InverterPhaseVoltageScaleFactor"
                                }
                            };
                        case "InverterWatt":
                            return this.cache.watt != null ? null : {
                                "type": "readRegister",
                                "value": {
                                    "registerAddress": "InverterWattScaleFactor"
                                }
                            };
                        case "InverterHertz":
                            return this.cache.hertz != null ? null : {
                                "type": "readRegister",
                                "value": {
                                    "registerAddress": "InverterHertzScaleFactor"
                                }
                            };
                        case "InverterPowerFactor":
                            return this.cache.powerFactor != null ? null : {
                                "type": "readRegister",
                                "value": {
                                    "registerAddress": "InverterPowerFactorScaleFactor"
                                }
                            };
                        case "InverterWattHours":
                            return this.cache.wattHours != null ? null : {
                                "type": "readRegister",
                                "value": {
                                    "registerAddress": "InverterWattHoursScaleFactor"
                                }
                            };
                        case "InverterDcVoltage":
                            return this.cache.dcVoltage != null ? null : {
                                "type": "readRegister",
                                "value": {
                                    "registerAddress": "InverterDcVoltageScaleFactor"
                                }
                            };
                        case "InverterTemperature":
                            return this.cache.temperature != null ? null : {
                                "type": "readRegister",
                                "value": {
                                    "registerAddress": "InverterTemperatureScaleFactor"
                                }
                            };
                    }
            }
            return null;
        }


        this.wait = function(ms) {
            return new Promise((_, reject) => {
                setTimeout(() => reject('Timeout'), ms);
            });
        }

        this.uartCall = function(request, send) {
            return new Promise(function(resolve, reject) {

                var parser = new Parser(node.modbusid, request);
                var serial = new SerialPort(node.config, function(err, results) {
                    if (err) {
                        reject(err);
                    }
                });
                node.serial = serial;
                serial.on('error', function(err) {
                    reject(err);
                });
                serial.on('close', function() {});
                serial.on('open', function() {
                    serial.write(send);
                });
                serial.on('data', function(d) {
                    var result = null;
                    try {
                        for (var i = 0; i < d.length; i++) {
                            result = parser.read(d[i]);
                        }
                        if (result != null) {
                            serial.close();
                            resolve(result);
                        }
                    } catch (err) {
                        reject(err);
                    }
                });
            });
        };

        this.on("input",
            function(msg, nodeSend, nodeDone) {



                function mainCall(msg, nodeSend, nodeDone) {
                    const send = node.convertRequestToModbus(msg.payload);
                    Promise.race([node.wait(node.timer), node.uartCall(msg.payload, send)]).then(function(value) {
                        node.updateCache(value);
                        msg.payload = value;
                        nodeSend([msg]);
                        nodeDone();
                    }, function(error) {
                        msg.payload = {
                            "type": "error",
                            "value": error.toString()
                        };
                        if (node.serial != null && node.serial.isOpen) node.serial.close(); //Does not unlock correct
                        nodeSend([msg]);
                        nodeDone();
                    });
                };

                function handlePreCall(msg, nodeSend, nodeDone) {
                    const preRequest = node.preRequest(msg);
                    if (preRequest == null) mainCall(msg, nodeSend, nodeDone);
                    else {
                        const send = node.convertRequestToModbus(preRequest);
                        Promise.race([node.wait(node.timer), node.uartCall(preRequest, send)]).then(function(value) {
                            node.updateCache(value);
                            mainCall(msg, nodeSend, nodeDone);
                        }, function(error) {
                            msg.payload = {
                                "type": "error",
                                "value": error.toString()
                            };
                            if (node.serial != null && node.serial.isOpen) node.serial.close(); //Does not unlock correct
                            nodeSend([msg]);
                            nodeDone();
                        });
                    }
                };
                handlePreCall(msg, nodeSend, nodeDone);

            });

        this.on('close',
            function() {
                node.activeProcesses = {};
                node.status({});
            });
    }
    RED.nodes.registerType("batteryinvert", BatteryInvertNode);
}