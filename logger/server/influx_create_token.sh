#!/bin/bash

HEAD=""
DESCRIPTION=""
TYPE=""
BUCKETS=""

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
    echo "${0} DESCRIPTION read  BUCKETS"
    echo "${0} DESCRIPTION write BUCKETS"
    echo "${0} DESCRIPTION all"
    echo "   DESCRIPTION -- The description for the token."
    echo "   BUCKETS     -- The buckets seperated by comma."
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
        DESCRIPTION="${1}"
        TYPE="${2}"
        case ${2} in
          read)
            if [[ $# -ge 3 ]]; then
                BUCKETS="${3}"
            else
                echo "'read' Type needs BUCKETS parameter."
                print_help 1
            fi

            if [[ $# -ge 4 ]]; then
                HEAD="${4}"
            fi
          ;;
          write)
            if [[ $# -ge 3 ]]; then
                BUCKETS="${3}"
            else
                echo "'write' Type needs BUCKETS parameter."
                print_help 1
            fi

            if [[ $# -ge 4 ]]; then
                HEAD="${4}"
            fi
          ;;
          all)
            if [[ $# -ge 3 ]]; then
                HEAD="${3}"
            fi
          ;;
          *)
            echo "Type must be 'read', 'write' or 'all'."
            print_help 1
          ;;
        esac

        status "InfluxDB create token:"
        status "   description: '${DESCRIPTION}'"
        status "   type:        ${TYPE}"
        status "   bucket:      ${BUCKETS}"
    else
        echo "Need at least two parameter:"
        print_help 1
    fi
}

name_to_id()
{
    LINES=$(influx bucket list)

    while IFS= read -r LINE; do
        ID=$(echo -e "$LINE" | cut -d $'\t' -f1)
        NAME=$(echo -e "$LINE" | cut -d $'\t' -f2)
        if [[ "${NAME}" == "${1}" ]]; then
            echo "${ID}"
            return 0
        fi
    done <<< "${LINES}"
    error "There is no '${BUCKET}' bucket." 2
}

token()
{
    status "InfluxDB token"

    case ${TYPE} in
      read)
        CMD=( influx auth create --org "solarinvert" --description "${DESCRIPTION}" )
        IFS=',' read -r -a BUCKET_LIST <<< "${BUCKETS}"
        for BUCKET in "${BUCKET_LIST[@]}"; do

            CMD+=( --read-bucket "$(name_to_id "${BUCKET}")" )
        done
        LINES=$("${CMD[@]}")
        CODE="${?}"
      ;;
      write)
        CMD=( influx auth create --org "solarinvert" --description "${DESCRIPTION}" )
        IFS=',' read -r -a BUCKET_LIST <<< "${BUCKETS}"
        for BUCKET in "${BUCKET_LIST[@]}"; do

            CMD+=( --write-bucket "$(name_to_id "${BUCKET}")" )
        done
        LINES=$("${CMD[@]}")
        CODE="${?}"
      ;;
      all)
        LINES=$(influx auth create --org "solarinvert" --all-access --description "${DESCRIPTION}")
        CODE="${?}"
      ;;
    esac

    if [[ "${CODE}" -eq 0 ]]; then
        status_multy "${LINES}"
    else
        error_multy "${LINES}" 3
    fi

    TOKEN=$(echo -e "$LINES" | awk 'NR==2 {print $3}')

    status "Token: ${TOKEN}"
}

check_for_help "${@}"
check_arg "${@}"
name_to_id
token
