#ifndef SRC_S21_SET_H
#define SRC_S21_SET_H

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {
template <class T, class Compare = std::less<T>>
class multiset {
 public:
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename BinaryTree<T, Compare>::iterator;
  using const_iterator = typename BinaryTree<T, Compare>::const_iterator;
  using size_type = std::size_t;

 public:
  multiset() {
    size_ = 0;
    root_ = new BinaryTree<T, Compare>(root);
  }

  multiset(std::initializer_list<value_type> const &items) {
    size_ = 0;
    root_ = new BinaryTree<T, Compare>(root);
    for (const value_type &item : items) insert(item);
  }

  multiset(const multiset &other) {
    size_ = 0;
    root_ = new BinaryTree<T, Compare>(root);
    *this = other;
  }

  multiset(multiset &&other) noexcept {
    size_ = std::exchange(other.size_, 0);
    root_ = std::exchange(other.root_, nullptr);
  }

  multiset &operator=(const multiset &other) {
    if (!other.root_) return *this;
    size_ = other.size_;
    *root_ = *other.root_;
    return *this;
  }

  ~multiset() {
    size_ = 0;
    delete root_;
    root_ = nullptr;
  }

  iterator begin() { return root_->begin(); }

  iterator end() { return root_->end(); }

  const_iterator begin() const { return root_->cbegin(); }

  const_iterator end() const { return root_->cend(); }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() /
           sizeof(BinaryTree<T, Compare>) / 2;
  }

  void clear() {
    delete root_;
    root_ = new BinaryTree<T, Compare>(root);
    size_ = 0;
  }

  std::pair<iterator, bool> insert(const_reference value) {
    std::pair<iterator, bool> ret = root_->insert_non_unique(value);
    if (ret.second == true) size_++;
    return ret;
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> ret;
    for (auto &&item : {std::forward<Args>(args)...})
      ret.push_back(insert(item));
    return ret;
  }


  size_type erase(const T &value) {
    size_type count = root_->del(value);
    size_ -= count;
    return count;
  }

  void erase(iterator pos) {
    size_type count = root_->erase(pos);
    size_ -= count;
  }

  size_type count(const value_type value) { return root_->count(value); }


  void merge(multiset &other) {
    *root_ += other.root_;
    size_ += other.size_;
  }

  void swap(multiset &other) {
    std::swap(other.root_, this->root_);
    std::swap(other.size_, this->size_);
  }

  iterator find(const_reference value) { return root_->find(value); }

  bool contains(const T value) const { return root_->contains(value); }

 private:
  static constexpr bool root = true;
  size_type size_;
  BinaryTree<T, Compare> *root_;
};
}  // namespace s21

#endif  // SRC_S21_SET_H
