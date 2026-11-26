#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <cstddef>
#include <stdexcept>

class Dynarray {
  int *data;
  std::size_t len;
  public:
    Dynarray() : data(nullptr), len(0) {}
    explicit Dynarray(std::size_t n) : data(new int[n]), len(n) {}
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
            throw std::out_of_range("Index out of range");
        }
        return data[i];
    }
    const int &at(std::size_t i) const {
        if (i >= len) {
            throw std::out_of_range("Index out of range");
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

};

#endif // DYNARRAY_HPP
   