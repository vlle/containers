#ifndef SRC_S21_SET_H
#define SRC_S21_SET_H

#include "s21_tree.h"

namespace s21 {
template <class T>
class set {
 public:
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename BinaryTree<T>::iterator;
  using const_iterator = typename BinaryTree<T>::const_iterator;
  using size_type = std::size_t;

public:
  set() {
    size_ = 0;
    root_ = new BinaryTree<T>(true);
  }

  void print() {
    std::cout << 1 << std::endl;
  };
  set(std::initializer_list<value_type> const &items) {
    size_ = 0;
    root_ = new BinaryTree<T>(true);
    for (value_type item : items)
      insert(item);
    print();
  }

  set(const set& other) {
    size_ = 0;
    root_ = new BinaryTree<T>(true);
    if (other.size_ > 0) {
      for (const_iterator it = other.begin(); it != other.end(); it++) {
        insert(*it);
      }
    }
  }

  set(set && other) noexcept {
    std::swap(other.root_, root_);
    std::swap(other.size_, size_);
    other.root_ = nullptr;
    other.size_ = 0;
  }

  set& operator=(const set& other) {
    if (this == &other) {
      return *this;
    }
    this->clear();
    for (const_iterator it = other.begin(); it != other.end(); it++) {
      insert(*it);
    }
    return *this;
  }

  ~set() {
    size_ = 0;
    delete root_;
    root_ = nullptr;
  }


  bool empty() const noexcept {
    return size_ == 0;
  }

  void clear() {
    delete root_;
    root_ = new BinaryTree<T>(true);
    size_ = 0;
  }

  iterator find(const_reference value) {
    return root_->find(value);
  }

  void erase(iterator pos) {
    size_type count = root_->erase(pos);
    size_ -= count;
  }


  std::pair<iterator, bool> insert(const_reference value) {
    bool is_value_inserted = false;
    iterator it = root_->find(value);
    if (it.is_null()) {
      it = root_->insert(value);
      size_++;
      is_value_inserted = true;
    }
    return std::make_pair(it, is_value_inserted);
  }



  bool contains(const T value) {
    return root_->contains(value);
  }

  size_type size() const noexcept {
    return size_;
  }

  size_type max_size() const noexcept {
    // TODO:CHECK
    return std::numeric_limits<size_type>::max() / sizeof(BinaryTree<T>) / 2;
  }

  iterator begin() {
    return root_->begin();
  }

  iterator end() {
    return root_->end();
  }

  const_iterator begin() const {
    return root_->cbegin();
  }

  const_iterator end() const {
    return root_->cend();
  }

private:
  size_type size_;
  BinaryTree<T> *root_;
};
}  // namespace s21

#endif  // SRC_S21_SET_H
