#!/bin/bash

HEAD=""
DIRECTORY=""

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

status_multy()
{
    while IFS= read -r LINE; do
        echo "${HEAD}STATUS: ${LINE}"
    done <<< "${1}"
}

error_multy()
{
    while IFS= read -r LINE; do
        echo "${HEAD}ERROR: ${LINE}" >&2
    done <<< "${1}"
    exit ${2}
}

print_help()
{
    echo "${0} DIRECTORY"
    echo "   DIRECTORY -- The directory for the restore."
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
    if [[ $# -ge 1 ]]; then
        DIRECTORY="${1}"
        if [[ $# -ge 2 ]]; then
            HEAD="${2}"
        fi
        status "InfluxDB restore:"
        status "   directory: ${DIRECTORY}"
    else
        echo "Need one parameter:"
        print_help 1
    fi
}

restore()
{
    status "InfluxDB restore"
    LINES="$(influx restore "${DIRECTORY}" 2>&1)"
    CODE="${?}"

    if [[ "${CODE}" -eq 0 ]]; then
        status_multy "${LINES}"
    else
        error_multy "${LINES}" 2
    fi
}


check_for_help "${@}"
check_arg "${@}"
restore
