#!/bin/bash

SOURCE="$(readlink -f ${BASH_SOURCE[0]})"
ROOT="${SOURCE%/*/*}"
unset SOURCE

if [ ! -d "${HOME}/.node-red" ]; then
    echo "node-red is not installed!"
else
    cd ${HOME}/.node-red
    npm install "${ROOT}/node-red/node-solarinvert/"
fi
