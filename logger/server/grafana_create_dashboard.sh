#!/bin/bash

HEAD=""
VAR_USER_PASSWORD=""
VAR_NAME=""
VAR_BUCKET=""
VAR_DATASOURCE=""
VAR_NUMBER_ELEMENTS=""
VAR_REST=()

status()
{
    echo "${HEAD}STATUS: ${1}"
}

error()
{
    echo "${HEAD}ERROR: ${1}" >&2
    exit ${2}
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

print_help()
{
    echo "${0} USER:PASSWORD NAME BUCKET DATASOURCE NUMBER_ELEMENTS [WIND] [TIME] [AC_POWER] [DC_VOLTAGE] [OPERATING_STATE] [TEMPERATURE] [AC_VOLTAGE] [ENERGY_PRODUCTION]"
    echo "   USER:PASSWORD -- The user and password to create the token, seperated by :."
    echo "   NAME            -- The name of the dashboard."
    echo "   BUCKET          -- The name of the (raw) bucket."
    echo "   DATASOURCE      -- The hash of the datasource."
    echo "   NUMBER_ELEMENTS -- The number of inveters."
    echo "   VALUES          -- The values to show. Order is important. Same order (top to bottom) is used in dashboard."
    exit ${1}
}

check_for_help()
{
    if [[ $# -gt 0 && ( "${1}" == "h" || "${1}" == "-h" || "${1}" == "--h" || "${1}" == "help" || "${1}" == "-help" || "${1}" == "--help" ) ]]; then
        echo "ussage:"
        print_help 0
    fi
}

check_arg()
{
    if [[ $# -ge 7 ]]; then
        VAR_USER_PASSWORD="${1}"
        shift
        VAR_NAME="${1}"
        shift
        VAR_BUCKET="${1}"
        shift
        VAR_DATASOURCE="${1}"
        shift
        VAR_NUMBER_ELEMENTS="${1}"
        shift

        VAR_REST=( "$@" )

        status "Grafana create dashboard:"
        status "   user:password: ${VAR_USER_PASSWORD}"
        status "   name:         '${VAR_NAME}'"
        status "   bucket:        ${VAR_BUCKET}"
        status "   datashource:   ${VAR_DATASOURCE}"
        status "   elements:      ${VAR_NUMBER_ELEMENTS}"
        status "   values:"
        for r in "${VAR_REST[@]}"; do
            status "      $r"
        done
    else
        echo "Need at least seven parameter:"
        print_help 1
    fi
}

token()
{
    status "InfluxDB token"

    LINES=$(curl -X POST -u "${USER_PASSWORD}" -H "Content-Type: application/json" -d "{\"name\":\"${NAME}\",\"role\":\"${TYPE}\"}" http://localhost:3000/api/auth/keys)
    CODE="${?}"

    if [[ "${CODE}" -eq 0 ]]; then
        status_multy "${LINES}"
    else
        error_multy "${LINES}" 3
    fi

    TOKEN=$(echo -e "$LINES" | grep "\"key\"" | cut -d'"' -f4)

    status "Token: ${TOKEN}"
}

gauge()
{
    ID="${1}"
    X="${2}"
    Y="${3}"
    W="${4}"
    NAME="${5}"
    MIN="${6}"
    MAX="${7}"
    RED="${8}"
    UNIT="${9}"
    INFLUXDB_BUCKET="${10}"
    INFLUXDB_NAME="${11}"
    INFLUXDB_DATASOURCE="${12}"
    CONTENT="{\"datasource\":{\"type\":\"influxdb\",\"uid\":\"${INFLUXDB_DATASOURCE}\"},\"fieldConfig\":{\"defaults\":{\"color\":{\"mode\":\"thresholds\"},\"mappings\":[],"
    if [ -n "${MAX}" ]; then
        CONTENT="${CONTENT}\"max\":${MAX},"
    fi
    if [ -n "${MIN}" ]; then
        CONTENT="${CONTENT}\"min\":${MIN},"
    fi
    CONTENT="${CONTENT}\"thresholds\":{\"mode\":\"absolute\",\"steps\":[{\"color\":\"green\",\"value\":"
    if [ -n "${RED}" ]; then
        CONTENT="${CONTENT}${MIN}},{\"color\":\"red\",\"value\":${RED}"
    else
        CONTENT="${CONTENT}null"
    fi
    CONTENT="${CONTENT}}]}"
    if [ -n "${UNIT}" ]; then
        CONTENT="${CONTENT},\"unit\":\"${UNIT}\""
    fi
    CONTENT="${CONTENT}},\"overrides\":[]},\"gridPos\":{\"h\":6,\"w\":${W},\"x\":${X},\"y\":${Y}},\"id\":${ID},\"options\":{\"minVizHeight\":75,\"minVizWidth\":75,\"orientation\":\"auto\",\"reduceOptions\":{\"calcs\":[\"last\"],\"fields\":\"\",\"values\":false},\"showThresholdLabels\":false,\"showThresholdMarkers\":true,\"sizing\":\"auto\"},\"pluginVersion\":\"12.1.0\",\"targets\":[{\"query\":\"from(bucket: \\\"${INFLUXDB_BUCKET}\\\")\\n  |>range(start: -5m)\\n  |>filter(fn: (r) => r._measurement == \\\"${INFLUXDB_NAME}\\\")\\n  |>yield(name: \\\"_results\\\")\",\"refId\":\"A\"}],\"title\":\"${NAME}\",\"type\":\"gauge\"}"
    echo "${CONTENT}"
}

statt()
{
    ID="${1}"
    X="${2}"
    Y="${3}"
    W="${4}"
    NAME="${5}"
    UNIT="${6}"
    INFLUXDB_BUCKET="${7}"
    INFLUXDB_NAME="${8}"
    INFLUXDB_DATASOURCE="${9}"
    CONTENT="{\"id\":${ID},\"type\": \"stat\",\"title\":\"${NAME}\",\"gridPos\":{\"x\":${X},\"y\":${Y},\"h\":6,\"w\":${W}},\"fieldConfig\":{\"defaults\":{\"mappings\":[],\"thresholds\":{\"mode\":\"absolute\",\"steps\":[{\"color\":\"green\",\"value\":null}]},\"color\":{\"mode\":\"thresholds\"}"
    if [ -n "${UNIT}" ]; then
        CONTENT="${CONTENT},\"unit\":\"${UNIT}\""
    fi
    CONTENT="${CONTENT}},\"overrides\":[]},\"pluginVersion\":\"12.1.0\",\"targets\":[{\"refId\":\"A\",\"query\":\"from(bucket: \\\"${INFLUXDB_BUCKET}\\\")\\n  |>range(start: -5m)\\n  |>filter(fn: (r) => r._measurement == \\\"${INFLUXDB_NAME}\\\")\\n  |>yield(name: \\\"_results\\\")\"}],\"datasource\":{\"uid\":\"${INFLUXDB_DATASOURCE}\",\"type\":\"influxdb\"},\"options\":{\"reduceOptions\":{\"values\":false,\"calcs\":[\"lastNotNull\"],\"fields\":\"\"},\"orientation\":\"auto\",\"textMode\":\"auto\",\"wideLayout\":true,\"colorMode\":\"value\",\"graphMode\":\"none\",\"justifyMode\":\"center\",\"showPercentChange\":false,\"percentChangeColorMode\":\"standard\"}}"
    echo "${CONTENT}"
}

diagram()
{
    ID="${1}"
    X="${2}"
    Y="${3}"
    W="${4}"
    NAME="${5}"
    MIN="${6}"
    MAX="${7}"
    RED="${8}"
    UNIT="${9}"
    INFLUXDB_BUCKET_RAW="${10}"
    INFLUXDB_BUCKET_10s="${11}"
    INFLUXDB_BUCKET_1m="${12}"
    INFLUXDB_NAME="${13}"
    INFLUXDB_DATASOURCE="${14}"
    CONTENT="{\"datasource\":{\"type\":\"influxdb\",\"uid\":\"${INFLUXDB_DATASOURCE}\"},\"fieldConfig\":{\"defaults\":{\"color\":{\"mode\":\"palette-classic\"},\"custom\":{\"axisBorderShow\":false,\"axisCenteredZero\":false,\"axisColorMode\":\"text\",\"axisLabel\":\"\",\"axisPlacement\":\"auto\",\"barAlignment\":0,\"barWidthFactor\":0.6,\"drawStyle\":\"line\",\"fillOpacity\":0,\"gradientMode\":\"none\",\"hideFrom\":{\"legend\":false,\"tooltip\":false,\"viz\":false},\"insertNulls\":3600000,\"lineInterpolation\":\"linear\",\"lineWidth\":1,\"pointSize\":5,\"scaleDistribution\":{\"type\":\"linear\"},\"showPoints\":\"never\",\"spanNulls\":false,\"stacking\":{\"group\":\"A\",\"mode\":\"none\"},\"thresholdsStyle\":{\"mode\":\"off\"}},\"mappings\":[],"
    if [ -n "${MAX}" ]; then
        CONTENT="${CONTENT}\"max\":${MAX},"
    fi
    if [ -n "${MIN}" ]; then
        CONTENT="${CONTENT}\"min\":${MIN},"
    fi
    CONTENT="${CONTENT}\"thresholds\":{\"mode\":\"absolute\",\"steps\":[{\"color\":\"green\",\"value\":"
    if [ -n "${RED}" ]; then
        CONTENT="${CONTENT}${MIN}},{\"color\":\"red\",\"value\":${RED}"
    else
        CONTENT="${CONTENT}null"
    fi
    CONTENT="${CONTENT}}]}"
    if [ -n "${UNIT}" ]; then
        CONTENT="${CONTENT},\"unit\":\"${UNIT}\""
    fi
    CONTENT="${CONTENT}},\"overrides\":[{\"matcher\":{\"id\":\"byName\",\"options\":\"raw\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":10000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"10s\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":10000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1m\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":60000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1m\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":60000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"10m\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":600000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1h\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":3600000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"6h\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":21600000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1d\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":86400000}]}]},\"gridPos\":{\"h\":6,\"w\":${W},\"x\":${X},\"y\":${Y}},\"id\":${ID},\"options\":{\"legend\":{\"calcs\":[],\"displayMode\":\"list\",\"placement\":\"bottom\",\"showLegend\":true},\"tooltip\":{\"hideZeros\":false,\"mode\":\"single\",\"sort\":\"none\"}},\"pluginVersion\":\"12.1.0\",\"targets\":[{\"datasource\":{\"type\":\"influxdb\",\"uid\":\"${INFLUXDB_DATASOURCE}\"},\"hide\":false,\"query\":\"import \\\"experimental\\\"\\n\\nstart = v.timeRangeStart\\nstop = v.timeRangeStop\\n\\nbucket_name = if start > experimental.subDuration(from: now(), d: 30d) then\\n    \\\"${INFLUXDB_BUCKET_RAW}\\\"\\nelse if start > experimental.subDuration(from: now(), d: 1y) then\\n    \\\"${INFLUXDB_BUCKET_10s}\\\"\\nelse\\n    \\\"${INFLUXDB_BUCKET_1m}\\\"\\n\\nwindow_ns = int(v: v.windowPeriod)\\nwindow = if window_ns <= int(v: 10s) then 10s else v.windowPeriod\\n\\nfield_label = if window_ns <= int(v: 10s) then\\n    \\\"10s\\\"\\nelse if window_ns <= int(v: 1m) then\\n    \\\"1m\\\"\\nelse if window_ns <= int(v: 10m) then\\n    \\\"10m\\\"\\nelse if window_ns <= int(v: 1h) then\\n    \\\"1h\\\"\\nelse if window_ns <= int(v: 6h) then\\n    \\\"6h\\\"\\nelse\\n    \\\"1d\\\"\\n\\ndata = from(bucket: bucket_name)\\n|> range(start: start, stop: stop)\\n|> filter(fn: (r) => r._measurement == \\\"${INFLUXDB_NAME}\\\")\\n|> aggregateWindow(every:window, fn: mean)\\n|> set(key: \\\"_field\\\", value: field_label)\\n|> yield(name: \\\"auto\\\")\",\"refId\": \"A\"}],\"title\":\"${NAME}\",\"type\":\"timeseries\"}"
    echo "${CONTENT}"
}

dashboard_head()
{
    CONTENT="{\"dashboard\":{\"annotations\":{\"list\":[{\"builtIn\":1,\"datasource\":{\"type\":\"grafana\",\"uid\":\"-- Grafana --\"},\"enable\":true,\"hide\":true,\"iconColor\":\"rgba(0, 211, 255, 1)\",\"name\":\"Annotations & Alerts\",\"type\":\"dashboard\"}]},\"editable\":true,\"fiscalYearStartMonth\":0,\"graphTooltip\":0,\"id\":null,\"links\":[],\"panels\":["
    echo "${CONTENT}"
}

dashboard_tail()
{
    NAME="${1}"
    CONTENT="],\"preload\":false,\"schemaVersion\":41,\"tags\":[],\"templating\":{\"list\":[]},\"time\":{\"from\":\"now-30m\",\"to\":\"now\"},\"timepicker\":{},\"timezone\":\"browser\",\"title\":\"${NAME}\",\"permissions\":[{\"role\":\"Admin\",\"permission\":4}]},\"folderId\": 0,\"overwrite\": true}"
    echo "${CONTENT}"
}

get_small_width()
{
    case ${1} in
      1)
        echo "3"
        ;;
      2)
        echo "6"
        ;;
      3)
        echo "8"
        ;;
      4)
        echo "10"
        ;;
      *)
        echo "11"
        ;;
    esac
}

handle_Type()
{
    RESULT=""
    NUMBER="${2}"
    BUCKET="${3}"
    INFLUXDB_DATASOURCE="${4}"
    ELEMENTS="${5}"
    Y="$((NUMBER * 6))"
    ID_1="$((NUMBER * 2 + 0))"
    ID_2="$((NUMBER * 2 + 1))"
    case ${1} in
      TIME)
        W_1="$(get_small_width "${ELEMENTS}")"
        W_2="$((24 - W_1))"
        RESULT="${RESULT}$(statt   "${ID_1}"    0     "${Y}" "${W_1}" "Up Time"          "dtdhms" "${BUCKET}"                              "time" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "Up Time" "" "" "" "dtdhms" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "time" "${INFLUXDB_DATASOURCE}")"
        ;;
      AC_POWER)
        W_1="$(get_small_width "${ELEMENTS}")"
        W_2="$((24 - W_1))"
        RESULT="${RESULT}$(gauge   "${ID_1}"    0     "${Y}" "${W_1}" "AC Power" 0 "" "" "watt" "${BUCKET}"                              "acpower" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "AC Power" 0 "" "" "watt" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "acpower" "${INFLUXDB_DATASOURCE}")"
        ;;
      DC_VOLTAGE)
        W_1="$(get_small_width "${ELEMENTS}")"
        W_2="$((24 - W_1))"
        RESULT="${RESULT}$(gauge   "${ID_1}"    0     "${Y}" "${W_1}" "DC Voltage" "" "" "" "volt" "${BUCKET}"                              "dcvoltage" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "DC Voltage" "" "" "" "volt" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "dcvoltage" "${INFLUXDB_DATASOURCE}")"
        ;;
      OPERATING_STATE)
        W_1="$(get_small_width "${ELEMENTS}")"
        W_2="$((24 - W_1))"
        RESULT="${RESULT}$(statt   "${ID_1}"    0     "${Y}" "${W_1}" "State"         "" "${BUCKET}"                              "state" "${INFLUXDB_DATASOURCE}"),"
        #TODO diagram is not the right tool
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "State" 0 11 "" "" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "state" "${INFLUXDB_DATASOURCE}")"
        ;;
      TEMPERATURE)
        W_1="$(get_small_width "${ELEMENTS}")"
        W_2="$((24 - W_1))"
        RESULT="${RESULT}$(gauge   "${ID_1}"    0     "${Y}" "${W_1}" "Temperature" 10 100 80 "celsius" "${BUCKET}"                              "temperature" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "Temperature" 10 100 80 "celsius" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "temperature" "${INFLUXDB_DATASOURCE}")"
        ;;
      AC_VOLTAGE)
        W_1="$(get_small_width "${ELEMENTS}")"
        W_2="$((24 - W_1))"
        RESULT="${RESULT}$(gauge   "${ID_1}"    0     "${Y}" "${W_1}" "AC Voltage" "" "" "" "volt" "${BUCKET}"                              "acvoltage" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "AC Voltage" "" "" "" "volt" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "acvoltage" "${INFLUXDB_DATASOURCE}")"
        ;;
      ENERGY_PRODUCTION)
        W_1="$(get_small_width "${ELEMENTS}")"
        W_2="$((24 - W_1))"
        RESULT="${RESULT}$(statt   "${ID_1}"    0     "${Y}" "${W_1}" "Energy Production"          "watth" "${BUCKET}"                              "energy" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "Energy Production" "" "" "" "watth" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "energy" "${INFLUXDB_DATASOURCE}")"
        ;;
      WIND)
        W_1="$(get_small_width "1")"
        W_2="$((24 - W_1))"
        RESULT="${RESULT}$(gauge   "${ID_1}"    0     "${Y}" "${W_1}" "Wind" 0 45 "" "velocityms" "${BUCKET}"                              "wind" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "Wind" 0 45 "" "velocityms" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "wind" "${INFLUXDB_DATASOURCE}")"
        ;;
      *)
        error "handle_Type: '${1}' is not a valid type. [TIME,AC_POWER,DC_VOLTAGE,OPERATING_STATE,TEMPERATURE,AC_VOLTAGE,AC_VOLTAGE,ENERGY_PRODUCTION]" 1
      ;;
    esac
    echo "${RESULT}"
}

dashboard()
{
    C="$(dashboard_head)"
    I="1"
    NAME="${1}"
    shift
    BUCKET="${1}"
    shift
    INFLUXDB_DATASOURCE="${1}"
    shift
    ELEMENTS="${1}"
    shift
    while [[ ${#} -gt 0 ]]; do
        C="${C}$(handle_Type "${1}" "${I}" "${BUCKET}" "${INFLUXDB_DATASOURCE}" "${ELEMENTS}")"
        shift
        if [[ ${#} -gt 0 ]]; then
            C="${C},"
        fi
        I="$((I + 1))"
    done
    DASHBOARD="${C}$(dashboard_tail "${NAME}")"
    echo "${C}"
}


send()
{
    status "Grafana dashboard"

    LINES=$(curl -X POST -u "${VAR_USER_PASSWORD}" -H "Content-Type: application/json" -d "${DASHBOARD}" http://localhost:3000/api/dashboards/db)
    CODE="${?}"

    if [[ "${CODE}" -eq 0 ]]; then
        status_multy "${LINES}"
    else
        error_multy "${LINES}" 3
    fi
}

check_for_help "${@}"
check_arg "${@}"
dashboard "${VAR_NAME}" "${VAR_BUCKET}" "${VAR_DATASOURCE}" "${VAR_NUMBER_ELEMENTS}" "${VAR_REST[@]}"
send
