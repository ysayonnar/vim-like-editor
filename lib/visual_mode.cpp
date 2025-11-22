#include "../include/modes/visual_mode.h"
#include "../include/editor.h"
#include "../include/string.h"
#include <iostream>

VisualMode::VisualMode(Editor &editor) : OperatingMode(editor, true) {
    // initialize selection anchor at current cursor
    editor.buf.selection_active = true;
    editor.buf.sel_anchor_x = editor.buf.get_current_pos_x();
    editor.buf.sel_anchor_y = editor.buf.get_current_pos_y();
}

void VisualMode::exit() const {
    // clear selection and return to normal mode
    editor.buf.selection_active = false;
    editor.operating_mode = new NormalMode(editor);
}

void VisualMode::handle_input(String str) const {
    char last_symbol = str[str.get_length() - 1];

    if (last_symbol == 27) { // ESC
        editor.command_input = "";
        exit();
        return;
    }

    // movement keys: hjkl, w, b
    if (last_symbol == 'h') {
        editor.buf.prev_symbol();
    } else if (last_symbol == 'l') {
        editor.buf.next_symbol();
    } else if (last_symbol == 'j') {
        editor.buf.next_line();
    } else if (last_symbol == 'k') {
        editor.buf.prev_line();
    } else if (last_symbol == 'w') {
        editor.buf.next_word();
    } else if (last_symbol == 'b') {
        editor.buf.prev_word();
    } else if (last_symbol == 'v') {
        // toggle back to normal
        exit();
        return;
    } else {
        // ignore other keys for now
        return;
    }

    // ensure selection remains active; current cursor position defines selection end
    editor.buf.selection_active = true;

    return;
}