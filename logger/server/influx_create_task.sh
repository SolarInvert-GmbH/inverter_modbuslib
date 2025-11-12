#!/bin/bash

ORG=""
FLUX=""
HEAD=""

status()
{
    echo "${HEAD}STATUS: ${1}"
}

error()
{
    echo "${HEAD}ERROR: ${1}" >&2
    exit ${2}
}

status_multy()
{
    PRE_HEAD=""
    if [[ $# -ge 2 ]]; then
        PRE_HEAD="${2}"
    fi
    while IFS= read -r LINE; do
        echo "${HEAD}STATUS: ${PRE_HEAD}${LINE}"
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
    echo "${0} ORG FLUX"
    echo "   ORG       -- The organsiation."
    echo "   FLUX      -- The flux script."
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
    if [[ $# -ge 2 ]]; then
        ORG="${1}"
        FLUX="${2}"
        if [[ $# -ge 3 ]]; then
            HEAD="${3}"
        fi
        status "InfluxDB create task:"
        status "   org:    ${ORG}"
        status "   flux:"
        status_multy "${FLUX}" "      "
    else
        echo "Need one parameter:"
        print_help 1
    fi
}

create()
{
    status "InfluxDB create task"
    LINES="$(influx task create --org "${ORG}"  "${FLUX}" 2>&1)"
    CODE="${?}"

    if [[ "${CODE}" -eq 0 ]]; then
        status_multy "${LINES}"
    else
        error_multy "${LINES}" 2
    fi
}


check_for_help "${@}"
check_arg "${@}"
create
