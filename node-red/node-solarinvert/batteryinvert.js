/**
 * TODO LICENSE
 **/

module.exports = function(RED) {
    "use strict";
    var exec = require('child_process').exec;
    var fs = require('fs');
    const isWindows = process.platform === 'win32'

    function BatteryInvertNode(n) {
        RED.nodes.createNode(this, n);
        this.cache = {
            "voltScale" : null,
            "amps" : null,
            "phaseVoltage":null,
            "watt" : null,
            "hertz" : null,
            "powerFactor" : null,
            "wattHours" : null,
            "dcVoltage" : null,
            "temperature" : null
        };
        this.cmd = (n.command || "").trim();
        this.port = (n.serialport || "").trim();
        this.modbusid = (n.modbusid || "00").trim();
        this.timer = Number(n.timer || 0) * 1000;
        this.activeProcesses = {};
        this.execOpt = {
            encoding: 'binary',
            maxBuffer: RED.settings.execMaxBufferSize || 10000000,
            windowsHide: (n.winHide === true)
        };
        this.getScaleFactor = function(nodeValue)
        {
            if (nodeValue.value !== parseInt(nodeValue.value, 10)) return null;
            var value = nodeValue.value > 32767 ? nodeValue.value - 65536 : nodeValue.value;
            if (value<-10 || value>10) return null;
            nodeValue.value = value;
            return 10**value;
        };
        this.setVolt = function(nodeValue)
        {
            switch(nodeValue.type)
            {
                case "solar":
                    switch(nodeValue.voltageType)
                    {
                        case  1: nodeValue.voltageType={"quantety": 12,"unit":"V"}; this.cache.voltScale=0.028; break;
                        case  2: nodeValue.voltageType={"quantety": 17,"unit":"V"}; this.cache.voltScale=0.054; break;
                        case  3: nodeValue.voltageType={"quantety": 35,"unit":"V"}; this.cache.voltScale=0.054; break;
                        case  4: nodeValue.voltageType={"quantety": 50,"unit":"V"}; this.cache.voltScale=0.079; break;
                        case  5: nodeValue.voltageType={"quantety": 70,"unit":"V"}; this.cache.voltScale=0.108; break;
                        case  6: nodeValue.voltageType={"quantety": 90,"unit":"V"}; this.cache.voltScale=0.142; break;
                        case  7: nodeValue.voltageType={"quantety":120,"unit":"V"}; this.cache.voltScale=0.186; break;
                        case  8: nodeValue.voltageType={"quantety":160,"unit":"V"}; this.cache.voltScale=0.244; break;
                        case  9: nodeValue.voltageType={"quantety":240,"unit":"V"}; this.cache.voltScale=0.357; break;
                        case 10: nodeValue.voltageType={"quantety":320,"unit":"V"}; this.cache.voltScale=0.479; break;
                        default: nodeValue.voltageType=null; break;
                    }
                    break;
                case "wind":
                    switch(nodeValue.voltageType)
                    {
                        case  1: nodeValue.voltageType={"quantety": 12,"unit":"V"}; this.cache.voltScale=0.028; break;
                        case  2: nodeValue.voltageType={"quantety": 18,"unit":"V"}; this.cache.voltScale=0.054; break;
                        case  3: nodeValue.voltageType={"quantety": 24,"unit":"V"}; this.cache.voltScale=0.054; break;
                        case  4: nodeValue.voltageType={"quantety": 36,"unit":"V"}; this.cache.voltScale=0.079; break;
                        case  5: nodeValue.voltageType={"quantety": 48,"unit":"V"}; this.cache.voltScale=0.108; break;
                        case  6: nodeValue.voltageType={"quantety": 72,"unit":"V"}; this.cache.voltScale=0.142; break;
                        case  7: nodeValue.voltageType={"quantety": 96,"unit":"V"}; this.cache.voltScale=0.186; break;
                        case  8: nodeValue.voltageType={"quantety":120,"unit":"V"}; this.cache.voltScale=0.244; break;
                        case  9: nodeValue.voltageType={"quantety":160,"unit":"V"}; this.cache.voltScale=0.357; break;
                        case 10: nodeValue.voltageType={"quantety":240,"unit":"V"}; this.cache.voltScale=0.479; break;
                        default: nodeValue.voltageType=null; break;
                    }
                    break;
                case "battery":
                    switch(nodeValue.voltageType)
                    {
                        case  1: nodeValue.voltageType={"quantety":  8,"unit":"V"}; this.cache.voltScale=0.028; break;
                        case  2: nodeValue.voltageType={"quantety": 12,"unit":"V"}; this.cache.voltScale=0.054; break;
                        case  3: nodeValue.voltageType={"quantety": 24,"unit":"V"}; this.cache.voltScale=0.054; break;
                        case  4: nodeValue.voltageType={"quantety": 30,"unit":"V"}; this.cache.voltScale=0.079; break;
                        case  5: nodeValue.voltageType={"quantety": 36,"unit":"V"}; this.cache.voltScale=0.108; break;
                        case  6: nodeValue.voltageType={"quantety": 48,"unit":"V"}; this.cache.voltScale=0.142; break;
                        case  7: nodeValue.voltageType={"quantety": 96,"unit":"V"}; this.cache.voltScale=0.186; break;
                        case  8: nodeValue.voltageType={"quantety":120,"unit":"V"}; this.cache.voltScale=0.244; break;
                        case  9: nodeValue.voltageType={"quantety":160,"unit":"V"}; this.cache.voltScale=0.357; break;
                        case 10: nodeValue.voltageType={"quantety":240,"unit":"V"}; this.cache.voltScale=0.479; break;
                        default: nodeValue.voltageType=null; break;
                    }
                    break;
                default: nodeValue.voltageType=null; break;
            }
        };
        this.handleResponse = function(msg)
        {
            switch (msg.payload.type)
            {
                case "readOperatingData33":
                    msg.payload.value.dcVoltage = this.cache.voltScale === null ? null : {"quantety" : msg.payload.value.dcVoltage*this.cache.voltScale, "unit":"V"};
                    msg.payload.value.acVoltage = {"quantety" : msg.payload.value.acVoltage+50, "unit":"V"};
                    msg.payload.value.gridFrequency = {"quantety" : msg.payload.value.gridFrequency/100, "unit":"Hz"};
                    msg.payload.value.acPower = {"quantety" : msg.payload.value.acPower/10, "unit":"W"};
                    break;
                case "readOperatingData3e":
                    msg.payload.value.cosphi = 1.0 + (100-msg.payload.value.cosphi)/200;
                    msg.payload.value.nominalPower = {"quantety" : msg.payload.value.nominalPower*100 , "unit":"W"};
                    msg.payload.value.gridSupplyDailySum = {"quantety" : msg.payload.value.gridSupplyDailySum/36000 , "unit":"Wh"};
                    msg.payload.value.powerLimitation = {"quantety" : msg.payload.value.powerLimitation/10 , "unit":"W"};
                    msg.payload.value.operatingHours = {"quantety" : msg.payload.value.operatingHours/36000 , "unit":"h"};
                    this.setVolt(msg.payload.value);
                    break;
                case "readRegister":
                    switch (msg.payload.value.registerAddress)
                    {
                        case "InverterAmps":
                        case "InverterAmpsPhaseA":
                        case "InverterAmpsPhaseB":
                        case "InverterAmpsPhaseC":
                            msg.payload.value.value = this.cache.amps === null ? null : {"quantety" : msg.payload.value.value*this.cache.amps, "unit":"A"};
                            break;
                        case "InverterPhaseVoltageA":
                        case "InverterPhaseVoltageB":
                        case "InverterPhaseVoltageC":
                            msg.payload.value.value = this.cache.phaseVoltage === null ? null : {"quantety" : msg.payload.value.value*this.cache.phaseVoltage, "unit":"V"};
                            break;
                        case "InverterWatt":
                            msg.payload.value.value = this.cache.watt === null ? null : {"quantety" : msg.payload.value.value*this.cache.watt, "unit":"W"};
                            break;
                        case "InverterHertz":
                            msg.payload.value.value = this.cache.hertz === null ? null : {"quantety" : msg.payload.value.value*this.cache.hertz, "unit":"Hz"};
                            break;
                        case "InverterPowerFactor":
                            msg.payload.value.value = this.cache.powerFactor === null ? null : {"quantety" : msg.payload.value.value*this.cache.powerFactor, "unit":"%"};
                            break;
                        case "InverterWattHours":
                            msg.payload.value.value = this.cache.wattHours === null ? null : {"quantety" : msg.payload.value.value*this.cache.wattHours, "unit":"Wh"};
                            break;
                        case " InverterDcVoltage":
                            msg.payload.value.value = this.cache.dcVoltage === null ? null : {"quantety" : msg.payload.value.value*this.cache.dcVoltage, "unit":"V"};
                            break;
                        case "InverterTemperature":
                            msg.payload.value.value = this.cache.temperature === null ? null : {"quantety" : msg.payload.value.value*this.cache.temperature, "unit":"°C"};
                            break;
                        case "InverterAmpsScaleFactor":
                            this.cache.amps=this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterPhaseVoltageScaleFactor":
                            this.cache.phaseVoltage=this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterWattScaleFactor":
                            this.cache.watt=this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterHertzScaleFactor":
                            this.cache.hertz=this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterPowerFactorScaleFactor":
                            this.cache.powerFactor=this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterWattHoursScaleFactor":
                            this.cache.wattHours=this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterDcVoltageScaleFactor":
                            this.cache.dcVoltage=this.getScaleFactor(msg.payload.value);
                            break;
                        case "InverterTemperatureScaleFactor":
                            this.cache.temperature=this.getScaleFactor(msg.payload.value);
                            break;
                        case "ExtendedMesurementsAcWattHours":
                            msg.payload.value.value = {"quantety" : msg.payload.value.value, "unit":"Wh"};
                            break;
                    }
                break;
            }
        };
        this.handleRequest = function(msg)
        {
            var checkPhsicalValue = function(value,unit,name,minValue,maxValue)
            {
                if (Object.keys(value).length!==2 || value.unit!==unit || typeof value.quantety !== "number")
                    throw new Error(name+" is wrong");
                if (value.quantety<minValue || value.quantety>maxValue)
                    throw new Error(name+".quantety has to be in "+minValue+" … "+maxValue);
            };
            switch(msg.payload.type)
            {
                case "startConstantVoltage":
                    checkPhsicalValue(msg.payload.value.uSet,"V","value.uSet",0.0,6553.5);
                    msg.payload.value.uSet=(msg.payload.value.uSet.quantety*10) | 0;
                    break;
                case "setPowerFactor":
                    if (typeof msg.payload.value.cosPhi !== "number")
                        throw new Error("value.cosPhi is wrong");
                    if (msg.payload.value.cosPhi<0.5 || msg.payload.value.cosPhi>1.5)
                        throw new Error("value.cosPhi has to be in 0.5 … 1.5");
                    msg.payload.value.cosPhi=(100-(msg.payload.value.cosPhi-1)*200) | 0;
                    break;
                case "controlBatteryInvert":
                    checkPhsicalValue(msg.payload.value.pMax.Power,"W","value.pMax.Power",0,3200);
                    msg.payload.value.pMax.Power=msg.payload.value.pMax.Power.quantety | 0;
                    checkPhsicalValue(msg.payload.value.uMin,"V","value.uMin",0.0,6553.5);
                    msg.payload.value.uMin=(msg.payload.value.uMin.quantety*10) | 0;
                    checkPhsicalValue(msg.payload.value.uMax,"V","value.uMax",0.0,6553.5);
                    msg.payload.value.uMax=(msg.payload.value.uMax.quantety*10) | 0;
                    checkPhsicalValue(msg.payload.value.timeout,"s","value.timeout",15.0,12000.0);
                    msg.payload.value.timeout=(msg.payload.value.timeout.quantety*5) | 0;
                    break;
                case "limitBatteryInvert":
                     checkPhsicalValue(msg.payload.value.pMaxfeed,"%","value.pMaxfeed",0,100);
                    msg.payload.value.pMaxfeed=msg.payload.value.pMaxfeed.quantety | 0;
                    break;
            }
        };
        var node = this;

        if (process.platform === 'linux' && fs.existsSync('/bin/bash')) {
            node.execOpt.shell = '/bin/bash';
        }

        var cleanup = function(p) {
            node.activeProcesses[p].kill();
        }

        this.on("input",
        function(msg, nodeSend, nodeDone) {
            if (msg.hasOwnProperty("kill")) {
                if (typeof msg.kill !== "string" || msg.kill.length === 0 || !msg.kill.toUpperCase().startsWith("SIG")) {
                    msg.kill = "SIGTERM";
                }
                if (msg.hasOwnProperty("pid")) {
                    if (node.activeProcesses.hasOwnProperty(msg.pid)) {
                        node.activeProcesses[msg.pid].kill(msg.kill.toUpperCase());
                        node.status({
                            fill: "red",
                            shape: "dot",
                            text: "killed"
                        });
                    }
                } else {
                    if (Object.keys(node.activeProcesses).length === 1) {
                        node.activeProcesses[Object.keys(node.activeProcesses)[0]].kill(msg.kill.toUpperCase());
                        node.status({
                            fill: "red",
                            shape: "dot",
                            text: "killed"
                        });
                    }
                }
                nodeDone();
            } else {
                try {
                    node.handleRequest(msg);
                }
                catch(e) {
                    msg.payload={"type":"error","value":e.message};
                    nodeDone();
                }

                var child;
                const quote = isWindows ? "": "'";
                var arg = node.cmd + " --uart " + node.port + " --modbusid " + node.modbusid + " --request " + quote + JSON.stringify(msg.payload) + quote;
                if (node.timer !== 0) {
                    arg += " --timeout " + node.timer;
                }
                child = exec(arg, node.execOpt,
                function(error, stdout, stderr) {
                    delete msg.payload;
                    if (error) {
                        node.debug('[exec] stderr: ' + stderr);
                        msg.payload={"type":"error","value":stderr};
                        nodeDone();
                    }
                    try {
                        var result = Buffer.from(stdout, "binary");
                        node.status({
                            fill: "red",
                            shape: "dot",
                            text: result
                        });
                        result = result.toString();
                        try {
                            msg.payload = JSON.parse(result);
                        }
                        catch(e) {
                            msg.payload={"type":"error","value":result};
                            nodeDone();
                        }
                        node.handleResponse(msg);
                    } catch(e) {
                        msg.payload={"type":"error","value":e.message};
                        nodeDone();
                    }
                    node.status({});
                    if (error !== null) {
                        node.debug('[exec] error: ' + error);
                    }
                    nodeSend([msg]);
                    if (child.tout) {
                        clearTimeout(child.tout);
                    }
                    delete node.activeProcesses[child.pid];
                    nodeDone();
                });
                node.status({
                    fill: "blue",
                    shape: "dot",
                    text: "pid:" + child.pid
                });
                child.on('error',
                function() {});
                if (node.timer !== 0) {
                    child.tout = setTimeout(function() {
                        cleanup(child.pid);
                    },
                    node.timer + 1000);
                }
                node.activeProcesses[child.pid] = child;
            }
        });

        this.on('close',
        function() {
            for (var pid in node.activeProcesses) {
                if (node.activeProcesses.hasOwnProperty(pid)) {
                    if (node.activeProcesses[pid].tout) {
                        clearTimeout(node.activeProcesses[pid].tout);
                    }
                    var process = node.activeProcesses[pid];
                    node.activeProcesses[pid] = null;
                    process.kill();
                }
            }
            node.activeProcesses = {};
            node.status({});
        });
    }
    RED.nodes.registerType("batteryinvert", BatteryInvertNode);
}
