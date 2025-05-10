//
// Created by Henning Tandberg on 10/05/2025.
//

#ifndef USB_RUBBER_DUCKY_COMMANDPARSER_H
#define USB_RUBBER_DUCKY_COMMANDPARSER_H

#include <string>
#include <command.h>

/* - Read packet and parse commands
*      - Keypress          e.g. "KP ENTER" or "KP LEFT_CTRL+LEFT_SHIFT+d"
*      - Print             e.g. "P echo hello world"
*      - Println           e.g. "PLN echo hello world" Writes ENTER at the end
*      - Mouse             e.g. "MM 10,23" Move mose to location x = 10, y = 23
*      - Mouse Click       e.g. "MC LEFT" Press mouse left button
*      - Execute Script    e.g. "EXEC win/deploy_keylogger.ducky"
*/

class CommandParser {
public:
    static command_t * parse_command(const std::string &command_string);
private:
    static command_t * parse_keyboard_keypress(const std::string& command_string_without_type);
    //static command_t parse_keyboard_print(const std::string& command_string_without_type);
    //static command_t parse_keyboard_println(const std::string& command_string_without_type);
    //static command_t parse_mouse_move(const std::string& command_string_without_type);
    //static command_t parse_mouse_move(const std::string& command_string_without_type);
    //static command_t parse_mouse_click(const std::string& command_string_without_type);
    //static command_t parse_execute_script(const std::string& command_string_without_type);
    static int count_tokens(const char * str, const char * delimiter);
    static char** split(const char * str, const char * delimiter);
};

#endif //USB_RUBBER_DUCKY_COMMANDPARSER_H
