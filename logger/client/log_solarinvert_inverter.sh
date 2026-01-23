#!/bin/bash

COMMAND="SendRequest"
UART="${1}"

PARAMETER_TIME="${2}"
PARAMETER_AC_POWER="${3}"
PARAMETER_DC_VOLTAGE="${4}"
PARAMETER_OPERATING_STATE="${5}"
PARAMETER_TEMPERATURE="${6}"
PARAMETER_AC_VOLTAGE="${7}"
PARAMETER_ENERGY_PRODUCTION="${8}"

INFLUX_ENDPOINT="${9}"
INFLUX_ORG="${10}"
INFLUX_BUCKET="${11}"
INFLUX_HASH="${12}"

LINES_PROD=""
LINES_TEST=""

MAX_ERROR="10000"
ERROR_COUNTER="0"
LOOP_TIME_SECONDS="${13}"
NANO_FACTOR="1000000000"
LOOP_TIME_NANO_SECONDS=$((NANO_FACTOR * LOOP_TIME_SECONDS))
MAX_ID="110"
VALID_TIME=$(( MAX_ID * LOOP_TIME_SECONDS * 5 ))


CHECK_ID="00"

INVERTER_LIST=()

listAddObject()
{
    declare -gA "INVERTER_LIST_OBJECT_${1}"
    declare -n OBJECT="INVERTER_LIST_OBJECT_${1}"
    OBJECT[ID]="${1}"
    OBJECT[NAME]="${2}"
    OBJECT[LAST_SEEN]="${3}"
    INVERTER_LIST+=("INVERTER_LIST_OBJECT_${1}")
}

listRemoveObject()
{
    local NEW_INVERTER_LIST=()
    for OBJECT in "${INVERTER_LIST[@]}"; do
        if [[ "${OBJECT}" != "INVERTER_LIST_OBJECT_${1}" ]]; then
            NEW_INVERTER_LIST+=("${OBJECT}")
        fi
    done
    INVERTER_LIST=("${NEW_INVERTER_LIST[@]}")

    unset "INVERTER_LIST_OBJECT_${1}"
}

listHasObject()
{
    for OBJECT in "${INVERTER_LIST[@]}"; do
        [[ "${OBJECT}" == "INVERTER_LIST_OBJECT_${1}" ]] && return 0
    done
    return 1
}

listToString()
{
    RESULT=""
    for ELEMENT in "${INVERTER_LIST[@]}"; do
        declare -n OBJECT="${ELEMENT}"
        if [[ -n "$RESULT" ]]; then
            RESULT="${RESULT},"
        fi
        RESULT="${RESULT}[${OBJECT[ID]},${OBJECT[NAME]},${OBJECT[LAST_SEEN]}]"
    done
    echo "${RESULT}"
}

readRegisterToLines()
{
    REGISTER_TYPE="${6}"
    RESULT=$("${COMMAND}" --uart "${UART}" --modbusid "${4}" --request "{\"type\":\"readRegister\",\"value\":{\"registerAddress\":\"${1}\"}}" --timeout 50)

    if [ $? -eq 0 ]; then
        VALUE_INTEGER=$(echo "${RESULT}" | cut -d: -f5 | cut -d\} -f1)
        if [[ ( ( "${REGISTER_TYPE}" != "uI32" && "${REGISTER_TYPE}" != "sI32" ) || "${VALUE_INTEGER}" -ne 4294967295 ) && "${VALUE_INTEGER}" -ne 65535 ]]; then
            if [[ "${REGISTER_TYPE}" == "sI16" && "${VALUE_INTEGER}" -gt 32767 ]]; then
                VALUE_INTEGER=$(( (65536 - VALUE_INTEGER)*(-1) ))
            fi
            if [[ "${REGISTER_TYPE}" == "sI32" && "${VALUE_INTEGER}" -gt 2147483647 ]]; then
                VALUE_INTEGER=$(( (4294967296 - VALUE_INTEGER)*(-1) ))
            fi
            if [[ "${2}" == "temperature" ]]; then
                VALUE_FLOAT=$(echo "124.0 - ${VALUE_INTEGER}/2.0" | bc -l | sed -E 's/\.?0+$//' | sed -E 's/^$/0/'1)
            else
                VALUE_FLOAT=$(echo "${VALUE_INTEGER}/${2}" | bc -l | sed -E 's/\.?0+$//' | sed -E 's/^$/0/'1)
            fi
            if [[ "${4}" != "09" ]]; then
                LINES_PROD="${LINES_PROD}
${3},_inverter=${5} value=${VALUE_FLOAT}   $(date +%s%N)"

            else
                LINES_TEST="${LINES_TEST}
${3},_inverter=${5} value=${VALUE_FLOAT}   $(date +%s%N)"
            fi
        fi
        ERROR_COUNTER="0"
        CALL_WAS_SUCCESFULL="true"
    else
        ((ERROR_COUNTER++))
        if [ "${ERROR_COUNTER}" -ge "${MAX_ERROR}" ]; then
            echo "Failed ${MAX_ERROR} times in a row. Exit."
            exit 1
        fi
    fi
    echo "[${ERROR_COUNTER}] ${RESULT}"
}

readName()
{
        echo "${COMMAND}" --uart "${UART}" --modbusid "${1}" --request \''{"type":"readRegister","value":{"registerAddress":"CommonSerialNumber"}}'\' --timeout 100 >&2

    RESULT=$("${COMMAND}" --uart "${UART}" --modbusid "${1}" --request   '{"type":"readRegister","value":{"registerAddress":"CommonSerialNumber"}}'   --timeout 100)

    if [ $? -eq 0 ]; then
        VALUE=$(echo "${RESULT}" | cut -d: -f5 | cut -d\} -f1)
        ERROR_COUNTER="0"
        echo "${VALUE}" >&2
        echo "${VALUE}"
        return 0
    else
        echo "Error: ${RESULT}" >&2
        ((ERROR_COUNTER++))
        return 1
    fi
}

sendData()
{
    LINE="${1}"
    TAIL="${2}"
    if [ -n "${1}" ]; then
             curl -X POST "${INFLUX_ENDPOINT}/api/v2/write?bucket=${INFLUX_BUCKET}${TAIL}&org=${INFLUX_ORG}" --header "Authorization: Token ${INFLUX_HASH}" --data-raw "${1}" 2>/dev/null &
	    echo curl -X POST "${INFLUX_ENDPOINT}/api/v2/write?bucket=${INFLUX_BUCKET}${TAIL}&org=${INFLUX_ORG}" --header "Authorization: Token ${INFLUX_HASH}" --data-raw "${1}" >&2
    fi
}

echo "start..." >&2

while true; do
    START_TIME_NANO_SECONDS=$(date +%s%N)
    LINES_PROD=""
    LINES_TEST=""

    for ELEMENT in "${INVERTER_LIST[@]}"; do
        declare -n INVERTER="${ELEMENT}"
        ID="${INVERTER[ID]}"
        NAME="${INVERTER[NAME]}"
        CALL_WAS_SUCCESFULL="false"
        echo "ID: ${ID} NAME: ${NAME}" >&2
        if [[ -n ${ID} ]]; then
            if [[ "${PARAMETER_TIME}" == "true" ]]; then
                readRegisterToLines SiControlUptime                        1 time        "${ID}" "${NAME}" "uI32"
            fi
            if [[ "${PARAMETER_AC_POWER}" == "true" ]]; then
                readRegisterToLines InverterAcPower                       10 acpower     "${ID}" "${NAME}" "sI16"
            fi
            if [[ "${PARAMETER_DC_VOLTAGE}" == "true" ]]; then
                readRegisterToLines InverterDcVoltage                    100 dcvoltage   "${ID}" "${NAME}" "uI16"
            fi
            if [[ "${PARAMETER_OPERATING_STATE}" == "true" ]]; then
                readRegisterToLines InverterVendorOperatingState           1 state       "${ID}" "${NAME}" "uI16"
            fi
            if [[ "${PARAMETER_TEMPERATURE}" == "true" ]]; then
                readRegisterToLines InverterTemperature          temperature temperature "${ID}" "${NAME}" "sI16"
            fi
            if [[ "${PARAMETER_AC_VOLTAGE}" == "true" ]]; then
                readRegisterToLines InverterPhaseVoltageA                  1 acvoltage   "${ID}" "${NAME}" "uI16"
            fi
            if [[ "${PARAMETER_ENERGY_PRODUCTION}" == "true" ]]; then
                readRegisterToLines InverterWattHours                     10 energy      "${ID}" "${NAME}" "sI32"
            fi
        fi
        if [[ ${CALL_WAS_SUCCESFULL} == "true" ]];then
            INVERTER[LAST_SEEN]="$(date +%s)"
        fi
        if (( $(date +%s) - INVERTER[LAST_SEEN] > VALID_TIME )); then
            listRemoveObject "${ID}"
            echo "Have not heared from inverter ${ID} for ${VALID_TIME} seconds. Drop inverter ${ID}." >&2
        fi
    done
    sendData "${LINES_PROD}" ""
    sendData "${LINES_TEST}" "test"


    END_TIME_NANO_SECONDS=$(date +%s%N)
    DURATION_NANO_SECONDS=$((END_TIME_NANO_SECONDS - START_TIME_NANO_SECONDS))
    SLEEP_NANO_SECONDS=$((LOOP_TIME_NANO_SECONDS - DURATION_NANO_SECONDS))

    if ! listHasObject "${CHECK_ID}"; then
        if VALUE=$(readName "${CHECK_ID}"); then
            listAddObject "${CHECK_ID}" "${VALUE}" "$(date +%s)"
            echo "Add inverter ${CHECK_ID} (${VALUE})." >&2
        fi
    fi

    CHECK_ID_DEC=$(( 16#$CHECK_ID ))
    CHECK_ID_DEC=$(( CHECK_ID_DEC + 1 ))
    if (( "${CHECK_ID_DEC}" > "${MAX_ID}" )); then
        CHECK_ID_DEC=0
    fi
    CHECK_ID=$(printf "%02x" "${CHECK_ID_DEC}")

    echo "Inverter list {$(listToString)}. Next id to check ${CHECK_ID}." >&2

    if (( SLEEP_NANO_SECONDS > 0 )); then
        SLEEP_SECONDS=$(echo "${SLEEP_NANO_SECONDS}/${NANO_FACTOR}" | bc -l)
        echo "sleep ${SLEEP_SECONDS} "
        sleep "${SLEEP_SECONDS}"

    fi
done
