#ifndef _SRC_STACK_S21_STACK_H_
#define _SRC_STACK_S21_STACK_H_

#include "../list/s21_list.h"
#include <initializer_list>

namespace s21 {
template <class T> class stack {
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
} // namespace s21

#include "s21_stack.tpp"

#endif // _SRC_STACK_S21_STACK_H_