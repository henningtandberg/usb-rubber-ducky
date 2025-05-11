//
// Created by Henning Tandberg on 10/05/2025.
//

#include "unity.h"
#include "DuckypCreatePacketTests.h"
#include "CommandParserTests.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

int runUnityTests(void) {
    UNITY_BEGIN();

    RUN_TEST(KeyboardKeypressCommand_ParseKeyboardKeypress_CommandTypeIsSetToKeyboardKeypress);
    RUN_TEST(KeyboardKeypressCommand_ParseKeyboardKeypress_CommandLenIsAmountOfKeyboardKeypress);
    RUN_TEST(KeyboardKeypressCommand_ParseKeyboardKeypress_CommandContainsAllKeyboardKeypress);

    RUN_TEST(KeyboardKeypressCommandWithAllModifiers_ParseKeyboardKeypress_CommandContainsAllModifiers);
    RUN_TEST(KeyboardKeypressCommandWithAllSpecials_ParseKeyboardKeypress_CommandContainsAllSpecials);
    RUN_TEST(KeyboardKeypressCommandWithAllNavigation_ParseKeyboardKeypress_CommandContainsAllNavigation);
    RUN_TEST(KeyboardKeypressCommandWithAllNumeric_ParseKeyboardKeypress_CommandContainsAllNumeric);
    RUN_TEST(KeyboardKeypressCommandWithAllFunctionAndEscape_ParseKeyboardKeypress_CommandContainsAllFunctionAndEscape);
    RUN_TEST(KeyboardKeypressCommandWithAllFunctionControl_ParseKeyboardKeypress_CommandContainsAllFunctionControl);
    RUN_TEST(KeyboardKeypressCommandWithAllNumbers_ParseKeyboardKeypress_CommandContainsAllNumbers);
    RUN_TEST(KeyboardKeypressCommandWithAllCapitalLetters_ParseKeyboardKeypress_CommandContainsAllCapitalLetters);
    RUN_TEST(KeyboardKeypressCommandWithAllLetters_ParseKeyboardKeypress_CommandContainsAllLetters);

    RUN_TEST(KeyboardPrintCommand_ParseCommand_CommandTypeIsSetToKeyboardPrint);
    RUN_TEST(KeyboardPrintCommand_ParseCommand_CommandLenIsLengthOfStringToPrint);
    RUN_TEST(KeyboardPrintCommand_ParseCommand_CommandContainsCorrectStringToPrint);

    RUN_TEST(KeyboardPrintlnCommand_ParseCommand_CommandTypeIsSetToKeyboardPrintln);
    RUN_TEST(KeyboardPrintlnCommand_ParseCommand_CommandLenIsLengthOfStringToPrint);
    RUN_TEST(KeyboardPrintlnCommand_ParseCommand_CommandContainsCorrectStringToPrint);

    RUN_TEST(ExecuteScriptCommand_ParseCommand_CommandTypeIsSetToExecuteScript);
    RUN_TEST(ExecuteScriptCommand_ParseCommand_CommandLenIsLengthOfScriptPath);
    RUN_TEST(ExecuteScriptCommand_ParseCommand_CommandContainsCorrectScriptToExecute);

    RUN_TEST(duckyp_create_packet_PacketContainsProvidedCommand);
    RUN_TEST(duckyp_create_packet_HeaderIndicatesCommandPacket);
    RUN_TEST(duckyp_create_packet_HeaderHasCorrectCommandLen);

    return UNITY_END();
}

/**
  * For native dev-platform or for some embedded frameworks
  */
int main(void) {
    return runUnityTests();
}
