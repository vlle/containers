#ifndef _SRC_QUEUE_S21_QUEUE_H_
#define _SRC_QUEUE_S21_QUEUE_H_

#include <initializer_list>

#include "s21_list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q) = default;
  queue(queue &&q) = default;
  ~queue();
  queue &operator=(queue &&q) = default;

  const_reference front();
  const_reference back();

  bool empty() const;
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void emplace_back(Args &&...args);

 private:
  list<value_type> object;
};

template <typename value_type>
queue<value_type>::queue() = default;

template <typename value_type>
queue<value_type>::queue(std::initializer_list<value_type> const &items) {
  for (auto p = items.begin(); p != items.end(); p++) {
    object.push_back(*p);
  }
}

template <typename value_type>
queue<value_type>::~queue() = default;

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::front() {
  return *(object.begin());
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::back() {
  return *(--object.end());
}

template <typename value_type>
bool queue<value_type>::empty() const {
  return object.empty();
}

template <typename value_type>
typename queue<value_type>::size_type queue<value_type>::size() {
  return object.size();
}

template <typename value_type>
void queue<value_type>::push(const_reference value) {
  object.push_back(value);
}

template <typename value_type>
void queue<value_type>::pop() {
  if (object.size() != 0) {
    object.pop_front();
  }
}

template <typename value_type>
void queue<value_type>::swap(queue &other) {
  object.swap(other.object);
}

// template <typename value_type>
// template <typename... Args>
// void queue<value_type>::emplace_back(Args &&...args) {}

}  // namespace s21

#endif  // _SRC_QUEUE_S21_QUEUE_H_
