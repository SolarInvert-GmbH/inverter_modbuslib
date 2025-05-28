module.exports = function(RED) {
    "use strict";
    const {
        SerialPort
    } = require('serialport')

    function BatteryInvertNode(n) {
        RED.nodes.createNode(this, n);
        var node = this;
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
        this.convertRequestToModbus = function(request) {

            function build(array) {
                var buffer = new Uint8Array(array.length + 2);
                var crc = 0xffff;
                for (var i = 0; i < array.length; i++) {
                    buffer[i] = array[i];
                    crc = node.computeCrc(crc, array[i]);
                }
                buffer[array.length + 0] = (crc >> 0) & 0xff;
                buffer[array.length + 1] = (crc >> 8) & 0xff;
                return buffer;
            };
            switch (request.type) {
                case "factoryValues":
                    return build([node.modbusid, 0x31, 0x01, 0x01]);
                default:
                    return null;
            }
        }
        class Parser {

            constructor(id) {
                this.state = 0;
                this.id = id;
                this.crc = 0xffff;
            }
            read(byte) {
                this.blub = byte;
                const STATE_ID = 0;
                const STATE_FUNCTION = STATE_ID + 1;
                const STATE_FACTORY_VALUES = STATE_FUNCTION + 1;
                const STATE_DONE = STATE_FACTORY_VALUES + 15;

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
                            case 0x31:
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
                    default:
                        throw new Error("Unexpected state");
                }
            }
        }
        this.getScaleFactor = function(nodeValue) {
            if (nodeValue.value !== parseInt(nodeValue.value, 10)) return null;
            var value = nodeValue.value > 32767 ? nodeValue.value - 65536 : nodeValue.value;
            if (value < -10 || value > 10) return null;
            nodeValue.value = value;
            return 10 ** value;
        };

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
        this.handleResponse = function(msg) {
            switch (msg.payload.type) {
                case "readOperatingData33":
                    msg.payload.value.dcVoltage = this.cache.voltScale === null ? null : {
                        "quantety": msg.payload.value.dcVoltage * this.cache.voltScale,
                        "unit": "V"
                    };
                    msg.payload.value.acVoltage = {
                        "quantety": msg.payload.value.acVoltage + 50,
                        "unit": "V"
                    };
                    msg.payload.value.gridFrequency = {
                        "quantety": msg.payload.value.gridFrequency / 100,
                        "unit": "Hz"
                    };
                    msg.payload.value.acPower = {
                        "quantety": msg.payload.value.acPower / 10,
                        "unit": "W"
                    };
                    break;
                case "readOperatingData3e":
                    msg.payload.value.cosphi = 1.0 + (100 - msg.payload.value.cosphi) / 200;
                    msg.payload.value.nominalPower = {
                        "quantety": msg.payload.value.nominalPower * 100,
                        "unit": "W"
                    };
                    msg.payload.value.gridSupplyDailySum = {
                        "quantety": msg.payload.value.gridSupplyDailySum / 36000,
                        "unit": "Wh"
                    };
                    msg.payload.value.powerLimitation = {
                        "quantety": msg.payload.value.powerLimitation / 10,
                        "unit": "W"
                    };
                    msg.payload.value.operatingHours = {
                        "quantety": msg.payload.value.operatingHours / 36000,
                        "unit": "h"
                    };
                    this.setVolt(msg.payload.value);
                    break;
                case "readRegister":
                    switch (msg.payload.value.registerAddress) {
                        case "InverterAmps":
                        case "InverterAmpsPhaseA":
                        case "InverterAmpsPhaseB":
                        case "InverterAmpsPhaseC":
                            msg.payload.value.value = this.cache.amps === null ? null : {
                                "quantety": msg.payload.value.value * this.cache.amps,
                                "unit": "A"
                            };
                            break;
                        case "InverterPhaseVoltageA":
                        case "InverterPhaseVoltageB":
                        case "InverterPhaseVoltageC":
                            msg.payload.value.value = this.cache.phaseVoltage === null ? null : {
                                "quantety": msg.payload.value.value * this.cache.phaseVoltage,
                                "unit": "V"
                            };
                            break;
                        case "InverterWatt":
                            msg.payload.value.value = this.cache.watt === null ? null : {
                                "quantety": msg.payload.value.value * this.cache.watt,
                                "unit": "W"
                            };
                            break;
                        case "InverterHertz":
                            msg.payload.value.value = this.cache.hertz === null ? null : {
                                "quantety": msg.payload.value.value * this.cache.hertz,
                                "unit": "Hz"
                            };
                            break;
                        case "InverterPowerFactor":
                            msg.payload.value.value = this.cache.powerFactor === null ? null : {
                                "quantety": msg.payload.value.value * this.cache.powerFactor,
                                "unit": "%"
                            };
                            break;
                        case "InverterWattHours":
                            msg.payload.value.value = this.cache.wattHours === null ? null : {
                                "quantety": msg.payload.value.value * this.cache.wattHours,
                                "unit": "Wh"
                            };
                            break;
                        case "InverterDcVoltage":
                            msg.payload.value.value = this.cache.dcVoltage === null ? null : {
                                "quantety": msg.payload.value.value * this.cache.dcVoltage,
                                "unit": "V"
                            };
                            break;
                        case "InverterTemperature":
                            msg.payload.value.value = this.cache.temperature === null ? null : {
                                "quantety": msg.payload.value.value * this.cache.temperature,
                                "unit": "°C"
                            };
                            break;
                        case "InverterAmpsScaleFactor":
                            this.cache.amps = this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterPhaseVoltageScaleFactor":
                            this.cache.phaseVoltage = this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterWattScaleFactor":
                            this.cache.watt = this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterHertzScaleFactor":
                            this.cache.hertz = this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterPowerFactorScaleFactor":
                            this.cache.powerFactor = this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterWattHoursScaleFactor":
                            this.cache.wattHours = this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterDcVoltageScaleFactor":
                            this.cache.dcVoltage = this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterTemperatureScaleFactor":
                            this.cache.temperature = this.getScaleFactor(msg.payload.value);
                            break;
                        case "ExtendedMesurementsAcWattHours":
                            msg.payload.value.value = {
                                "quantety": msg.payload.value.value,
                                "unit": "Wh"
                            };
                            break;
                    }
                    break;
            }
        };
        this.handleRequest = function(msg) {
            var checkPhsicalValue = function(value, unit, name, minValue, maxValue) {
                if (Object.keys(value).length !== 2 || value.unit !== unit || typeof value.quantety !== "number")
                    throw new Error(name + " is wrong");
                if (value.quantety < minValue || value.quantety > maxValue)
                    throw new Error(name + ".quantety has to be in " + minValue + " … " + maxValue);
            };
            switch (msg.payload.type) {
                case "startConstantVoltage":
                    checkPhsicalValue(msg.payload.value.uSet, "V", "value.uSet", 0.0, 6553.5);
                    msg.payload.value.uSet = (msg.payload.value.uSet.quantety * 10) | 0;
                    break;
                case "setPowerFactor":
                    if (typeof msg.payload.value.cosPhi !== "number")
                        throw new Error("value.cosPhi is wrong");
                    if (msg.payload.value.cosPhi < 0.5 || msg.payload.value.cosPhi > 1.5)
                        throw new Error("value.cosPhi has to be in 0.5 … 1.5");
                    msg.payload.value.cosPhi = (100 - (msg.payload.value.cosPhi - 1) * 200) | 0;
                    break;
                case "controlBatteryInvert":
                    checkPhsicalValue(msg.payload.value.pMax.Power, "W", "value.pMax.Power", 0, 3200);
                    msg.payload.value.pMax.Power = msg.payload.value.pMax.Power.quantety | 0;
                    checkPhsicalValue(msg.payload.value.uMin, "V", "value.uMin", 0.0, 6553.5);
                    msg.payload.value.uMin = (msg.payload.value.uMin.quantety * 10) | 0;
                    checkPhsicalValue(msg.payload.value.uMax, "V", "value.uMax", 0.0, 6553.5);
                    msg.payload.value.uMax = (msg.payload.value.uMax.quantety * 10) | 0;
                    checkPhsicalValue(msg.payload.value.timeout, "s", "value.timeout", 15.0, 12000.0);
                    msg.payload.value.timeout = (msg.payload.value.timeout.quantety * 5) | 0;
                    break;
                case "limitBatteryInvert":
                    checkPhsicalValue(msg.payload.value.pMaxfeed, "%", "value.pMaxfeed", 0, 100);
                    msg.payload.value.pMaxfeed = msg.payload.value.pMaxfeed.quantety | 0;
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

        // TODO timeout
        this.uartCall = function(send) {
            return new Promise(function(resolve, reject) {

                var parser = new Parser(node.modbusid);
                var serial = new SerialPort(node.config, function(err, results) {
                    if (err) {
                        reject(err);
                    }
                });
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
                            resolve(result);
                            serial.close();
                        }
                    } catch (err) {
                        reject(err);
                    }
                });
            });
        };

        this.on("input",
            function(msg, nodeSend, nodeDone) {
                const send = node.convertRequestToModbus(msg.payload);
                node.uartCall(send).then(function(value) {
                    msg.payload = value;
                    nodeSend([msg]);
                    nodeDone();
                }, function(error) {
                    msg.payload = error;
                    nodeSend([msg]);
                    nodeDone();
                });
            });

        this.on('close',
            function() {
                node.activeProcesses = {};
                node.status({});
            });
    }
    RED.nodes.registerType("batteryinvert", BatteryInvertNode);
}
