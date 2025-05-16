//
// Created by Henning Tandberg on 10/05/2025.
//

#include <stdlib.h>
#include <string.h>
#include <Command.h>
#include <KeypressMapper.h>

#include "CommandParser.h"

Command * CommandParser::parse_command(const char * command_string) {
    // Create buffer and capture command type
    char Commandype[32] = { 0 };
    int end_of_Commandype = index_of(command_string, ' ');
    memcpy(Commandype, command_string, end_of_Commandype);

    char * command_string_without_type = (char *)malloc(strlen(command_string) - end_of_Commandype);
    memcpy(command_string_without_type, command_string+end_of_Commandype+1, strlen(command_string)-end_of_Commandype);

    Command * command;
    if (strcmp(Commandype, "KP") == 0) {
        command = CommandParser::parse_keyboard_keypress(command_string_without_type);
    } else if (strcmp(Commandype, "P") == 0) {
        command = CommandParser::parse_keyboard_print(command_string_without_type);
    } else if (strcmp(Commandype, "PLN") == 0) {
        command = CommandParser::parse_keyboard_println(command_string_without_type);
    } /* else if (Commandype.compare("MM")) {
        return CommandParser::parse_mouse_move(command_string_without_type);
    } else if (Commandype.compare("MC")) {
        return CommandParser::parse_mouse_click(command_string_without_type);
    } */ else if (strcmp(Commandype, "EXEC") == 0) {
        command = CommandParser::parse_execute_script(command_string_without_type);
    } else {
        command = (Command *)malloc(sizeof(Command));
        command->type = COMMAND_TYPE_UNKNOWN;
        command->len = 0;
    }

    free(command_string_without_type);
    return command;
}

Command * CommandParser::parse_keyboard_keypress(const char * command_string_without_type) {
    int token_count = CommandParser::count_tokens(command_string_without_type, "+");
    Command *command = (Command *)malloc(sizeof(Command) + token_count);
    int str_len = strlen(command_string_without_type);
    char * str_copy = (char *) malloc(sizeof(char) * str_len + 1);

    memcpy(str_copy, command_string_without_type, str_len);
    str_copy[str_len] = '\0';

    command->type = COMMAND_TYPE_KEYBOARD_KEYPRESS;
    command->len = token_count;

    char * token = strtok(str_copy, "+");
    for (int i = 0; token != NULL && i < token_count; i++) {
        command->payload[i] = lookup_keypress(token, strlen(token));
        token = strtok(NULL, "+");
    }

    free(str_copy);
    return command;
}

Command * CommandParser::parse_keyboard_print(const char * command_string_without_type) {
    int str_len = strlen(command_string_without_type);
    Command *command = (Command *)malloc(sizeof(Command) + str_len);

    command->type = COMMAND_TYPE_KEYBOARD_PRINT;
    command->len = str_len;
    memcpy(command->payload, command_string_without_type, str_len);

    return command;
}

Command * CommandParser::parse_keyboard_println(const char * command_string_without_type) {
    int str_len = strlen(command_string_without_type);
    Command *command = (Command *)malloc(sizeof(Command) + str_len);

    command->type = COMMAND_TYPE_KEYBOARD_PRINTLN;
    command->len = str_len;
    memcpy(command->payload, command_string_without_type, str_len);

    return command;
}

//Command CommandParser::parse_mouse_move(const std::string& command_string_without_type) {
//
//}

//Command CommandParser::parse_mouse_click(const std::string& command_string_without_type) {
//
//}

Command * CommandParser::parse_execute_script(const char * command_string_without_type) {
    int script_path_len = strlen(command_string_without_type);
    Command *command = (Command *)malloc(sizeof(Command) + script_path_len);

    command->type = COMMAND_TYPE_EXECUTE_SCRIPT;
    command->len = script_path_len;
    memcpy(command->payload, command_string_without_type, script_path_len);

    return command;
}

int CommandParser::count_tokens(const char * str, const char * delimiter) {
    int count = 0;
    int str_len = strlen(str);
    char * str_copy = (char *) malloc(sizeof(char) * str_len);

    memcpy(str_copy, str, str_len);

    char * token = strtok(str_copy, delimiter);
    while (token != NULL) {
        count++;
        token = strtok(NULL, delimiter);
    }

    free(str_copy);
    return count;
}

int CommandParser::index_of(const char *str, char chr) {
    int index = 0;

    while (str[index] != '\0' && str[index] != chr) {
        index++;
    }

    return index;
}