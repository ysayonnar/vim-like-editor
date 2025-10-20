#include "../include/modes/normal_mode.h"
#include "../include/editor.h"
#include "../include/string.h"
#include <iostream>

void NormalMode::exit() const {
    // TODO: placeholder implementation
    std::cout << "Exiting NORMAL mode" << std::endl;
}

void NormalMode::handle_input(String str) const {
    // TODO: проверять, есть ли такая команда и если нет, возвращать что то плохое
    if (str == "l") {
        editor.buf.next_symbol();
    } else if (str == "h") {
        editor.buf.prev_symbol();
    }
}