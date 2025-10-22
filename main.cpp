#include "include/editor.h"
#include "include/string.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "you need to provide filename" << std::endl;
        return 1;
    }

    Editor editor(argv[1]);
    try {
        editor.run();
    } catch (const std::out_of_range &err) {
        std::cout << err.what() << std::endl;
    }
    return 0;
}