#ifndef EDITOR_H
#define EDITOR_H

#include <cstring>

class TextBuffer {
  private:
    int length;
    char *data;
    int current_pos_x = 0;
    int current_pos_y = 0;

  public:
    TextBuffer(char *data) : data(data), length(strlen(data)) {}
    ~TextBuffer() {
        delete data;
    }

    int get_length() const;
    int get_current_pos_x() const;
    int get_current_pos_x() const;

    // TODO: методы nextWord(), nextSymbol() и тп
};

#endif