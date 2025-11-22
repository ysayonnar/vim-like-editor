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
        // Split current line at cursor: everything after cursor becomes a new line
        int y = editor.buf.get_current_pos_y();
        int x = editor.buf.get_current_pos_x();

        Slice<UnicodeSymbol> &cur_line = editor.buf.data[y];
        Slice<UnicodeSymbol> new_line;

        int cur_len = cur_line.get_length();
        // move symbols from cursor position to new_line
        for (int i = x; i < cur_len; ++i) {
            new_line.push(cur_line[i]);
        }

        // remove moved symbols from current line
        while (cur_line.get_length() > x) {
            cur_line.pop_at(x);
        }

        // insert new line after current line
        int total_lines = editor.buf.data.get_length();
        if (y >= total_lines - 1) {
            editor.buf.data.push(new_line);
        } else {
            editor.buf.data.push_after(new_line, y);
        }

        // move cursor to beginning of new line
        editor.buf.current_pos_x = 0;
        editor.buf.prev_pos_x = 0;
        editor.buf.next_line();
    } else if (last_symbol == 8 || last_symbol == 127) {
        if (editor.buf.get_current_pos_y() == 0 && editor.buf.get_current_pos_x() == 0) {
            return;
        }

        if (editor.buf.get_current_pos_x() == 0) {
            // merge with previous line
            int cur_y = editor.buf.get_current_pos_y();
            int prev_y = cur_y - 1;
            int old_length = editor.buf.data[prev_y].get_length();
            int cur_line_length = editor.buf.data[cur_y].get_length();
            for (int i = 0; i < cur_line_length; ++i) {
                editor.buf.data[prev_y].push(editor.buf.data[cur_y][i]);
            }
            editor.buf.data.pop_at(cur_y);
            editor.buf.prev_line();
            editor.buf.current_pos_x = old_length;
        } else {
            editor.buf.data[editor.buf.get_current_pos_y()].pop_at(editor.buf.get_current_pos_x() - 1);
            editor.buf.prev_symbol();
        }
    } else {
        // Insert UnicodeSymbol at cursor position (allow insert before first and after last)
        char ch = last_symbol;
        std::string tmp(1, ch);
        UnicodeSymbol symbol(tmp);

        auto &line = editor.buf.data[editor.buf.get_current_pos_y()];
        int idx = editor.buf.get_current_pos_x();

        // insert at idx (0..length). insert_at handles append when idx == length
        line.insert_at(idx, symbol);
        editor.buf.next_symbol();
    }

    throw UnknownCommand("ok");
}