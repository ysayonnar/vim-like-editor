#ifndef CLIPBOARD_BUFFER_H
#define CLIPBOARD_BUFFER_H

#include "text_buffer.h"

class ClipboardBuffer : public TextBuffer {
  public:
    ClipboardBuffer() = default;
    ~ClipboardBuffer() = default;

    // Флаг: содержимое буфера построчное (true) или посимвольное (false)
    bool linewise = false;

    void clear();
    void copy_from(const TextBuffer &source, int start_line, int end_line);
    // Вставка: если postрочно -> добавить строки после (line_position),
    // если посимвольно -> вставить символы в target на (line_position, col_position)
    void paste_into(TextBuffer &target, int line_position, int col_position) const;
    void set_linewise(bool v) { linewise = v; }
    bool is_linewise() const { return linewise; }
};

#endif
