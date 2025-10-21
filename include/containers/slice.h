#ifndef SLICE_H
#define SLICE_H

#include <stdexcept>
#include <utility>

template <typename T>
class Slice {
  private:
    T *data = nullptr;
    int length = 0;
    int capacity = 0;

    void resize(int new_capacity);

  public:
    Slice() = default;
    Slice(unsigned int capacity) : capacity(capacity), data(new T[capacity]), length(0) {};

    Slice(const Slice &other) : data(new T[other.capacity]), length(other.length), capacity(other.capacity) {
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
    }

    Slice(Slice &&other) noexcept : data(other.data), length(other.length), capacity(other.capacity) {
        other.data = nullptr;
        other.length = 0;
        other.capacity = 0;
    }

    ~Slice() {
        delete[] data;
    };

    int get_length() const;
    int get_capacity() const;

    void clear();
    bool is_empty() const;
    void push(const T &value);
    void push_after(const T &value, int index);
    T pop();
    T pop_at(int index);

    T &operator[](int index);
    const T &operator[](int index) const;
    Slice &operator=(const Slice &other);
    Slice &operator=(Slice &&other) noexcept;

    class Iterator {
      private:
        T *ptr;

      public:
        explicit Iterator(T *p) : ptr(p) {}

        T &operator*() { return *ptr; }
        const T &operator*() const { return *ptr; }

        Iterator &operator++() {
            ++ptr;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++ptr;
            return tmp;
        }
        Iterator &operator--() {
            --ptr;
            return *this;
        }
        Iterator operator--(int) {
            Iterator tmp = *this;
            --ptr;
            return tmp;
        }

        bool operator==(const Iterator &other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator &other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + length); }
};

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
void Slice<T>::clear() {
    length = 0;
}

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

#endif