#!/bin/bash

AP_SSID="${1}"
AP_PASS="${2}"
WLAN_INTERFACE="${3}"
LAN_INTERFACE="${4}"
HYSTERESE="${5}"
AP_DURATION="${6}"
WLAN_RETRY="${7}"
UI_PATH="${8}"

start()
{
    echo "Start"
    echo "   AP_SSID:        ${AP_SSID}"
    echo "   AP_PASS:        ${AP_PASS}"
    echo "   WLAN_INTERFACE: ${WLAN_INTERFACE}"
    echo "   LAN_INTERFACE:  ${LAN_INTERFACE}"
    echo "   HYSTERESE:      ${HYSTERESE}"
    echo "   AP_DURATION:    ${AP_DURATION}"
    echo "   WLAN_RETRY:     ${WLAN_RETRY}"
    echo "   UI_PATH:        ${UI_PATH}"
}

check_for_lan()
{
    if nmcli device status | grep -q "^$LAN_INTERFACE.*connected"; then
        echo "LAN is conneced. Exit."
        exit 0
    else
        echo "LAN is not conneced."
    fi
}

check_for_wlan()
{
    local WLAN_STATE=$(nmcli -t -f GENERAL.STATE device show "$WLAN_INTERFACE" | awk -F'[: ]+' '{print $2}')
    local CONNECTED=100
    if [[ "${WLAN_STATE}" -eq "${CONNECTED}" ]]; then
        echo "WLAN is conneced. Exit."
        exit 0
    else
        echo "WLAN is not conneced."
    fi
}

wait_seconds()
{
    echo "Wait for ${1} s"
    sleep "${1}"
}

use_access_point()
{
    echo "Activate access point."

    wifi-connect --portal-ssid "${AP_SSID}" --portal-passphrase "${AP_PASS}" --ui-directory "${UI_PATH}" &
    AP_PID=$!
}

kill_access_point()
{
    echo "Deactivate access point…"
    kill "${AP_PID}"
    wait "${AP_PID}" 2>/dev/null
    echo "Done."
}

search_for_wlan()
{
    echo "Search for WLAN"
    nmcli device wifi rescan
}

check_for_lan
check_for_wlan
wait_seconds "${HYSTERESE}"
check_for_wlan
use_access_point
wait_seconds "${AP_DURATION}"
kill_access_point
search_for_wlan
wait_seconds "${WLAN_RETRY}"
