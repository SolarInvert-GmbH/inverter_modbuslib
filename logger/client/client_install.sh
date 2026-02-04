#!/bin/bash

SOURCE="$(readlink -f ${BASH_SOURCE[0]})"
ROOT="${SOURCE%/*}"
unset SOURCE
CURRENT="$(pwd)"

exit_and_clean_up()
{
    cd "${CURRENT}"
    exit "${1}"
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

print_help_and_leave()
{
    echo "ussage:"
    echo "${0} [--influxDB PASSWORD [--remote <REMOTE_ENDPOINT> <REMOTE_ID_RAW> <REMOTE_ID_10S> <REMOTE_ID_1M> <REMOTE_ID_TEST> <REMOTE_TOKEN> <REMOTE_ORG_ID>]] [--grafana <COUNT>] [--inverter <LOOP> <DEVICE>] [--wind GPIO DURATION FACTOR] [--modbuslib] [--provision <AP_SSID> <AP_PASS> <WLAN_INTERFACE> <LAN_INTERFACE> <HYSTERESE> <AP_DURATION> <WLAN_RETRY>]"
    echo "${0} --help"
    echo "${0} --unistall"
    echo "  --influxDB          Installs InfluxDB. Is in conflict do '--remote'"
    echo "     PASSWORD         The password for the influxDB"
    echo "  --remote            Create. Needs '--influxDB'"
    echo "     REMOTE_ENDPOINT  The address url of the remote influxDB"
    echo "     REMOTE_ID_RAW    The id of the remote raw bucket."
    echo "     REMOTE_ID_10S    The id of the remote 10s bucket."
    echo "     REMOTE_ID_1M     The id of the remote 1min bucket."
    echo "     REMOTE_ID_TEST   The id of the remote test bucket."
    echo "     REMOTE_TOKEN     The access (write) token for the remote buckets"
    echo "     REMOTE_ORG_ID    The id of the remote organisation"
    echo "  --grafana           Installs grafana"
    echo "     COUNT            The number of inverter in grafana"
    echo "  --inverter          Installs the inverter Service. --remote is needed. List all values you want to read: TIME, AC_POWER, DC_VOLTAGE, OPERATING_STATE, TEMPERATURE, AC_VOLTAGE and ENERGY_PRODUCTION"
    echo "     LOOP             The seconds per loop"
    echo "     DEVICE           The uart device. e.g. '/dev/ttyUSB0'"
    echo "  --wind              Installs the wind Service. --remote is needed"
    echo "     GPIO             The number of the gpio to read wind impulse"
    echo "     DURATION         The measurement duration for the wind measurement"
    echo "     FACTOR           The factor from impulses to speed"
    echo "  --provision         Installs wlan provision service"
    echo "     AP_SSID          The wlan name of the access point"
    echo "     AP_PASS          The wlan password of the access point"
    echo "     WLAN_INTERFACE   The linux wlan interface e.g. 'wlan0'"
    echo "     LAN_INTERFACE    The linux lan interface e.g. 'eth0'"
    echo "     HYSTERESE        The time to wait after ap time"
    echo "     AP_DURATION      The time the access point is active"
    echo "     WLAN_RETRY       The time system trys to connect to existing wlan"
    echo "  --help              Print this help"
    echo "  --unistall          Remove all files that can be created with this script. Do not remove influxdb of grafana"
    exit_and_clean_up "${1}"
}

set_and_check_for_conflict()
{
    if [ -z "${!1}" ]; then
        eval "${1}"=${2}
        return 0
    elif [[ "${!1}" == "${2}" ]]; then
        echo "'${3}' more than once."
    elif [[ "${!1}" == "${4}" ]]; then
        echo "Cant use '${3}' and '${5}' together."
    else
        echo "Internal error while parsing arguments"
    fi
    print_help_and_leave 1
}

check_param_and_set()
{
    if [[ ${#} -eq 2 ]]; then
        echo "Expected ${2} for ${1}, but got nothing"
        exit 1
    fi
    if [[ ${3} == --* ]]; then
        echo "Expected ${2} for ${1}, but got ${3}"
        exit 1
    fi
    declare -n REF="PARAMETER_${2}"
    REF="${3}"
}

parse_arguments()
{
    TASK_INFLUX_DB="false"
    PARAMETER_PASSWORD=""
    TASK_REMOTE="false"
    PARAMETER_REMOTE_ENDPOINT=""
    PARAMETER_REMOTE_ID_RAW=""
    PARAMETER_REMOTE_ID_10S=""
    PARAMETER_REMOTE_ID_1M=""
    PARAMETER_REMOTE_ID_TEST=""
    PARAMETER_REMOTE_TOKEN=""
    PARAMETER_REMOTE_ORG_ID=""
    TASK_GRAFANA="false"
    PARAMETER_COUNT=""
    TASK_INVERTER="false"
    PARAMETER_LOOP=""
    PARAMETER_DEVICE=""
    TASK_WIND="false"
    PARAMETER_GPIO=""
    PARAMETER_DURATION=""
    PARAMETER_FACTOR=""
    TASK_MODBUSLIB="false"
    TASK_PROVISION="false"
    PARAMETER_AP_SSID=""
    PARAMETER_AP_PASS=""
    PARAMETER_WLAN_INTERFACE=""
    PARAMETER_LAN_INTERFACE=""
    PARAMETER_HYSTERESE=""
    PARAMETER_AP_DURATION=""
    PARAMETER_WLAN_RETRY=""
    TASK_UNINSTALL="false"

    if [[ ${#} -eq "1" && ${1} == "--uninstall" ]]; then
        TASK_UNINSTALL="true"
        shift
    fi
    while [[ ${#} -gt 0 ]]; do
        key="${1}"
        shift
        case ${key} in
          -h|--help)
            print_help_and_leave 0
            ;;
          --influxDB)
            check_param_and_set "--influxDB" "PASSWORD" "${@}"
            shift
            TASK_INFLUX_DB="true"
            ;;
          --remote)
            TASK_REMOTE="true"
            check_param_and_set "--remote" "REMOTE_ENDPOINT" "${@}"
            shift
            check_param_and_set "--remote" "REMOTE_ID_RAW" "${@}"
            shift
            check_param_and_set "--remote" "REMOTE_ID_10S" "${@}"
            shift
            check_param_and_set "--remote" "REMOTE_ID_1M" "${@}"
            shift
            check_param_and_set "--remote" "REMOTE_ID_TEST" "${@}"
            shift
            check_param_and_set "--remote" "REMOTE_TOKEN" "${@}"
            shift
            check_param_and_set "--remote" "REMOTE_ORG_ID" "${@}"
            shift
            ;;
          --grafana)
            TASK_GRAFANA="true"
            check_param_and_set "--remote" "COUNT" "${@}"
            shift
            ;;
          --inverter)
            TASK_INVERTER="true"
            PARAMETER_LOOP="${1}"
            shift
            check_param_and_set "--inverter" "DEVICE" "${@}"
            shift
            ;;
          --wind)
            TASK_WIND="true"
            check_param_and_set "--wind" "GPIO" "${@}"
            shift
            check_param_and_set "--wind" "DURATION" "${@}"
            shift
            check_param_and_set "--wind" "FACTOR" "${@}"
            shift
            ;;
          --modbuslib)
            TASK_MODBUSLIB="true"
            ;;
          --provision)
            TASK_PROVISION="true"
            check_param_and_set "--provision" "AP_SSID" "${@}"
            shift
            check_param_and_set "--provision" "AP_PASS" "${@}"
            shift
            check_param_and_set "--provision" "WLAN_INTERFACE" "${@}"
            shift
            check_param_and_set "--provision" "LAN_INTERFACE" "${@}"
            shift
            check_param_and_set "--provision" "HYSTERESE" "${@}"
            shift
            check_param_and_set "--provision" "AP_DURATION" "${@}"
            shift
            check_param_and_set "--provision" "WLAN_RETRY" "${@}"
            shift
            ;;
          --uninstall)
            echo "Only use --uninstall as single option"
            exit 1
            ;;
          *)
            echo "Unknown argument '${key}'"
            print_help_and_leave 1
          ;;
      esac
    done
    if [[ "${TASK_REMOTE}" == "true" && "${TASK_INFLUX_DB}" == "false" ]]; then
        echo "--remote needs the --influxDB flag."
        exit 1
    fi
    if [[ "${TASK_INVERTER}" == "true" && "${TASK_INFLUX_DB}" == "false" ]]; then
        echo "--inverter needs the --influxDB flag."
        exit 1
    fi
    if [[ "${TASK_WIND}" == "true" && "${TASK_REMOTE}" == "false" && "${TASK_INFLUX_DB}" == "false" ]]; then
        echo "--wind needs the --remote or --influxDB flag."
        exit 1
    fi
}

TASK_SET_MEAN="\"time\", \"acpower\", \"dcvoltage\", \"temperature\", \"acvoltage\", \"energy\", \"wind\""
TASK_SET_FIRST="\"state\""

task()
{
    SOURCE="${1}"
    TARGET="${2}"
    RETENTION="${3}"
    NAME="${4}"
    SET="${5}"
    echo "option task = {name: \"${NAME}\", every: ${RETENTION}}

from(bucket: \"${SOURCE}\")
  |> range(start: -task.every)
  |> filter(fn: (r) => contains(value: r._measurement, set: [\"time\", \"acpower\", \"dcvoltage\", \"state\", \"temperature\", \"acvoltage\", \"energy\", \"wind\"]))
  |> aggregateWindow(every: ${RETENTION}, fn: mean, createEmpty: false)
  |> to(bucket: \"${TARGET}\")"
}

BUCKET="messurement"
INFLUX_ENDPOINT="localhost:8086"
GRAFANA_ENDPOINT="http://localhost:3000"
ORG="solarinvert"
REMOTE_NAME="SolarinvertServer"


execute_influxdb()
{
    if [[ "${TASK_INFLUX_DB}" == "true" && ! -f /usr/share/keyrings/influxdata-archive-keyring.gpg ]]; then
        HEAD="InfluxDB: "

        LINES="$(wget -qO- https://repos.influxdata.com/influxdata-archive.key | sudo gpg --dearmor --yes -o /usr/share/keyrings/influxdata-archive-keyring.gpg 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi

        LINES="$(echo "deb [signed-by=/usr/share/keyrings/influxdata-archive-keyring.gpg] https://repos.influxdata.com/debian bookworm stable" | sudo tee /etc/apt/sources.list.d/influxdata.list 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi

        LINES="$(sudo apt update 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi

        LINES="$(sudo DEBIAN_FRONTEND=noninteractive UCF_FORCE_CONFFNEW=1 UCF_FORCE_CONFFMISS=1 apt-get install -y influxdb2 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi

        LINES="$(sudo systemctl start influxdb.service 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi



        "${ROOT}"/../server/influx_init.sh "${PARAMETER_PASSWORD}" "${BUCKET}" "30d" "    InfluxDB_init: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        CONTENT="$(influx bucket list --org solarinvert | grep "${BUCKET}")"
        LAST=${CONTENT##*$'\n'}
        TABLE=${LAST##*:}
        LOCAL_ID_RAW="$(awk '{print $1}' <<< "$TABLE")"

        CONTENT="$("${ROOT}"/../server/influx_create_bucket.sh "${BUCKET}10s" "365d" "    InfluxDB_createBucket: ")"
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            echo "${CONTENT}"
            exit ${CODE}
        fi

        echo "${CONTENT}"
        LAST=${CONTENT##*$'\n'}
        TABLE=${LAST##*:}
        LOCAL_ID_10S="$(awk '{print $1}' <<< "$TABLE")"

        CONTENT="$("${ROOT}"/../server/influx_create_bucket.sh "${BUCKET}1m" "3650d" "    InfluxDB_createBucket: ")"
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            echo "${CONTENT}"
            exit ${CODE}
        fi

        echo "${CONTENT}"
        LAST=${CONTENT##*$'\n'}
        TABLE=${LAST##*:}
        LOCAL_ID_1M="$(awk '{print $1}' <<< "$TABLE")"

        CONTENT="$("${ROOT}"/../server/influx_create_bucket.sh "${BUCKET}test" "12h" "    InfluxDB_createBucket: ")"
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            echo "${CONTENT}"
            exit ${CODE}
        fi

        echo "${CONTENT}"
        LAST=${CONTENT##*$'\n'}
        TABLE=${LAST##*:}
        LOCAL_ID_TEST="$(awk '{print $1}' <<< "$TABLE")"

        "${ROOT}"/../server/influx_create_task.sh "${ORG}" "$(task "${BUCKET}"    "${BUCKET}10s" "10s" "DownsampleMean10s" "${TASK_SET_MEAN}")" "    InfluxDB_createTask: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        "${ROOT}"/../server/influx_create_task.sh "${ORG}" "$(task "${BUCKET}10s" "${BUCKET}1m"  "1m" "DownsampleMean1m" "${TASK_SET_MEAN}")" "    InfluxDB_createTask: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        "${ROOT}"/../server/influx_create_task.sh "${ORG}" "$(task "${BUCKET}"    "${BUCKET}10s" "10s" "DownsampleFirst10s" "${TASK_SET_FIRST}")" "    InfluxDB_createTask: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        "${ROOT}"/../server/influx_create_task.sh "${ORG}" "$(task "${BUCKET}10s" "${BUCKET}1m"  "1m" "DownsampleFirst1m" "${TASK_SET_FIRST}")" "    InfluxDB_createTask: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        CONTENT=$("${ROOT}"/../server/influx_create_token.sh "WRITE_TOKEN" "write"  "${BUCKET},${BUCKET}test" "    InfluxDB_createToken: ")
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            echo "${CONTENT}"
            exit ${CODE}
        fi

        echo "${CONTENT}"
        LAST=${CONTENT##*$'\n'}
        TOKEN=${LAST##*:}
        local HASH="$(echo "${TOKEN}" | sed 's/^[[:space:]]*//')"
        WRITE_TOKEN="${HASH}"

        CONTENT=$("${ROOT}"/../server/influx_create_token.sh "READ_TOKEN" "read"  "${BUCKET},${BUCKET}10s,${BUCKET}1m" "    InfluxDB_createToken: ")
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            echo "${CONTENT}"
            exit ${CODE}
        fi

        echo "${CONTENT}"
        LAST=${CONTENT##*$'\n'}
        TOKEN=${LAST##*:}
        READ_TOKEN="$(echo "${TOKEN}" | sed 's/^[[:space:]]*//')"

        CONTENT=$("${ROOT}"/../server/influx_create_token.sh "READ_TOKEN" "read"  "${BUCKET},${BUCKET}10s,${BUCKET}1m" "    InfluxDB_createToken: ")
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            echo "${CONTENT}"
            exit ${CODE}
        fi

        echo "${CONTENT}"
        LAST=${CONTENT##*$'\n'}
        TOKEN=${LAST##*:}
        READ_TOKEN="$(echo "${TOKEN}" | sed 's/^[[:space:]]*//')"

        sudo mkdir -p "/etc/solarinvert"
        sudo sh -c "cat > /etc/solarinvert/influxdb.env <<EOF
INFLUX_ENDPOINT=${INFLUX_ENDPOINT}
INFLUX_BUCKET=${BUCKET}
INFLUX_HASH=${HASH}
INFLUX_ORG=${ORG}
EOF"
    fi
}

execute_remote()
{
    if [[ "${TASK_REMOTE}" == "true" ]]; then
        CONTENT="$("${ROOT}"/../server/influx_create_remote.sh "${REMOTE_NAME}" "${PARAMETER_REMOTE_ENDPOINT}"  "${PARAMETER_REMOTE_TOKEN}" "${PARAMETER_REMOTE_ORG_ID}" "    InfluxDB_createRemote: ")"
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            echo "${CONTENT}"
            exit ${CODE}
        fi

        echo "${CONTENT}"
        LAST=${CONTENT##*$'\n'}
        REMOTE_ID="$(awk -F: '{print $3}' <<< "${LAST}" | awk '{print $1}')"

        "${ROOT}"/../server/influx_create_replication.sh "toServerRaw" "${REMOTE_ID}"  "${LOCAL_ID_RAW}" "${PARAMETER_REMOTE_ID_RAW}" "${ORG}" "    InfluxDB_createReplication: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        "${ROOT}"/../server/influx_create_replication.sh "toServer10s" "${REMOTE_ID}"  "${LOCAL_ID_10S}" "${PARAMETER_REMOTE_ID_10S}" "${ORG}" "    InfluxDB_createReplication: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        "${ROOT}"/../server/influx_create_replication.sh "toServer1m" "${REMOTE_ID}"  "${LOCAL_ID_1M}" "${PARAMETER_REMOTE_ID_1M}" "${ORG}" "    InfluxDB_createReplication: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        "${ROOT}"/../server/influx_create_replication.sh "toServertest" "${REMOTE_ID}"  "${LOCAL_ID_TEST}" "${PARAMETER_REMOTE_ID_TEST}" "${ORG}" "    InfluxDB_createReplication: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi
    fi
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

execute_grafana()
{
    if [[ "${TASK_GRAFANA}" == "true" ]]; then
        HEAD="Grafana: "
        LINES="$(sudo mkdir -p /etc/apt/keyrings 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi

        LINES="$(curl -fsSL https://packages.grafana.com/gpg.key | sudo gpg --dearmor --yes -o /etc/apt/keyrings/grafana.gpg 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi


        LINES="$(echo "deb [signed-by=/etc/apt/keyrings/grafana.gpg] https://packages.grafana.com/oss/deb stable main" | sudo tee /etc/apt/sources.list.d/grafana.list 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi


        LINES="$(sudo apt-get update 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi

        LINES="$(sudo apt-get install -y grafana 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi

        LINES="$(sudo systemctl start grafana-server.service 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi

        LINES="$(sudo systemctl enable grafana-server.service 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi

        sleep 20

        local GRAFANA_USER_PASSWORD="admin:admin"

        LINES="$("${ROOT}/../server/grafana_create_datasource.sh" "influxdb" "${GRAFANA_USER_PASSWORD}" "http://localhost:8086" "solarinvert" "${READ_TOKEN}" "    InfluxDB_createToken: ")"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi

        LAST=${LINES##*$'\n'}
        JSON=$(echo "${LAST}" | sed 's/^[[:space:]]*InfluxDB_createToken:[[:space:]]*STATUS:[[:space:]]*//')
        DATASOURCE_UID=$(echo "${JSON}" | jq -r '.datasource.uid')

        if [[ "${TASK_WIND}" == "true" ]]; then

            LINES="$(create_dashboard "${BUCKET}" wind_only  "${DATASOURCE_UID}" "${PARAMETER_COUNT}" GRAFANA_VALUES_WIND_ONLY  "${GRAFANA_USER_PASSWORD}" "${GRAFANA_ENDPOINT}")"
            CODE="${?}"
            if [[ "${CODE}" -eq 0 ]]; then
                status_multy "${LINES}"
            else
                error_multy "${LINES}" 2
            fi

            LINES="$(create_dashboard "${BUCKET}" wind       "${DATASOURCE_UID}" "${PARAMETER_COUNT}" GRAFANA_VALUES_WIND       "${GRAFANA_USER_PASSWORD}" "${GRAFANA_ENDPOINT}")"
            CODE="${?}"
            if [[ "${CODE}" -eq 0 ]]; then
                status_multy "${LINES}"
            else
                error_multy "${LINES}" 2
            fi

        fi

        LINES="$(create_dashboard "${BUCKET}" solar      "${DATASOURCE_UID}" "${PARAMETER_COUNT}" GRAFANA_VALUES_SOLAR      "${GRAFANA_USER_PASSWORD}" "${GRAFANA_ENDPOINT}")"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi
    fi
}

execute_inverter()
{
    if [[ "${TASK_INVERTER}" == "true" ]]; then
        sudo mkdir -p "/etc/solarinvert"
        sudo sh -c "cat > /etc/solarinvert/inverter.env <<EOF
UART=${PARAMETER_DEVICE}
PARAMETER_TIME=true
PARAMETER_AC_POWER=true
PARAMETER_DC_VOLTAGE=true
PARAMETER_OPERATING_STATE=true
PARAMETER_TEMPERATURE=true
PARAMETER_AC_VOLTAGE=true
PARAMETER_ENERGY_PRODUCTION=true
LOOP_TIME_SECONDS=true
EOF"

        sudo cp "${ROOT}/log_solarinvert_inverter.sh"  "/usr/bin/log_solarinvert_inverter.sh"
        sudo cp "${ROOT}/SolarInvertInverter.service"  "/etc/systemd/system/SolarInvertInverter.service"

        sudo systemctl daemon-reload
        sudo systemctl enable SolarInvertInverter.service
        sudo systemctl start  SolarInvertInverter.service
    fi

}

execute_wind()
{
    if [[ "${TASK_WIND}" == "true" ]]; then
        sudo mkdir -p "/etc/solarinvert"
        sudo sh -c "cat > /etc/solarinvert/wind.env <<EOF
GIOP=${PARAMETER_GPIO}
MEASUREMENT_DURATION_SECONDS=${PARAMETER_DURATION}
FACTOR=${PARAMETER_FACTOR}
EOF"
        sudo cp "${ROOT}/log_solarinvert_wind.sh"      "/usr/bin/log_solarinvert_wind.sh"
        sudo cp "${ROOT}/SolarInvertWind.service"      "/etc/systemd/system/SolarInvertWind.service"

        sudo systemctl daemon-reload
        sudo systemctl enable SolarInvertWind.service
        sudo systemctl start  SolarInvertWind.service
    fi
}

execute_modbuslib()
{
    if [[ "${TASK_MODBUSLIB}" == "true" ]]; then
        HEAD="Modbuslib: "

        LINES="$("${ROOT}/../../build.sh" --requestonly --install 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi
    fi
}

execute_provision()
{
    if [[ "${TASK_PROVISION}" == "true" ]]; then
        local WIFI_CONNECT_VERSION="v4.11.84"
        local WIFI_CONNECT_WEB="https://github.com/balena-os/wifi-connect/releases/download/${WIFI_CONNECT_VERSION}/"

        local WIFI_CONNECT_UI="/opt/wifi-connect"

        sudo mkdir -p "/etc/solarinvert"
        sudo sh -c "cat > /etc/solarinvert/provision.env <<EOF
AP_SSID=${PARAMETER_AP_SSID}
AP_PASS=${PARAMETER_AP_PASS}
WLAN_INTERFACE=${PARAMETER_WLAN_INTERFACE}
LAN_INTERFACE=${PARAMETER_LAN_INTERFACE}
HYSTERESE=${PARAMETER_HYSTERESE}
AP_DURATION=${PARAMETER_AP_DURATION}
WLAN_RETRY=${PARAMETER_WLAN_RETRY}
UI_PATH=${WIFI_CONNECT_UI}
EOF"
        sudo cp "${ROOT}/wlan_solarinvert_provision.sh" "/usr/bin/wlan_solarinvert_provision.sh"
        sudo cp "${ROOT}/SolarInvertProvision.service"       "/etc/systemd/system/SolarInvertProvision.service"

        sudo mkdir -p "${WIFI_CONNECT_UI}"
        curl -L "${WIFI_CONNECT_WEB}/wifi-connect-ui.tar.gz" | sudo tar xz -C "${WIFI_CONNECT_UI}"
        curl -L "${WIFI_CONNECT_WEB}/wifi-connect-aarch64-unknown-linux-gnu.tar.gz" | sudo tar xz -C "/usr/bin"

        sudo raspi-config nonint do_wifi_country DE

        sudo systemctl daemon-reload
        sudo systemctl enable SolarInvertProvision.service
        sudo systemctl start  SolarInvertProvision.service
    fi
}

execute_uninstall()
{
    if [[ "${TASK_UNINSTALL}" == "true" ]]; then
            sudo systemctl disable SolarInvertInverter.service
        sudo systemctl stop SolarInvertInverter.service

        sudo rm -r "/etc/solarinvert"
        sudo rm "/usr/bin/log_solarinvert_inverter.sh"
        sudo rm "/usr/bin/log_solarinvert_wind.sh"
        sudo rm "/etc/systemd/system/SolarInvertInverter.service"
        sudo rm "/etc/systemd/system/SolarInvertWind.service"

        sudo rm "/usr/local/bin/SendRequest"

        sudo systemctl daemon-reload
    fi
}

parse_arguments "${@}"
execute_modbuslib
execute_influxdb
execute_remote
execute_grafana
execute_inverter
execute_wind
execute_provision
execute_uninstall

if [ -v WRITE_TOKEN ]; then
    echo "WRITE_TOKEN: ${WRITE_TOKEN}"
fi
if [ -v READ_TOKEN ]; then
    echo "READ_TOKEN: ${READ_TOKEN}"
fi

exit 0
