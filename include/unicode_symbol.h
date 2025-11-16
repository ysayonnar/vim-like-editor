#ifndef UNICODE_SYMBOL_H
#define UNICODE_SYMBOL_H

#include <iostream>
#include <string>

class UnicodeSymbol {
  public:
    std::string symbol;
    int length;

    UnicodeSymbol() = default;
    UnicodeSymbol(const std::string &symbol) : symbol(symbol), length(static_cast<int>(symbol.length())) {}
    ~UnicodeSymbol() = default;

    bool is_space() {
        return std::strcmp(symbol.c_str(), " ") == 0;
    }

    friend std::ostream &operator<<(std::ostream &os, const UnicodeSymbol &s) {
        os << s.symbol;
        return os;
    }
};

#endif