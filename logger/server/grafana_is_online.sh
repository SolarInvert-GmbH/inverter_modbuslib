#!/bin/bash

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

print_help()
{
    echo "${0}"
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
        HEAD="${1}"
    fi

    status "Grafana is online:"
}

is_online()
{
    local MAX_WAIT=300
    local COUNTER=0

    while (( COUNTER < MAX_WAIT )); do
        if curl -fs http://localhost:3000/ >/dev/null 2>&1; then
            status "Grafana is running."
            exit 0
        else
            status "Grafana is not running."
        fi

        sleep 1
        ((COUNTER++))
    done

    error "Grafana is not running after ${MAX_WAIT} sekonds." 1
}

check_for_help "${@}"
check_arg "${@}"
is_online
