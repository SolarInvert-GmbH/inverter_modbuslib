#!/bin/bash

gauge()
{
    local ID="${1}"
    local X="${2}"
    local Y="${3}"
    local W="${4}"
    local NAME="${5}"
    local MIN="${6}"
    local MAX="${7}"
    local RED="${8}"
    local UNIT="${9}"
    local INFLUXDB_BUCKET="${10}"
    local INFLUXDB_NAME="${11}"
    local INFLUXDB_DATASOURCE="${12}"
    local CONTENT="{\"datasource\":{\"type\":\"influxdb\",\"uid\":\"${INFLUXDB_DATASOURCE}\"},\"fieldConfig\":{\"defaults\":{\"color\":{\"mode\":\"thresholds\"},\"mappings\":[],"
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
    local ID="${1}"
    local X="${2}"
    local Y="${3}"
    local W="${4}"
    local NAME="${5}"
    local UNIT="${6}"
    local INFLUXDB_BUCKET="${7}"
    local INFLUXDB_NAME="${8}"
    local INFLUXDB_DATASOURCE="${9}"
    local CONTENT="{\"id\":${ID},\"type\": \"stat\",\"title\":\"${NAME}\",\"gridPos\":{\"x\":${X},\"y\":${Y},\"h\":6,\"w\":${W}},\"fieldConfig\":{\"defaults\":{\"mappings\":[],\"thresholds\":{\"mode\":\"absolute\",\"steps\":[{\"color\":\"green\",\"value\":null}]},\"color\":{\"mode\":\"thresholds\"}"
    if [ -n "${UNIT}" ]; then
        CONTENT="${CONTENT},\"unit\":\"${UNIT}\""
    fi
    CONTENT="${CONTENT}},\"overrides\":[]},\"pluginVersion\":\"12.1.0\",\"targets\":[{\"refId\":\"A\",\"query\":\"from(bucket: \\\"${INFLUXDB_BUCKET}\\\")\\n  |>range(start: -5m)\\n  |>filter(fn: (r) => r._measurement == \\\"${INFLUXDB_NAME}\\\")\\n  |>yield(name: \\\"_results\\\")\"}],\"datasource\":{\"uid\":\"${INFLUXDB_DATASOURCE}\",\"type\":\"influxdb\"},\"options\":{\"reduceOptions\":{\"values\":false,\"calcs\":[\"lastNotNull\"],\"fields\":\"\"},\"orientation\":\"auto\",\"textMode\":\"auto\",\"wideLayout\":true,\"colorMode\":\"value\",\"graphMode\":\"none\",\"justifyMode\":\"center\",\"showPercentChange\":false,\"percentChangeColorMode\":\"standard\"}}"
    echo "${CONTENT}"
}

diagram()
{
    local ID="${1}"
    local X="${2}"
    local Y="${3}"
    local W="${4}"
    local NAME="${5}"
    local MIN="${6}"
    local MAX="${7}"
    local RED="${8}"
    local UNIT="${9}"
    local INFLUXDB_BUCKET_RAW="${10}"
    local INFLUXDB_BUCKET_10s="${11}"
    local INFLUXDB_BUCKET_1m="${12}"
    local INFLUXDB_NAME="${13}"
    local INFLUXDB_DATASOURCE="${14}"
    local LINE="${15}"
    local FUNCTION="${16}"
    local CONTENT="{\"datasource\":{\"type\":\"influxdb\",\"uid\":\"${INFLUXDB_DATASOURCE}\"},\"fieldConfig\":{\"defaults\":{\"color\":{\"mode\":\"palette-classic\"},\"custom\":{\"axisBorderShow\":false,\"axisCenteredZero\":false,\"axisColorMode\":\"text\",\"axisLabel\":\"\",\"axisPlacement\":\"auto\",\"barAlignment\":0,\"barWidthFactor\":0.6,\"drawStyle\":\"line\",\"fillOpacity\":0,\"gradientMode\":\"none\",\"hideFrom\":{\"legend\":false,\"tooltip\":false,\"viz\":false},\"insertNulls\":3600000,\"lineInterpolation\":\"${LINE}\",\"lineWidth\":1,\"pointSize\":5,\"scaleDistribution\":{\"type\":\"linear\"},\"showPoints\":\"never\",\"spanNulls\":false,\"stacking\":{\"group\":\"A\",\"mode\":\"none\"},\"thresholdsStyle\":{\"mode\":\"off\"}},\"mappings\":[],"
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
    CONTENT="${CONTENT}},\"overrides\":[{\"matcher\":{\"id\":\"byName\",\"options\":\"raw\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":10000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"10s\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":10000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1m\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":60000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1m\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":60000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"10m\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":600000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1h\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":3600000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"6h\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":21600000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1d\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":86400000}]}]},\"gridPos\":{\"h\":6,\"w\":${W},\"x\":${X},\"y\":${Y}},\"id\":${ID},\"options\":{\"legend\":{\"calcs\":[],\"displayMode\":\"list\",\"placement\":\"bottom\",\"showLegend\":true},\"tooltip\":{\"hideZeros\":false,\"mode\":\"single\",\"sort\":\"none\"}},\"pluginVersion\":\"12.1.0\",\"targets\":[{\"datasource\":{\"type\":\"influxdb\",\"uid\":\"${INFLUXDB_DATASOURCE}\"},\"hide\":false,\"query\":\"import \\\"experimental\\\"\\n\\nstart = v.timeRangeStart\\nstop = v.timeRangeStop\\n\\nbucket_name = if start > experimental.subDuration(from: now(), d: 30d) then\\n    \\\"${INFLUXDB_BUCKET_RAW}\\\"\\nelse if start > experimental.subDuration(from: now(), d: 1y) then\\n    \\\"${INFLUXDB_BUCKET_10s}\\\"\\nelse\\n    \\\"${INFLUXDB_BUCKET_1m}\\\"\\n\\nwindow_ns = int(v: v.windowPeriod)\\nwindow = if window_ns <= int(v: 10s) then 10s else v.windowPeriod\\n\\nfield_label = if window_ns <= int(v: 10s) then\\n    \\\"10s\\\"\\nelse if window_ns <= int(v: 1m) then\\n    \\\"1m\\\"\\nelse if window_ns <= int(v: 10m) then\\n    \\\"10m\\\"\\nelse if window_ns <= int(v: 1h) then\\n    \\\"1h\\\"\\nelse if window_ns <= int(v: 6h) then\\n    \\\"6h\\\"\\nelse\\n    \\\"1d\\\"\\n\\ndata = from(bucket: bucket_name)\\n|> range(start: start, stop: stop)\\n|> filter(fn: (r) => r._measurement == \\\"${INFLUXDB_NAME}\\\")\\n|> aggregateWindow(every:window, fn: ${FUNCTION})\\n|> set(key: \\\"_field\\\", value: field_label)\\n|> yield(name: \\\"auto\\\")\",\"refId\": \"A\"}],\"title\":\"${NAME}\",\"type\":\"timeseries\"}"
    cat <<EOF
${CONTENT}
EOF
}

multi_diagram()
{
    local ID="${1}"
    local X="${2}"
    local Y="${3}"
    local W="${4}"
    local NAME="${5}"
    local INFLUXDB_BUCKET_RAW="${6}"
    local INFLUXDB_BUCKET_10s="${7}"
    local INFLUXDB_BUCKET_1m="${8}"
    local INFLUXDB_DATASOURCE="${9}"
    local LINE="${10}"
    shift 10
    local MATCHER_TAIL=""
    local CURVE="["
    local REF_ID="A"
    while (( $# >= 3 )); do
        local INFLUXDB_NAME="${1}"
        local FUNCTION="${2}"
        local UNIT="${3}"
        shift 3
        if [[ "$INFLUXDB_NAME" == "wind" ]]; then
            MATCHER_OPACITY=",{\"id\":\"custom.fillOpacity\",\"value\":30}"
        else
            MATCHER_OPACITY=""
        fi
        MATCHER_TAIL="${MATCHER_TAIL},{\"matcher\":{\"id\":\"byName\",\"options\":\"${INFLUXDB_NAME}\"},\"properties\":[{\"id\":\"min\"},{\"id\":\"max\"},{\"id\":\"unit\",\"value\": \"${UNIT}\"}${MATCHER_OPACITY}]}"
        CURVE="${CURVE}{\"datasource\":{\"type\":\"influxdb\",\"uid\":\"${INFLUXDB_DATASOURCE}\"},\"hide\":false,\"query\":\"import \\\"experimental\\\"\\n\\nstart = v.timeRangeStart\\nstop = v.timeRangeStop\\n\\nbucket_name = if start > experimental.subDuration(from: now(), d: 30d) then\\n    \\\"${INFLUXDB_BUCKET_RAW}\\\"\\nelse if start > experimental.subDuration(from: now(), d: 1y) then\\n    \\\"${INFLUXDB_BUCKET_10s}\\\"\\nelse\\n    \\\"${INFLUXDB_BUCKET_1m}\\\"\\n\\nwindow_ns = int(v: v.windowPeriod)\\nwindow = if window_ns <= int(v: 10s) then 10s else v.windowPeriod\\n\\nfield_label = if window_ns <= int(v: 10s) then\\n    \\\"10s\\\"\\nelse if window_ns <= int(v: 1m) then\\n    \\\"1m\\\"\\nelse if window_ns <= int(v: 10m) then\\n    \\\"10m\\\"\\nelse if window_ns <= int(v: 1h) then\\n    \\\"1h\\\"\\nelse if window_ns <= int(v: 6h) then\\n    \\\"6h\\\"\\nelse\\n    \\\"1d\\\"\\n\\ndata = from(bucket: bucket_name)\\n|> range(start: start, stop: stop)\\n|> filter(fn: (r) => r._measurement == \\\"${INFLUXDB_NAME}\\\")\\n|> aggregateWindow(every:window, fn: ${FUNCTION})\\n|> set(key: \\\"_field\\\", value: field_label)\\n|> set(key: \\\"_field\\\", value: \\\"${INFLUXDB_NAME}\\\")\\n|> yield(name: \\\"auto\\\")\",\"refId\": \"${REF_ID}\"}"
        if (( $# >= 3 )); then
            CURVE="${CURVE},"
        fi
        REF_ID=$(printf "%b" "$(printf '\\x%02x' "$(( $(printf '%d' "'${REF_ID}") + 1 ))")")
    done
    CURVE="${CURVE}]"

    local CONTENT="{\"datasource\":{\"type\":\"influxdb\",\"uid\":\"${INFLUXDB_DATASOURCE}\"},\"fieldConfig\":{\"defaults\":{\"color\":{\"mode\":\"palette-classic\"}},\"custom\":{\"axisBorderShow\":false,\"axisCenteredZero\":false,\"axisColorMode\":\"text\",\"axisLabel\":\"\",\"axisPlacement\":\"auto\",\"barAlignment\":0,\"barWidthFactor\":0.6,\"drawStyle\":\"line\",\"fillOpacity\":0,\"gradientMode\":\"none\",\"hideFrom\":{\"legend\":false,\"tooltip\":false,\"viz\":false},\"insertNulls\":3600000,\"lineInterpolation\":\"${LINE}\",\"lineWidth\":1,\"pointSize\":5,\"scaleDistribution\":{\"type\":\"linear\"},\"showPoints\":\"never\",\"spanNulls\":false,\"stacking\":{\"group\":\"A\",\"mode\":\"none\"},\"thresholdsStyle\":{\"mode\":\"off\"}},\"mappings\":[],\"thresholds\":{\"mode\":\"absolute\",\"steps\":[{\"color\":\"green\",\"value\":null}]},\"overrides\":[{\"matcher\":{\"id\":\"byName\",\"options\":\"raw\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":10000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"10s\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":10000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1m\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":60000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1m\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":60000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"10m\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":600000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1h\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":3600000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"6h\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":21600000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1d\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":86400000}]}${MATCHER_TAIL}]},\"gridPos\":{\"h\":6,\"w\":${W},\"x\":${W},\"y\":${Y}},\"id\":${ID},\"options\":{\"legend\":{\"calcs\":[],\"displayMode\":\"list\",\"placement\":\"bottom\",\"showLegend\":true},\"tooltip\":{\"hideZeros\":false,\"mode\":\"single\",\"sort\":\"none\"}},\"pluginVersion\":\"12.1.0\",\"targets\":${CURVE},\"title\":\"${NAME}\",\"type\":\"timeseries\"}"
    cat <<EOF
${CONTENT}
EOF
}

dashboard_head()
{
    local CONTENT="{\"dashboard\":{\"annotations\":{\"list\":[{\"builtIn\":1,\"datasource\":{\"type\":\"grafana\",\"uid\":\"-- Grafana --\"},\"enable\":true,\"hide\":true,\"iconColor\":\"rgba(0, 211, 255, 1)\",\"name\":\"Annotations & Alerts\",\"type\":\"dashboard\"}]},\"editable\":true,\"fiscalYearStartMonth\":0,\"graphTooltip\":0,\"id\":null,\"links\":[],\"panels\":["
    cat <<EOF
${CONTENT}
EOF
}

dashboard_tail()
{
    local NAME="${1}"
    local CONTENT="],\"preload\":false,\"schemaVersion\":41,\"tags\":[],\"templating\":{\"list\":[]},\"time\":{\"from\":\"now-30m\",\"to\":\"now\"},\"timepicker\":{},\"timezone\":\"browser\",\"title\":\"${NAME}\",\"permissions\":[{\"role\":\"Admin\",\"permission\":4}]},\"folderId\": 0,\"overwrite\": true}"
    cat <<EOF
${CONTENT}
EOF
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
    local RESULT=""
    local NUMBER="${2}"
    local BUCKET="${3}"
    local INFLUXDB_DATASOURCE="${4}"
    local ELEMENTS="${5}"
    local Y="$((NUMBER * 6))"
    local ID_1="$((NUMBER * 2 + 0))"
    local ID_2="$((NUMBER * 2 + 1))"
    case ${1} in
      TIME)
        local W_1="$(get_small_width "${ELEMENTS}")"
        local W_2="$((24 - W_1))"
        RESULT="${RESULT}$(statt   "${ID_1}"    0     "${Y}" "${W_1}" "Up Time"          "dtdhms" "${BUCKET}"                              "time" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "Up Time" "" "" "" "dtdhms" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "time" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      AC_POWER)
        local W_1="$(get_small_width "${ELEMENTS}")"
        local W_2="$((24 - W_1))"
        RESULT="${RESULT}$(gauge   "${ID_1}"    0     "${Y}" "${W_1}" "AC Power" "" "" "" "watt" "${BUCKET}"                              "acpower" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "AC Power" "" "" "" "watt" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "acpower" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      DC_VOLTAGE)
        local W_1="$(get_small_width "${ELEMENTS}")"
        local W_2="$((24 - W_1))"
        RESULT="${RESULT}$(gauge   "${ID_1}"    0     "${Y}" "${W_1}" "DC Voltage" "" "" "" "volt" "${BUCKET}"                              "dcvoltage" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "DC Voltage" "" "" "" "volt" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "dcvoltage" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      OPERATING_STATE)
        local W_1="$(get_small_width "${ELEMENTS}")"
        local W_2="$((24 - W_1))"
        RESULT="${RESULT}$(statt   "${ID_1}"    0     "${Y}" "${W_1}" "State"         "" "${BUCKET}"                              "state" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "State" 0 11 "" "" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "state" "${INFLUXDB_DATASOURCE}" "stepBefore" "first")"
        ;;
      TEMPERATURE)
        local W_1="$(get_small_width "${ELEMENTS}")"
        local W_2="$((24 - W_1))"
        RESULT="${RESULT}$(gauge   "${ID_1}"    0     "${Y}" "${W_1}" "Temperature" "" "" "" "celsius" "${BUCKET}"                              "temperature" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "Temperature" "" "" "" "celsius" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "temperature" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      AC_VOLTAGE)
        local W_1="$(get_small_width "${ELEMENTS}")"
        local W_2="$((24 - W_1))"
        RESULT="${RESULT}$(gauge   "${ID_1}"    0     "${Y}" "${W_1}" "AC Voltage" "" "" "" "volt" "${BUCKET}"                              "acvoltage" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "AC Voltage" "" "" "" "volt" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "acvoltage" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      ENERGY_PRODUCTION)
        local W_1="$(get_small_width "${ELEMENTS}")"
        local W_2="$((24 - W_1))"
        RESULT="${RESULT}$(statt   "${ID_1}"    0     "${Y}" "${W_1}" "Energy Production"          "watth" "${BUCKET}"                              "energy" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "Energy Production" "" "" "" "watth" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "energy" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      WIND_SINGLE)
        local W_1="$(get_small_width "1")"
        local W_2="$((24 - W_1))"
        RESULT="${RESULT}$(gauge   "${ID_1}"    0     "${Y}" "${W_1}" "Wind" "" "" "" "velocityms" "${BUCKET}"                              "wind" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "Wind" "" "" "" "velocityms" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "wind" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      WIND_MULTI)
        local W_1="$(get_small_width "1")"
        local W_2="$((24 - W_1))"
        RESULT="${RESULT}$(gauge   "${ID_1}"    0     "${Y}" "${W_1}" "Wind" "" "" "" "velocityms" "${BUCKET}"                              "wind" "${INFLUXDB_DATASOURCE}"),"
        RESULT="${RESULT}$(multi_diagram "${ID_2}" "${W_1}" "${Y}" "${W_2}" "Wind" "${BUCKET}" "${BUCKET}10s" "${BUCKET}1m" "${INFLUXDB_DATASOURCE}" "smooth" "wind" "mean" "velocityms" "acpower" "mean" "watt" "dcvoltage" "mean" "volt" )"
        ;;
      *)
        echo "handle_Type: '${1}' is not a valid type. [TIME,AC_POWER,DC_VOLTAGE,OPERATING_STATE,TEMPERATURE,AC_VOLTAGE,AC_VOLTAGE,ENERGY_PRODUCTION]" 1  >&2
        exit 1
      ;;
    esac
    cat <<EOF
${RESULT}
EOF
}


CONTENT="$(dashboard_head)"
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
    CONTENT="${CONTENT}$(handle_Type "${1}" "${I}" "${BUCKET}" "${INFLUXDB_DATASOURCE}" "${ELEMENTS}")"
    shift
    if [[ ${#} -gt 0 ]]; then
        CONTENT="${CONTENT},"
    fi
    I="$((I + 1))"
done
CONTENT="${CONTENT}$(dashboard_tail "${NAME}")"
cat <<EOF
${CONTENT}
EOF
