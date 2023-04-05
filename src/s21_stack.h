#ifndef _SRC_STACK_S21_STACK_H_
#define _SRC_STACK_S21_STACK_H_

#include <initializer_list>

#include "s21_list.h"

namespace s21 {
template <class T>
class stack {
 public:
  // in-class type overrides
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // main public methods for interacting with the class
  stack() = default;

  stack(std::initializer_list<T> const &items) {
    for (auto p = items.begin(); p != items.end(); p++) {
      object.push_back(*p);
    }
  }

  stack(const stack &s) = default;

  stack(stack &&s) { object = std::move(s.object); }

  ~stack() = default;

  stack &operator=(stack &&s) = default;

  // methods for accessing the elements of the class
  const_reference top() { return *(--object.end()); }

  // methods for accessing the container capacity information
  bool empty() const { return object.empty(); }

  size_type size() { return object.size(); }

  // methods for modifying a container
  void push(const_reference value) { object.push_back(value); }

  void pop() {
    if (object.size() != 0) object.pop_back();
  }

  void swap(stack &other) { object.swap(other.object); }

 private:
  s21::list<T> object;
};

}  // namespace s21

#endif  // _SRC_STACK_S21_STACK_H_