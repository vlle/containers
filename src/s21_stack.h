#ifndef _SRC_STACK_S21_STACK_H_
#define _SRC_STACK_S21_STACK_H_

#include <initializer_list>

#include "s21_list.h"

namespace s21 {
template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack();
  stack(std::initializer_list<T> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();
  stack &operator=(stack &&s);

  const_reference top();

  bool empty() const;
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(stack &other);

 private:
  s21::list<T> object;
};

template <typename value_type>
stack<value_type>::stack() = default;

template <typename value_type>
stack<value_type>::stack(const stack &s) = default;

template <typename value_type>
stack<value_type>::stack(stack &&s) {
  object = std::move(s.object);
}

template <typename value_type>
stack<value_type> &stack<value_type>::operator=(stack &&s) = default;

template <typename value_type>
stack<value_type>::stack(std::initializer_list<value_type> const &items) {
  for (auto p = items.begin(); p != items.end(); p++) {
    object.push_back(*p);
  }
}

template <typename value_type>
stack<value_type>::~stack() = default;

template <typename value_type>
typename stack<value_type>::size_type stack<value_type>::size() {
  return object.size();
}

template <typename value_type>
void stack<value_type>::push(const_reference value) {
  object.push_back(value);
}

template <typename value_type>
void stack<value_type>::pop() {
  if (object.size() != 0) object.pop_back();
}

template <typename value_type>
void stack<value_type>::swap(stack &other) {
  object.swap(other.object);
}

template <typename value_type>
bool stack<value_type>::empty() const {
  return object.empty();
}

template <typename value_type>
const value_type &stack<value_type>::top() {
  return *(--object.end());
}

}  // namespace s21

#endif  // _SRC_STACK_S21_STACK_H_