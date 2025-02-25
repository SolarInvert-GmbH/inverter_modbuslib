#!/bin/bash

SOURCE="$(readlink -f ${BASH_SOURCE[0]})"
ROOT="${SOURCE%/*}"
unset SOURCE

"${ROOT}/fltk.sh"
"${ROOT}/modbuslib.sh"
"${ROOT}/node-red.sh"
