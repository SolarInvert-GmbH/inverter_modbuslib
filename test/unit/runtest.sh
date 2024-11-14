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
check automatic_test_Decimal
check automatic_test_Hexadecimal
check automatic_test_hardware_uart_Baudrate
check automatic_test_hardware_uart_DataBits
check automatic_test_hardware_uart_Parity
check automatic_test_hardware_uart_StopBits
check automatic_test_json_Parser
check automatic_test_json_ParsingError
check automatic_test_json_Token
check automatic_test_json_TokenType
check automatic_test_modbus_sunspec_ScaleFactor
check automatic_test_parser_DefaultToken
check automatic_test_parser_DefaultTokenType
check automatic_test_parser_InputHandled
check automatic_test_parser_LineColumnCounter
check automatic_test_parser_State
check automatic_test_parser_TextPosition
check automatic_test_parser_Utf8ParserSerializer
check automatic_test_state_ActiveCloseErrorState
check automatic_test_state_DefaultError

echo ""
if [ "${ERROR}" -eq 0 ]; then
    echo "All tests were successful."
else
    echo "Following tests failed:${FAILED}"
fi

exit "${ERROR}"
