#!/bin/bash

COMMAND="SendRequest"
UART="${1}"
ID_1="${2}"
ID_2="${3}"
ID_3="${4}"
ID_4="${5}"
ID_5="${6}"

OLD_NAME_1="${7}"
OLD_NAME_2="${8}"
OLD_NAME_3="${9}"
OLD_NAME_4="${10}"
OLD_NAME_5="${11}"

NEW_NAME_1=""
NEW_NAME_2=""
NEW_NAME_3=""
NEW_NAME_4=""
NEW_NAME_5=""

NAME_1=""
NAME_2=""
NAME_3=""
NAME_4=""
NAME_5=""

read_name()
{
    MAX_ERROR="100"
    ERROR_COUNTER="0"

    while true; do
	        echo "${COMMAND}" --uart "${UART}" --modbusid "${1}" --request "'{\"type\":\"readRegister\",\"value\":{\"registerAddress\":\"CommonSerialNumber\"}}'" --timeout 100 >&2

        RESULT=$("${COMMAND}" --uart "${UART}" --modbusid "${1}" --request "{\"type\":\"readRegister\",\"value\":{\"registerAddress\":\"CommonSerialNumber\"}}" --timeout 100)

        if [ $? -eq 0 ]; then
            VALUE=$(echo "${RESULT}" | cut -d: -f5 | cut -d\} -f1)
            ERROR_COUNTER="0"
            echo "${VALUE}" >&2
            echo "${VALUE}"
            return
        else
            ((ERROR_COUNTER++))
            echo "ERROR(${ERROR_COUNTER}): ${RESULT}" >&2
            if [ "${ERROR_COUNTER}" -ge "${MAX_ERROR}" ]; then
                return
            fi
        fi
	sleep 1
    done
}

ALL_THE_SAME="true"

for i in {1..5}; do
    declare -n ID="ID_${i}"
    declare -n OLD_NAME="OLD_NAME_${i}"
    declare -n NEW_NAME="NEW_NAME_${i}"
    declare -n NAME="NAME_${i}"
    if [[ -n ${ID} ]]; then
        NEW_NAME=$(read_name "${ID}")
        echo "${NEW_NAME}" >&2
        if [[ -n ${NEW_NAME} ]]; then
            NAME="${NEW_NAME}"
            echo "A" >&2
        else
            NAME="${OLD_NAME}"
            echo "B" >&2
        fi
        echo "'${OLD_NAME}' ?= '${NAME}'" >&2
        if [[ "${OLD_NAME}" != "${NAME}" ]]; then
            ALL_THE_SAME="false"
            echo "New names found." >&2
        fi
    fi
done

if [[ "${ALL_THE_SAME}" == "false" ]]; then
    sudo sh -c "cat > /etc/solarinvert/name.env <<EOF
NAME_1=${NAME_1}
NAME_2=${NAME_2}
NAME_3=${NAME_3}
NAME_4=${NAME_4}
NAME_5=${NAME_5}
EOF"
fi

if [[ -n "${NAME_1}" ]]; then
    echo "Read at least name 1." >&2
    exit 0
else
    echo "Read no name." >&2
    exit 1
fi
