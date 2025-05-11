//
// Created by Henning Tandberg on 10/05/2025.
//

#include <stdlib.h>
#include <string.h>
#include <command.h>
#include <KeypressMapper.h>

#include "CommandParser.h"

command_t * CommandParser::parse_command(const char * command_string) {
    // Create buffer and capture command type
    char command_type[32] = { 0 };
    int end_of_command_type = index_of(command_string, ' ');
    memcpy(command_type, command_string, end_of_command_type);

    char * command_string_without_type = (char *)malloc(strlen(command_string) - end_of_command_type);
    memcpy(command_string_without_type, command_string+end_of_command_type+1, strlen(command_string)-end_of_command_type);

    command_t * command;
    if (strcmp(command_type, "KP") == 0) {
        command = CommandParser::parse_keyboard_keypress(command_string_without_type);
    } else if (strcmp(command_type, "P") == 0) {
        command = CommandParser::parse_keyboard_print(command_string_without_type);
    } else if (strcmp(command_type, "PLN") == 0) {
        command = CommandParser::parse_keyboard_println(command_string_without_type);
    } /* else if (command_type.compare("MM")) {
        return CommandParser::parse_mouse_move(command_string_without_type);
    } else if (command_type.compare("MC")) {
        return CommandParser::parse_mouse_click(command_string_without_type);
    } */ else if (strcmp(command_type, "EXEC") == 0) {
        command = CommandParser::parse_execute_script(command_string_without_type);
    } else {
        command = (command_t *)malloc(sizeof(command_t));
        command->type = COMMAND_TYPE_UNKNOWN;
        command->len = 0;
    }

    free(command_string_without_type);
    return command;
}

command_t * CommandParser::parse_keyboard_keypress(const char * command_string_without_type) {
    int token_count = CommandParser::count_tokens(command_string_without_type, "+");
    char ** keys_to_press = CommandParser::split(command_string_without_type, "+");

    command_t *command = (command_t *)malloc(sizeof(command_t) + token_count);

    command->type = COMMAND_TYPE_KEYBOARD_KEYPRESS;
    command->len = token_count;

    for(int i = 0; i < token_count; i++) {
        command->payload[i] = lookup_keypress(keys_to_press[i]);
    }

    // Should go through each element and free
    free(*keys_to_press);
    free(keys_to_press);
    return command;
}

command_t * CommandParser::parse_keyboard_print(const char * command_string_without_type) {
    int str_len = strlen(command_string_without_type);
    command_t *command = (command_t *)malloc(sizeof(command_t) + str_len);

    command->type = COMMAND_TYPE_KEYBOARD_PRINT;
    command->len = str_len;
    memcpy(command->payload, command_string_without_type, str_len);

    return command;
}

command_t * CommandParser::parse_keyboard_println(const char * command_string_without_type) {
    int str_len = strlen(command_string_without_type);
    command_t *command = (command_t *)malloc(sizeof(command_t) + str_len);

    command->type = COMMAND_TYPE_KEYBOARD_PRINTLN;
    command->len = str_len;
    memcpy(command->payload, command_string_without_type, str_len);

    return command;
}

//command_t CommandParser::parse_mouse_move(const std::string& command_string_without_type) {
//
//}

//command_t CommandParser::parse_mouse_click(const std::string& command_string_without_type) {
//
//}

command_t * CommandParser::parse_execute_script(const char * command_string_without_type) {
    int script_path_len = strlen(command_string_without_type);
    command_t *command = (command_t *)malloc(sizeof(command_t) + script_path_len);

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

char ** CommandParser::split(const char * str, const char * delimiter) {
    int str_len = strlen(str);
    int token_count = count_tokens(str, delimiter);

    char * str_copy = (char *) malloc(sizeof(char) * (str_len + 1));
    memcpy(str_copy, str, str_len);
    str_copy[str_len] = '\0';

    char **tokens = (char **)malloc(sizeof(char *) * token_count);

    char * token = strtok(str_copy, delimiter);
    for (int i = 0; i < token_count && token != NULL; i++) {
        int token_len = strlen(token);
        tokens[i] = (char *)malloc(sizeof(char) * token_len);
        memcpy(tokens[i], token, token_len);
        token = strtok(NULL, delimiter);
    }

    free(str_copy);
    return tokens;
}

int CommandParser::index_of(const char *str, char chr) {
    int index = 0;

    while (str[index] != '\0' && str[index] != chr) {
        index++;
    }

    return index;
}