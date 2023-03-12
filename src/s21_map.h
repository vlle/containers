#ifndef SRC_S21_MAP_H
#define SRC_S21_MAP_H

#include "s21_tree.h"

namespace s21 {
template <class Key, class T>
class MapCompare {
 public:
  using value_type = std::pair<Key, T>;
  bool operator()(const value_type &x, const value_type &y) const {
    return x.first < y.first;
  }
};

template <typename Key, typename T>
class map : public BinaryTree<std::pair<Key, T>, MapCompare<Key, T>> {
 public:
  using BinaryTree<std::pair<Key, T>, MapCompare<Key, T>>::BinaryTree;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using compare = MapCompare<Key, T>;
  using node = typename map<Key, T>::node;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<value_type, compare>::treeIterator;
  using const_iterator = typename BinaryTree<value_type, compare>::treeConstIterator;
  using size_type = std::size_t;

 public:
  T &at(const Key &key) {
    auto *res = FindByKey(key);
    if (res == nullptr) throw std::out_of_range("This key is not in the map");
    return res->data_.second;
  }

  T &operator[](const Key &key) {
    try {
      at(key);
    } catch (...) {
      insert(key, mapped_type());
    }
    return at(key);
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    return this->unique_insert(value);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    std::pair<Key, T> new_val(key, obj);
    return this->unique_insert(new_val);
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    node *if_exist = FindByKey(key);
    if (if_exist) {
      if_exist->data_.second = obj;
      return std::make_pair(iterator(if_exist), true);
    } else {
      std::pair<Key, T> new_val(key, obj);
      return this->unique_insert(new_val);
    }
  }

  bool contains(const Key &key) {
    node *res = FindByKey(key);
    return res ? true : false;
  }

 private:
  node *FindByKey(const key_type &key) {
    if (this->size_ > 0) {
      node *res = this->root_;
      while (res != nullptr && res != this->last_) {
        if (key < res->data_.first) {
          res = res->left_;
        } else if (key > res->data_.first) {
          res = res->right_;
        } else {
          return res;
        }
      }
    }
    return nullptr;
  }
};
}  // namespace s21

#endif  // SRC_S21_MAP_H
