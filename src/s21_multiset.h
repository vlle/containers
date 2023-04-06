#ifndef SRC_S21_SET_H
#define SRC_S21_SET_H

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename T, class Compare = std::less<T>>
class multiset {
 public:
  // in-class type overrides
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename BinaryTree<T, Compare>::iterator;
  using const_iterator = typename BinaryTree<T, Compare>::const_iterator;
  using size_type = std::size_t;

  // main methods for interacting with the class
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

  // methods for iterating over class elements (access to iterators)
  iterator begin() { return root_->begin(); }

  iterator end() { return root_->end(); }

  const_iterator begin() const { return root_->cbegin(); }

  const_iterator end() const { return root_->cend(); }

  // methods for accessing the container capacity information
  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() /
           sizeof(BinaryTree<T, Compare>) / 2;
  }

  // methods for modifying a container
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
  s21::vector<std::pair<iterator, bool>> emplace(Args &&... args) {
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

  void merge(multiset &other) {
    std::cout << root_->inorder_traversal(true) << std::endl;
    root_->Merge(other.root_);
    size_ += other.size_;
    std::cout << root_->inorder_traversal(true) << std::endl;
  }

  void swap(multiset &other) {
    std::swap(other.root_, this->root_);
    std::swap(other.size_, this->size_);
  }

  // methods for viewing the container
  size_type count(const value_type value) { return root_->count(value); }

  iterator lower_bound(const value_type &key) {
    return root_->lower_bound(key);
  }

  iterator upper_bound(const value_type &key) {
    return root_->upper_bound(key);
  }

  std::pair<iterator, iterator> equal_range(const value_type &key) {
    return std::make_pair(root_->lower_bound(key), root_->upper_bound(key));
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
