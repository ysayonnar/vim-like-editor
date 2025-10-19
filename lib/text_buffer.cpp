#include "../include/text_buffer.h"
#include <cstring>
#include <iostream>

int TextBuffer::get_length() const { return length; }
int TextBuffer::get_current_symbol_number() const { return current_symbol_number; }
int TextBuffer::get_current_pos_x() const { return current_pos_x; }
int TextBuffer::get_current_pos_y() const { return current_pos_y; }

void TextBuffer::next_symbol() {
    if (current_symbol_number == length - 1 || data[current_symbol_number + 1] == '\n' || data[current_symbol_number] == '\n') {
        return;
    }

    current_symbol_number++;
    current_pos_x++;
}

void TextBuffer::prev_symbol() {
    if (current_symbol_number == 0 || current_pos_x == 0) {
        return;
    }

    current_symbol_number--;
    current_pos_x--;
}

std::ostream &operator<<(std::ostream &os, const TextBuffer &buf) {
    os << buf.data << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, TextBuffer &buf) {
    if (buf.data) {
        delete[] buf.data;
        buf.data = nullptr;
    }
    buf.length = 0;
    buf.current_pos_x = 0;
    buf.current_pos_y = 0;
    buf.current_symbol_number = 0;

    std::string temp((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());

    buf.length = temp.size();

    buf.data = new char[buf.length + 1];
    std::memcpy(buf.data, temp.c_str(), buf.length + 1);

    return is;
}
