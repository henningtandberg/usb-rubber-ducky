//
// Created by Henning Tandberg on 10/05/2025.
//

#include "unity.h"

#include <cstdint>
#include <cstring>
#include <command.h>
#include <CommandParser.h>
#include "CommandParserTests.h"

/**
 * Command KP Tests
 */

#define KEYBOARD_KEYPRESS_COMMAND_COMBINATION "KP LEFT_CTRL+LEFT_SHIFT+n"

void KeyboardKeypressCommand_ParseKeyboardKeypress_CommandTypeIsSetToKeyboardKeypress(void) {
    command_t *command = CommandParser::parse_command(KEYBOARD_KEYPRESS_COMMAND_COMBINATION);

    TEST_ASSERT_EQUAL(COMMAND_TYPE_KEYBOARD_KEYPRESS, command->type);
    free(command);
}

void KeyboardKeypressCommand_ParseKeyboardKeypress_CommandLenIsAmountOfKeyboardKeypress(void) {
    command_t *command = CommandParser::parse_command(KEYBOARD_KEYPRESS_COMMAND_COMBINATION);

    TEST_ASSERT_EQUAL(3, command->len);
    free(command);
}

void KeyboardKeypressCommand_ParseKeyboardKeypress_CommandContainsAllKeyboardKeypress(void) {
    command_t *command = CommandParser::parse_command(KEYBOARD_KEYPRESS_COMMAND_COMBINATION);

    TEST_ASSERT_EQUAL(0x80 /*LEFT_CTRL*/, (uint8_t)command->payload[0]);
    TEST_ASSERT_EQUAL(0x81 /*LEFT_SHIFT*/, (uint8_t)command->payload[1]);
    TEST_ASSERT_EQUAL(0x6E /*n*/, (uint8_t)command->payload[2]);
    free(command);
}

/**
 * The following test are a bit strange as these keypress combinations would never be made, but the tests verify
 * that the mapping from tokens to keypress values are correct.
 */

#define KEYPRESS_COMMAND_MODIFIERS "KP LEFT_CTRL+LEFT_SHIFT+LEFT_ALT+LEFT_GUI+RIGHT_CTRL+RIGHT_SHIFT+RIGHT_ALT+RIGHT_GUI"
void KeyboardKeypressCommandWithAllModifiers_ParseKeyboardKeypress_CommandContainsAllModifiers(void) {
    command_t *command = CommandParser::parse_command(KEYPRESS_COMMAND_MODIFIERS);

    TEST_ASSERT_EQUAL(0x80, (uint8_t)command->payload[0]);
    TEST_ASSERT_EQUAL(0x81, (uint8_t)command->payload[1]);
    TEST_ASSERT_EQUAL(0x82, (uint8_t)command->payload[2]);
    TEST_ASSERT_EQUAL(0x83, (uint8_t)command->payload[3]);
    TEST_ASSERT_EQUAL(0x84, (uint8_t)command->payload[4]);
    TEST_ASSERT_EQUAL(0x85, (uint8_t)command->payload[5]);
    TEST_ASSERT_EQUAL(0x86, (uint8_t)command->payload[6]);
    TEST_ASSERT_EQUAL(0x87, (uint8_t)command->payload[7]);
    free(command);
}

#define KEYPRESS_COMMAND_SPECIALS "KP BACKSPACE+TAB+RETURN+MENU+CAPS_LOCK"
void KeyboardKeypressCommandWithAllSpecials_ParseKeyboardKeypress_CommandContainsAllSpecials(void) {
    command_t *command = CommandParser::parse_command(KEYPRESS_COMMAND_SPECIALS);

    TEST_ASSERT_EQUAL(0xB2, (uint8_t)command->payload[0]);
    TEST_ASSERT_EQUAL(0xB3, (uint8_t)command->payload[1]);
    TEST_ASSERT_EQUAL(0xB0, (uint8_t)command->payload[2]);
    TEST_ASSERT_EQUAL(0xED, (uint8_t)command->payload[3]);
    TEST_ASSERT_EQUAL(0xC1, (uint8_t)command->payload[4]);
    free(command);
}

#define KEYPRESS_COMMAND_NAVIGATION "KP UP_ARROW+DOWN_ARROW+LEFT_ARROW+RIGHT_ARROW+ESC+INSERT+DELETE+PAGE_UP+PAGE_DOWN+HOME+END"
void KeyboardKeypressCommandWithAllNavigation_ParseKeyboardKeypress_CommandContainsAllNavigation(void) {
    command_t *command = CommandParser::parse_command(KEYPRESS_COMMAND_NAVIGATION);

    TEST_ASSERT_EQUAL(0xDA, (uint8_t)command->payload[0]);
    TEST_ASSERT_EQUAL(0xD9, (uint8_t)command->payload[1]);
    TEST_ASSERT_EQUAL(0xD8, (uint8_t)command->payload[2]);
    TEST_ASSERT_EQUAL(0xD7, (uint8_t)command->payload[3]);
    TEST_ASSERT_EQUAL(0xB1, (uint8_t)command->payload[4]);
    TEST_ASSERT_EQUAL(0xD1, (uint8_t)command->payload[5]);
    TEST_ASSERT_EQUAL(0xD4, (uint8_t)command->payload[6]);
    TEST_ASSERT_EQUAL(0xD3, (uint8_t)command->payload[7]);
    TEST_ASSERT_EQUAL(0xD6, (uint8_t)command->payload[8]);
    TEST_ASSERT_EQUAL(0xD2, (uint8_t)command->payload[9]);
    TEST_ASSERT_EQUAL(0xD5, (uint8_t)command->payload[10]);
    free(command);
}

#define KEYPRESS_COMMAND_NUMERIC "KP NUM_LOCK+KP_SLASH+KP_ASTERISK+KP_MINUS+KP_PLUS+KP_ENTER+KP_1+KP_2+KP_3+KP_4+KP_5+KP_6+KP_7+KP_8+KP_9+KP_0+KP_DOT"
void KeyboardKeypressCommandWithAllNumeric_ParseKeyboardKeypress_CommandContainsAllNumeric(void) {
    command_t *command = CommandParser::parse_command(KEYPRESS_COMMAND_NUMERIC);

    TEST_ASSERT_EQUAL(0xDB, (uint8_t)command->payload[0]);
    TEST_ASSERT_EQUAL(0xDC, (uint8_t)command->payload[1]);
    TEST_ASSERT_EQUAL(0xDD, (uint8_t)command->payload[2]);
    TEST_ASSERT_EQUAL(0xDE, (uint8_t)command->payload[3]);
    TEST_ASSERT_EQUAL(0xDF, (uint8_t)command->payload[4]);
    TEST_ASSERT_EQUAL(0xE0, (uint8_t)command->payload[5]);
    TEST_ASSERT_EQUAL(0xE1, (uint8_t)command->payload[6]);
    TEST_ASSERT_EQUAL(0xE2, (uint8_t)command->payload[7]);
    TEST_ASSERT_EQUAL(0xE3, (uint8_t)command->payload[8]);
    TEST_ASSERT_EQUAL(0xE4, (uint8_t)command->payload[9]);
    TEST_ASSERT_EQUAL(0xE5, (uint8_t)command->payload[10]);
    TEST_ASSERT_EQUAL(0xE6, (uint8_t)command->payload[11]);
    TEST_ASSERT_EQUAL(0xE7, (uint8_t)command->payload[12]);
    TEST_ASSERT_EQUAL(0xE8, (uint8_t)command->payload[13]);
    TEST_ASSERT_EQUAL(0xE9, (uint8_t)command->payload[14]);
    TEST_ASSERT_EQUAL(0xEA, (uint8_t)command->payload[15]);
    TEST_ASSERT_EQUAL(0xEB, (uint8_t)command->payload[16]);
    free(command);
}

#define KEYPRESS_COMMAND_FUNCTION_AND_ESCAPE "KP F1+F2+F3+F4+F5+F6+F7+F8+F9+F10+F11+F12+F13+F14+F15+F16+F17+F18+F19+F20+F21+F22+F23+F24"
void KeyboardKeypressCommandWithAllFunctionAndEscape_ParseKeyboardKeypress_CommandContainsAllFunctionAndEscape(void) {
    command_t *command = CommandParser::parse_command(KEYPRESS_COMMAND_FUNCTION_AND_ESCAPE);

    TEST_ASSERT_EQUAL(0xC2, (uint8_t)command->payload[0]);
    TEST_ASSERT_EQUAL(0xC3, (uint8_t)command->payload[1]);
    TEST_ASSERT_EQUAL(0xC4, (uint8_t)command->payload[2]);
    TEST_ASSERT_EQUAL(0xC5, (uint8_t)command->payload[3]);
    TEST_ASSERT_EQUAL(0xC6, (uint8_t)command->payload[4]);
    TEST_ASSERT_EQUAL(0xC7, (uint8_t)command->payload[5]);
    TEST_ASSERT_EQUAL(0xC8, (uint8_t)command->payload[6]);
    TEST_ASSERT_EQUAL(0xC9, (uint8_t)command->payload[7]);
    TEST_ASSERT_EQUAL(0xCA, (uint8_t)command->payload[8]);
    TEST_ASSERT_EQUAL(0xCB, (uint8_t)command->payload[9]);
    TEST_ASSERT_EQUAL(0xCC, (uint8_t)command->payload[10]);
    TEST_ASSERT_EQUAL(0xCD, (uint8_t)command->payload[11]);
    TEST_ASSERT_EQUAL(0xF0, (uint8_t)command->payload[12]);
    TEST_ASSERT_EQUAL(0xF1, (uint8_t)command->payload[13]);
    TEST_ASSERT_EQUAL(0xF2, (uint8_t)command->payload[14]);
    TEST_ASSERT_EQUAL(0xF3, (uint8_t)command->payload[15]);
    TEST_ASSERT_EQUAL(0xF4, (uint8_t)command->payload[16]);
    TEST_ASSERT_EQUAL(0xF5, (uint8_t)command->payload[17]);
    TEST_ASSERT_EQUAL(0xF6, (uint8_t)command->payload[18]);
    TEST_ASSERT_EQUAL(0xF7, (uint8_t)command->payload[19]);
    TEST_ASSERT_EQUAL(0xF8, (uint8_t)command->payload[20]);
    TEST_ASSERT_EQUAL(0xF9, (uint8_t)command->payload[21]);
    TEST_ASSERT_EQUAL(0xFA, (uint8_t)command->payload[22]);
    TEST_ASSERT_EQUAL(0xFB, (uint8_t)command->payload[23]);
    free(command);
}

#define KEYPRESS_COMMAND_FUNCTION_CONTROL "KP PRINT_SCREEN+SCROLL_LOCK+PAUSE"
void KeyboardKeypressCommandWithAllFunctionControl_ParseKeyboardKeypress_CommandContainsAllFunctionControl(void) {
    command_t *command = CommandParser::parse_command(KEYPRESS_COMMAND_FUNCTION_CONTROL);

    TEST_ASSERT_EQUAL(0xCE, (uint8_t)command->payload[0]);
    TEST_ASSERT_EQUAL(0xCF, (uint8_t)command->payload[1]);
    TEST_ASSERT_EQUAL(0xD0, (uint8_t)command->payload[2]);
    free(command);
}

#define KEYPRESS_COMMAND_NUMBERS "KP 0+1+2+3+4+5+6+7+8+9"
void KeyboardKeypressCommandWithAllNumbers_ParseKeyboardKeypress_CommandContainsAllNumbers(void) {
    command_t *command = CommandParser::parse_command(KEYPRESS_COMMAND_NUMBERS);

    TEST_ASSERT_EQUAL(0x30, (uint8_t)command->payload[0]);
    TEST_ASSERT_EQUAL(0x31, (uint8_t)command->payload[1]);
    TEST_ASSERT_EQUAL(0x32, (uint8_t)command->payload[2]);
    TEST_ASSERT_EQUAL(0x33, (uint8_t)command->payload[3]);
    TEST_ASSERT_EQUAL(0x34, (uint8_t)command->payload[4]);
    TEST_ASSERT_EQUAL(0x35, (uint8_t)command->payload[5]);
    TEST_ASSERT_EQUAL(0x36, (uint8_t)command->payload[6]);
    TEST_ASSERT_EQUAL(0x37, (uint8_t)command->payload[7]);
    TEST_ASSERT_EQUAL(0x38, (uint8_t)command->payload[8]);
    TEST_ASSERT_EQUAL(0x39, (uint8_t)command->payload[9]);
    free(command);
}

#define KEYPRESS_COMMAND_CAPITAL_LETTERS "KP A+B+C+D+E+F+G+H+I+J+K+L+M+N+O+P+Q+R+S+T+U+V+W+X+Y+Z"
void KeyboardKeypressCommandWithAllCapitalLetters_ParseKeyboardKeypress_CommandContainsAllCapitalLetters(void) {
    command_t *command = CommandParser::parse_command(KEYPRESS_COMMAND_CAPITAL_LETTERS);

    TEST_ASSERT_EQUAL(0x41, (uint8_t)command->payload[0]);
    TEST_ASSERT_EQUAL(0x42, (uint8_t)command->payload[1]);
    TEST_ASSERT_EQUAL(0x43, (uint8_t)command->payload[2]);
    TEST_ASSERT_EQUAL(0x44, (uint8_t)command->payload[3]);
    TEST_ASSERT_EQUAL(0x45, (uint8_t)command->payload[4]);
    TEST_ASSERT_EQUAL(0x46, (uint8_t)command->payload[5]);
    TEST_ASSERT_EQUAL(0x47, (uint8_t)command->payload[6]);
    TEST_ASSERT_EQUAL(0x48, (uint8_t)command->payload[7]);
    TEST_ASSERT_EQUAL(0x49, (uint8_t)command->payload[8]);
    TEST_ASSERT_EQUAL(0x4A, (uint8_t)command->payload[9]);
    TEST_ASSERT_EQUAL(0x4B, (uint8_t)command->payload[10]);
    TEST_ASSERT_EQUAL(0x4C, (uint8_t)command->payload[11]);
    TEST_ASSERT_EQUAL(0x4D, (uint8_t)command->payload[12]);
    TEST_ASSERT_EQUAL(0x4E, (uint8_t)command->payload[13]);
    TEST_ASSERT_EQUAL(0x4F, (uint8_t)command->payload[14]);
    TEST_ASSERT_EQUAL(0x50, (uint8_t)command->payload[15]);
    TEST_ASSERT_EQUAL(0x51, (uint8_t)command->payload[16]);
    TEST_ASSERT_EQUAL(0x52, (uint8_t)command->payload[17]);
    TEST_ASSERT_EQUAL(0x53, (uint8_t)command->payload[18]);
    TEST_ASSERT_EQUAL(0x54, (uint8_t)command->payload[19]);
    TEST_ASSERT_EQUAL(0x55, (uint8_t)command->payload[20]);
    TEST_ASSERT_EQUAL(0x56, (uint8_t)command->payload[21]);
    TEST_ASSERT_EQUAL(0x57, (uint8_t)command->payload[22]);
    TEST_ASSERT_EQUAL(0x58, (uint8_t)command->payload[23]);
    TEST_ASSERT_EQUAL(0x59, (uint8_t)command->payload[24]);
    TEST_ASSERT_EQUAL(0x5A, (uint8_t)command->payload[25]);
    free(command);
}

#define KEYPRESS_COMMAND_LETTERS "KP a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z"
void KeyboardKeypressCommandWithAllLetters_ParseKeyboardKeypress_CommandContainsAllLetters(void) {
    command_t *command = CommandParser::parse_command(KEYPRESS_COMMAND_LETTERS);

    TEST_ASSERT_EQUAL(0x61, (uint8_t)command->payload[0]);
    TEST_ASSERT_EQUAL(0x62, (uint8_t)command->payload[1]);
    TEST_ASSERT_EQUAL(0x63, (uint8_t)command->payload[2]);
    TEST_ASSERT_EQUAL(0x64, (uint8_t)command->payload[3]);
    TEST_ASSERT_EQUAL(0x65, (uint8_t)command->payload[4]);
    TEST_ASSERT_EQUAL(0x66, (uint8_t)command->payload[5]);
    TEST_ASSERT_EQUAL(0x67, (uint8_t)command->payload[6]);
    TEST_ASSERT_EQUAL(0x68, (uint8_t)command->payload[7]);
    TEST_ASSERT_EQUAL(0x69, (uint8_t)command->payload[8]);
    TEST_ASSERT_EQUAL(0x6A, (uint8_t)command->payload[9]);
    TEST_ASSERT_EQUAL(0x6B, (uint8_t)command->payload[10]);
    TEST_ASSERT_EQUAL(0x6C, (uint8_t)command->payload[11]);
    TEST_ASSERT_EQUAL(0x6D, (uint8_t)command->payload[12]);
    TEST_ASSERT_EQUAL(0x6E, (uint8_t)command->payload[13]);
    TEST_ASSERT_EQUAL(0x6F, (uint8_t)command->payload[14]);
    TEST_ASSERT_EQUAL(0x70, (uint8_t)command->payload[15]);
    TEST_ASSERT_EQUAL(0x71, (uint8_t)command->payload[16]);
    TEST_ASSERT_EQUAL(0x72, (uint8_t)command->payload[17]);
    TEST_ASSERT_EQUAL(0x73, (uint8_t)command->payload[18]);
    TEST_ASSERT_EQUAL(0x74, (uint8_t)command->payload[19]);
    TEST_ASSERT_EQUAL(0x75, (uint8_t)command->payload[20]);
    TEST_ASSERT_EQUAL(0x76, (uint8_t)command->payload[21]);
    TEST_ASSERT_EQUAL(0x77, (uint8_t)command->payload[22]);
    TEST_ASSERT_EQUAL(0x78, (uint8_t)command->payload[23]);
    TEST_ASSERT_EQUAL(0x79, (uint8_t)command->payload[24]);
    TEST_ASSERT_EQUAL(0x7A, (uint8_t)command->payload[25]);
    free(command);
}

/**
 * Command P Tests
 */

#define KEYBOARD_PRINT_COMMAND "P echo \"hello world!\" > message.txt"
void KeyboardPrintCommand_ParseCommand_CommandTypeIsSetToKeyboardPrint(void) {
    command_t *command = CommandParser::parse_command(KEYBOARD_PRINT_COMMAND);

    TEST_ASSERT_EQUAL(COMMAND_TYPE_KEYBOARD_PRINT, command->type);
    free(command);
}

void KeyboardPrintCommand_ParseCommand_CommandLenIsLengthOfStringToPrint(void) {
    command_t *command = CommandParser::parse_command(KEYBOARD_PRINT_COMMAND);

    TEST_ASSERT_EQUAL(33, command->len);
    free(command);
}

void KeyboardPrintCommand_ParseCommand_CommandContainsCorrectStringToPrint(void) {
    command_t *command = CommandParser::parse_command(KEYBOARD_PRINT_COMMAND);

    TEST_ASSERT_EQUAL(0, strcmp("echo \"hello world!\" > message.txt", command->payload));
    free(command);
}

/**
 * Command PLN Tests
 */

#define KEYBOARD_PRINTLN_COMMAND "PLN echo \"hello world!\" > message.txt"
void KeyboardPrintlnCommand_ParseCommand_CommandTypeIsSetToKeyboardPrintln(void) {
    command_t *command = CommandParser::parse_command(KEYBOARD_PRINTLN_COMMAND);

    TEST_ASSERT_EQUAL(COMMAND_TYPE_KEYBOARD_PRINTLN, command->type);
    free(command);
}

void KeyboardPrintlnCommand_ParseCommand_CommandLenIsLengthOfStringToPrint(void) {
    command_t *command = CommandParser::parse_command(KEYBOARD_PRINTLN_COMMAND);

    TEST_ASSERT_EQUAL(33, command->len);
    free(command);
}

void KeyboardPrintlnCommand_ParseCommand_CommandContainsCorrectStringToPrint(void) {
    command_t *command = CommandParser::parse_command(KEYBOARD_PRINTLN_COMMAND);

    TEST_ASSERT_EQUAL(0, strcmp("echo \"hello world!\" > message.txt", command->payload));
    free(command);
}

// MM and MC here

/**
 * Command PLN Tests
 */

#define EXECUTE_SCRIPT_COMMAND "EXEC ./script.rd"
void ExecuteScriptCommand_ParseCommand_CommandTypeIsSetToExecuteScript(void) {
    command_t *command = CommandParser::parse_command(EXECUTE_SCRIPT_COMMAND);

    TEST_ASSERT_EQUAL(COMMAND_TYPE_EXECUTE_SCRIPT, command->type);
    free(command);
}

void ExecuteScriptCommand_ParseCommand_CommandLenIsLengthOfScriptPath(void) {
    command_t *command = CommandParser::parse_command(EXECUTE_SCRIPT_COMMAND);

    TEST_ASSERT_EQUAL(11, command->len);
    free(command);
}

void ExecuteScriptCommand_ParseCommand_CommandContainsCorrectScriptToExecute(void) {
    command_t *command = CommandParser::parse_command(EXECUTE_SCRIPT_COMMAND);

    TEST_ASSERT_EQUAL(0, strcmp("./script.rd", command->payload));
    free(command);
}
