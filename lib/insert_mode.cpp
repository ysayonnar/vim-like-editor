#include "../include/modes/insert_mode.h"
#include "../include/editor.h"
#include "../include/exceptions/unknown_command.h"
#include "../include/string.h"
#include <iostream>
#include <string>

void InsertMode::exit() const {
    editor.operating_mode = new NormalMode(editor);
}

void InsertMode::handle_input(String str) const {
    char last_symbol = str[str.get_length() - 1];
    editor.command_input = "";
    if (last_symbol == 27) {
        exit();
        return;
    }

    if (last_symbol == '\n') {
        editor.buf.current_pos_x = 0;
        editor.buf.prev_pos_x = 0;
        // TODO: insert line here
        editor.buf.next_line();
    } else if (last_symbol == 8 || last_symbol == 127) {
        if (editor.buf.get_current_pos_y() == 0 && editor.buf.get_current_pos_x() == 0) {
            return;
        }

        if (editor.buf.get_current_pos_x() == 0) {
            int old_length = editor.buf.data[editor.buf.get_current_pos_y() - 1].get_length();
            int cur_line_length = editor.buf.data[editor.buf.get_current_pos_y()].get_length();
            if (cur_line_length > 1) {
                for (int i = 0; i < cur_line_length; i++) {
                    editor.buf.data[editor.buf.get_current_pos_y() - 1].push(editor.buf.data[editor.buf.get_current_pos_y()][i]);
                }
            }
            editor.buf.data.pop_at(editor.buf.get_current_pos_y());
            editor.buf.prev_line();
            editor.buf.current_pos_x = old_length;
            editor.buf.current_pos_x = old_length;
        } else {
            editor.buf.data[editor.buf.get_current_pos_y()].pop_at(editor.buf.get_current_pos_x() - 1);
            editor.buf.prev_symbol();
        }
    } else {
        editor.buf.data[editor.buf.get_current_pos_y()].push_after(UnicodeSymbol(str.get_c_style()), editor.buf.get_current_pos_x() - 1);
        editor.buf.next_symbol();
    }

    throw UnknownCommand("ok");
}