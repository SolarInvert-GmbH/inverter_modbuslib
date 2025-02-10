#!/bin/bash

MODBUS_LIB_VERSION="v0.0.1-15-g054ddfc"

sudo apt update
sudo apt install -y git build-essential cmake wget
wget -O "ModbusLib-master-${MODBUS_LIB_VERSION}.zip"  "https://cloud.cattatech.de/index.php/s/qPpdrr7A8Ak3G4i/download?path=/&files=ModbusLib-master-${MODBUS_LIB_VERSION}.zip"
unzip ModbusLib-master-${MODBUS_LIB_VERSION}.zip
cd ~/Downloads/ModbusLib-master
./build.sh --guionly --requestonly
