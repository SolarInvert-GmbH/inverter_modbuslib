#!/bin/bash

NAME=""
REMOTE_ID=""
LOCAL_ID=""
SERVER_ID=""
ORG=""
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
    echo "${0} NAME REMOTE_ID LOCAL_ID SERVER_ID ORG"
    echo "   NAME      -- The name for the replication."
    echo "   REMOTE_ID -- The id of the remote."
    echo "   LOCAL_ID  -- The id of the local bucket."
    echo "   SERVER_ID -- The id of the server bucket."
    echo "   ORG       -- The organisation."

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
        REMOTE_ID="${2}"
        LOCAL_ID="${3}"
        SERVER_ID="${4}"
        ORG="${5}"
        if [[ $# -ge 6 ]]; then
            HEAD="${6}"
        fi
        status "InfluxDB create replication:"
        status "   replication: ${NAME}"
        status "   remote id:   ${REMOTE_ID}"
        status "   local id:    ${LOCAL_ID}"
        status "   server id:   ${SERVER_ID}"
        status "   org:         ${ORG}"
    else
        echo "Need one parameter:"
        print_help 1
    fi
}

create()
{
    status "InfluxDB create replication"
    LINES="$(influx replication create --name "${NAME}" --remote-id "${REMOTE_ID}" --local-bucket-id ${LOCAL_ID} --remote-bucket-id ${SERVER_ID} --org "${ORG}" 2>&1)"
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
