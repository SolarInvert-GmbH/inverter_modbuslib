#!/bin/bash

SOURCE="$(readlink -f ${BASH_SOURCE[0]})"
ROOT="${SOURCE%/*}"
unset SOURCE

CUSTOMER="${1}"
shift
GRAFANA_GROUP="${1}"
shift
INFLUXDB_HOST="${1}"
shift
INFLUXDB_TOKEN="${1}"
shift
INFLUXDB_ORG="${1}"
shift
GRAFANA_HOST="${1}"
shift
GRAFANA_USER_PASSWORD="${1}"
shift

TAIL=(     ""    "10s"  "1m"    "test")
RETENTION=("30d" "356d" "3560d" "12h")
SIZE=4

INVERTER_COUNT="2"

BUCKET_ID=()

log()
{
    echo "${1}" >&2
}

check()
{
    if [[ "${1}" != 0 ]]; then
        echo "${2}" >&2
        exit
    fi
}


create_bucket()
{
    log ""
    log "create_bucket"
    log "influx bucket create --name \"${1}\"    --retention \"${2}\"   --host \"${INFLUXDB_HOST}\" -t \"${INFLUXDB_TOKEN}\""
    local TEXT="$(influx bucket create --name "${1}" --retention "${2}"   --host "${INFLUXDB_HOST}" -t "${INFLUXDB_TOKEN}")"
    local RESULT="${?}"
    log "${TEXT}"
    check "${RESULT}" "create bucket"
    local LAST_LINE="${TEXT##*$'\n'}"
    local FIRST_ENTRY="${LAST_LINE%%$'\t'*}"

    echo "${FIRST_ENTRY}"
}

write_token()
{
    log ""
    log "write_token"
    local CMD=( influx auth create --org "solarinvert" --description "${CUSTOMER}_WRITE")
    for ((i=0; i<SIZE; i++)); do
        CMD+=( --write-bucket "${BUCKET_ID[$i]}" )
    done
    CMD+=( --host "${INFLUXDB_HOST}" -t "${INFLUXDB_TOKEN}" )
    log $(echo ${CMD[@]})
    local TEXT="$("${CMD[@]}")"
    local RESULT="${?}"
    log "${TEXT}"
    check "${RESULT}" "write token"
    local LAST_LINE="${TEXT##*$'\n'}"
    local THIRD_ENTRY="$(echo "$LAST_LINE" | cut -f3)"
    echo "${THIRD_ENTRY}"
}

read_token()
{
    log ""
    log "read_token"
    local CMD=( influx auth create --org "solarinvert" --description "${CUSTOMER}_READ")
    for ((i=0; i<SIZE; i++)); do
        CMD+=( --read-bucket "${BUCKET_ID[$i]}" )
    done
    CMD+=( --host "${INFLUXDB_HOST}" -t "${INFLUXDB_TOKEN}" )
    log $(echo ${CMD[@]})
    local TEXT="$("${CMD[@]}")"
    local RESULT="${?}"
    log "${TEXT}"
    check "${RESULT}" "read token"
    local LAST_LINE="${TEXT##*$'\n'}"
    local THIRD_ENTRY="$(echo "$LAST_LINE" | cut -f3)"
    echo "${THIRD_ENTRY}"
}

datasource()
{
    local NAME="${1}"
    local URL="${2}"
    local ORG="${3}"
    local TOKEN="${4}"
    local USER_PASSWORD="${5}"
    local HOST="${6}"
    log ""
    log "Grafana datasource"

    local JSON="{\"name\":\"${NAME}\",\"type\":\"influxdb\",\"access\":\"proxy\",\"url\":\"${URL}\",\"jsonData\":{\"version\":\"Flux\",\"organization\": \"${ORG}\"},\"secureJsonData\":{\"token\":\"${TOKEN}\"}}"
    log "${JSON}"

    log "curl -X POST -u '${USER_PASSWORD}' -H 'Content-Type: application/json' -d '${JSON}' '${HOST}/api/datasources'"
    local TEXT=$(curl -X POST -u "${USER_PASSWORD}" -H "Content-Type: application/json" -d "${JSON}" "${HOST}/api/datasources")
    local RESULT="${?}"
    log "${TEXT}"
    check "${RESULT}" "read token"
    jq -r '.datasource.uid' <<< "${TEXT}"
}

GRAFANA_VALUES_WIND_ONLY=( "WIND_SINGLE" )
GRAFANA_VALUES_WIND=(      "WIND_MULTI" "AC_POWER" "DC_VOLTAGE" "ENERGY_PRODUCTION" "AC_VOLTAGE" "TEMPERATURE" "TIME" "OPERATING_STATE" )
GRAFANA_VALUES_SOLAR=(                  "AC_POWER" "DC_VOLTAGE" "ENERGY_PRODUCTION" "AC_VOLTAGE" "TEMPERATURE" "TIME" "OPERATING_STATE" )

create_dashboard()
{
    local CUSTOMER="${1}"
    local POSTFIX="${2}"
    local GRAFANA_DATASOURCE="${3}"
    local NUMBER_OF_INVERTER="${4}"
    local -n VALUES="$5"
    local GRAFANA_USER_PASSWORD="${6}"
    local GRAFANA_HOST="${7}"
    log ""
    log "create_dashboard"
    dashboard_cmd=("${ROOT}/../server/DashboardContent.sh" "${CUSTOMER}_${POSTFIX}" "${CUSTOMER}" "${GRAFANA_DATASOURCE}" "${NUMBER_OF_INVERTER}" "${VALUES[@]}")
    log "$(echo "${dashboard_cmd[@]}")"
    local DASHBOARD="$("${dashboard_cmd[@]}")"
    local curl_cmd=(curl -X POST -u "$GRAFANA_USER_PASSWORD" -H "Content-Type: application/json" -d "${DASHBOARD}"  "${GRAFANA_HOST}/api/dashboards/db")
    log "$(echo "${curl_cmd[@]}")"
    local TEXT="$("${curl_cmd[@]}")"
    local RESULT="${?}"
    log "${TEXT}"
    check "${RESULT}" "create dashboard"
    jq -r '.id' <<< "${TEXT}"
}

create_test_dashboard()
{
    local CUSTOMER="${1}"
    local GRAFANA_DATASOURCE="${2}"
    local -n VALUES="$3"
    local GRAFANA_USER_PASSWORD="${4}"
    local GRAFANA_HOST="${5}"
    log ""
    log "create_dashboard"
    dashboard_cmd=("${ROOT}/../server/TestDashboardContent.sh" "${CUSTOMER}_test" "${CUSTOMER}" "${GRAFANA_DATASOURCE}" "${VALUES[@]}")
    log "$(echo "${dashboard_cmd[@]}")"
    local DASHBOARD="$("${dashboard_cmd[@]}")"
    local curl_cmd=(curl -X POST -u "$GRAFANA_USER_PASSWORD" -H "Content-Type: application/json" -d "${DASHBOARD}"  "${GRAFANA_HOST}/api/dashboards/db")
    log "$(echo "${curl_cmd[@]}")"
    local TEXT="$("${curl_cmd[@]}")"
    local RESULT="${?}"
    log "${TEXT}"
    check "${RESULT}" "create dashboard"
    jq -r '.id' <<< "${TEXT}"
}

create_password()
{
    local PASSWORD=$(openssl rand -base64 24)
    log ""
    log "create_pass"
    log "PASSWORD ${PASSWORD}"
    echo "${PASSWORD}"
}

add_user()
{
    local CUSTOMER="${1}"
    local PASSWORD="${2}"
    local GRAFANA_USER_PASSWORD="${3}"
    local GRAFANA_HOST="${4}"

    local JSON="{\"login\":\"${CUSTOMER}\",\"password\":\"${PASSWORD}\"}"
    log "${JSON}"

    log "curl -X POST -u '${GRAFANA_USER_PASSWORD}' -H 'Content-Type: application/json' -d '${JSON}' '${GRAFANA_HOST}/api/admin/users'"
    local TEXT=$(curl -X POST -u "${GRAFANA_USER_PASSWORD}" -H "Content-Type: application/json" -d "${JSON}" "${GRAFANA_HOST}/api/admin/users")
    local RESULT="${?}"
    log "${TEXT}"
    check "${RESULT}" "add user"
    jq -r '.id' <<< "${TEXT}"
}


set_dashboard_rights()
{
    local DASHBOARD_ID="${1}"
    local TAEM_ID="${2}"
    local USER_ID="${3}"
    local GRAFANA_USER_PASSWORD="${4}"
    local GRAFANA_HOST="${5}"


    local JSON="{\"items\":[{\"teamId\":1,\"permission\":1}"
    if [[ -n "${TAEM_ID}" ]]; then
        JSON="${JSON},{\"teamId\":${TAEM_ID},\"permission\":1}"
    fi
    if [[ -n "${USER_ID}" ]]; then
        JSON="${JSON},{\"userId\":${USER_ID},\"permission\":1}"
    fi
    JSON="${JSON}]}"
    log "${JSON}"


    log "curl -X POST -u '${GRAFANA_USER_PASSWORD}' -H 'Content-Type: application/json' -d '${JSON}' '${GRAFANA_HOST}/api/dashboards/id/${DASHBOARD_ID}/permissions'"
    local TEXT=$(curl -X POST -u "${GRAFANA_USER_PASSWORD}" -H "Content-Type: application/json" -d "${JSON}" "${GRAFANA_HOST}/api/dashboards/id/${DASHBOARD_ID}/permissions")
    local RESULT="${?}"
    log "${TEXT}"
    check "${RESULT}" "set dashboard rights"

}


log_csv_line()
{
    local HEADER="Name;Grafana Server Password;Grafana User Id;Group;Pi Password;Server Write Token;Server Read Token;Bucket Raw;Bucket 10s; Bucket 1m; Bucket 10s; Bucket test;"
    local LINE="${CUSTOMER};${PASSWORD};${USER};${GROUP};${PASSWORD};${WRITE_TOKEN};${READ_TOKEN};${DATASOURCE};${BUCKET_ID[0]};${BUCKET_ID[1]};${BUCKET_ID[2]};${BUCKET_ID[3]}"
    local BUILD="${ROOT}/../../build"
    mkdir -p "${BUILD}"
    echo "${LINE}" >> "${BUILD}/Logger.csv"
}

log_command()
{
    local BUILD="${ROOT}/../../build"
    local LINE="./client_install.sh --influxDB ${PASSWORD} --remote https://iot.solarinvert.de:8086 ${BUCKET_ID[@]} ${WRITE_TOKEN} ${INFLUXDB_ORG} --grafana ${INVERTER_COUNT} --inverter 1 /dev/ttyUSB0 --windpulse 10 5 0.4 --modbuslib --provision ${CUSTOMER} ${CUSTOMER}! wlan0 eth0 60 300 300 --shutdown 90 --swapfile 4G"
    mkdir -p "${BUILD}"
    echo "${LINE}" >> "${BUILD}/Command.txt"
    echo "${LINE}"
}

create_buckets()
{
    for ((i=0; i<SIZE; i++)); do
        log ""
        log "create_bucket ${CUSTOMER}${TAIL[$i]} ${RETENTION[$i]}"
        BUCKET_ID[$i]="$(create_bucket "${CUSTOMER}${TAIL[$i]}" "${RETENTION[$i]}")"
    done
}

create_buckets

WRITE_TOKEN="$(write_token)"
READ_TOKEN="$(read_token)"

DATASOURCE="$(datasource "Source${CUSTOMER}" "http://localhost:8085" "solarinvert" "${READ_TOKEN}" "${GRAFANA_USER_PASSWORD}" "${GRAFANA_HOST}")"

PASSWORD="$( create_password )"

USER="$(add_user "${CUSTOMER}" "${PASSWORD}" "${GRAFANA_USER_PASSWORD}" "${GRAFANA_HOST}" )"



DASHBOARD_1="$( create_dashboard      "${CUSTOMER}" wind_only  "${DATASOURCE}" "${INVERTER_COUNT}" GRAFANA_VALUES_WIND_ONLY  "${GRAFANA_USER_PASSWORD}" "${GRAFANA_HOST}" )"
DASHBOARD_2="$( create_dashboard      "${CUSTOMER}" wind       "${DATASOURCE}" "${INVERTER_COUNT}" GRAFANA_VALUES_WIND       "${GRAFANA_USER_PASSWORD}" "${GRAFANA_HOST}" )"
DASHBOARD_3="$( create_dashboard      "${CUSTOMER}" solar      "${DATASOURCE}" "${INVERTER_COUNT}" GRAFANA_VALUES_SOLAR      "${GRAFANA_USER_PASSWORD}" "${GRAFANA_HOST}" )"
DASHBOARD_4="$( create_test_dashboard "${CUSTOMER}"            "${DATASOURCE}"                     GRAFANA_VALUES_SOLAR      "${GRAFANA_USER_PASSWORD}" "${GRAFANA_HOST}" )"

set_dashboard_rights "${DASHBOARD_1}" "${GRAFANA_GROUP}" "${USER}" "${GRAFANA_USER_PASSWORD}" "${GRAFANA_HOST}"
set_dashboard_rights "${DASHBOARD_2}" "${GRAFANA_GROUP}" "${USER}" "${GRAFANA_USER_PASSWORD}" "${GRAFANA_HOST}"
set_dashboard_rights "${DASHBOARD_3}" "${GRAFANA_GROUP}" "${USER}" "${GRAFANA_USER_PASSWORD}" "${GRAFANA_HOST}"
set_dashboard_rights "${DASHBOARD_4}" "${GRAFANA_GROUP}" ""        "${GRAFANA_USER_PASSWORD}" "${GRAFANA_HOST}"

log_csv_line

echo ""
log_command
echo ""
echo "Name:               ${CUSTOMER}"
echo "Password:           ${PASSWORD}"
echo "Grafana user:       ${USER}"
echo "Grafana group:      ${GROUP}"
echo "Server Write Token: ${WRITE_TOKEN}"
echo "Server Read Token:  ${READ_TOKEN}"
echo "Datasource:         ${DATASOURCE}"
