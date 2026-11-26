#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <iostream>

// Problem 3 (Dynamic Array 2.0) builds on your Problem 2 Dynarray.
// Start from your finished p2.cc, then add everything required by the
// handout:
//   - public type alias members (size_type, value_type, pointer, reference,
//     const_pointer, const_reference)
//   - subscript operator a[i] (like at(i), but no bounds checking)
//   - the six relational operators (lexicographical comparison,
//     no loops/recursions allowed)
//   - operator<< printing "[e1, e2, ...]"
class Dynarray {
  int *data;
  std::size_t len;
  public:
  using size_type = std::size_t;
  using value_type = int;
  using pointer = value_type*;
  using reference = value_type&;
  using const_pointer = const value_type*;
  using const_reference = const value_type&;
    Dynarray() : data(nullptr), len(0) {}
    explicit Dynarray(std::size_t n) : data(new int[n]), len(n) {
        for (std::size_t i = 0; i < len; ++i) {
            data[i] = 0;
        }   
    }
    Dynarray(std::size_t n, int x) : data(new int[n]), len(n) {
        for (std::size_t i = 0; i < len; ++i) {
            data[i] = x;
        }
    }
    Dynarray(const int *begin, const int *end) : data(new int[end - begin]), len(end - begin) {
        for (std::size_t i = 0; i < len; ++i) {
            data[i] = begin[i];
        }
    }
    std::size_t size() const {
        return len;
    }
    bool empty() const {
        return len == 0;
    }
    int &at(std::size_t i) {
        if (i >= len) {
            throw std::out_of_range("Index out of range!");
        }
        return data[i];
    }
    const int &at(std::size_t i) const {
        if (i >= len) {
            throw std::out_of_range("Index out of range!");
        }
        return data[i];
    }
    ~Dynarray() {
        delete[] data;
    } 
    Dynarray(const Dynarray &other) : data(new int[other.len]), len(other.len) {
        for (std::size_t i = 0; i < len; ++i) {
            data[i] = other.data[i];
        }
    }
    Dynarray &operator=(const Dynarray &other) {
        if (this != &other) {
            Dynarray temp(other);
            int* temp_data = data;
            data = temp.data;
            temp.data = temp_data;
            std::size_t temp_len = len;
            len = temp.len;
            temp.len = temp_len;
        }
        return *this;
    }

    Dynarray(Dynarray &&other) noexcept : data(other.data), len(other.len) {
        other.data = nullptr;
        other.len = 0;
    }
    Dynarray &operator=(Dynarray &&other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            len = other.len;
            other.data = nullptr;
            other.len = 0;
        }
        return *this;
    }
  reference operator[](size_type i) {
    return data[i];
  } 
  const_reference operator[](size_type i) const {
    return data[i];
  }
  bool operator==(const Dynarray &other) const {
    return len == other.len && std::equal(data, data + len, other.data);
  }
  bool operator!=(const Dynarray &other) const {
    return !(*this == other);
  }
  bool operator<(const Dynarray &other) const {
    return std::lexicographical_compare(data, data + len, other.data, other.data + other.len);
  }
  bool operator<=(const Dynarray &other) const {
    return !(*this > other);
  }
  bool operator>(const Dynarray &other) const {
    return other < *this;
  }
  bool operator>=(const Dynarray &other) const {
    return !(*this < other);
  }
  friend std::ostream& operator<<(std::ostream &os, const Dynarray &arr) {
    os << "[";
    for (size_type i = 0; i < arr.len; ++i) {
        os << arr.data[i];
        if (i < arr.len - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
  }
};

#endif // DYNARRAY_HPP
