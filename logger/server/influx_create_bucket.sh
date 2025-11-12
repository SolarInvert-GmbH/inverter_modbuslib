#!/bin/bash

BUCKET=""
RETENTION=""
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
    echo "   RETENTION -- The retention for the bucket. Number plus unit. e.g. (10s, 2m, 1h, 2d or 1w)"
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
        BUCKET="${1}"
        RETENTION="${2}"
        if [[ $# -ge 3 ]]; then
            HEAD="${3}"
        fi
        status "InfluxDB create bucket:"
        status "   bucket:    ${BUCKET}"
        status "   retention: ${RETENTION}"
    else
        echo "Need one parameter:"
        print_help 1
    fi
}

create()
{
    status "InfluxDB create bucket"
    LINES="$(influx bucket create --name "${BUCKET}" --retention "${RETENTION}" 2>&1)"
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
