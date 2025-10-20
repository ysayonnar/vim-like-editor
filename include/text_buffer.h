#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

#include <cstring>
#include <iostream>
#include <istream>

#define RESET "\033[0m"
#define WHITE_BG "\033[47m"

class TextBuffer {
  private:
    int length = 0;
    char *data = nullptr; // TODO: подумать над хранением и изменением, мб сделать построчную запись, но тогда нужен свой контейнер слайс-вектор
    int current_symbol_number = 0;
    int current_pos_x = 0;
    int current_pos_y = 0;

  public:
    TextBuffer() {}
    ~TextBuffer() {
        delete[] data;
    }

    int get_length() const;
    int get_current_symbol_number() const;
    int get_current_pos_x() const;
    int get_current_pos_y() const;

    void next_symbol();
    void prev_symbol();

    void next_word();
    void prev_word();

    void next_line();
    void prev_line();

    friend std::ostream &operator<<(std::ostream &os, const TextBuffer &buf);
    friend std::istream &operator>>(std::istream &is, TextBuffer &buf);
};

#endif
