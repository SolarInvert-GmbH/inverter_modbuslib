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
                var child;
                const quote = isWindows ? "": "'";
                var arg = node.cmd + " --uart " + node.port + " --modbusid " + node.modbusid + " --request " + quote + JSON.stringify(msg.payload) + quote;
                if (node.timer !== 0) {
                    arg += " --timeout " + node.timer;
                }
                node.debug(arg);
                child = exec(arg, node.execOpt,
                function(error, stdout, stderr) {
                    delete msg.payload;
                    if (error) {
                        node.debug('[exec] stderr: ' + stderr);
                    }
                    try {
                        var result = Buffer.from(stdout, "binary");
                        node.status({
                            fill: "red",
                            shape: "dot",
                            text: result
                        });
                        result = result.toString();
                        msg.payload = JSON.parse(result);
                    } catch(e) {
                        nodeDone(e.message);
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
