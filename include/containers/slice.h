#ifndef SLICE_H
#define SLICE_H

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

#endif