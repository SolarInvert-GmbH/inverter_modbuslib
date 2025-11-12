#!/bin/bash

COMMAND="SendRequest"
UART="${1}"
ID_1="${2}"
ID_2="${3}"
ID_3="${4}"
ID_4="${5}"
ID_5="${6}"

PARAMETER_TIME="${7}"
PARAMETER_AC_POWER="${8}"
PARAMETER_DC_VOLTAGE="${9}"
PARAMETER_OPERATING_STATE="${10}"
PARAMETER_TEMPERATURE="${11}"
PARAMETER_AC_VOLTAGE="${12}"
PARAMETER_ENERGY_PRODUCTION="${13}"

INFLUX_ENDPOINT="${14}"
INFLUX_ORG="${15}"
INFLUX_BUCKET="${16}"
INFLUX_HASH="${17}"

NAME_1="${19}"
NAME_2="${20}"
NAME_3="${21}"
NAME_4="${22}"
NAME_5="${23}"

LINES=""

MAX_ERROR="100"
ERROR_COUNTER="0"
LOOP_TIME_SECONDS="${18}"
NANO_FACTOR="1000000000"
LOOP_TIME_NANO_SECONDS=$((NANO_FACTOR * LOOP_TIME_SECONDS))

readRegisterToLines()
{
    RESULT=$("${COMMAND}" --uart "${UART}" --modbusid "${4}" --request "{\"type\":\"readRegister\",\"value\":{\"registerAddress\":\"${1}\"}}" --timeout 50)


    if [ $? -eq 0 ]; then
        VALUE_INTEGER=$(echo "${RESULT}" | cut -d: -f5 | cut -d\} -f1)
        VALUE_FLOAT=$(echo "${VALUE_INTEGER}/${2}" | bc -l | sed -E 's/\.?0+$//' | sed -E 's/^$/0/'1)
        LINES="${LINES}
${3},_inverter=${5} value=${VALUE_FLOAT}   $(date +%s%N)"
        ERROR_COUNTER="0"
    else
        ((ERROR_COUNTER++))
        if [ "${ERROR_COUNTER}" -ge "${MAX_ERROR}" ]; then
            echo "Failed ${MAX_ERROR} times in a row. Exit."
            exit 1
        fi
    fi
    echo "[${ERROR_COUNTER}] ${RESULT}"
}

echo "start..." >&2

while true; do
    START_TIME_NANO_SECONDS=$(date +%s%N)
    LINES=""

    for i in {1..5}; do
        declare -n ID="ID_${i}"
        declare -n NAME="NAME_${i}"
        echo "ID: ${ID} NAME: ${NAME}" >&2
        if [[ -n ${ID} ]]; then
            if [[ "${PARAMETER_TIME}" == "true" ]]; then
                readRegisterToLines SiControlUptime 1 time "${ID}" "${NAME}"
            fi
            if [[ "${PARAMETER_AC_POWER}" == "true" ]]; then
                readRegisterToLines InverterAcPower 10 acpower "${ID}" "${NAME}"
            fi
            if [[ "${PARAMETER_DC_VOLTAGE}" == "true" ]]; then
                readRegisterToLines InverterDcVoltage 10 dcvoltage "${ID}" "${NAME}"
            fi
            if [[ "${PARAMETER_OPERATING_STATE}" == "true" ]]; then
                readRegisterToLines InverterVendorOperatingState 1 state "${ID}" "${NAME}"
            fi
            if [[ "${PARAMETER_TEMPERATURE}" == "true" ]]; then
                readRegisterToLines InverterTemperature 10 temperature "${ID}" "${NAME}"
            fi
            if [[ "${PARAMETER_AC_VOLTAGE}" == "true" ]]; then
                readRegisterToLines InverterPhaseVoltageA 1 acvoltage "${ID}" "${NAME}"
            fi
            if [[ "${PARAMETER_ENERGY_PRODUCTION}" == "true" ]]; then
                readRegisterToLines InverterWattHours 10 energy "${ID}" "${NAME}"
            fi
        fi
    done
    if [ -n "${LINES}" ]; then
        curl -X POST "${INFLUX_ENDPOINT}/api/v2/write?bucket=${INFLUX_BUCKET}&org=${INFLUX_ORG}"   --header "Authorization: Token ${INFLUX_HASH}"   --data-raw "${LINES}" &
	echo curl -X POST "${INFLUX_ENDPOINT}/api/v2/write?bucket=${INFLUX_BUCKET}&org=${INFLUX_ORG}" --header "Authorization: Token ${INFLUX_HASH}" --data-raw "${LINES}" >&2
    fi


    END_TIME_NANO_SECONDS=$(date +%s%N)
    DURATION_NANO_SECONDS=$((END_TIME_NANO_SECONDS - START_TIME_NANO_SECONDS))
    SLEEP_NANO_SECONDS=$((LOOP_TIME_NANO_SECONDS - DURATION_NANO_SECONDS))

    if (( SLEEP_NANO_SECONDS > 0 )); then
        SLEEP_SECONDS=$(echo "${SLEEP_NANO_SECONDS}/${NANO_FACTOR}" | bc -l)
        echo "sleep ${SLEEP_SECONDS} "
        sleep "${SLEEP_SECONDS}"

    fi
done
