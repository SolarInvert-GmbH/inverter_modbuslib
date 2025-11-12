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

print_help_and_leave()
{
    echo "ussage:"
    echo "${0} [--influxDB PASSWORD | --remote <ENDPOINT> <ORG> <BUCKET> <HASH>] [--grafana] [--inverter <LOOP> <ADDRESS1> [ADDRESS2] [ADDRESS3] [ADDRESS4] [ADDRESS5] <DEVICE> [TIME] [AC_POWER] [DC_VOLTAGE] [OPERATING_STATE] [TEMPERATURE] [AC_VOLTAGE] [ENERGY_PRODUCTION]] [--wind GPIO DURATION FACTOR] [--modbuslib]"
    echo "${0} --help"
    echo "${0} --unistall"
    echo "  --influxDB    Installs InfluxDB. Is in conflict do '--remote'"
    echo "     PASSWORD   The password for the influxDB"
    echo "  --grafana     Installs grafana"
    echo "  --remote      Sets the endpopint and hash for an already installed InfluxDB. Is in conflict do '--influxDB'"
    echo "     ENDPOINT   The address of the influxDB"
    echo "     ORG        The org of the influxDB"
    echo "     BUCKET     The bucket of the influxDB"
    echo "     HASH       The access hash for the influxDB"
    echo "  --inverter    Installs the inverter Service. --remote is needed. List all values you want to read: TIME, AC_POWER, DC_VOLTAGE, OPERATING_STATE, TEMPERATURE, AC_VOLTAGE and ENERGY_PRODUCTION"
    echo "     LOOP       The seconds per loop"
    echo "     ADDRESS<n> The modbus address of the inverter as two hex digets. There can be one to five modbus addresses"
    echo "     DEVICE     The uart device. e.g. '/dev/ttyUSB0'"
    echo "  --wind        Installs the wind Service. --remote is needed"
    echo "     GPIO       The number of the gpio to read wind impulse"
    echo "     DURATION   The measurement duration for the wind measurement"
    echo "     FACTOR     The factor from impulses to speed"
    echo "  --help        Print this help"
    echo "  --unistall    Remove all files that can be created with this script. Do not remove influxdb of grafana"
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

set_param_double_hex()
{
    if [[ ${#} -eq 1 ]]; then
        if [[ ${1} == 1 ]]; then
            echo "Expected ADDRESS1 for --inverter, but got nothing"
            exit 1
        fi
        return 1
    fi
    if [[ ${2} =~ ^[0-9a-fA-F]{2}$ ]]; then
        declare -n REF="PARAMETER_ADDRESS_${1}"
        REF="${2}"
        return 0
    else
        if [[ ${1} == 1 ]]; then
            echo "Expected ADDRESS1 for --inverter, but got ${2}"
            exit 1
        fi
        return 1
    fi
}

set_param_inverter_variabel()
{
    if [[ ${#} -eq 0 ]]; then
        return 1
    fi
    if [[ ${1} == --* ]]; then
        return 1
    fi
    case ${1} in
      TIME)
        PARAMETER_TIME="true"
        PARAMETER_VALUES=( "${PARAMETER_VALUES[@]}" "TIME" )
        return 0
        ;;
      AC_POWER)
        PARAMETER_AC_POWER="true"
        PARAMETER_VALUES=( "${PARAMETER_VALUES[@]}" "AC_POWER" )
        return 0
        ;;
      DC_VOLTAGE)
        PARAMETER_DC_VOLTAGE="true"
        PARAMETER_VALUES=( "${PARAMETER_VALUES[@]}" "DC_VOLTAGE" )
        return 0
        ;;
      OPERATING_STATE)
        PARAMETER_OPERATING_STATE="true"
        PARAMETER_VALUES=( "${PARAMETER_VALUES[@]}" "OPERATING_STATE" )
        return 0
        ;;
      TEMPERATURE)
        PARAMETER_TEMPERATURE="true"
        PARAMETER_VALUES=( "${PARAMETER_VALUES[@]}" "TEMPERATURE" )
        return 0
        ;;
      AC_VOLTAGE)
        PARAMETER_AC_VOLTAGE="true"
        PARAMETER_VALUES=( "${PARAMETER_VALUES[@]}" "AC_VOLTAGE" )
        return 0
        ;;
      ENERGY_PRODUCTION)
        PARAMETER_ENERGY_PRODUCTION="true"
        PARAMETER_VALUES=( "${PARAMETER_VALUES[@]}" "ENERGY_PRODUCTION" )
        return 0
        ;;
      *)
        return 1
      ;;
    esac
}

parse_arguments()
{
    TASK_INFLUX_DB="false"
    PARAMETER_PASSWORD=""
    TASK_REMOTE="false"
    PARAMETER_ENDPOINT=""
    PARAMETER_ORG=""
    PARAMETER_BUCKET=""
    PARAMETER_HASH=""
    TASK_GRAFANA="false"
    TASK_INVERTER="false"
    PARAMETER_LOOP=""
    PARAMETER_ADDRESS_1=""
    PARAMETER_ADDRESS_2=""
    PARAMETER_ADDRESS_3=""
    PARAMETER_ADDRESS_4=""
    PARAMETER_ADDRESS_5=""
    PARAMETER_DEVICE=""
    PARAMETER_TIME="false"
    PARAMETER_AC_POWER="false"
    PARAMETER_DC_VOLTAGE="false"
    PARAMETER_OPERATING_STATE="false"
    PARAMETER_TEMPERATURE="false"
    PARAMETER_AC_VOLTAGE="false"
    PARAMETER_ENERGY_PRODUCTION="false"
    PARAMETER_VALUES=()
    TASK_WIND="false"
    PARAMETER_GPIO=""
    PARAMETER_DURATION=""
    PARAMETER_FACTOR=""
    TASK_MODBUSLIB="false"
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
            set_and_check_for_conflict "INFLUX_TYPE" "INSTALL" "--influxDB" "REMOTE" "--remote"
            check_param_and_set "--influxDB" "PASSWORD" "${@}"
            shift
            TASK_INFLUX_DB="true"
            PARAMETER_ENDPOINT="localhost:8086"
            PARAMETER_ORG="solarinvert"
            PARAMETER_BUCKET="messurement"
            ;;
          --remote)
            set_and_check_for_conflict "INFLUX_TYPE" "REMOTE" "--remote" "INSTALL" "--influxDB"
            TASK_REMOTE="true"
            check_param_and_set "--remote" "ENDPOINT" "${@}"
            shift
            check_param_and_set "--remote" "ORG" "${@}"
            shift
            check_param_and_set "--remote" "BUCKET" "${@}"
            shift
            check_param_and_set "--remote" "HASH" "${@}"
            shift
            ;;
          --grafana)
            TASK_GRAFANA="true"
            ;;
          --inverter)
            TASK_INVERTER="true"
            PARAMETER_LOOP="${1}"
            shift
             for i in {1..5}; do
                if set_param_double_hex "${i}" "${@}"; then
                    shift
                fi
            done
            check_param_and_set "--inverter" "DEVICE" "${@}"
            shift
            VAR_REST=( "$@" )
            while set_param_inverter_variabel "${@}"; do
                shift
            done
            ;;
          --wind)
            TASK_WIND="true"
            check_param_and_set "--wind" "GPIO" "${@}"
            shift
            check_param_and_set "--wind" "DURATION" "${@}"
            shift
            check_param_and_set "--wind" "FACTOR" "${@}"
            shift
            PARAMETER_VALUES=( "WIND" "${PARAMETER_VALUES[@]}" )
            ;;
          --modbuslib)
            TASK_MODBUSLIB="true"
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
    if [[ "${TASK_INVERTER}" == "true" && "${TASK_REMOTE}" == "false" && "${TASK_INFLUX_DB}" == "false" ]]; then
        echo "--inverter needs the --remote or --influxDB flag."
        exit 1
    fi
    if [[ "${TASK_WIND}" == "true" && "${TASK_REMOTE}" == "false" && "${TASK_INFLUX_DB}" == "false" ]]; then
        echo "--wind needs the --remote or --influxDB flag."
        exit 1
    fi
}

task()
{
    SOURCE="${1}"
    TARGET="${2}"
    RETENTION="${3}"
    NAME="${4}"
    echo "option task = {name: \"${NAME}\", every: ${RETENTION}}

from(bucket: \"${SOURCE}\")
  |> range(start: -task.every)
  |> filter(fn: (r) => contains(value: r._measurement, set: [\"time\", \"acpower\", \"dcvoltage\", \"state\", \"temperature\", \"acvoltage\", \"energy\", \"wind\"]))
  |> aggregateWindow(every: ${RETENTION}, fn: mean, createEmpty: false)
  |> to(bucket: \"${TARGET}\")"
}

execute_influxdb()
{
    if [[ "${TASK_INFLUX_DB}" == "true" && ! -f /usr/share/keyrings/influxdata-archive-keyring.gpg ]]; then
        HEAD="InfluxDB: "

        LINES="$(wget -qO- https://repos.influxdata.com/influxdata-archive_compat.key | sudo gpg --dearmor --yes -o /usr/share/keyrings/influxdata-archive-keyring.gpg 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi

        LINES="$(wget -qO- https://repos.influxdata.com/influxdata-archive_compat.key | sudo gpg --dearmor --yes -o /usr/share/keyrings/influxdata-archive-keyring.gpg 2>&1)"
        CODE="${?}"
        if [[ "${CODE}" -eq 0 ]]; then
            status_multy "${LINES}"
        else
            error_multy "${LINES}" 2
        fi

        LINES="$(echo "deb [signed-by=/usr/share/keyrings/influxdata-archive-keyring.gpg] https://repos.influxdata.com/debian stable main" | sudo tee /etc/apt/sources.list.d/influxdata.list 2>&1)"
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

        LINES="$(sudo apt install -y influxdb2 2>&1)"
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

        "${ROOT}"/../server/influx_init.sh "${PARAMETER_PASSWORD}" "${PARAMETER_BUCKET}" "30d" "    InfluxDB_init: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        "${ROOT}"/../server/influx_create_bucket.sh "${PARAMETER_BUCKET}10s" "365d" "    InfluxDB_createBucket: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        "${ROOT}"/../server/influx_create_bucket.sh "${PARAMETER_BUCKET}1m" "3650d" "    InfluxDB_createBucket: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        "${ROOT}"/../server/influx_create_task.sh "${PARAMETER_ORG}" "$(task "${PARAMETER_BUCKET}"    "${PARAMETER_BUCKET}10s" "10s" "Downsample10s")" "    InfluxDB_createTask: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        "${ROOT}"/../server/influx_create_task.sh "${PARAMETER_ORG}" "$(task "${PARAMETER_BUCKET}10s" "${PARAMETER_BUCKET}1m"  "1m" "Downsample1m")" "    InfluxDB_createTask: "
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            exit ${CODE}
        fi

        CONTENT=$("${ROOT}"/../server/influx_create_token.sh "WRITE_TOKEN" "write"  "${PARAMETER_BUCKET}" "    InfluxDB_createToken: ")
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            echo "${CONTENT}"
            exit ${CODE}
        fi

        echo "${CONTENT}"
        LAST=${CONTENT##*$'\n'}
        TOKEN=${LAST##*:}
        PARAMETER_HASH="$(echo "${TOKEN}" | sed 's/^[[:space:]]*//')"

        TASK_REMOTE="true"

        CONTENT=$("${ROOT}"/../server/influx_create_token.sh "READ_TOKEN" "read"  "${PARAMETER_BUCKET},${PARAMETER_BUCKET}10s,${PARAMETER_BUCKET}1m" "    InfluxDB_createToken: ")
        CODE="${?}"
        if [[ "${CODE}" -ne 0 ]]; then
            echo "${CONTENT}"
            exit ${CODE}
        fi

        echo "${CONTENT}"
        LAST=${CONTENT##*$'\n'}
        TOKEN=${LAST##*:}
        READ_TOKEN="$(echo "${TOKEN}" | sed 's/^[[:space:]]*//')"

    fi
}

execute_remote()
{
    if [[ "${TASK_REMOTE}" == "true" ]]; then
        sudo mkdir -p "/etc/solarinvert"
        sudo sh -c "cat > /etc/solarinvert/influxdb.env <<EOF
INFLUX_ENDPOINT=${PARAMETER_ENDPOINT}
INFLUX_BUCKET=${PARAMETER_BUCKET}
INFLUX_HASH=${PARAMETER_HASH}
INFLUX_ORG=${PARAMETER_ORG}
EOF"
    fi
}

number_of_elements()
{
    local COUNT="0"
    for i in {1..5}; do
        local VARNAME="PARAMETER_ADDRESS_${i}"
        local VALUE="${!VARNAME}"
        if [[ -n "$VALUE" ]]; then
            ((COUNT++))
        fi
    done

    echo "${COUNT}"
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

        GRAFANA_USER_PASSWORD="admin:admin"

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

        LINES="$("${ROOT}/../server/grafana_create_dashboard.sh" "${GRAFANA_USER_PASSWORD}" "InverterValues"  "${PARAMETER_BUCKET}" "${DATASOURCE_UID}" "$(number_of_elements)" ${PARAMETER_VALUES[@]})"
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
ID_1=${PARAMETER_ADDRESS_1}
ID_2=${PARAMETER_ADDRESS_2}
ID_3=${PARAMETER_ADDRESS_3}
ID_4=${PARAMETER_ADDRESS_4}
ID_5=${PARAMETER_ADDRESS_5}
PARAMETER_TIME=${PARAMETER_TIME}
PARAMETER_AC_POWER=${PARAMETER_AC_POWER}
PARAMETER_DC_VOLTAGE=${PARAMETER_DC_VOLTAGE}
PARAMETER_OPERATING_STATE=${PARAMETER_OPERATING_STATE}
PARAMETER_TEMPERATURE=${PARAMETER_TEMPERATURE}
PARAMETER_AC_VOLTAGE=${PARAMETER_AC_VOLTAGE}
PARAMETER_ENERGY_PRODUCTION=${PARAMETER_ENERGY_PRODUCTION}
LOOP_TIME_SECONDS=${PARAMETER_LOOP}
EOF"

        sudo cp "${ROOT}/log_solarinvert_inverter.sh"  "/usr/bin/log_solarinvert_inverter.sh"
        sudo cp "${ROOT}/log_solarinvert_name.sh"      "/usr/bin/log_solarinvert_name.sh"
        sudo cp "${ROOT}/SolarInvertName.service"      "/etc/systemd/system/SolarInvertName.service"
        sudo cp "${ROOT}/SolarInvertInverter.service"  "/etc/systemd/system/SolarInvertInverter.service"

        sudo systemctl daemon-reload
        sudo systemctl enable SolarInvertName.service
        sudo systemctl enable SolarInvertInverter.service
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

execute_uninstall()
{
    if [[ "${TASK_UNINSTALL}" == "true" ]]; then
            sudo systemctl disable SolarInvertInverter.service
        sudo systemctl stop SolarInvertInverter.service

        sudo rm -r "/etc/solarinvert"
        sudo rm "/usr/bin/log_solarinvert_inverter.sh"
        sudo rm "/usr/bin/log_solarinvert_name.sh"
        sudo rm "/usr/bin/log_solarinvert_wind.sh"
        sudo rm "/etc/systemd/system/SolarInvertInverter.service"
        sudo rm "/etc/systemd/system/SolarInvertName.service"
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
execute_uninstall

exit 0
