#!/bin/bash

UART="${1}"
SHUTDOWN_TIME="${2}"

COUNTER="0"
HAS_EVER_SEEN_UART="false"

while true; do
    if [ -c "${UART}" ]; then
        COUNTER="0"
        HAS_EVER_SEEN_UART="true"
    else
        ((COUNTER++))
    fi
    echo "Time without Inverter device ${UART} [${COUNTER}s/${SHUTDOWN_TIME}s]. HAS_EVER_SEEN_UART=${HAS_EVER_SEEN_UART}."

    if (( COUNTER > SHUTDOWN_TIME )) && [ "${HAS_EVER_SEEN_UART}" = "true" ]; then
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
