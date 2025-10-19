#ifndef EDITOR_H
#define EDITOR_H

#include "modes/normal_mode.h"
#include "modes/operating_mode.h"
#include "string.h"
#include "text_buffer.h"
#include <fstream>
#include <iostream>

class Editor {
  private:
    OperatingMode *operating_mode;
    String filename;
    std::ifstream file;
    TextBuffer buf;

  public:
    Editor(String filename) : filename(filename) {
        file.open(filename.get_c_style());
        if (!file.is_open()) {
            std::cerr << "error while reading file " << filename << std::endl;
            return;
        }

        file >> buf;
        operating_mode = new NormalMode(*this);
    }
    ~Editor() {
        file.close();
        delete operating_mode;
    }

    void run();
};

#endif
