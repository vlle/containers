#ifndef SRC_S21_TREE_H_
#define SRC_S21_TREE_H_

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <ios>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "s21_vector.h"

namespace s21 {
template <class T, class Comparator = std::less<T>>
class BinaryTree {
 public:
  struct tree_iterator;
  struct tree_const_iterator;

  using value_type = T;
  using size_type = std::size_t;
  using reference = T &;
  using const_reference = const T &;
  using iterator = tree_iterator;
  using const_iterator = tree_const_iterator;

  BinaryTree() noexcept { InitEmptyNode(); }

  BinaryTree(bool parent_is_root) noexcept : parent_(nullptr) {
    InitEmptyNode();
    InitParentRoot(parent_is_root);
  };

  BinaryTree(BinaryTree *node, bool root = false) noexcept : parent_(node) {
    InitEmptyNode();
    if (root) {
      InitRoot(node);
    }
  };

  BinaryTree(const_reference value) noexcept : parent_(nullptr) {
    bool parent_is_root = true;
    InitNode(value);
    InitParentRoot(parent_is_root);
  };

  BinaryTree(const BinaryTree &other) {
    if (!other)
      throw std::invalid_argument("s21::tree::CopyConstructor(): No root");
    CopyTree(other);
  }

  BinaryTree &operator=(const BinaryTree &other) {
    if (this == &other) {
      return *this;
    }
    this->DeleteNode();
    CopyTree(other);
    return *this;
  }

  ~BinaryTree() noexcept {
    if (IsParentRoot()) delete parent_;
    DeleteNode();
  }

  void Merge(const BinaryTree *other) { this->CopyAllTree(other); }

  iterator find(const value_type value) { return Find(value); }

  size_type count(const value_type value) { return CountAll(value); }

  size_type count_unique(const value_type value) {
    return FindNode(value) ? 1 : 0;
  }

  iterator lower_bound(const value_type &key) { return FindLowerBound(key); }

  iterator upper_bound(const value_type &key) { return FindUpperBound(key); }

  size_type del(const_reference value) {
    BinaryTree *node = FindNode(value);
    return DeleteByAddress(node);
  }

  size_type erase(iterator pos) {
    if (pos == end()) return 0;
    BinaryTree *node = FindNode(*pos);
    return DeleteByAddress(node);
  }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(BinaryTree<T>);
  }

  bool contains(const value_type value) {
    return this->FindNode(value) ? true : false;
  }

  std::pair<iterator, bool> insert(const value_type &pair) {
    std::pair<BinaryTree *, bool> p = InsertValue(pair);
    iterator it = tree_iterator(p.first);
    return std::make_pair(it, p.second);
  }

  std::pair<iterator, bool> insert_non_unique(const value_type &pair) {
    std::pair<BinaryTree *, bool> p = InsertNonUniqueValue(pair);
    iterator it = tree_iterator(p.first);
    return std::make_pair(it, p.second);
  }

  std::string inorder_traversal(bool endl) {
    if (!data_) return "";
    std::string ans = "";
    ans += left_->inorder_traversal(endl);
    ans += std::to_string(data_->value) + ":" + std::to_string(height_);
    ans += ",";
    if (endl) ans += "\n";
    ans += right_->inorder_traversal(endl);
    return ans;
  }

  iterator begin() {
    tree_iterator it(MinimumNode(this));
    return it;
  }

  iterator end() {
    tree_iterator it(this);
    return it.end();
  }

  const_iterator cbegin() {
    const_iterator it(MinimumNode(this));
    return it;
  }

  const_iterator cend() {
    const_iterator it(this);
    return it.end();
  }

  void CopyAllTree(const BinaryTree *other) {
    if (!other || !other->data_) return;
    CopyAllTree(other->left_);
    InsertNonUniqueValue(other->data_->value);
    CopyAllTree(other->right_);
  }

  BinaryTree *FindNode(const value_type value) {
    if (!data_) return nullptr;
    if (comparator_(value, data_->value)) {
      return left_->FindNode(value);
    } else if (comparator_(data_->value, value)) {
      return right_->FindNode(value);
    } else {
      return this;
    }
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> Emplace(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> ret;
    for (auto &&item : {std::forward<Args>(args)...})
      ret.push_back(insert(item));
    return ret;
  }

 private:
  void InitNode(const_reference value) {
    left_ = new BinaryTree(this);
    right_ = new BinaryTree(this);
    height_ = 0;
    root_child_ = nullptr;
    data_ = new node_(value);
  }

  void InitEmptyNode() {
    root_child_ = nullptr;
    left_ = nullptr;
    right_ = nullptr;
    height_ = -1;
    data_ = nullptr;
    status_ = BalanceStatus::kNone;
  }

  void InitParentRoot(bool root) {
    parent_ = new BinaryTree(this, root);
    parent_->root_child_ = this;
  }

  void InitRoot(BinaryTree *node) {
    root_child_ = node;
    height_ = -2;
  }

  void DeleteNode() {
    delete data_;
    delete left_;
    delete right_;
    data_ = nullptr;
    left_ = nullptr;
    right_ = nullptr;
    height_ = -1;
  }

  bool IsParentRoot() { return parent_ && parent_->height_ == -2; }

  size_type RemoveNode() {
    DeleteNode();
    return 0;
  }

  void CopyTree(const BinaryTree &other) {
    if (!other.data_) return;
    insert(other.data_->value);
    if (other.left_) CopyTree(*other.left_);
    if (other.right_) CopyTree(*other.right_);
  }

  void CopyNonUniqueTree(const BinaryTree &other) {
    if (!other.data_) return;
    insert_non_unique(other.data_->value);
    if (other.left_) CopyNonUniqueTree(*other.left_);
    if (other.right_) CopyNonUniqueTree(*other.right_);
  }

  size_type CountAll(const value_type value) {
    if (!data_)
      return 0;
    else {
      return (value == data_->value ? 1 : 0) + left_->CountAll(value) +
             right_->CountAll(value);
    }
  }

  size_type DeleteByAddress(BinaryTree *node) {
    BinaryTree *to_delete = nullptr;
    if (!node) return 0;
    if (!node->left_->data_ && !node->right_->data_) {
      node->RemoveNode();
      node->InitEmptyNode();
    } else if (node->data_) {
      to_delete = SearchAndSwap(node);
      to_delete->RemoveNode();
      to_delete->InitEmptyNode();
    }
    UpdateHeight();
    return 1;
  }

  iterator FindLowerBound(const value_type &key) {
    BinaryTree *node = this;
    while (node->data_ && comparator_(node->data_->value, key)) {
      node = node->right_;
    }
    node = MinimumNode(node);
    return node ? iterator(node) : end();
  }

  iterator FindUpperBound(const value_type &key) {
    BinaryTree *node = this;
    while (node->data_ && !comparator_(node->data_->value, key)) {
      node = node->left_;
    }
    node = node->right_;
    return node ? iterator(node) : end();
  }

  iterator Find(const value_type &value) {
    BinaryTree *node = FindNode(value);
    if (node) {
      return tree_iterator(node);
    } else {
      return end();
    }
  }

  void AssignBalanceStatus() {
    int l = left_ ? left_->height_ : 0;
    int r = right_ ? right_->height_ : 0;
    if (l > r) {
      status_ = BalanceStatus::kLeftHeavy;
    } else if (l < r) {
      status_ = BalanceStatus::kRightHeavy;
    } else if (l == r) {
      status_ = BalanceStatus::kBalanced;
    }
  }

  BinaryTree *RightRotate() {
    std::swap(data_, left_->data_);
    std::swap(left_, right_);
    std::swap(left_, right_->left_);
    left_->parent_ = this;
    right_->left_->parent_ = right_;
    std::swap(right_->left_, right_->right_);
    right_->UpdateHeight();
    this->UpdateHeight();
    return this;
  }

  BinaryTree *LeftRotate() {
    std::swap(data_, right_->data_);
    std::swap(left_, right_);
    std::swap(right_, left_->right_);
    right_->parent_ = this;
    left_->right_->parent_ = left_;
    std::swap(left_->left_, left_->right_);
    left_->UpdateHeight();
    this->UpdateHeight();
    return this;
  }

  void BalanceNode() {
    if (!IsNodeUnbalanced()) return;

    if (status_ == BalanceStatus::kLeftHeavy) {
      if (left_->left_->height_ < left_->right_->height_) {
        left_->LeftRotate();
      }
      RightRotate();
    } else if (status_ == BalanceStatus::kRightHeavy) {
      if (right_->right_->height_ < right_->left_->height_) {
        right_->RightRotate();
      }
      LeftRotate();
    }
  }

  bool IsNodeUnbalanced() {
    int l = left_ ? left_->height_ : 0;
    int r = right_ ? right_->height_ : 0;
    return std::abs(l - r) > 1;
  }

  void UpdateHeight() {
    int l = left_ ? left_->height_ : 0;
    int r = right_ ? right_->height_ : 0;
    height_ = std::max(l, r) + 1;
  }

  BinaryTree *SearchAndSwap(BinaryTree *node) {
    BinaryTree *to_delete = nullptr;
    if (!node) return to_delete;
    if (node->left_ && node->left_->data_) {
      to_delete = node->left_;
      while (to_delete->right_ && to_delete->right_->data_) {
        to_delete = to_delete->right_;
      }
      std::swap(node->data_, to_delete->data_);
    } else {
      to_delete = node->right_;
      std::swap(node->data_, to_delete->data_);
    }
    return to_delete;
  }

  std::pair<BinaryTree *, bool> InsertNonUniqueValue(const_reference value) {
    if (!data_) {
      data_ = new node_(value);
      left_ = new BinaryTree(this);
      right_ = new BinaryTree(this);
      height_ = 0;
      AssignBalanceStatus();
      return std::make_pair(this, true);
    } else {
      std::pair<BinaryTree *, bool> ret = {{}, {}};
      if (comparator_(value, data_->value)) {
        ret = left_->InsertNonUniqueValue(value);
      } else if (comparator_(data_->value, value) ||
                 (!(comparator_(value, data_->value) &&
                    !comparator_(data_->value, value)))) {
        ret = right_->InsertNonUniqueValue(value);
      }
      height_++;
      UpdateHeight();
      AssignBalanceStatus();
      BalanceNode();
      return ret;
    }
  }

  std::pair<BinaryTree *, bool> InsertValue(const_reference value) {
    if (!data_) {
      data_ = new node_(value);
      left_ = new BinaryTree(this);
      right_ = new BinaryTree(this);
      height_ = 0;
      AssignBalanceStatus();
      return std::make_pair(this, true);
    } else if (comparator_(value, data_->value) ||
               comparator_(data_->value, value)) {
      std::pair<BinaryTree *, bool> ret = {{}, {}};
      if (comparator_(value, data_->value)) {
        ret = left_->InsertValue(value);
      } else if (comparator_(data_->value, value)) {
        ret = right_->InsertValue(value);
      }
      height_++;
      UpdateHeight();
      AssignBalanceStatus();
      BalanceNode();
      return ret;
    } else {
      return std::make_pair(this, false);
    }
  }

  enum class BalanceStatus {
    kNone,
    kBalanced,
    kLeftHeavy,
    kRightHeavy,
  };

  BinaryTree *parent_;
  BinaryTree *left_;
  BinaryTree *right_;
  BinaryTree *root_child_;
  int height_;

  static BinaryTree *MinimumNode(BinaryTree *node) {
    while (node && node->left_ && node->left_->data_) {
      node = node->left_;
    }
    return node;
  }
  static BinaryTree *MaximumNode(BinaryTree *node) {
    while (node && node->right_ && node->right_->data_) {
      node = node->right_;
    }
    return node;
  }

  BalanceStatus status_;

  struct node_ {
   public:
    value_type value;

    node_(value_type value) noexcept : value(value){};
  };

  node_ *data_;
  Comparator comparator_;

 public:
  struct tree_iterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    using value_type = BinaryTree::value_type;
    using local_value_type = value_type;
    using pointer = local_value_type *;
    using reference = local_value_type &;

    tree_iterator() { tree_ = nullptr; }

    explicit tree_iterator(BinaryTree *tree) { tree_ = tree; }

    tree_iterator(const tree_iterator &other) { *this = other; }

    tree_iterator(tree_iterator &&other) {
      tree_ = other.tree_;
      other.tree_ = nullptr;
    }

    ~tree_iterator() { tree_ = nullptr; }

    tree_iterator begin() { return tree_iterator(MinimumNode(tree_)); }

    tree_iterator end() {
      BinaryTree *node = tree_;
      while (node && node->height_ != -2) node = node->parent_;
      return tree_iterator(node);
    }

    bool is_null() { return tree_ == nullptr || tree_->data_ == nullptr; }

    BinaryTree *data() { return tree_; }

    std::pair<BinaryTree *, bool> next_node(BinaryTree *res) {
      if (!res || res->height_ == -2) return std::make_pair(res, true);
      if (res->right_ && !res->right_->data_) {
        while (res && res->parent_ && res->parent_->left_ != res) {
          if (res->height_ == -2) return std::make_pair(res, true);
          res = res->parent_;
        }
        if (res->parent_) res = res->parent_;
      } else {
        res = res->right_;
        while (res && res->left_ && res->left_->data_) {
          res = res->left_;
        }
      }
      return std::make_pair(res, false);
    }

    std::pair<BinaryTree *, bool> prev_node(BinaryTree *res) {
      if (res->root_child_) {
        res = res->root_child_;
        while (res && res->right_ && res->right_->data_) res = res->right_;
        return std::make_pair(res, false);
      }
      if (res->left_ && res->left_->data_) {
        res = res->left_;
        while (res->right_->data_) {
          res = res->right_;
        }
      } else {
        if (res->parent_->right_ == res) {
          return std::make_pair(res->parent_, false);
        } else if (res->parent_->left_ == res) {
          while (res->parent_->right_ != res) {
            res = res->parent_;
            if (res->height_ == -2)
              return std::make_pair(res->root_child_, false);
          }
          if (res->parent_->right_ == res) res = res->parent_;
        }
      }
      return std::make_pair(res, false);
    }

    local_value_type &operator*() const {
      if (!tree_ || !tree_->data_) {
        throw std::runtime_error("s21::tree::operator*: No value");
      }
      return tree_->data_->value;
    }

    tree_iterator &operator++() noexcept {
      std::pair<BinaryTree *, bool> next = next_node(tree_);
      if (next.second == true) {
        *this = end();
      } else {
        tree_ = next.first;
      }
      return *this;
    }

    tree_iterator operator++(int) noexcept {
      tree_iterator temp{tree_};
      ++(*this);
      return temp;
    }

    tree_iterator &operator--() noexcept {
      tree_ = prev_node(tree_).first;
      return *this;
    }

    tree_iterator operator--(int) noexcept {
      tree_iterator temp{tree_};
      --(*this);
      return temp;
    }

    tree_iterator &operator=(const tree_iterator &other) {
      tree_ = other.tree_;
      return *this;
    }

    BinaryTree *operator->() { return tree_; }

    bool operator==(const tree_iterator &other) const noexcept {
      return tree_ == other.tree_;
    }

    bool operator!=(const tree_iterator &other) const noexcept {
      return tree_ != other.tree_;
    }

   private:
    BinaryTree *tree_;
  };

  struct tree_const_iterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    using value_type = BinaryTree::value_type;
    using local_value_type = value_type;
    using pointer = local_value_type *;
    using reference = local_value_type &;

    tree_const_iterator() { tree_ = nullptr; }

    explicit tree_const_iterator(BinaryTree *tree) { tree_ = tree; }

    tree_const_iterator(const tree_const_iterator &other) { *this = other; }

    tree_const_iterator(tree_const_iterator &&other) {
      tree_ = other.tree_;
      other.tree_ = nullptr;
    }

    ~tree_const_iterator() { tree_ = nullptr; }

    tree_const_iterator begin() {
      return tree_const_iterator(MinimumNode(tree_));
    }

    tree_const_iterator end() {
      BinaryTree *node = tree_;
      while (node && node->height_ != -2) node = node->parent_;
      return tree_const_iterator(node);
    }

    bool is_null() { return tree_ == nullptr || tree_->data_ == nullptr; }

    BinaryTree *data() { return tree_; }

    std::pair<BinaryTree *, bool> next_node(BinaryTree *res) {
      if (!res || res->height_ == -2) return std::make_pair(res, true);
      if (res->right_ && !res->right_->data_) {
        while (res && res->parent_ && res->parent_->left_ != res) {
          if (res->height_ == -2) return std::make_pair(res, true);
          res = res->parent_;
        }
        if (res->parent_) res = res->parent_;
      } else {
        res = res->right_;
        while (res && res->left_ && res->left_->data_) {
          res = res->left_;
        }
      }
      return std::make_pair(res, false);
    }

    std::pair<BinaryTree *, bool> prev_node(BinaryTree *res) {
      if (res->root_child_) {
        res = res->root_child_;
        while (res && res->right_ && res->right_->data_) res = res->right_;
        return std::make_pair(res, false);
      }
      if (res->left_ && res->left_->data_) {
        res = res->left_;
        while (res->right_->data_) {
          res = res->right_;
        }
      } else {
        if (res->parent_->right_ == res) {
          return std::make_pair(res->parent_, false);
        } else if (res->parent_->left_ == res) {
          while (res->parent_->right_ != res) {
            res = res->parent_;
            if (res->height_ == -2)
              return std::make_pair(res->root_child_, false);
          }
          if (res->parent_->right_ == res) res = res->parent_;
        }
      }
      return std::make_pair(res, false);
    }

    local_value_type &operator*() const {
      if (!tree_ || !tree_->data_) {
        throw std::runtime_error("s21::tree::operator*: No value");
      }
      return tree_->data_->value;
    }

    tree_const_iterator &operator++() noexcept {
      std::pair<BinaryTree *, bool> next = next_node(tree_);
      if (next.second == true) {
        *this = end();
      } else {
        tree_ = next.first;
      }
      return *this;
    }

    tree_const_iterator operator++(int) noexcept {
      tree_const_iterator temp{tree_};
      ++(*this);
      return temp;
    }

    tree_const_iterator &operator--() noexcept {
      tree_ = prev_node(tree_).first;
      return *this;
    }

    tree_const_iterator operator--(int) noexcept {
      tree_const_iterator temp{tree_};
      --(*this);
      return temp;
    }

    tree_const_iterator &operator=(const tree_const_iterator &other) {
      tree_ = other.tree_;
      return *this;
    }

    BinaryTree *operator->() { return tree_; }

    bool operator==(const tree_const_iterator &other) const noexcept {
      return tree_ == other.tree_;
    }

    bool operator!=(const tree_const_iterator &other) const noexcept {
      return tree_ != other.tree_;
    }

   private:
    BinaryTree *tree_;
  };
};
}  // namespace s21

#endif  // SRC_S21_TREE_H_
