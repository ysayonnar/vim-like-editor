#include "include/editor.h"
#include "include/string.h"
#include "include/text_buffer.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "you need to provide filename" << std::endl;
        return 1;
    }

    Editor editor(argv[1]);
    editor.run();
    return 0;
}