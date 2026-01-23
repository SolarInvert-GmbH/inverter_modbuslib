#!/bin/bash

REMOTE=""
URL=""
TOKEN=""
ORG_ID=""
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
    echo "${0} REMOTE URL TOKEN ORG_ID"
    echo "   REMOTE    -- The name for the remote."
    echo "   URL       -- The url for the remote."
    echo "   TOKEN     -- The write token for the remote."
    echo "   ORG_ID    -- The org id for the remote."

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
    if [[ $# -ge 4 ]]; then
        REMOTE="${1}"
        URL="${2}"
        TOKEN="${3}"
        ORG_ID="${4}"
        if [[ $# -ge 5 ]]; then
            HEAD="${5}"
        fi
        status "InfluxDB create remote:"
        status "   remote: ${REMOTE}"
        status "   url:    ${URL}"
        status "   token:  ${TOKEN}"
        status "   org id: ${ORG_ID}"
    else
        echo "Need one parameter:"
        print_help 1
    fi
}

create()
{
    status "InfluxDB create remote"
    LINES="$(influx remote create --name  "${REMOTE}" --remote-url "${URL}" --remote-api-token "${TOKEN}" --remote-org-id "${ORG_ID}" 2>&1)"
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
