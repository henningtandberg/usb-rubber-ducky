//
// Created by Henning Tandberg on 10/05/2025.
//

#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <command.h>
#include <KeypressMapper.h>

#include "CommandParser.h"

command_t * CommandParser::parse_command(const std::string &command_string) {
    // Create buffer and capture command type
    std::string command_type = command_string.substr(0, command_string.find(' '));
    // Pointer evilness
    std::string command_string_without_type = command_string.substr(command_type.length() + 1, command_string.length());

    if (command_type.compare("KP") == 0) {
        return CommandParser::parse_keyboard_keypress(command_string_without_type);
    }/* else if (command_type.compare("P")) {
        return CommandParser::parse_keyboard_print(command_string_without_type);
    } else if (command_type.compare("PLN")) {
        return CommandParser::parse_keyboard_println(command_string_without_type);
    } else if (command_type.compare("MM")) {
        return CommandParser::parse_mouse_move(command_string_without_type);
    } else if (command_type.compare("MM")) {
        return CommandParser::parse_mouse_move(command_string_without_type);
    } else if (command_type.compare("MC")) {
        return CommandParser::parse_mouse_click(command_string_without_type);
    } else if (command_type.compare("MC")) {
        return CommandParser::parse_execute_script(command_string_without_type);
    }*/ else {
        command_t *command = (command_t *)malloc(sizeof(command_t));
        command->type = COMMAND_TYPE_UNKNOWN;
        command->len = 0;

        return command;
    }
}

command_t * CommandParser::parse_keyboard_keypress(const std::string& command_string_without_type) {
    // strtok :(((
    int token_count = CommandParser::count_tokens(command_string_without_type.c_str(), "+");
    char ** keys_to_press = CommandParser::split(command_string_without_type.c_str(), "+");

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

//command_t CommandParser::parse_keyboard_print(const std::string& command_string_without_type) {
//
//}
//
//command_t CommandParser::parse_keyboard_println(const std::string& command_string_without_type) {
//
//}
//
//command_t CommandParser::parse_mouse_move(const std::string& command_string_without_type) {
//
//}
//
//command_t CommandParser::parse_mouse_move(const std::string& command_string_without_type) {
//
//}
//
//command_t CommandParser::parse_mouse_click(const std::string& command_string_without_type) {
//
//}
//
//command_t CommandParser::parse_execute_script(const std::string& command_string_without_type) {
//
//}

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

    printf("Token count: %d \n", token_count);
    printf("String: %s \n", str);

    char * str_copy = (char *) malloc(sizeof(char) * (str_len + 1));
    memcpy(str_copy, str, str_len);
    str_copy[str_len] = '\0';

    char **tokens = (char **)malloc(sizeof(char *) * token_count);

    char * token = strtok(str_copy, delimiter);
    for (int i = 0; i < token_count && token != NULL; i++) {
        printf("Token: %s \n", token);
        int token_len = strlen(token);
        tokens[i] = (char *)malloc(sizeof(char) * token_len);
        memcpy(tokens[i], token, token_len);
        token = strtok(NULL, delimiter);
    }

    free(str_copy);
    return tokens;
}
