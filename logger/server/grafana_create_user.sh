#!/bin/bash

HEAD=""
VAR_USER_PASSWORD=""
VAR_NAME=""
VAR_EMAIL=""
VAR_LOGIN=""
VAR_PASSWORD=""

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
    echo "${0} NAME USER:PASSWORD NAME EMAIL LOGIN PASSWORD"
    echo "   USER:PASSWORD -- The user and password to create the user, seperated by :."
    echo "   NAME          -- The name of the user."
    echo "   EMAIL         -- The email of the user. Can be empty."
    echo "   LOGIN         -- The login of the user."
    echo "   PASSWORD      -- The password of the user."
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
    if [[ $# -ge 5 ]]; then
        VAR_USER_PASSWORD="${1}"
        VAR_NAME="${2}"
        VAR_EMAIL="${3}"
        VAR_LOGIN="${4}"
        VAR_PASSWORD="${5}"
        if [[ $# -ge 6 ]]; then
            HEAD="${6}"
        fi
        status "Grafana create user:"
        status "   user:password: ${VAR_USER_PASSWORD}"
        status "   name:          ${VAR_NAME}"
        status "   email:         ${VAR_EMAIL}"
        status "   login:         ${VAR_LOGIN}"
        status "   password:      ${VAR_PASSWORD}"

    else
        echo "Need at least five parameter:"
        print_help 1
    fi
}

user()
{
    status "Grafana user"

    JSON="{\"name\":\"${VAR_NAME}\","
    if [ -n "${VAR_EMAIL}" ]; then
        JSON="${JSON}\"email\":\"${VAR_EMAIL}\","
    fi
    JSON="${JSON}\"login\":\"${VAR_LOGIN}\",\"password\":\"${VAR_PASSWORD}\"}"


    LINES=$(curl -X POST -u "${VAR_USER_PASSWORD}" -H "Content-Type: application/json" -d "${JSON}" http://localhost:3000/api/admin/users)
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
