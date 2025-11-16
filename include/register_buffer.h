#ifndef REGISTER_BUFFER_H
#define REGISTER_BUFFER_H

#include "clipboard_buffer.h"
#include <map>
#include <string>

class RegisterBuffer : public ClipboardBuffer {
  private:
    std::map<char, Slice<char *>> registers;

  public:
    RegisterBuffer() = default;
    ~RegisterBuffer() = default;

    void save_to_register(char reg_name);

    void paste_from_register(char reg_name, TextBuffer &target, int line_position) const;

    void clear_registers();
};

#endif
