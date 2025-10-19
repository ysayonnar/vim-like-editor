#include "../include/string.h"
#include <cstring>
#include <iostream>

String::String() : data(new char[1]), length(0), capacity(1) { data[0] = '\0'; }

String::String(const char *str) : data(nullptr), length(0), capacity(0) {
    if (str != nullptr) {
        length = std::strlen(str);
        capacity = length + 1;
        data = new char[capacity];
        std::strcpy(data, str);
    } else {
        capacity = 1;
        data = new char[capacity];
        data[0] = '\0';
    }
}

String::String(const String &other) : data(nullptr), length(other.length), capacity(other.capacity) {
    if (this != &other) {
        data = new char[capacity];
        std::strcpy(data, other.data);
    }
}

String::~String() { delete[] data; }

char *String::get_c_style() const {
    char *str = new char[capacity];
    std::strcpy(str, data);

    return str;
}

String String::operator+(const String &other) {
    String new_string;

    // Освобождаем память нового объекта
    delete[] new_string.data;

    new_string.length = this->length + other.length;
    new_string.capacity = new_string.length + 1;
    new_string.data = new char[new_string.capacity];

    if (this->length > 0) {
        std::strcpy(new_string.data, this->data);
    } else {
        new_string.data[0] = '\0';
    }

    if (other.length > 0) {
        std::strcat(new_string.data, other.data);
    }

    return new_string;
}

String &String::operator+=(const String &other) {
    *this = *this + other;
    return *this;
}

String &String::operator=(const String &other) {
    if (this == &other) {
        return *this;
    }

    *this = other.data;

    return *this;
}

String &String::operator=(const char *str) {
    int len = std::strlen(str);
    if (len + 1 > capacity) {
        delete[] data;
        capacity = len + 1;
        data = new char[capacity];
    }

    length = len;

    if (str != nullptr) {
        std::strcpy(data, str);
    } else {
        data[0] = '\0';
    }

    return *this;
}

String String::operator()(int start, int end) {
    if (start < 0 || start >= this->length || end < start || end > this->length) {
        return String();
    }

    int substr_length = end - start;
    String sub_string;

    // Освобождаем память подстроки и выделяем новую
    delete[] sub_string.data;
    sub_string.length = substr_length;
    sub_string.capacity = substr_length + 1;
    sub_string.data = new char[sub_string.capacity];

    for (int i = 0; i < substr_length; i++) {
        sub_string.data[i] = this->data[start + i];
    }

    sub_string.data[substr_length] = '\0';

    return sub_string;
}

bool String::operator==(const String &other) const { return std::strcmp(this->data, other.data) == 0; }

bool String::operator==(const char *str) const { return std::strcmp(this->data, str) == 0; }

bool String::operator!=(const String &other) { return std::strcmp(this->data, other.data) != 0; }

bool String::operator<(const String &other) { return std::strcmp(this->data, other.data) < 0; }

bool String::operator>(const String &other) { return std::strcmp(this->data, other.data) > 0; }

bool String::operator<=(const String &other) { return std::strcmp(this->data, other.data) <= 0; }

bool String::operator>=(const String &other) { return std::strcmp(this->data, other.data) >= 0; }

char String::operator[](unsigned int index) {
    if (index >= length) {
        return '\0';
    }
    return data[index];
}

std::ostream &operator<<(std::ostream &os, const String &s) {
    os << s.data;
    return os;
}

std::istream &operator>>(std::istream &is, String &s) {
    const size_t BUFFER_SIZE = 80;
    char buffer[BUFFER_SIZE];

    is >> buffer;

    // Проверяем, достаточно ли текущей памяти
    unsigned int new_length = std::strlen(buffer);
    if (new_length + 1 > s.capacity) {
        delete[] s.data;
        s.capacity = new_length + 1;
        s.data = new char[s.capacity];
    }

    s.length = new_length;
    std::strcpy(s.data, buffer);

    return is;
}
