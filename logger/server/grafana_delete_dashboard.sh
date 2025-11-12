#!/bin/bash

TASK=""
VAR_USER_PASSWORD=""
VAR_DASHBOARD=""

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
    echo "${0} USER:PASSWORD DASHBOARD"
    echo "   USER:PASSWORD -- The user and password to create the token, seperated by :."
    echo "   DASHBOARD     -- The name for the dashboard."
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
        VAR_USER_PASSWORD="${1}"
        VAR_DASHBOARD="${2}"
        if [[ $# -ge 3 ]]; then
            HEAD="${3}"
        fi
        status "Grafana delete dashboard:"
        status "   user:password: ${VAR_USER_PASSWORD}"
        status "   dashboard:     ${VAR_DASHBOARD}"
    else
        echo "Need one parameter:"
        print_help 1
    fi
}

delete()
{
    status "Grafana dashboard delete"
    LINES="$(curl -X DELETE -s -u "${VAR_USER_PASSWORD}" -H "Content-Type: application/json" "http://localhost:3000/api/dashboards/uid/${VAR_DASHBOARD}" 2>&1)"
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
