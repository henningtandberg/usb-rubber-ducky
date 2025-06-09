//
// Created by Henning Tandberg on 10/05/2025.
//

#ifndef USB_RUBBER_DUCKY_COMMANDPARSER_H
#define USB_RUBBER_DUCKY_COMMANDPARSER_H

#include <Command.h>

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
    static Command * parse_command(const char * command_string);
private:
    static Command * parse_keyboard_keypress(const char * command_string_without_type);
    static Command * parse_keyboard_print(const char * command_string_without_type);
    static Command * parse_keyboard_println(const char * command_string_without_type);
    //static Command parse_mouse_move(const std::string& command_string_without_type);
    //static Command parse_mouse_click(const std::string& command_string_without_type);
    static Command * parse_execute_script(const char * command_string_without_type);
    static int count_tokens(const char * str, const char * delimiter);
    static int index_of(const char * str, char chr);
};

#endif //USB_RUBBER_DUCKY_COMMANDPARSER_H
