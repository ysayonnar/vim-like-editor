#ifndef SLICE_ITERATOR_H
#define SLICE_ITERATOR_H

template <typename T>
class SliceIterator {
  private:
    T *ptr;

  public:
    explicit SliceIterator(T *p) : ptr(p) {}

    T &operator*() { return *ptr; }
    const T &operator*() const { return *ptr; }

    SliceIterator &operator++() {
        ++ptr;
        return *this;
    }
    SliceIterator operator++(int) {
        SliceIterator tmp = *this;
        ++ptr;
        return tmp;
    }
    SliceIterator &operator--() {
        --ptr;
        return *this;
    }
    SliceIterator operator--(int) {
        SliceIterator tmp = *this;
        --ptr;
        return tmp;
    }

    bool operator==(const SliceIterator &other) const { return ptr == other.ptr; }
    bool operator!=(const SliceIterator &other) const { return ptr != other.ptr; }
};

#endif
