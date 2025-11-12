#!/bin/bash

HEAD=""
BUCKET=""

status()
{
    echo "${HEAD}STATUS: ${1}"
}

status_multy()
{
    while IFS= read -r LINE; do
        echo "${HEAD}STATUS: ${LINE}"
    done <<< "${1}"
}

print_help()
{
    echo "${0}"
    exit ${1}
}

check_for_help()
{
    if [[ $# -gt 0 && ( "${1}" == "h" || "${1}" == "-h" || "${1}" == "--h" || "${1}" == "help" || "${1}" == "-help" || "${1}" == "--help" ) ]]; then
        echo "ussage:"
        print_help 0
    fi
}

check_arg()
{
    BUCKET="${1}"
    if [[ $# -ge 1 ]]; then
        HEAD="${1}"
    fi
}

list()
{
    status "InfluxDB task list"
    LINES="$(influx task list)"

    status_multy "${LINES}"
}


check_for_help "${@}"
check_arg "${@}"
list
