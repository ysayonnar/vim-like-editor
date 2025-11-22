#include "../include/commands/change_mode.h"
#include "../include/editor.h"

void ChangeToNormalMode::execute(String combination) const {
    editor.operating_mode = new NormalMode(editor);
}

void ChangeToInsertMode::execute(String combination) const {
    if (combination == "A") {
        editor.buf.end_line();
    } else if (combination == "I") {
        editor.buf.start_line();
    } else if (combination == "a") {
        editor.buf.next_symbol();
    }

    editor.operating_mode = new InsertMode(editor);
}

void ChangeToVisualMode::execute(String combination) const {
    if (combination == "V") {
        editor.operating_mode = new VisualMode(editor, true);
    } else {
        editor.operating_mode = new VisualMode(editor, false);
    }
}
