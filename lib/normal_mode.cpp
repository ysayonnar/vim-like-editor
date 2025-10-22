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
    } else {
        throw UnknownCommand("bad pattern");
    }
}