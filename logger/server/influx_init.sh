#!/bin/bash


PASSWORD=""
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
    echo "${0} PASSWORD BUCKET"
    echo "   PASSWORD  -- The password for the admin user."
    echo "   BUCKET    -- The name for the first bucket."
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
    if [[ $# -ge 3 ]]; then
        PASSWORD="${1}"
        BUCKET="${2}"
        RETENTION="${3}"
        if [[ $# -ge 4 ]]; then
            HEAD="${4}"
        fi
        status "InfluxDB init:"
        status "   password:  ${PASSWORD}"
        status "   bucket:    ${BUCKET}"
        status "   retention: ${RETENTION}"
    else
        echo "Need three parameter:"
        print_help 1
    fi
}

check_installed_and_running()
{
    if command -v influxd >/dev/null 2>&1; then
        status "InfluxDB is installed."
    else
        error "InfluxDB is not installed." 1
    fi

    if curl -s -o /dev/null -w "%{http_code}" http://localhost:8086/ping | grep -q "204"; then
        status "InfluxDB is running."
    else
        error "InfluxDB is not running." 2
    fi
}

check_already_initialized()
{
    if [[ "$(curl http://localhost:8086/api/v2/setup 2>/dev/null)" == *"false"* ]]; then
        error "InfluxDB is already initialized." 3
    else
        status "InfluxDB is not initialized yet."
    fi
}

init()
{
    status "InfluxDB init"

    LINES=$(influx setup --username "admin" --password "${PASSWORD}" --org "solarinvert" --bucket "${BUCKET}" --retention "${RETENTION}" --force)
    CODE="${?}"

    if [[ "${CODE}" -eq 0 ]]; then
        status_multy "${LINES}"
    else
        error_multy "${LINES}" 4
    fi
}


check_for_help "${@}"
check_arg "${@}"
check_installed_and_running
check_already_initialized
init
