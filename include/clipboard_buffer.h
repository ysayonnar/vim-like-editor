#ifndef CLIPBOARD_BUFFER_H
#define CLIPBOARD_BUFFER_H

#include "text_buffer.h"

class ClipboardBuffer : public TextBuffer {
  public:
    ClipboardBuffer() = default;
    ~ClipboardBuffer() = default;

    void clear();
    void copy_from(const TextBuffer &source, int start_line, int end_line);
    void paste_into(TextBuffer &target, int line_position) const;
};

#endif
