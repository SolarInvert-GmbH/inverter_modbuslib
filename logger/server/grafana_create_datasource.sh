#!/bin/bash

HEAD=""
NAME=""
USER_PASSWORD=""
URL=""
ORG=""
TOKEN=""

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
    echo "${0} NAME USER:PASSWORD URL ORG TOKEN"
    echo "   NAME          -- The description for the token."
    echo "   USER:PASSWORD -- The user and password to create the token, seperated by :."
    echo "   URL           -- The url to influxDB."
    echo "   ORG           -- The org of the influxDB."
    echo "   TOKEN         -- The read token of the influxDB."
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
        NAME="${1}"
        USER_PASSWORD="${2}"
        URL="${3}"
        ORG="${4}"
        TOKEN="${5}"
        if [[ $# -ge 6 ]]; then
            HEAD="${6}"
        fi

        status "Grafana create datasource:"
        status "   name:         '${NAME}'"
        status "   user:password: ${USER_PASSWORD}"
        status "   url:           ${URL}"
        status "   org:           ${ORG}"
        status "   token:         ${TOKEN}"
    else
        echo "Need at least five parameter:"
        print_help 1
    fi
}

datasource()
{
    status "InfluxDB token"

    JSON="{\"name\":\"${NAME}\",\"type\":\"influxdb\",\"access\":\"proxy\",\"url\":\"${URL}\",\"jsonData\":{\"version\":\"Flux\",\"organization\": \"${ORG}\"},\"secureJsonData\":{\"token\":\"${TOKEN}\"}}"
    status "${JSON}"


    LINES=$(curl -X POST -u "${USER_PASSWORD}" -H "Content-Type: application/json" -d "${JSON}" http://localhost:3000/api/datasources)
    CODE="${?}"

    if [[ "${CODE}" -eq 0 ]]; then
        status_multy "${LINES}"
    else
        error_multy "${LINES}" 3
    fi
}

check_for_help "${@}"
check_arg "${@}"
datasource
