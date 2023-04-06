#ifndef SRC_S21_MAP_H
#define SRC_S21_MAP_H

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {
template <class T>
class MapCompare {
 public:
  using value_type = T;
  bool operator()(const value_type& x, const value_type& y) const {
    return x.first < y.first;
  }
};

template <typename Key, typename T,
          class Compare = MapCompare<std::pair<Key, T>>>
class map {
 public:
  // in-class type overrides
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using key_compare = Compare;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<value_type, key_compare>::iterator;
  using const_iterator =
      typename BinaryTree<value_type, key_compare>::const_iterator;
  using size_type = std::size_t;

  // main methods for interacting with the class
  map() {
    size_ = 0;
    root_ = new BinaryTree<value_type, key_compare>(root);
  }

  map(std::initializer_list<value_type> const& items) {
    size_ = 0;
    root_ = new BinaryTree<value_type, key_compare>(root);
    for (value_type c : items) {
      insert(c);
    }
  }

  map(const map& other) {
    size_ = 0;
    root_ = new BinaryTree<value_type, key_compare>(root);
    *this = other;
  }

  map(map&& other) noexcept {
    size_ = std::exchange(other.size_, 0);
    root_ = std::exchange(other.root_, nullptr);
  }

  ~map() {
    size_ = 0;
    delete root_;
    root_ = nullptr;
  }

  map& operator=(const map& other) {
    if (!other.root_) return *this;
    size_ = other.size_;
    *root_ = *other.root_;
    return *this;
  }

  // methods for accessing the elements of the class
  mapped_type& at(const key_type& key) { return FindByKey(key); }

  mapped_type& operator[](const key_type& key) {
    try {
      return at(key);
    } catch (std::out_of_range const&) {
      root_->insert({key, {}});
    }
    return at(key);
  }

  // methods for iterating over class elements (access to iterator)
  iterator begin() { return root_->begin(); }

  iterator end() { return root_->end(); }

  const_iterator begin() const { return root_->cbegin(); }

  const_iterator end() const { return root_->cend(); }

  // methods for accessing the container capacity information
  bool empty() { return size_ == 0; }

  size_type size() { return size_; }

  // methods for modifying a container
  void merge(map& other) {
    s21::vector<key_type> values_to_erase;
    if (other.empty()) return;
    for (iterator it = other.begin(); it != other.end(); it++) {
      iterator i = find(*it);
      if (i == end()) {
        insert(*it);
        values_to_erase.push_back((*it).first);
      }
    }
    while (!values_to_erase.empty()) {
      other.erase(values_to_erase.back());
      values_to_erase.pop_back();
    }
  }

  iterator find(const_reference value) { return root_->find(value); }

  size_type erase(const Key& key) {
    size_type count = root_->del({key, {}});
    size_ -= count;
    return count;
  }

  void erase(iterator pos) {
    size_type count = root_->erase(pos);
    size_ -= count;
  }

  void clear() {
    delete root_;
    root_ = new BinaryTree<value_type, key_compare>(root);
    size_ = 0;
  }

  size_type count(const value_type value) { return root_->count_unique(value); }

  size_type count(const Key& key) { return root_->count_unique({key, {}}); }

  std::pair<iterator, bool> insert(const_reference value) {
    std::pair<iterator, bool> ret = root_->insert(value);
    if (ret.second == true) size_++;
    return ret;
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args&&... args) {
    return root_->Emplace(std::forward<Args>(args)...);
  }

  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    value_type value = std::make_pair(key, obj);
    return insert(value);
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& k,
                                             const mapped_type& obj) {
    value_type value = std::make_pair(k, obj);
    std::pair<iterator, bool> ret = insert(value);
    if (ret.second == false) {
      (*(ret.first)).second = obj;
    }
    return ret;
  }

  // methods for viewing the container
  bool contains(const Key& key) { return root_->contains({key, {}}); }

 private:
  mapped_type& FindByKey(const key_type& key) {
    auto pair = std::make_pair(key, 0);
    auto res = root_->find(pair);
    if (res == end()) throw std::out_of_range("Key is not in the map");
    return ((*res).second);
  }

  static constexpr bool root = true;
  size_type size_;
  BinaryTree<value_type, key_compare>* root_;
};
}  // namespace s21

#endif  // SRC_S21_MAP_H
