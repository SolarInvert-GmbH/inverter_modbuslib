#!/bin/bash

UART="${1}"
SHUTDOWN_TIME="${2}"

COUNTER="0"

while true; do
    if [ -c "${UART}" ]; then
        COUNTER="0"
    else
        ((COUNTER++))
    fi
    echo "Time without Inverter device ${UART} [${COUNTER}s/${SHUTDOWN_TIME}s]"

    if (( COUNTER > SHUTDOWN_TIME )); then
        echo "Stop sending sevices…"
        systemctl stop SolarInvertInverter.service
        systemctl stop SolarInvertWind.service
        sleep 5
        echo "Shutdown"
        sleep 1
        shutdown now
    fi

    sleep 1
done
