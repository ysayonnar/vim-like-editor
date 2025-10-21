#include "../include/modes/normal_mode.h"
#include "../include/editor.h"
#include "../include/exceptions/unknown_command.h"
#include "../include/string.h"
#include <iostream>

void NormalMode::exit() const {
    // TODO: placeholder implementation
    std::cout << "Exiting NORMAL mode" << std::endl;
}

void NormalMode::handle_input(String str) const {
    // TODO: проверять, есть ли такая команда и если нет, возвращать что то плохое

    // проверка на нажатие ESC
    if (str[str.get_length() - 1] == 27) {
        editor.command_input = "";
    } else if (str == "l") {
        editor.buf.next_symbol();
    } else if (str == "h") {
        editor.buf.prev_symbol();
    } else {
        throw UnknownCommand("bad pattern");
    }
}