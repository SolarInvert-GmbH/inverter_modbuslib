#!/bin/bash

HEAD=""
VAR_USER_PASSWORD=""

status()
{
    echo "${HEAD}STATUS: ${1}"
}

status_multy()
{
    while IFS= read -r LINE; do
        echo "${HEAD}STATUS: ${LINE}"
    done <<< "${1}"
}

print_help()
{
    echo "${0} USER:PASSWORD"
    echo "   USER:PASSWORD -- The user and password to create the token, seperated by :."
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
        VAR_USER_PASSWORD="${1}"
        if [[ $# -ge 2 ]]; then
            HEAD="${2}"
        fi
        status "Grafana show dashboard list:"
        status "   user:password: ${VAR_USER_PASSWORD}"

    else
        echo "Need at least seven parameter:"
        print_help 1
    fi
}

list()
{
    status "Grafana dashboard list"
    LINES="$(curl -s -u "${VAR_USER_PASSWORD}" -H "Content-Type: application/json" http://localhost:3000/api/search?query= | jq -r '.[] | "\(.id)\t\(.uid)\t\(.title)"')"
    status_multy "${LINES}"
}


check_for_help "${@}"
check_arg "${@}"
list
