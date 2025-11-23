#include "../include/clipboard_buffer.h"

void ClipboardBuffer::clear() {
    data.clear();
    linewise = false;
}

void ClipboardBuffer::copy_from(const TextBuffer &source, int start_line, int end_line) {
    clear();
    if (start_line < 0)
        start_line = 0;
    if (end_line >= source.data.get_length())
        end_line = source.data.get_length() - 1;
    for (int i = start_line; i <= end_line; ++i) {
        // Копируем всю строку — это построчный буфер
        Slice<UnicodeSymbol> line_copy = source.data[i];
        data.push(line_copy);
    }
    linewise = true;
}

void ClipboardBuffer::paste_into(TextBuffer &target, int line_position, int col_position) const {
    if (data.get_length() == 0)
        return;

    if (linewise) {
        int insert_at = line_position;
        for (int i = 0; i < data.get_length(); ++i) {
            target.data.push_after(data[i], insert_at + i);
        }
    } else {
        // По символам: вставляем символы из первой записи буфера в target на (line_position, col_position)
        if (data.get_length() >= 1) {
            Slice<UnicodeSymbol> chars = data[0];
            // Вставляем каждый символ в строку target по смещению col_position
            for (int i = 0; i < chars.get_length(); ++i) {
                target.data[line_position].insert_at(col_position + i, chars[i]);
            }
        }
    }
}
