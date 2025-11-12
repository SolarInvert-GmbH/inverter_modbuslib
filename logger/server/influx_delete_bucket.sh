#!/bin/bash

BUCKET=""
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
    echo "${0} BUCKET"
    echo "   BUCKET    -- The name for the bucket."
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
        BUCKET="${1}"
        if [[ $# -ge 2 ]]; then
            HEAD="${2}"
        fi
        status "InfluxDB delete bucket:"
        status "   bucket:   ${BUCKET}"
    else
        echo "Need one parameter:"
        print_help 1
    fi
}

delete()
{
    status "InfluxDB delete bucket"
    LINES="$(influx bucket delete --name "${BUCKET}" 2>&1)"
    CODE="${?}"

    if [[ "${CODE}" -eq 0 ]]; then
        status_multy "${LINES}"
    else
        error_multy "${LINES}" 2
    fi
}


check_for_help "${@}"
check_arg "${@}"
delete
