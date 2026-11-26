#ifndef SMART_POINTERS_HPP
#define SMART_POINTERS_HPP 1

#include <cstddef>
#include <utility>

// Problem 4 (Smart Pointers): implement UniquePtr<T> and SharedPtr<T>.
// See the handout for the full requirements:
//
// UniquePtr<T>: exclusive ownership.
//   - default ctor (owns nothing), ctor from T*, destructor deletes
//   - copy ctor/assignment = delete; move ctor/assignment noexcept,
//     self-assignment safe, source becomes "null"
//   - *p, *cp (const), p->, explicit operator bool, get()
//   - reset(T* = nullptr), release()
//
// SharedPtr<T>: shared ownership via reference counting.
//   - default ctor (owns nothing), ctor from T* (count starts at 1)
//   - copy ctor/assignment increment the counter; copy-assignment must be
//     self-assignment safe (increment before decrement!)
//   - move ctor/assignment steal the pointer (noexcept), source becomes empty
//   - destructor decrements; destroys the object exactly once at zero
//   - *p, p->, explicit operator bool, get(), use_count()
//
// Do NOT include <memory>.

template <typename T>
class UniquePtr {
  T* ptr;
  public:
  UniquePtr() : ptr(nullptr) {}
  explicit UniquePtr(T* p) : ptr(p) {};
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
  }
  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
      delete ptr;
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  }
  ~UniquePtr() {
    delete ptr;
  }
  T& operator*() const {
    return *ptr;
  }
  T* operator->() const {
    return ptr;
  }
  explicit operator bool() const {
    return ptr != nullptr;
  }
  T* get() const {
    return ptr;
  }
  void reset(T* p = nullptr) {
    delete ptr;
    ptr = p;
  }
  T* release() {
    T* old_ptr = ptr;
    ptr = nullptr;
    return old_ptr;
  }
};

template <typename T>
class SharedPtr {
  private:
  T* ptr;
  std::size_t* count;
  public:
  SharedPtr() : ptr(nullptr), count(new std::size_t(0)) {}
  explicit SharedPtr(T* p) : ptr(p), count(new std::size_t(1)) {}
  SharedPtr(const SharedPtr& other) : ptr(other.ptr), count(other.count) {
    ++(*count);
  }
  SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {
      --(*count);
      if (*count == 0) {
        delete ptr;
        delete count;
      }
      ptr = other.ptr;
      count = other.count;
      ++(*count);
    }
    return *this;
  }
  SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), count(other.count) {
    other.ptr = nullptr;
    other.count = new std::size_t(0);
  }
  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
      --(*count);
      if (*count == 0) {
        delete ptr;
        delete count;
      }
      ptr = other.ptr;
      count = other.count;
      other.ptr = nullptr;
      other.count = new std::size_t(0);
    }
    return *this;
  }
  ~SharedPtr() {
    --(*count);
    if (*count == 0) {
      delete ptr;
      delete count;
    }
  }
  T& operator*() const {
    return *ptr;
  }
  T* operator->() const {
    return ptr;
  }
  explicit operator bool() const {
    return ptr != nullptr;
  }
  T* get() const {
    return ptr;
  }
  std::size_t use_count() const {
    return *count;
  }
};

#endif // SMART_POINTERS_HPP
