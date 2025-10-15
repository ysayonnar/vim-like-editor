#include "include/string.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "you need to provide filename" << std::endl;
        return 1;
    }

    String filename(argv[1]);
    std::ifstream file(filename.get_c_style());
    if (!file.is_open()) {
        std::cout << "error while reading file " << filename << std::endl;
        return 1;
    }

    // FIXME: писать в класс буфера
    String file_data;
    file >> file_data;

    std::cout << file_data << std::endl;
    file.close();

    return 0;
}