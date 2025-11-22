#include "../include/modes/visual_mode.h"
#include "../include/editor.h"
#include "../include/string.h"
#include <iostream>

VisualMode::VisualMode(Editor &editor, bool line_mode) : OperatingMode(editor, true), line_mode(line_mode) {
    // initialize selection anchor at current cursor
    editor.buf.selection_active = true;
    if (line_mode) {
        editor.buf.sel_anchor_y = editor.buf.get_current_pos_y();
        editor.buf.sel_anchor_x = 0; // start of line
        // move cursor to end of line to show full-line selection
        editor.buf.current_pos_x = editor.buf.data[editor.buf.get_current_pos_y()].get_length();
    } else {
        editor.buf.sel_anchor_x = editor.buf.get_current_pos_x();
        editor.buf.sel_anchor_y = editor.buf.get_current_pos_y();
    }
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
    } else if (last_symbol == 'y') {
        // Yank selection: copy to clipboard but do not delete
        int ay = editor.buf.sel_anchor_y;
        int ax = editor.buf.sel_anchor_x;
        int by = editor.buf.get_current_pos_y();
        int bx = editor.buf.get_current_pos_x();

        int sY = ay, sX = ax, eY = by, eX = bx;
        if (sY > eY || (sY == eY && sX > eX)) {
            sY = by;
            sX = bx;
            eY = ay;
            eX = ax;
        }

        // empty selection -> do nothing
        if (sY == eY && sX == eX) {
            return;
        }

        editor.clipboard.clear();

        if (sY == eY) {
            // char-wise
            Slice<UnicodeSymbol> fragment;
            int line_len = editor.buf.data[sY].get_length();
            int end_idx = std::min(eX, line_len);
            for (int i = sX; i < end_idx; ++i) {
                fragment.push(editor.buf.data[sY][i]);
            }
            editor.clipboard.data.push(fragment);
            editor.clipboard.set_linewise(false);
        } else {
            // line-wise copy
            // if selection covers full lines, copy them as lines; otherwise copy partial lines as separate entries
            // For simplicity, treat multi-line visual selection as linewise
            for (int line = sY; line <= eY; ++line) {
                editor.clipboard.data.push(editor.buf.data[line]);
            }
            editor.clipboard.set_linewise(true);
        }

        // exit to normal mode
        editor.buf.selection_active = false;
        editor.operating_mode = new NormalMode(editor);
        return;
    } else if (last_symbol == 'd') {
        // Delete visual selection: copy to clipboard and remove selected text
        int ay = editor.buf.sel_anchor_y;
        int ax = editor.buf.sel_anchor_x;
        int by = editor.buf.get_current_pos_y();
        int bx = editor.buf.get_current_pos_x();

        int sY = ay, sX = ax, eY = by, eX = bx;
        if (sY > eY || (sY == eY && sX > eX)) {
            sY = by;
            sX = bx;
            eY = ay;
            eX = ax;
        }

        // if empty selection, do nothing
        if (sY == eY && sX == eX) {
            return;
        }

        // prepare clipboard
        editor.clipboard.clear();

        if (sY == eY) {
            Slice<UnicodeSymbol> line_copy;
            int line_len = editor.buf.data[sY].get_length();
            int end_idx = std::min(eX, line_len);
            for (int i = sX; i < end_idx; ++i) {
                line_copy.push(editor.buf.data[sY][i]);
            }
            editor.clipboard.data.push(line_copy);
            editor.clipboard.set_linewise(false);

            // remove from end to start to keep indices valid
            for (int i = end_idx - 1; i >= sX; --i) {
                if (i >= 0 && i < editor.buf.data[sY].get_length())
                    editor.buf.data[sY].pop_at(i);
            }
        } else {
            // first partial line
            Slice<UnicodeSymbol> first_part;
            int first_len = editor.buf.data[sY].get_length();
            for (int i = sX; i < first_len; ++i) {
                first_part.push(editor.buf.data[sY][i]);
            }
            editor.clipboard.data.push(first_part);

            // middle full lines
            for (int line = sY + 1; line < eY; ++line) {
                editor.clipboard.data.push(editor.buf.data[line]);
            }

            // last partial line
            Slice<UnicodeSymbol> last_part;
            int last_len = editor.buf.data[eY].get_length();
            int end_idx = std::min(eX, last_len);
            for (int i = 0; i < end_idx; ++i) {
                last_part.push(editor.buf.data[eY][i]);
            }
            editor.clipboard.data.push(last_part);
            editor.clipboard.set_linewise(true);

            // build merged line = prefix of sY (0..sX-1) + suffix of eY (eX..end)
            Slice<UnicodeSymbol> merged;
            for (int i = 0; i < sX && i < editor.buf.data[sY].get_length(); ++i) {
                merged.push(editor.buf.data[sY][i]);
            }
            for (int i = eX; i < editor.buf.data[eY].get_length(); ++i) {
                merged.push(editor.buf.data[eY][i]);
            }

            // assign merged into sY
            editor.buf.data[sY] = merged;

            // remove lines sY+1 .. eY
            int remove_count = eY - sY;
            for (int r = 0; r < remove_count; ++r) {
                // after each pop_at, lines shift up, so always remove at sY+1
                editor.buf.data.pop_at(sY + 1);
            }
        }

        // move cursor to start of selection
        editor.buf.current_pos_y = sY;
        editor.buf.current_pos_x = sX;
        int new_len = editor.buf.data[sY].get_length();
        if (editor.buf.current_pos_x > new_len)
            editor.buf.current_pos_x = new_len;

        editor.buf.selection_active = false;
        // exit to normal mode
        editor.operating_mode = new NormalMode(editor);
        return;
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