#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

#include "containers/slice.h"
#include "string.h"
#include "unicode_symbol.h"
#include <iostream>

class TextBuffer {
  public:
    int current_pos_x = 0;
    int current_pos_y = 0;

    int prev_pos_x = 0;

    int top_screen_offset = 0;
    int right_screen_offset = 0;

    Slice<Slice<UnicodeSymbol>> data;

    bool selection_active = false;
    int sel_anchor_x = 0;
    int sel_anchor_y = 0;

    TextBuffer() {
        data = Slice<Slice<UnicodeSymbol>>();
    };
    ~TextBuffer() = default;

    int get_current_pos_x() const;
    int get_current_pos_y() const;

    void next_symbol();
    void prev_symbol();

    void next_word();
    void prev_word();

    void next_line();
    void prev_line();

    void move_to_end();
    void move_to_begin();

    void end_line();
    void start_line();

    void cut_current_symbol();
    void cut_current_line();

    void new_line_after();
    void new_line_before();

    void save(String filename);

    friend std::ostream &operator<<(std::ostream &os, TextBuffer &buf);
    friend std::istream &operator>>(std::istream &is, TextBuffer &buf);
};

#endif
