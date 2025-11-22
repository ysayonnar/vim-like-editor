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