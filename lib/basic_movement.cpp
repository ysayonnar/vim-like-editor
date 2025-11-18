#include "../include/commands/basic_movement.h"
#include "../include/editor.h"
#include <cctype>
#include <string>

int extract_num(String str) {
    int result = 0;
    for (int i = 0; i < str.get_length(); i++) {
        if (std::isdigit(str[i])) {
            result = result * 10 + (str[i] - '0');
        } else {
            break;
        }
    }

    return result;
}

void MoveLeft::execute(String combination) const {
    int times_to_repeat = extract_num(combination);
    if (times_to_repeat == 0) {
        times_to_repeat = 1;
    }
    for (int i = 0; i < times_to_repeat; i++) {
        editor.buf.prev_symbol();
    }
}

void MoveRight::execute(String combination) const {
    int times_to_repeat = extract_num(combination);
    if (times_to_repeat == 0) {
        times_to_repeat = 1;
    }
    for (int i = 0; i < times_to_repeat; i++) {
        editor.buf.next_symbol();
    }
}

void MoveUp::execute(String combination) const {
    int times_to_repeat = extract_num(combination);
    if (times_to_repeat == 0) {
        times_to_repeat = 1;
    }
    for (int i = 0; i < times_to_repeat; i++) {
        editor.buf.prev_line();
    }
}

void MoveDown::execute(String combination) const {
    int times_to_repeat = extract_num(combination);
    if (times_to_repeat == 0) {
        times_to_repeat = 1;
    }
    for (int i = 0; i < times_to_repeat; i++) {
        editor.buf.next_line();
    }
}

void MoveNextWord::execute(String combination) const {
    int times_to_repeat = extract_num(combination);
    if (times_to_repeat == 0) {
        times_to_repeat = 1;
    }
    for (int i = 0; i < times_to_repeat; i++) {
        editor.buf.next_word();
    }
}

void MovePrevWord::execute(String combination) const {
    int times_to_repeat = extract_num(combination);
    if (times_to_repeat == 0) {
        times_to_repeat = 1;
    }
    for (int i = 0; i < times_to_repeat; i++) {
        editor.buf.prev_word();
    }
}

void MoveBeginBuf::execute(String combination) const {
    editor.buf.move_to_begin();
}

void MoveEndBuf::execute(String combination) const {
    editor.buf.move_to_end();
}

void MoveBeginLine::execute(String combination) const {
    editor.buf.start_line();
}

void MoveEndLine::execute(String combination) const {
    editor.buf.end_line();
}