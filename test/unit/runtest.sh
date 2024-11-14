#!/bin/bash

SOURCE="$(readlink -f ${BASH_SOURCE[0]})"
ROOT="${SOURCE%/*}"
unset SOURCE

ERROR=0
FAILED=""

check()
{
    "${ROOT}/${1}"
    RESULT="${?}"
    let ERROR="${ERROR}"+"${RESULT}"
    if [ "${RESULT}" -ne 0 ]; then
        FAILED=$(printf "${FAILED}\n   * ${1}")
    fi
}

check automatic_test_ConstString
#check automatic_test_container_RingBuffer
check automatic_test_Decimal
#check automatic_test_graphic_color_Rgb565
#check automatic_test_graphic_color_Rgb888
check automatic_test_Hexadecimal
#check automatic_test_hardware_can_Bitrate
#check automatic_test_hardware_can_Data
#check automatic_test_hardware_can_Id
#check automatic_test_hardware_can_Message
#check automatic_test_hardware_spi_Mode
check automatic_test_hardware_uart_Baudrate
check automatic_test_hardware_uart_DataBits
check automatic_test_hardware_uart_Parity
check automatic_test_hardware_uart_StopBits
#check automatic_test_http_Code
#check automatic_test_http_Fragment
#check automatic_test_http_FragmentParserSerializer
#check automatic_test_http_Query
#check automatic_test_http_QueryParserSerializer
#check automatic_test_http_UrlParsingError
#check automatic_test_http_Version
check automatic_test_json_Parser
check automatic_test_json_ParsingError
check automatic_test_json_Token
check automatic_test_json_TokenType
#check automatic_test_network_IpV4Address
#check automatic_test_network_IpV6Address
#check automatic_test_network_MacAddress
check automatic_test_parser_DefaultToken
check automatic_test_parser_DefaultTokenType
check automatic_test_parser_InputHandled
check automatic_test_parser_LineColumnCounter
check automatic_test_parser_State
check automatic_test_parser_TextPosition
check automatic_test_parser_Utf8ParserSerializer
#check automatic_test_physics_ElectricalResistance
#check automatic_test_physics_Frequency
#check automatic_test_physics_PartsPer
#check automatic_test_physics_Temperature
#check automatic_test_physics_Voltage
#check automatic_test_software_GitHash
#check automatic_test_software_Version
check automatic_test_state_ActiveCloseErrorState
check automatic_test_state_DefaultError

echo ""
if [ "${ERROR}" -eq 0 ]; then
    echo "All tests were successful."
else
    echo "Following tests failed:${FAILED}"
fi

exit "${ERROR}"
