#ifndef SRC_S21_MULTISET_H
#define SRC_S21_MULTISET_H

#include "s21_set.h"
#include "s21_tree.h"

namespace s21 {
template <class T>
class MultisetCompare {
 public:
  using value_type = T;
  bool operator()(const value_type &x, const value_type &y) const {
    return x <= y;
  }
};

template <class T>
class multiset : public set<T, MultisetCompare<T>> {
 public:
  using set<T, MultisetCompare<T>>::set;
  using key_type = T;
  using mapped_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename set<T, MultisetCompare<T>>::iterator;
  using const_iterator = typename set<T, MultisetCompare<T>>::const_iterator;
  using size_type = std::size_t;

  size_type count(const key_type &key) {
    size_type res = 0;
    iterator iter = this->find(key);
    while (!iter.is_null() && *iter == key) {
      ++res;
      --iter;
    }
    return res;
  }
};
}  // namespace s21

#endif  // SRC_S21_MULTISET_H
