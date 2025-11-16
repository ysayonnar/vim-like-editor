#include "../include/modes/normal_mode.h"
#include "../include/editor.h"
#include "../include/exceptions/exit_command.h"
#include "../include/exceptions/unknown_command.h"
#include "../include/string.h"
#include <iostream>

void NormalMode::exit() const {
    // TODO: placeholder implementation
    std::cout << "Exiting NORMAL mode" << std::endl;
}

void NormalMode::handle_input(String str) const {
    // проверка нажатия ESC
    if (str[str.get_length() - 1] == 27) {
        editor.command_input = "";
    } else if (str == ":q") {
        throw ExitCommand("exit");
    } else if (str == "l") {
        editor.buf.next_symbol();
    } else if (str == "h") {
        editor.buf.prev_symbol();
    } else if (str == "j") {
        editor.buf.next_line();
    } else if (str == "k") {
        editor.buf.prev_line();
    } else if (str == "w") {
        editor.buf.next_word();
    } else if (str == "b") {
        editor.buf.prev_word();
    } else if (str == "G") {
        editor.buf.move_to_end();
    } else if (str == "gg") {
        editor.buf.move_to_begin();
    } else if (str == "0") {
        editor.buf.start_line();
    } else if (str == "$") {
        editor.buf.end_line();
    } else {
        throw UnknownCommand("bad pattern");
    }
}