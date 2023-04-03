#ifndef SRC_S21_SET_H
#define SRC_S21_SET_H

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {
template <class T, class Compare = std::less<T>>
class set {
 public:
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename BinaryTree<T, Compare>::iterator;
  using const_iterator = typename BinaryTree<T, Compare>::const_iterator;
  using size_type = std::size_t;

 public:
  set() {
    size_ = 0;
    root_ = new BinaryTree<T, Compare>(root);
  }

  set(std::initializer_list<value_type> const &items) {
    size_ = 0;
    root_ = new BinaryTree<T, Compare>(root);
    for (const value_type &item : items) insert(item);
  }

  set(const set &other) {
    size_ = 0;
    root_ = new BinaryTree<T, Compare>(root);
    *this = other;
  }

  set(set &&other) noexcept {
    size_ = std::exchange(other.size_, 0);
    root_ = std::exchange(other.root_, nullptr);
  }

  set &operator=(const set &other) {
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
    std::pair<iterator, bool> ret = root_->insert(value);
    if (ret.second == true) size_++;
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

  size_type count(const value_type value) { return root_->count_unique(value); }

  void merge(set &other) {
    s21::vector<key_type> values_to_erase;
    if (other.empty()) return;
    for (iterator it = other.begin(); it != other.end(); it++) {
      iterator i = find(*it);
      if (i == end()) {
        insert(*it);
        values_to_erase.push_back(*it);
      }
    }
    while (!values_to_erase.empty()) {
      other.erase(values_to_erase.back());
      values_to_erase.pop_back();
    }
  }

  void swap(set &other) {
    std::swap(other.root_, this->root_);
    std::swap(other.size_, this->size_);
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> ret;
    for (auto &&item : {std::forward<Args>(args)...})
      ret.push_back(insert(item));
    return ret;
  }

  iterator find(const_reference value) { return root_->find(value); }

  bool contains(const T value) { return root_->contains(value); }

 private:
  static constexpr bool root = true;
  size_type size_;
  BinaryTree<T, Compare> *root_;
};
}  // namespace s21

#endif  // SRC_S21_SET_H
