#include "../include/editor.h"
#include "../include/string.h"
#include "string.h"
#include <iostream>

void Editor::run() {
    String input("");
    while (true) {
        render_buffer();
        std::cin >> input;

        operating_mode->handle_input(input);
    }
}

void Editor::render_buffer() {
    std::cout << "\033[2J\033[H" << buf << std::endl;
}