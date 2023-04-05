#ifndef _SRC_QUEUE_S21_QUEUE_H_
#define _SRC_QUEUE_S21_QUEUE_H_

#include <initializer_list>

#include "s21_list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  // in-class type overrides
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // main methods for interacting with the class
  queue() = default;

  queue(std::initializer_list<value_type> const &items) {
    for (auto p = items.begin(); p != items.end(); p++) {
      object.push_back(*p);
    }
  }

  queue(const queue &q) = default;

  queue(queue &&q) = default;

  ~queue() = default;

  queue &operator=(queue &&q) = default;

  // methods for accessing the elements of the class
  const_reference front() { return *(object.begin()); }

  const_reference back() { return *(--object.end()); }

  // methods for accessing the container capacity information
  bool empty() const { return object.empty(); }

  size_type size() { return object.size(); }

  // methods for modifying a container
  void push(const_reference value) { object.push_back(value); }

  void pop() {
    if (object.size() != 0) {
      object.pop_front();
    }
  }

  void swap(queue &other) { object.swap(other.object); }

  template <typename... Args>
  void emplace_back(Args &&... args) {}

 private:
  list<value_type> object;
};

}  // namespace s21

#endif  // _SRC_QUEUE_S21_QUEUE_H_
