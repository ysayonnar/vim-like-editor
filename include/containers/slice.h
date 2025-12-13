#ifndef SLICE_H
#define SLICE_H

#include "iterator.h"
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

    Slice(const Slice &other);
    Slice(Slice &&other) noexcept;

    ~Slice();

    int get_length() const;
    int get_capacity() const;

    void clear();
    bool is_empty() const;
    void push(const T &value);
    void push_after(const T &value, int index);
    void insert_at(int index, const T &value);
    T pop();
    T pop_at(int index);

    T &operator[](int index);
    const T &operator[](int index) const;
    Slice &operator=(const Slice &other);
    Slice &operator=(Slice &&other) noexcept;

    using Iterator = SliceIterator<T>;

    Iterator begin();
    Iterator end();
};

#include "../../lib/slice.tpp"

#endif