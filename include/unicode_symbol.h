#ifndef UNICODE_SYMBOL_H
#define UNICODE_SYMBOL_H

#include <iostream>
#include <string>

class UnicodeSymbol {
  private:
    std::string symbol;
    int length;

  public:
    UnicodeSymbol() = default;
    UnicodeSymbol(const std::string &symbol) : symbol(symbol), length(static_cast<int>(symbol.length())) {}
    ~UnicodeSymbol() = default;

    friend std::ostream &operator<<(std::ostream &os, const UnicodeSymbol &s) {
        // for (int i = 0; i < s.length; i++) {
        //     os << s.symbol[i];
        // }
        os << s.symbol;
        return os;
    }
};

#endif