#include "../include/commands/edit.h"
#include "../include/commands/basic_movement.h"
#include "../include/editor.h"
#include "../include/exceptions/exit_command.h"

void CutSymbol::execute(String combination) const {
    int times_to_repeat = extract_num(combination);
    if (times_to_repeat == 0) {
        times_to_repeat = 1;
    }

    for (int i = 0; i < times_to_repeat; i++) {
        editor.buf.cut_current_symbol();
    }
}

void CutLine::execute(String combination) const {
    int times_to_repeat = extract_num(combination);
    if (times_to_repeat == 0) {
        times_to_repeat = 1;
    }

    int start_line = editor.buf.get_current_pos_y();
    int end_line = start_line + times_to_repeat - 1;
    if (end_line >= editor.buf.data.get_length()) {
        end_line = editor.buf.data.get_length() - 1;
    }

    // copy lines to clipboard
    editor.clipboard.clear();
    editor.clipboard.set_linewise(true);
    for (int i = start_line; i <= end_line; ++i) {
        editor.clipboard.data.push(editor.buf.data[i]);
    }

    // remove lines
    for (int i = 0; i < times_to_repeat; i++) {
        editor.buf.cut_current_line();
    }
}

void NewLineAfterAndInsert::execute(String combination) const {
    editor.buf.new_line_after();
    editor.buf.next_line();

    editor.operating_mode = new InsertMode(editor);
}

void NewLineBeforeAndInsert::execute(String combination) const {
    editor.buf.new_line_before();
    editor.buf.prev_line();

    editor.operating_mode = new InsertMode(editor);
}

void SaveQuit::execute(String combination) const {
    if (combination == ":w\n" || combination == ":wq\n") {
        editor.buf.save(editor.filename);
    }

    if (combination == ":q\n" || combination == ":wq\n") {
        throw ExitCommand("exit");
    }
}

void Paste::execute(String combination) const {
    // Paste at current cursor position
    int line = editor.buf.get_current_pos_y();
    int col = editor.buf.get_current_pos_x();
    editor.clipboard.paste_into(editor.buf, line, col);
}

void YankLine::execute(String combination) const {
    int times_to_repeat = extract_num(combination);
    if (times_to_repeat == 0) {
        times_to_repeat = 1;
    }

    int start_line = editor.buf.get_current_pos_y();
    int end_line = start_line + times_to_repeat - 1;
    if (end_line >= editor.buf.data.get_length()) {
        end_line = editor.buf.data.get_length() - 1;
    }

    editor.clipboard.clear();
    editor.clipboard.set_linewise(true);
    for (int i = start_line; i <= end_line; ++i) {
        editor.clipboard.data.push(editor.buf.data[i]);
    }
}