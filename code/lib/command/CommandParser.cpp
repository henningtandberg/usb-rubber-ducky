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
    std::string command_type = command_string.substr(0, command_string.find(' '));
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
    std::vector<std::string> keys_to_press = CommandParser::split(command_string_without_type, '+');
    command_t *command = (command_t *)malloc(sizeof(command_t) + keys_to_press.size());

    command->type = COMMAND_TYPE_KEYBOARD_KEYPRESS;
    command->len = keys_to_press.size();

    std::vector<uint8_t> mapped_keys_to_press;
    for(int i = 0; i < keys_to_press.size(); i++) {
        //uint8_t keypress = lookup_keypress(keys_to_press[i]);
        //mapped_keys_to_press.push_back(keypress);
        printf("Key: %s \n", keys_to_press[i].c_str());
        command->payload[i] = lookup_keypress(keys_to_press[i]);
    }

    //memcpy(command->payload, mapped_keys_to_press.data(), command->len);

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

std::vector<std::string> CommandParser::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start));
    return tokens;
}
