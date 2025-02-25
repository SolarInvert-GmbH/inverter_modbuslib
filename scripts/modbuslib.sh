#!/bin/bash

SOURCE="$(readlink -f ${BASH_SOURCE[0]})"
ROOT="${SOURCE%/*/*}"
unset SOURCE

sudo apt update
sudo apt install -y git build-essential cmake wget

cd "${HOME}"
mkdir -p "SI_COMM"
cd "SI_COMM"

cp -r ${ROOT} .
echo $(pwd)
cd ModbusLib-master

./build.sh --guionly --requestonly
sudo ./build.sh --guionly --requestonly --install
