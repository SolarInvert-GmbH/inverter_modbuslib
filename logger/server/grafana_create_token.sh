#!/bin/bash

HEAD=""
NAME=""
TYPE=""
USER_PASSWORD=""

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
    echo "${0} NAME USER:PASSWORD TYPE"
    echo "   NAME          -- The description for the token."
    echo "   USER:PASSWORD -- The user and password to create the token, seperated by :."
    echo "   TYPE          -- The type: Viewer (read only), Editor (read write) and Admin (all)."
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
        NAME="${1}"
        TYPE="${2}"
        USER_PASSWORD="${3}"
        if [[ $# -ge 4 ]]; then
            HEAD="${4}"
        fi

        status "Grafana create token:"
        status "   name:         '${NAME}'"
        status "   type:          ${TYPE}"
        status "   user:password: ${USER_PASSWORD}"
    else
        echo "Need at least two parameter:"
        print_help 1
    fi
}

token()
{
    status "Grafana token"

    LINES=$(curl -X POST -u "${USER_PASSWORD}" -H "Content-Type: application/json" -d "{\"name\":\"${NAME}\",\"role\":\"${TYPE}\"}" http://localhost:3000/api/auth/keys)
    CODE="${?}"

    if [[ "${CODE}" -eq 0 ]]; then
        status_multy "${LINES}"
    else
        error_multy "${LINES}" 3
    fi

    TOKEN=$(echo -e "$LINES" | grep "\"key\"" | cut -d'"' -f4)

    status "Token: ${TOKEN}"
}

check_for_help "${@}"
check_arg "${@}"
token
