#!/bin/bash

COMMAND="/user/bin/SendRequest"duration
GIOP="${1}"
MEASUREMENT_DURATION_SECONDS="${2}"
FACTOR="${3}"

INFLUX_ENDPOINT="${4}"
INFLUX_ORG="${5}"
INFLUX_BUCKET="${6}"
INFLUX_HASH="${7}"

LINES=""

while true; do
    IMPULSES=$(echo $(timeout "${MEASUREMENT_DURATION_SECONDS}" gpiomon --edges rising   --format="%e" --chip /dev/gpiochip0  "${GIOP}" ) | grep -o "1" | wc -l)
    SPEED=$(echo "(${IMPULSES} / ${MEASUREMENT_DURATION_SECONDS}) * ${FACTOR}" | bc)
    echo "${IMPULSES} ${SPEED} a"
    echo curl -X POST "${INFLUX_ENDPOINT}/api/v2/write?bucket=${INFLUX_BUCKET}&org=${INFLUX_ORG}"   --header "Authorization: Token ${INFLUX_HASH}"  \
              --data-raw "wind value=${SPEED} $(date +%s%N)"
         curl -X POST "${INFLUX_ENDPOINT}/api/v2/write?bucket=${INFLUX_BUCKET}&org=${INFLUX_ORG}"   --header "Authorization: Token ${INFLUX_HASH}"  \
              --data-raw "wind value=${SPEED} $(date +%s%N)" &
done
