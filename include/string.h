#ifndef STRING_H
#define STRING_H
#include <iostream>

class String {
  private:
    char *data = nullptr;
    unsigned int length = 0;
    unsigned int capacity = 0;

  public:
    String();
    String(const char *);
    String(const String &other);
    ~String();

    char *get_c_style() const;

    String operator+(const String &other);
    String &operator+=(const String &other);
    String &operator=(const String &other);
    String &operator=(const char *str);
    String operator()(int start, int end);
    bool operator==(const String &other) const;
    bool operator==(const char *str) const;
    bool operator!=(const String &other);
    bool operator<(const String &other);
    bool operator>(const String &other);
    bool operator<=(const String &other);
    bool operator>=(const String &other);
    char operator[](unsigned int index);
    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);
};

#endif