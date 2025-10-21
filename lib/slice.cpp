#include "../include/containers/slice.h"
#include <stdexcept>
#include <utility>

template <typename T>
void Slice<T>::resize(int new_capacity) {
    T *new_data = new T[new_capacity];
    for (int i = 0; i < length; i++) {
        new_data[i] = std::move(data[i]);
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

template <typename T>
int Slice<T>::get_length() const { return length; }

template <typename T>
int Slice<T>::get_capacity() const { return capacity; }

template <typename T>
bool Slice<T>::is_empty() const {
    return length == 0;
}

template <typename T>
void Slice<T>::push(const T &value) {
    if (length == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    data[length++] = value;
}

template <typename T>
void Slice<T>::push_after(const T &value, int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("index is out of range");
    }

    if (length == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }

    for (int i = length; i > index + 1; i--) {
        data[i] = std::move(data[i - 1]);
    }

    data[index + 1] = value;
    length++;
}

template <typename T>
T Slice<T>::pop() {
    if (length == 0) {
        throw std::out_of_range("slice is empty");
    }
    return std::move(data[--length]);
}

template <typename T>
T Slice<T>::pop_at(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("index out of range");
    }

    T removed = std::move(data[index]);

    for (int i = index; i < length - 1; i++) {
        data[i] = std::move(data[i + 1]);
    }

    length--;
    return removed;
}

template <typename T>
T &Slice<T>::operator[](int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("index is out of range");
    }

    return data[index];
}

template <typename T>
const T &Slice<T>::operator[](int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("index is out of range");
    }

    return data[index];
}

template <typename T>
Slice<T> &Slice<T>::operator=(const Slice<T> &other) {
    if (this == &other) {
        return *this;
    }

    delete[] data;
    data = new T[other.capacity];
    length = other.length;
    capacity = other.capacity;

    for (int i = 0; i < length; i++) {
        data[i] = other.data[i];
    }

    return *this;
}

template <typename T>
Slice<T> &Slice<T>::operator=(Slice<T> &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete[] data;

    data = other.data;
    length = other.length;
    capacity = other.capacity;
    other.data = nullptr;
    other.length = 0;
    other.capacity = 0;

    return *this;
}