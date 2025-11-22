#ifndef EDITOR_H
#define EDITOR_H

#include "clipboard_buffer.h"
#include "modes/insert_mode.h"
#include "modes/normal_mode.h"
#include "modes/operating_mode.h"
#include "modes/visual_mode.h"
#include "string.h"
#include "text_buffer.h"
#include <fstream>
#include <iostream>
#include <termios.h>

class Editor {
  public:
    OperatingMode *operating_mode = nullptr;
    String filename;
    std::ifstream file;
    TextBuffer buf;
    ClipboardBuffer clipboard;
    String command_input = "";
    struct termios original_termios;

    Editor(String filename) : filename(filename) {
        file.open(filename.get_c_style(), std::ios::in);
        if (!file.is_open()) {
            std::cerr << "error while reading file " << filename << std::endl;
            buf.data.push(Slice<UnicodeSymbol>());
            operating_mode = new NormalMode(*this);
            return;
        }

        file >> buf;
        operating_mode = new NormalMode(*this);
    }

    ~Editor() {
        if (file.is_open())
            file.close();
        if (operating_mode)
            delete operating_mode;
    }

    void run();
    void render();
    void clear_screen();
    void print_toolbar();
};

#endif
