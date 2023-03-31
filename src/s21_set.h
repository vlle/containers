#ifndef SRC_S21_SET_H
#define SRC_S21_SET_H

#include "s21_tree.h"

namespace s21 {
template <class T>
class set: public BinaryTree<T>{
 public:
  using BinaryTree<T>::BinaryTree;
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename BinaryTree<T>::iterator;
  using const_iterator = typename BinaryTree<T>::const_iterator;
  using size_type = std::size_t;
  static constexpr bool root = true;

public:
  set() {
    size_ = 0;
    root_ = new BinaryTree<T>(root);
  }

  set(std::initializer_list<value_type> const &items) {
    size_ = 0;
    root_ = new BinaryTree<T>(root);
    for (const value_type &item: items)
      insert(item);
  }

  set(const set& other) {
    size_ = 0;
    root_ = new BinaryTree<T>(root);
    *this = other;
  }

  set(set && other) noexcept {
    std::swap(other.root_, root_);
    std::swap(other.size_, size_);
    other.root_ = nullptr;
    other.size_ = 0;
  }

  set& operator=(const set& other) {
    if (!other.root_) return *this;
    size_ = other.size_;
    *root_ = *other.root_;
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
    root_ = new BinaryTree<T>(root);
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
    std::pair<iterator, bool> ret = root_->insert(value);
    if (ret.second == true) size_++;
    return ret;
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
