#include "../include/text_buffer.h"
#include "../include/external/colors.h"
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

int TextBuffer::get_current_pos_x() const { return current_pos_x; }
int TextBuffer::get_current_pos_y() const { return current_pos_y; }

void TextBuffer::next_symbol() {
    int line_length = std::strlen(data[current_pos_y]);

    if (line_length == 0) {
        current_pos_x = 0;
        prev_pos_x = 0;
        return;
    }

    if (current_pos_x >= line_length - 1) {
        current_pos_x = line_length - 1;
        prev_pos_x = current_pos_x;
        return;
    }

    current_pos_x++;
    prev_pos_x = current_pos_x;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    if (current_pos_x >= right_screen_offset + w.ws_col - 9) {
        right_screen_offset++;
    }
}

void TextBuffer::prev_symbol() {
    if (current_pos_x == 0) {
        prev_pos_x = current_pos_x;
        return;
    }

    current_pos_x--;
    prev_pos_x = current_pos_x;

    if (current_pos_x < right_screen_offset) {
        right_screen_offset--;
    }
}

void TextBuffer::next_line() {
    if (current_pos_y == data.get_length() - 1) {
        return;
    }

    current_pos_y++;

    int line_length = std::strlen(data[current_pos_y]);
    if (line_length == 0) {
        current_pos_x = 0;
    } else {
        int preferred = prev_pos_x;
        if (preferred > line_length - 1) {
            current_pos_x = line_length - 1;
        } else {
            current_pos_x = preferred;
        }
    }

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    if (current_pos_y >= top_screen_offset + w.ws_row - 2) {
        top_screen_offset++;
    }

    if (current_pos_x < right_screen_offset) {
        right_screen_offset = current_pos_x;
    } else if (current_pos_x >= right_screen_offset + w.ws_col - 9) {
        right_screen_offset = current_pos_x - (w.ws_col - 9) + 1;
    }
}

void TextBuffer::prev_line() {
    if (current_pos_y == 0) {
        return;
    }

    current_pos_y--;

    int line_length = std::strlen(data[current_pos_y]);
    if (line_length == 0) {
        current_pos_x = 0;
    } else {
        int preferred = prev_pos_x;
        if (preferred > line_length - 1) {
            current_pos_x = line_length - 1;
        } else {
            current_pos_x = preferred;
        }
    }

    if (current_pos_y < top_screen_offset) {
        top_screen_offset--;
    }

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (current_pos_x < right_screen_offset) {
        right_screen_offset = current_pos_x;
    } else if (current_pos_x >= right_screen_offset + w.ws_col - 9) {
        right_screen_offset = current_pos_x - (w.ws_col - 9) + 1;
    }
}

std::ostream &operator<<(std::ostream &os, TextBuffer &buf) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    for (int i = buf.top_screen_offset; i < buf.top_screen_offset + w.ws_row - 2; i++) {
        std::cout << CLEAR_LINE;
        if (i >= buf.data.get_length()) {
            continue;
        }
        if (i == buf.current_pos_y) {
            std::cout << COLOR_BRIGHT_GREEN << STYLE_BOLD << std::left << std::setw(5) << buf.current_pos_y + 1 << "\t" << COLOR_RESET;
        } else {
            std::cout << COLOR_MAGENTA << std::right << std::setw(5) << std::abs(buf.current_pos_y - i) << "\t" << COLOR_RESET;
        }

        int len = std::strlen(buf.data[i]);
        for (int j = buf.right_screen_offset; j < buf.right_screen_offset + w.ws_col - 9 && j < len; j++) {
            if (i == buf.current_pos_y && j == buf.current_pos_x) {
                std::cout << COLOR_BG_WHITE << COLOR_BLACK << buf.data[i][j] << COLOR_RESET;
            } else {
                std::cout << buf.data[i][j];
            }
        }
        std::cout << std::endl;
    }
    std::cout << CLEAR_LINE;

    return os;
}

std::istream &operator>>(std::istream &is, TextBuffer &buf) {
    for (Slice<char *>::Iterator it = buf.data.begin(); it != buf.data.end(); ++it) {
        delete[] *it;
    }
    buf.data.clear();

    buf.current_pos_x = 0;
    buf.current_pos_y = 0;
    buf.prev_pos_x = 0;
    buf.top_screen_offset = 0;
    buf.right_screen_offset = 0;

    std::string line;
    while (std::getline(is, line)) {
        char *cstr = new char[line.size() + 1];
        std::memcpy(cstr, line.c_str(), line.size() + 1);
        buf.data.push(cstr);
    }

    return is;
}
