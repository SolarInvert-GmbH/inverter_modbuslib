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
check automatic_test_linux_UartError
check automatic_test_modbus_MasterUart
check automatic_test_modbus_MasterUartState
check automatic_test_modbus_si_Date
check automatic_test_modbus_si_PowerConfig
check automatic_test_modbus_si_ReadRegister
check automatic_test_modbus_si_RegisterAddress
check automatic_test_modbus_si_request_ConstantVoltage
check automatic_test_modbus_si_request_ControlBatteryInvert
check automatic_test_modbus_si_request_LimitBatteryInvert
check automatic_test_modbus_si_request_PowerFactor
check automatic_test_modbus_si_request_Request
check automatic_test_modbus_si_request_Small
check automatic_test_modbus_si_request_Type
check automatic_test_modbus_si_response_Exception
check automatic_test_modbus_si_response_ExceptionValue
check automatic_test_modbus_si_response_FactoryValues
check automatic_test_modbus_si_response_ReadError
check automatic_test_modbus_si_response_ReadOperatingData3e
check automatic_test_modbus_si_response_ReadOperatingData33
check automatic_test_modbus_si_response_Response
check automatic_test_modbus_si_response_Type
check automatic_test_modbus_si_State
check automatic_test_modbus_si_Type
check automatic_test_modbus_si_WriteRegister
check automatic_test_modbus_SlaveUart
check automatic_test_modbus_SlaveUartState
check automatic_test_modbus_sunspec_ConnectedPhase
check automatic_test_modbus_sunspec_ScaleFactor
check automatic_test_modbus_sunspec_String
check automatic_test_modbus_sunspec_ValueS16
check automatic_test_modbus_sunspec_ValueU8
check automatic_test_modbus_sunspec_ValueU16
check automatic_test_modbus_sunspec_ValueU32
check automatic_test_modbus_sunspec_ValueU64
check automatic_test_modbus_Token
check automatic_test_modbus_TokenType
check automatic_test_parser_DefaultToken
check automatic_test_parser_DefaultTokenType
check automatic_test_parser_InputHandled
check automatic_test_parser_LineColumnCounter
check automatic_test_parser_State
check automatic_test_parser_TextPosition
check automatic_test_parser_Utf8ParserSerializer
check automatic_test_state_ActiveCloseErrorState
check automatic_test_state_DefaultError
check automatic_test_windows_UartError

echo ""
if [ "${ERROR}" -eq 0 ]; then
    echo "All tests were successful."
else
    echo "Following tests failed:${FAILED}"
fi

exit "${ERROR}"
