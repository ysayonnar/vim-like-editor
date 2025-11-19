#include "../include/modes/insert_mode.h"
#include "../include/editor.h"
#include "../include/string.h"
#include <iostream>

void InsertMode::exit() const {
    editor.operating_mode = new NormalMode(editor);
}

void InsertMode::handle_input(String str) const {
    char last_symbol = str[str.get_length() - 1];
    if (last_symbol == 27) {
        editor.command_input = "";
        exit();
        return;
    }

    // TODO: implement input
    return;
}