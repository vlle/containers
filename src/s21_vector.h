#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

#include <cstring>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class vector {
  // in-class type overrides
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Main public methods for interacting with the class
 public:
  vector() : size_(0), capacity_(0), arr_(nullptr) {}

  explicit vector(size_type n)
      : size_(n), capacity_(n), arr_(n ? new value_type[n]() : nullptr) {}

  vector(std::initializer_list<value_type> const &items)
      : vector(items.size()) {
    std::copy(items.begin(), items.end(), arr_);
  }

  vector(const vector &v) : vector(v.size_) {
    std::copy(v.arr_, v.arr_ + v.size_, arr_);
  }

  vector(vector &&v) noexcept {
    size_ = std::exchange(v.size_, 0);
    capacity_ = std::exchange(v.capacity_, 0);
    arr_ = std::exchange(v.arr_, nullptr);
  }

  ~vector() { delete[] arr_; }

  vector &operator=(const vector &v) {
    delete[] arr_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    arr_ = new value_type[size_];
    std::copy(v.arr_, v.arr_ + v.size_, arr_);
    return *this;
  }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      delete[] arr_;
      size_ = std::exchange(v.size_, 0);
      capacity_ = std::exchange(v.capacity_, 0);
      arr_ = std::exchange(v.arr_, nullptr);
    }
    return *this;
  }

  // Methods for accessing the elements of the class
 public:
  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("Index is out of range");
    return arr_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size_) throw std::out_of_range("Index is out of range");
    return arr_[pos];
  }

  reference operator[](size_type pos) { return arr_[pos]; }
  const_reference operator[](size_type pos) const { return arr_[pos]; }

  reference front() { return *begin(); }
  const_reference front() const { return *cbegin(); }

  reference back() { return *(end() - 1); }
  const_reference back() const { return *(cend() - 1); }

  iterator data() noexcept { return arr_; }
  const_iterator data() const noexcept { return arr_; }

  // Methods for iterating over class elements
 public:
  iterator begin() { return arr_; }
  const_iterator cbegin() const { return arr_; }

  iterator end() { return arr_ + size_; }
  const_iterator cend() const { return arr_ + size_; }

  // Methods for accessing the container capacity information
 public:
  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; };

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void reserve(size_type size) {
    if (size > max_size())
      throw std::length_error("Size larger than the maximum size for allocate");
    if (size > capacity_) {
      auto *buf = new value_type[size];
      for (size_type i = 0; i < size_; i++) buf[i] = std::move(arr_[i]);
      delete[] arr_;
      arr_ = buf;
      capacity_ = size;
    }
  }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() {
    if (capacity_ != size_) {
      capacity_ = size_;
      reserve(size_);
    }
  }

  // Methods for accessing the container capacity information
 public:
  void clear() { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end())
      throw std::out_of_range("Position is out of range");
    size_type pos_value = pos - begin();
    if (size_ == capacity_) {
      reserve(size_ == 0 ? 1 : capacity_ * 2);
      pos = begin() + pos_value;
    }
    size_++;
    value_type temp1;
    value_type temp2 = value;

    for (int i = 0; pos + i != end();) {
      temp1 = pos[i];
      pos[i] = temp2;
      i++;
      if (pos + i == end()) break;
      temp2 = pos[i];
      pos[i] = temp1;
      i++;
    }
    return pos;
  }

  void erase(iterator pos) {
    if (pos < begin() || pos >= end())
      throw std::out_of_range("Position is out of range");
    for (size_type i = pos - begin(); i < size_ - 1; i++) arr_[i] = arr_[i + 1];
    size_--;
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(size_ == 0 ? 1 : capacity_ * 2);
    }
    size_++;
    arr_[size_ - 1] = value;
  }

  void pop_back() {
    if (size_ == 0) throw std::out_of_range("Container is empty");
    size_--;
  }

  void swap(vector &other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(arr_, other.arr_);
  }

 private:
  size_type size_;
  size_type capacity_;
  iterator arr_;
};
}  // namespace s21

#endif  //  SRC_S21_VECTOR_H
