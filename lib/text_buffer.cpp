#include "../include/text_buffer.h"
#include "../include/containers/slice.h"
#include "../include/external/colors.h"
#include "../include/unicode_symbol.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

int TextBuffer::get_current_pos_x() const { return current_pos_x; }
int TextBuffer::get_current_pos_y() const { return current_pos_y; }

void TextBuffer::next_symbol() {
    int line_length = data[current_pos_y].get_length();

    if (line_length == 0) {
        current_pos_x = 0;
        prev_pos_x = 0;
        return;
    }

    // Разрешаем курсору находиться на позиции сразу после последнего символа (индекс == длина строки)
    if (current_pos_x < line_length) {
        current_pos_x++;
    } else {
        // Уже у или за концом строки — зафиксируем позицию в конце
        current_pos_x = line_length;
    }
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

    int line_length = data[current_pos_y].get_length();
    if (line_length == 0) {
        current_pos_x = 0;
    } else {
        int preferred = prev_pos_x;
        // Предпочтительная позиция курсора не может превышать длину строки (разрешена позиция «после конца»)
        if (preferred > line_length) {
            current_pos_x = line_length;
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

    int line_length = data[current_pos_y].get_length();
    if (line_length == 0) {
        current_pos_x = 0;
    } else {
        int preferred = prev_pos_x;
        if (preferred > line_length) {
            current_pos_x = line_length;
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

void TextBuffer::next_word() {
    int len = data[current_pos_y].get_length();

    while (current_pos_x < len && !data[current_pos_y][current_pos_x].is_space()) {
        current_pos_x++;
    }

    while (current_pos_x < len && data[current_pos_y][current_pos_x].is_space()) {
        current_pos_x++;
    }

    while (current_pos_x >= len && current_pos_y < data.get_length() - 1) {
        current_pos_y++;
        current_pos_x = 0;
        len = data[current_pos_y].get_length();

        while (current_pos_x < len && data[current_pos_y][current_pos_x].is_space()) {
            current_pos_x++;
        }
    }

    prev_pos_x = current_pos_x;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (current_pos_x >= right_screen_offset + w.ws_col - 9) {
        right_screen_offset = current_pos_x - (w.ws_col - 9) + 1;
    }
}

void TextBuffer::prev_word() {
    while (current_pos_x > 0 && data[current_pos_y][current_pos_x - 1].is_space()) {
        current_pos_x--;
    }

    while (current_pos_x > 0 && !data[current_pos_y][current_pos_x - 1].is_space()) {
        current_pos_x--;
    }

    while (current_pos_x == 0 && current_pos_y > 0) {
        current_pos_y--;
        current_pos_x = data[current_pos_y].get_length();

        while (current_pos_x > 0 && data[current_pos_y][current_pos_x - 1].is_space()) {
            current_pos_x--;
        }
    }

    prev_pos_x = current_pos_x;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (current_pos_x < right_screen_offset) {
        right_screen_offset = current_pos_x;
    } else if (current_pos_x >= right_screen_offset + w.ws_col - 9) {
        right_screen_offset = current_pos_x - (w.ws_col - 9) + 1;
    }
}

void TextBuffer::move_to_end() {
    prev_pos_x = 0;
    current_pos_x = 0;
    current_pos_y = data.get_length() - 1;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (current_pos_y > w.ws_row - 3) {
        top_screen_offset = current_pos_y - w.ws_row + 3;
    }
    right_screen_offset = 0;
}

void TextBuffer::move_to_begin() {
    prev_pos_x = 0;
    current_pos_x = 0;
    current_pos_y = 0;
    right_screen_offset = 0;
    top_screen_offset = 0;
}

void TextBuffer::cut_current_symbol() {
    int cur_line_length = data[current_pos_y].get_length();
    if (cur_line_length == 0 || current_pos_x == cur_line_length) {
        return;
    }
    data[current_pos_y].pop_at(current_pos_x);

    if (current_pos_x == cur_line_length - 1) {
        prev_symbol();
    }
}

void TextBuffer::cut_current_line() {
    if (data.get_length() == 1) {
        data[current_pos_y].clear();
        return;
    }

    data.pop_at(current_pos_y);

    if (current_pos_y == data.get_length()) {
        prev_line();
    }
}

void TextBuffer::new_line_after() {
    data.push_after(Slice<UnicodeSymbol>(), current_pos_y);
}

void TextBuffer::new_line_before() {
    data.push_after(Slice<UnicodeSymbol>(), current_pos_y - 1);
}

void TextBuffer::end_line() {
    // Перемещаем курсор на позицию «после конца строки» (поведение команды $)
    int len = data[current_pos_y].get_length();
    current_pos_x = len; // позиция сразу после последнего символа

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int visible = w.ws_col - 9;
    if (current_pos_x >= visible) {
        right_screen_offset = current_pos_x - visible + 1;
    }
}

void TextBuffer::start_line() {
    prev_pos_x = 0;
    current_pos_x = 0;
    right_screen_offset = 0;
}

void TextBuffer::save(String filename) {
    std::ofstream outFile(filename.get_c_style(), std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "error while saving file " << filename << std::endl;
        return;
    }

    for (int i = 0; i < data.get_length(); i++) {
        for (int j = 0; j < data[i].get_length(); j++) {
            outFile << data[i][j];
        }
        if (i != data.get_length() - 1) {
            outFile << '\n';
        }
    }

    outFile.close();
}

std::ostream &operator<<(std::ostream &os, TextBuffer &buf) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    for (int i = buf.top_screen_offset; i < buf.top_screen_offset + w.ws_row - 2; i++) {
        std::cout << CLEAR_LINE;
        if (i >= buf.data.get_length()) {
            std::cout << COLOR_BLUE << std::right << std::setw(5) << "~" << "\t" << COLOR_RESET;
            std::cout << std::endl;
            continue;
        }
        if (i == buf.current_pos_y) {
            std::cout << COLOR_GREEN << STYLE_BOLD << std::left << std::setw(5) << buf.current_pos_y + 1 << "\t" << COLOR_RESET;
        } else {
            std::cout << COLOR_CYAN << std::right << std::setw(5) << std::abs(buf.current_pos_y - i) << "\t" << COLOR_RESET;
        }

        int len = buf.data[i].get_length();
        int visible = w.ws_col - 9;
        int start = buf.right_screen_offset;
        int end = std::min(buf.right_screen_offset + visible, len);

        int printed = 0;

        auto is_selected_pos = [&](int line, int col) {
            if (!buf.selection_active)
                return false;

            int ay = buf.sel_anchor_y;
            int ax = buf.sel_anchor_x;
            int by = buf.current_pos_y;
            int bx = buf.current_pos_x;

            int sY = ay, sX = ax, eY = by, eX = bx;
            if (sY > eY || (sY == eY && sX > eX)) {
                sY = by;
                sX = bx;
                eY = ay;
                eX = ax;
            }

            if (line < sY || line > eY)
                return false;

            int line_len = buf.data[line].get_length();

            if (sY == eY) {
                int end_index = std::min(eX - 1, line_len - 1);
                if (end_index < 0)
                    return false;
                return col >= sX && col <= end_index;
            }

            if (line == sY) {
                return col >= sX && col < line_len;
            }
            if (line == eY) {
                int end_index = std::min(eX - 1, line_len - 1);
                if (end_index < 0)
                    return false;
                return col <= end_index;
            }

            // Для полностью выделенных строк выделяются все существующие символы
            return col < line_len;
        };

        for (int j = start; j < end; j++) {
            if (is_selected_pos(i, j)) {
                // Серый фон для выделения, белый цвет текста
                std::cout << COLOR_BG_BRIGHT_BLACK << COLOR_WHITE << buf.data[i][j] << COLOR_RESET;
            } else if (i == buf.current_pos_y && j == buf.current_pos_x) {
                std::cout << COLOR_BG_WHITE << COLOR_BLACK << buf.data[i][j] << COLOR_RESET;
            } else {
                std::cout << buf.data[i][j];
            }
            printed++;
        }

        // Если курсор стоит на позиции «после конца» и видим на экране, покажем подсвеченный пробел-метку
        if (i == buf.current_pos_y && buf.current_pos_x == len && buf.current_pos_x >= buf.right_screen_offset && buf.current_pos_x < buf.right_screen_offset + visible) {
            int target_col = buf.current_pos_x - buf.right_screen_offset; // индекс в пределах видимой области (с нуля)
            int pad = target_col - printed;
            for (int p = 0; p < pad; ++p)
                std::cout << ' ';
            std::cout << COLOR_BG_WHITE << COLOR_BLACK << ' ' << COLOR_RESET;
        }

        std::cout << std::endl;
    }
    std::cout << CLEAR_LINE;

    return os;
}

std::istream &operator>>(std::istream &is, TextBuffer &buf) {
    buf.data.clear();

    buf.current_pos_x = 0;
    buf.current_pos_y = 0;
    buf.prev_pos_x = 0;
    buf.top_screen_offset = 0;
    buf.right_screen_offset = 0;

    std::string line;
    while (std::getline(is, line)) {
        Slice<UnicodeSymbol> unicode_line;
        for (int i = 0; i < static_cast<int>(line.length());) {
            unsigned char c = static_cast<unsigned char>(line[i]);
            int symbol_length = 1;

            if ((c & 0x80) == 0) {
                symbol_length = 1;
            } else if ((c & 0xE0) == 0xC0) {
                symbol_length = 2;
            } else if ((c & 0xF0) == 0xE0) {
                symbol_length = 3;
            } else if ((c & 0xF8) == 0xF0) {
                symbol_length = 4;
            }

            UnicodeSymbol symbol(line.substr(i, symbol_length));
            unicode_line.push(symbol);
            i += symbol_length;
        }
        buf.data.push(unicode_line);
    }

    if (buf.data.get_length() == 0) {
        buf.data.push(Slice<UnicodeSymbol>());
    }

    return is;
}
