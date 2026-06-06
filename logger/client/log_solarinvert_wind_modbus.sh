#!/bin/bash

UART="${1}"
MEASUREMENT_DURATION_SECONDS="${2}"

INFLUX_ENDPOINT="${3}"
INFLUX_ORG="${4}"
INFLUX_BUCKET="${5}"
INFLUX_HASH="${6}"

ERROR_FILE=$(mktemp)

cleanup() {
    echo "clean up"
    rm -f "$ERROR_FILE"
}

trap cleanup EXIT

while true; do
    if RESULT=$(mbpoll -m rtu -b 9600 -P none -a 2 -t 4 -0 -r 0 -c 1 -1 "${UART}" 2>"${ERROR_FILE}"); then
        VALUE=$(echo "${RESULT}" | awk 'END {print $NF}')
        SPEED=$(echo "scale=1; ${VALUE} / 10" | bc)
        echo "Speed: ${SPEED} m/s"
        echo curl -X POST "${INFLUX_ENDPOINT}/api/v2/write?bucket=${INFLUX_BUCKET}&org=${INFLUX_ORG}"   --header "Authorization: Token ${INFLUX_HASH}"  \
              --data-raw "wind value=${SPEED} $(date +%s%N)"
             curl -X POST "${INFLUX_ENDPOINT}/api/v2/write?bucket=${INFLUX_BUCKET}&org=${INFLUX_ORG}"   --header "Authorization: Token ${INFLUX_HASH}"  \
              --data-raw "wind value=${SPEED} $(date +%s%N)" &
    else
        ERROR=$(<"${ERROR_FILE}")
        echo "Invalid: ${ERROR}"
    fi
    sleep ${MEASUREMENT_DURATION_SECONDS}
done
