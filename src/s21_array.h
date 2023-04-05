#ifndef SRC_S21_ARRAY_H
#define SRC_S21_ARRAY_H

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace s21 {
template <class T, std::size_t S>
class array {
 public:
  // in-class type overrides
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  // main methods for interacting with the class
  array() noexcept = default;

  array(std::initializer_list<value_type> const &items) {
    if (items.size() != S)
      throw std::runtime_error(
          "s21::array::array(std::initializer_list<value_type> const &items) "
          "Size of initializer_list is not equal to size of array");
    for (size_type i = 0; i < S; i++) data_[i] = items.begin()[i];
  }

  array(const array &other) noexcept {
    for (size_type i = 0; i < S; i++) data_[i] = other.data_[i];
  }

  array &operator=(const array &other) noexcept {
    for (size_type i = 0; i < S; i++) data_[i] = other.data_[i];
    return *this;
  }

  array(array &&other) noexcept {
    if (this != &other) {
      for (size_type i = 0; i < S; i++) data_[i] = std::move(other.data_[i]);
    }
  }

  array &operator=(array &&other) noexcept {
    if (this != &other) {
      for (size_type i = 0; i < S; i++) data_[i] = std::move(other.data_[i]);
    }
    return *this;
  }

  ~array() noexcept = default;

  // methods for accessing the elements of the class
  reference at(size_type pos) {
    if (pos >= S)
      throw std::out_of_range("s21::array::at Index is out of range");
    return data_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= S)
      throw std::out_of_range("s21::array::at Index is out of range");
    return data_[pos];
  }

  reference operator[](size_type pos) { return at(pos); }

  const_reference operator[](size_type pos) const { return at(pos); }

  const_reference front() {
    if (S == 0)
      throw std::out_of_range(
          "s21::array::const_reference front Size of array equals zero");
    return data_[0];
  }

  const_reference front() const {
    if (S == 0)
      throw std::out_of_range(
          "s21::array::const_reference front Size of array equals zero");
    return data_[0];
  }

  const_reference back() {
    if (S == 0)
      throw std::out_of_range(
          "s21::array::const_reference back Size of array equals zero");
    return data_[S - 1];
  }

  const_reference back() const {
    if (S == 0)
      throw std::out_of_range(
          "s21::array::const_reference back Size of array equals zero");
    return data_[S - 1];
  }

  iterator data() noexcept { return data_; }

  const_iterator data() const noexcept { return data_; }

  // methods for iterating over class elements (access to iterators)
  iterator begin() noexcept { return data_; }

  const_iterator begin() const noexcept { return data_; }

  iterator end() noexcept { return data_ + S; }

  const_iterator end() const noexcept { return data_ + S; }

  // methods for accessing the container capacity information
  /**
   * @brief checks whether the container is empty
   * @return \b true if container is empty; \b false otherwise
   */
  [[nodiscard]] bool empty() const noexcept { return begin() == end(); }

  [[nodiscard]] size_type size() const noexcept { return S; }

  [[nodiscard]] size_type max_size() const noexcept { return S; }

  // methods for modifying a container
  void swap(array &other) { std::swap_ranges(begin(), end(), other.begin()); }

  void fill(const_reference value) {
    for (auto *iter = begin(), *iter_end = end(); iter != iter_end; ++iter) {
      *iter = value;
    }
  }

 private:
  value_type data_[S] = {};
};
}  // namespace s21

#endif  // SRC_S21_ARRAY_H
