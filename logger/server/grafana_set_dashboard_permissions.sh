#!/bin/bash

HEAD=""
VAR_USER_PASSWORD=""
VAR_USER=""
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
    echo "${0} NAME USER:PASSWORD USER DASHBOARD"
    echo "   USER:PASSWORD -- The user and password to create the user, seperated by :."
    echo "   USER          -- The user."
    echo "   DASHBOARD     -- The dashboard uid."
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
        VAR_USER_PASSWORD="${1}"
        VAR_USER="${2}"
        VAR_DASHBOARD="${3}"
        if [[ $# -ge 4 ]]; then
            HEAD="${4}"
        fi
        status "Grafana set dashboard permissions:"
        status "   user:password: ${VAR_USER_PASSWORD}"
        status "   user:          ${VAR_USER}"
        status "   dashboard:     ${VAR_DASHBOARD}"

    else
        echo "Need at least three parameter:"
        print_help 1
    fi
}

user()
{
    status "Grafana set dashboard permission"

    JSON="{\"items\":[{\"role\":\"Admin\",\"permission\":4},{\"userId\":${VAR_USER},\"permission\":1}]}"

    echo  curl -X POST -u "${VAR_USER_PASSWORD}" -H "Content-Type: application/json" -d "${JSON}" "http://localhost:3000/api/dashboards/uid/${VAR_DASHBOARD}/permissions"
    LINES=$(curl -X POST -u "${VAR_USER_PASSWORD}" -H "Content-Type: application/json" -d "${JSON}" "http://localhost:3000/api/dashboards/uid/${VAR_DASHBOARD}/permissions")
    CODE="${?}"

    if [[ "${CODE}" -eq 0 ]]; then
        status_multy "${LINES}"
    else
        error_multy "${LINES}" 3
    fi
}

check_for_help "${@}"
check_arg "${@}"
user
