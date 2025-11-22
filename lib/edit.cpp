#include "../include/commands/edit.h"
#include "../include/commands/basic_movement.h"
#include "../include/editor.h"

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