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
                case "readOperatingData33":
                    return build([node.modbusid, 0x33, 0x01, 0x01]);
                case "readOperatingData3e":
                    return build([node.modbusid, 0x3e, 0x01, 0x01]);
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
                const STATE_OPERATING_DATA_33 = STATE_FACTORY_VALUES + 15;
                const STATE_OPERATING_DATA_3E = STATE_OPERATING_DATA_33 + 24;
                const STATE_READ_REGISTER = STATE_OPERATING_DATA_3E + 22;
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
                            case 0x33:
                                if (this.request.type != "readOperatingData33") throw Error("Expected '0x33' as modbus function code for 'readOperatingData33' request, but got " + byte.toString(16).padStart(2, '0'));
                                return crcAndJump(STATE_OPERATING_DATA_33 + 0, byte, this);
                            case 0x3e:
                                if (this.request.type != "readOperatingData3e") throw Error("Expected '0x3e' as modbus function code for 'readOperatingData3e' request, but got " + byte.toString(16).padStart(2, '0'));
                                return crcAndJump(STATE_OPERATING_DATA_3E + 0, byte, this);

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
                    case STATE_OPERATING_DATA_33 + 0:
                        if (byte != 0x15) throw new Error("Expected 0x15 as length for operating data 3e response, but got 0x" + byte.toString(16).padStart(2, '0'));
                        return crcAndJump(STATE_OPERATING_DATA_33 + 1, byte, this);
                    case STATE_OPERATING_DATA_33 + 1:
                        this.dcVoltage |= byte << 8;
                        return crcAndJump(STATE_OPERATING_DATA_33 + 2, byte, this);
                    case STATE_OPERATING_DATA_33 + 2:
                        this.dcVoltage |= byte << 0;
                        this.dcVoltage = {
                            "quantety": node.cache.voltScale * this.dcVoltage,
                            "unit": "V"
                        };
                        return crcAndJump(STATE_OPERATING_DATA_33 + 3, byte, this);
                    case STATE_OPERATING_DATA_33 + 3:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 4, byte, this);
                    case STATE_OPERATING_DATA_33 + 4:
                        this.acVoltage = {
                            "quantety": byte + 50,
                            "unit": "V"
                        };
                        return crcAndJump(STATE_OPERATING_DATA_33 + 5, byte, this);
                    case STATE_OPERATING_DATA_33 + 5:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 6, byte, this);
                    case STATE_OPERATING_DATA_33 + 6:
                        this.gridFrequency = byte << 8;
                        return crcAndJump(STATE_OPERATING_DATA_33 + 7, byte, this);
                    case STATE_OPERATING_DATA_33 + 7:
                        this.gridFrequency |= byte << 0;
                        this.gridFrequency = {
                            "quantety": this.gridFrequency / 100,
                            "unit": "Hz"
                        };
                        return crcAndJump(STATE_OPERATING_DATA_33 + 8, byte, this);
                    case STATE_OPERATING_DATA_33 + 8:
                        this.acPower = byte << 8;
                        return crcAndJump(STATE_OPERATING_DATA_33 + 9, byte, this);
                    case STATE_OPERATING_DATA_33 + 9:
                        this.acPower |= byte << 0;
                        this.acPower = {
                            "quantety": this.acPower / 10,
                            "unit": "W"
                        };
                        return crcAndJump(STATE_OPERATING_DATA_33 + 10, byte, this);
                    case STATE_OPERATING_DATA_33 + 10:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 11, byte, this);
                    case STATE_OPERATING_DATA_33 + 11:
                        switch (byte) {
                            case 0x00:
                                this.statestring = "init level 1";
                                break;
                            case 0x01:
                                this.statestring = "init level 2";
                                break;
                            case 0x02:
                                this.statestring = "init level 3";
                                break;
                            case 0x03:
                                this.statestring = "mppt";
                                break;
                            case 0x04:
                                this.statestring = "reset";
                                break;
                            case 0x05:
                                this.statestring = "constant voltage";
                                break;
                            case 0x06:
                                this.statestring = "lower power mode";
                                break;
                            case 0x07:
                                this.statestring = "wind";
                                break;
                            case 0x08:
                                this.statestring = "factory mode";
                                break;
                            case 0x09:
                                this.statestring = "battery";
                                break;
                            case 0x0a:
                                this.statestring = "battery safety";
                                break;
                            default:
                                throw new Error("Expected 0x00…0x0a as state for operating data 33 response, but got 0x" + byte.toString(16).padStart(2, '0'));
                        }
                        return crcAndJump(STATE_OPERATING_DATA_33 + 12, byte, this);
                    case STATE_OPERATING_DATA_33 + 12:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 13, byte, this);
                    case STATE_OPERATING_DATA_33 + 13:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 14, byte, this);
                    case STATE_OPERATING_DATA_33 + 14:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 15, byte, this);
                    case STATE_OPERATING_DATA_33 + 15:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 16, byte, this);
                    case STATE_OPERATING_DATA_33 + 16:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 17, byte, this);
                    case STATE_OPERATING_DATA_33 + 17:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 18, byte, this);
                    case STATE_OPERATING_DATA_33 + 18:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 19, byte, this);
                    case STATE_OPERATING_DATA_33 + 19:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 20, byte, this);
                    case STATE_OPERATING_DATA_33 + 20:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 21, byte, this);
                    case STATE_OPERATING_DATA_33 + 21:
                        return crcAndJump(STATE_OPERATING_DATA_33 + 22, byte, this);
                    case STATE_OPERATING_DATA_33 + 22:
                        return checkCrcLowAndJump(STATE_OPERATING_DATA_33 + 23, this);
                    case STATE_OPERATING_DATA_33 + 23:
                        return checkCrcHighAndDone({
                            "type": "readOperatingData33",
                            "value": {
                                "dcVoltage": this.dcVoltage,
                                "acVoltage": this.acVoltage,
                                "gridFrequency": this.gridFrequency,
                                "acPower": this.acPower,
                                "state": this.statestring
                            }
                        }, this);
                    case STATE_OPERATING_DATA_3E + 0:
                        if (byte != 0x13) throw new Error("Expected 0x13 as length for operating data 3e response, but got 0x" + byte.toString(16).padStart(2, '0'));
                        return crcAndJump(STATE_OPERATING_DATA_3E + 1, byte, this);
                    case STATE_OPERATING_DATA_3E + 1:
                        this.serialnumber = byte << 8;
                        return crcAndJump(STATE_OPERATING_DATA_3E + 2, byte, this);
                    case STATE_OPERATING_DATA_3E + 2:
                        this.serialnumber |= byte;
                        return crcAndJump(STATE_OPERATING_DATA_3E + 3, byte, this);
                    case STATE_OPERATING_DATA_3E + 3:
                        switch (byte) {
                            case 0x01:
                                this.type = "solar";
                                break;
                            case 0x02:
                                this.type = "wind";
                                break;
                            case 0x03:
                                this.type = "battery";
                                break;
                            default:
                                throw new Error("Expected 0x01, 0x02 or 0x03 as type for operating data 3e response, but got 0x" + byte.toString(16).padStart(2, '0'));
                        }
                        return crcAndJump(STATE_OPERATING_DATA_3E + 4, byte, this);
                    case STATE_OPERATING_DATA_3E + 4:
                        if (byte < 0x01 || byte > 0x0a) throw new Error("Expected 0x01…0x0a as voltageType for operating data 3e response, but got 0x" + byte.toString(16).padStart(2, '0'));
                        var lookup = null;
                        switch (this.type) {
                            case "solar":
                                lookup = [12, 17, 35, 50, 70, 90, 120, 160, 240, 320];
                                break;
                            case "wind":
                                lookup = [12, 18, 24, 36, 48, 72, 96, 120, 160, 240];
                                break;
                            case "battery":
                                lookup = [8, 12, 24, 30, 36, 48, 96, 120, 160, 240];
                                break;
                        }
                        this.voltageType = {
                            "quantety": lookup[byte - 1],
                            "unit": "A"
                        };
                        return crcAndJump(STATE_OPERATING_DATA_3E + 5, byte, this);
                    case STATE_OPERATING_DATA_3E + 5:
                        if (byte < 0x01 || byte > 0x20) throw new Error("Expected 0x01…0x20 as nominalPower for operating data 3e response, but got 0x" + byte.toString(16).padStart(2, '0'));
                        this.nominalPower = {
                            "quantety": byte * 100,
                            "unit": "W"
                        };
                        return crcAndJump(STATE_OPERATING_DATA_3E + 6, byte, this);
                    case STATE_OPERATING_DATA_3E + 6:
                        this.cosphi = 1.0 + (100 - byte) / 200;
                        return crcAndJump(STATE_OPERATING_DATA_3E + 7, byte, this);
                    case STATE_OPERATING_DATA_3E + 7:
                        this.gridSupplyDailySum = byte << 24;
                        return crcAndJump(STATE_OPERATING_DATA_3E + 8, byte, this);
                    case STATE_OPERATING_DATA_3E + 8:
                        this.gridSupplyDailySum |= byte << 16;
                        return crcAndJump(STATE_OPERATING_DATA_3E + 9, byte, this);
                    case STATE_OPERATING_DATA_3E + 9:
                        this.gridSupplyDailySum |= byte << 8;
                        return crcAndJump(STATE_OPERATING_DATA_3E + 10, byte, this);
                    case STATE_OPERATING_DATA_3E + 10:
                        this.gridSupplyDailySum |= byte << 0;
                        this.gridSupplyDailySum = {
                            "quantety": this.gridSupplyDailySum / 36000,
                            "unit": "Wh"
                        };
                        return crcAndJump(STATE_OPERATING_DATA_3E + 11, byte, this);
                    case STATE_OPERATING_DATA_3E + 11:
                        this.powerLimitation = byte << 8;
                        return crcAndJump(STATE_OPERATING_DATA_3E + 12, byte, this);
                    case STATE_OPERATING_DATA_3E + 12:
                        this.powerLimitation |= byte << 0;
                        this.powerLimitation = {
                            "quantety": this.powerLimitation / 10,
                            "unit": "W"
                        };
                        return crcAndJump(STATE_OPERATING_DATA_3E + 13, byte, this);
                    case STATE_OPERATING_DATA_3E + 13:
                        this.operatingHours = byte << 24;
                        return crcAndJump(STATE_OPERATING_DATA_3E + 14, byte, this);
                    case STATE_OPERATING_DATA_3E + 14:
                        this.operatingHours |= byte << 16;
                        return crcAndJump(STATE_OPERATING_DATA_3E + 15, byte, this);
                    case STATE_OPERATING_DATA_3E + 15:
                        this.operatingHours |= byte << 8;
                        return crcAndJump(STATE_OPERATING_DATA_3E + 16, byte, this);
                    case STATE_OPERATING_DATA_3E + 16:
                        this.operatingHours |= byte << 0;
                        this.operatingHours = {
                            "quantety": this.operatingHours / 36000,
                            "unit": "h"
                        };
                        return crcAndJump(STATE_OPERATING_DATA_3E + 17, byte, this);
                    case STATE_OPERATING_DATA_3E + 17:
                        if (byte > 0x03) throw new Error("Expected 0x00…0x03 as phase for operating data 3e response, but got 0x" + byte.toString(16).padStart(2, '0'));
                        this.phase = byte;
                        return crcAndJump(STATE_OPERATING_DATA_3E + 18, byte, this);
                    case STATE_OPERATING_DATA_3E + 18:
                        if (byte > 0x0f) throw new Error("Expected 0x00…0x0f as modbusId for operating data 3e response, but got 0x" + byte.toString(16).padStart(2, '0'));
                        this.modbusId = byte;
                        return crcAndJump(STATE_OPERATING_DATA_3E + 19, byte, this);
                    case STATE_OPERATING_DATA_3E + 19:
                        return crcAndJump(STATE_OPERATING_DATA_3E + 20, byte, this);
                    case STATE_OPERATING_DATA_3E + 20:
                        return checkCrcLowAndJump(STATE_OPERATING_DATA_3E + 21, this);
                    case STATE_OPERATING_DATA_3E + 21:
                        return checkCrcHighAndDone({
                            "type": "readOperatingData3e",
                            "value": {
                                "serialNumber": this.serialnumber,
                                "type": this.type,
                                "voltageType": this.voltageType,
                                "nominalPower": this.nominalPower,
                                "cosphi": this.cosphi,
                                "gridSupplyDailySum": this.gridSupplyDailySum,
                                "powerLimitation": this.powerLimitation,
                                "operatingHours": this.operatingHours,
                                "phase": this.phase,
                                "modbusId": this.modbusId
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
                        throw new Error("Unexpected parsing state");
                }
            }
        }

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