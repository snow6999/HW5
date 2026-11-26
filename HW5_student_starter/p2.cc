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
            delete[] data;
            len = other.len;
            data = new int[len];
            for (std::size_t i = 0; i < len; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Dynarray(Dynarray &&other) noexcept : data(other.data), len(other.len) {
        other.data = nullptr;
        other.len = 0;
    }
};

#endif // DYNARRAY_HPP
   