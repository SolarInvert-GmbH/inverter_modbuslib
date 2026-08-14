#!/bin/bash

diagram()
{
    local X="0"
    local W="24"

    local ID="${1}"
    local Y="${2}"
    local NAME="${3}"
    local MIN="${4}"
    local MAX="${5}"
    local RED="${6}"
    local UNIT="${7}"
    local INFLUXDB_BUCKET_TEST="${8}"
    local INFLUXDB_NAME="${9}"
    local INFLUXDB_DATASOURCE="${10}"
    local LINE="${11}"
    local FUNCTION="${12}"
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
    CONTENT="${CONTENT}},\"overrides\":[{\"matcher\":{\"id\":\"byName\",\"options\":\"raw\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":10000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"10s\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":10000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1m\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":60000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1m\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":60000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"10m\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":600000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1h\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":3600000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"6h\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":21600000}]},{\"matcher\":{\"id\":\"byName\",\"options\":\"1d\"},\"properties\":[{\"id\":\"custom.insertNulls\",\"value\":86400000}]}]},\"gridPos\":{\"h\":6,\"w\":${W},\"x\":${X},\"y\":${Y}},\"id\":${ID},\"options\":{\"legend\":{\"calcs\":[],\"displayMode\":\"list\",\"placement\":\"bottom\",\"showLegend\":true},\"tooltip\":{\"hideZeros\":false,\"mode\":\"single\",\"sort\":\"none\"}},\"pluginVersion\":\"12.1.0\",\"targets\":[{\"datasource\":{\"type\":\"influxdb\",\"uid\":\"${INFLUXDB_DATASOURCE}\"},\"hide\":false,\"query\":\"import \\\"experimental\\\"\\n\\nstart = v.timeRangeStart\\nstop = v.timeRangeStop\\n\\nbucket_name = \\\"${INFLUXDB_BUCKET_TEST}\\\"\\n\\nwindow_ns = int(v: v.windowPeriod)\\nwindow = if window_ns <= int(v: 10s) then 10s else v.windowPeriod\\n\\nfield_label = if window_ns <= int(v: 10s) then\\n    \\\"10s\\\"\\nelse if window_ns <= int(v: 1m) then\\n    \\\"1m\\\"\\nelse if window_ns <= int(v: 10m) then\\n    \\\"10m\\\"\\nelse if window_ns <= int(v: 1h) then\\n    \\\"1h\\\"\\nelse if window_ns <= int(v: 6h) then\\n    \\\"6h\\\"\\nelse\\n    \\\"1d\\\"\\n\\ndata = from(bucket: bucket_name)\\n|> range(start: start, stop: stop)\\n|> filter(fn: (r) => r._measurement == \\\"${INFLUXDB_NAME}\\\")\\n|> aggregateWindow(every:window, fn: ${FUNCTION})\\n|> set(key: \\\"_field\\\", value: field_label)\\n|> yield(name: \\\"auto\\\")\",\"refId\": \"A\"}],\"title\":\"${NAME}\",\"type\":\"timeseries\"}"
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

handle_Type()
{
    local RESULT=""
    local NUMBER="${2}"
    local BUCKET="${3}"
    local INFLUXDB_DATASOURCE="${4}"
    local Y="$((NUMBER * 6))"
    case ${1} in
      TIME)
        RESULT="${RESULT}$(diagram "${NUMBER}" "${Y}" "Up Time" "" "" "" "dtdhms" "${BUCKET}test" "time" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      AC_POWER)
        RESULT="${RESULT}$(diagram "${NUMBER}" "${Y}" "AC Power" "" "" "" "watt" "${BUCKET}test" "acpower" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      DC_VOLTAGE)
        RESULT="${RESULT}$(diagram "${NUMBER}" "${Y}" "DC Voltage" "" "" "" "volt" "${BUCKET}test" "dcvoltage" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      OPERATING_STATE)
        RESULT="${RESULT}$(diagram "${NUMBER}" "${Y}" "State" 0 11 "" "" "${BUCKET}test" "state" "${INFLUXDB_DATASOURCE}" "stepBefore" "first")"
        ;;
      TEMPERATURE)
        RESULT="${RESULT}$(diagram "${NUMBER}" "${Y}" "Temperature" "" "" "" "celsius" "${BUCKET}test" "temperature" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      AC_VOLTAGE)
        RESULT="${RESULT}$(diagram "${NUMBER}" "${Y}" "AC Voltage" "" "" "" "volt" "${BUCKET}test" "acvoltage" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      ENERGY_PRODUCTION)
        RESULT="${RESULT}$(diagram "${NUMBER}" "${Y}" "Energy Production" "" "" "" "watth" "${BUCKET}test" "energy" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      FREQUENCY)
        RESULT="${RESULT}$(diagram "${NUMBER}" "${Y}" "Grid Frequency" "" "" "" "rothz" "${BUCKET}test" "frequency" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      WIND)
        RESULT="${RESULT}$(diagram "${NUMBER}" "${Y}" "Wind" "" "" "" "velocityms" "${BUCKET}test" "wind" "${INFLUXDB_DATASOURCE}" "smooth" "mean")"
        ;;
      *)
        echo "handle_Type: '${1}' is not a valid type. [TIME,AC_POWER,DC_VOLTAGE,OPERATING_STATE,TEMPERATURE,AC_VOLTAGE,AC_VOLTAGE,ENERGY_PRODUCTION,FREQUENCY]" 1  >&2
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
while [[ ${#} -gt 0 ]]; do
    CONTENT="${CONTENT}$(handle_Type "${1}" "${I}" "${BUCKET}" "${INFLUXDB_DATASOURCE}")"
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
