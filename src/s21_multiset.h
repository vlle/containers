#ifndef SRC_S21_MULTISET_H
#define SRC_S21_MULTISET_H

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
class multiset : public tree<T, MultisetCompare<T>> {
 public:
  using tree<T, MultisetCompare<T>>::tree;
  using key_type = T;
  using mapped_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename tree<value_type, MultisetCompare<T>>::treeIterator;
  using const_iterator =
      typename tree<value_type, MultisetCompare<T>>::treeConstIterator;
  using size_type = std::size_t;

  size_type count(const key_type &key) {
    size_type res = 0;
    iterator iter = this->find(key);
    while (iter.node_ != nullptr && iter.node_->data_ == key) {
      ++res;
      --iter;
    }
    return res;
  }

  std::pair<iterator, iterator> equal_range(const key_type &key) {
    iterator low = lower_bound(key);
    iterator upp = upper_bound(key);
    return std::make_pair(low, upp);
  }

  iterator lower_bound(const key_type &key) {
    iterator res = this->begin();
    while (res != this->end() && *res < key) {
      ++res;
    }
    return res;
  }

  iterator upper_bound(const key_type &key) {
    iterator res = this->begin();
    while (res != this->end() && *res <= key) {
      ++res;
    }
    return res;
  }
};
}  // namespace s21

#endif  // SRC_S21_MULTISET_H
