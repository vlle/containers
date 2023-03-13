#ifndef SRC_S21_AVLTREE_H
#define SRC_S21_AVLTREE_H

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <ios>
#include <iostream>
#include <limits>
#include <new>
#include <type_traits>
//#include "s21_tree.h"

namespace s21 {
  template<class T, class Comparator = std::less<T>>
  class avl_tree {
  public:
    struct treeIterator;
    struct treeConstIterator;

    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = size_t;

    avl_tree() noexcept {
      init_empty_node();
    };


    avl_tree(const_reference value) noexcept {
      init_node(value);
    };

    friend std::ostream &operator<<(std::ostream &o, const avl_tree &node) {
      if (node.left_ && node.right_ && node.data_) {
        return o << &node << ' ' << node.left_ << ' ' << node.right_ << ' ' << node.data_->value;
      } else {
        return o << &node << ' ' << node.left_ << ' ' << node.right_ << ' ' << node.data_;
      }
    }

    void delete_node() {
      delete data_;
      delete left_;
      delete right_;
      data_ = nullptr;
      left_ = nullptr;
      right_ = nullptr;
      height_ = -1;
    }

    void init_node(const_reference value) {
      left_ = (new avl_tree);
      right_ = (new avl_tree);
      height_ = (0);
      data_ = new node_(value);
    }

    void init_empty_node() {
      left_ = nullptr;
      right_ = nullptr;
      height_ = -1;
      data_ = nullptr;
    }

    ~avl_tree() noexcept {
      delete_node();
    }

    iterator find(const_reference value) {
      if (!data_) return nullptr;
      if (comparator_(value, data_->value)) {
        return left_->find(value);
      } else if (comparator_(data_->value, value)) {
        return right_->find(value);
      } else {
        return &(data_->value);
      }
    }

    avl_tree *find_node(const_reference value) {
      if (!data_) return nullptr;
      if (comparator_(value, data_->value)) {
        return left_->find_node(value);
      } else if (comparator_(data_->value, value)) {
        return right_->find_node(value);
      } else {
        return this;
      }
    }

    void del(const_reference value) {
      avl_tree *node = find_node(value);
      avl_tree *to_delete = nullptr;
      if (!node) return;
      if (!node->left_->data_ && !node->right_->data_) {
        node->delete_node();
        node->init_empty_node();
      } else {
        to_delete = search_and_swap(node);
        std::cout << *this << std::endl;
        std::cout << *to_delete << std::endl;
        to_delete->delete_node();
        to_delete->init_empty_node();
      }
      update_heights();
    }

    avl_tree *search_and_swap(avl_tree *node) {
      avl_tree *to_delete = nullptr;
      if (!node) return to_delete;
      if (node->right_->data_) {
        to_delete = node->right_;
        while (to_delete->right_->data_) {
          to_delete = to_delete->right_;
        }
        std::cout << to_delete->data_->value << std::endl;
        std::swap(node->data_, to_delete->data_);
      } else {
        to_delete = node->left_;
        std::swap(node->data_, to_delete->data_);
      }
      return to_delete;
    }


    avl_tree *insert(const_reference value) {
      auto r = insert_value(value);
      return r;
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

    void height_print() {
      if (!data_) return;
      left_->height_print();
      char p = 'n';
      if (status_ == BalanceStatus::Balanced) {
        p = 'B';
      } else if (status_ == BalanceStatus::LeftHeavy) {
        p = 'L';
      } else if (status_ == BalanceStatus::RightHeavy) {
        p = 'R';
        std::cout << data_->value << ' ' << height_ << p << std::endl;
      }
      right_->height_print();
    }

  private:

    void assign_balance_status(void) {
      int l = left_ ? left_->height_ : 0;
      int r = right_ ? right_->height_ : 0;
      if (l > r) {
        status_ = BalanceStatus::LeftHeavy;
      } else if (l < r) {
        status_ = BalanceStatus::RightHeavy;
      } else if (l == r) {
        status_ = BalanceStatus::Balanced;
      }
    }

    avl_tree *right_rotate(void) {
      std::swap(data_, left_->data_);
      std::swap(left_, right_);
      std::swap(left_, right_->left_);
      right_->update_heights();
      this->update_heights();
      return this;
    }

    avl_tree *left_rotate(void) {
      std::swap(data_, right_->data_);
      std::swap(left_, right_);
      std::swap(right_, left_->right_);
      left_->update_heights();
      this->update_heights();
      return this;
    }

    void balance_node(void) {
      if (!is_node_unbalanced()) return;

      if (status_ == BalanceStatus::LeftHeavy) {
        if (comparator_(left_->left_->height_, left_->right_->height_)) {
          left_->left_rotate();
        }
        right_rotate();
      } else if (status_ == BalanceStatus::RightHeavy) {
        if (comparator_(right_->right_->height_, right_->left_->height_)) {
          right_->right_rotate();
        }
        left_rotate();
      }
    }

    bool is_node_unbalanced(void) {
      int l = left_ ? left_->height_ : 0;
      int r = right_ ? right_->height_ : 0;
      return std::abs(l - r) > 1;
    }

    void update_heights(void) {
      int l = left_ ? left_->height_ : 0;
      int r = right_ ? right_->height_ : 0;
      height_ = std::max(l, r) + 1;
    }

    avl_tree *insert_value(const_reference value) {
      if (!data_) {
        data_ = new node_(value);
        left_ = new avl_tree;
        right_ = new avl_tree;
        height_ = 0;
        assign_balance_status();
        return this;
      } else {
        avl_tree *ret = nullptr;
        if (comparator_(value, data_->value)) {
          ret = left_->insert_value(value);
        } else {
          ret = right_->insert_value(value);
        }
        height_++;
        update_heights();
        assign_balance_status();
        balance_node();
        return ret;
      }
    }

    avl_tree *NextNode() {
      avl_tree *res = this;
      if (res->right_) {
        res = res->right_;
        while (res->left_) {
          res = res->left_;
        }
      } else {
        while (res->parent_ && (res->parent_->right_ == res)) {
          res = res->parent_;
        }
        res = res->parent_;
      }
      return res;
    }

    avl_tree *PrevNode() {
      avl_tree *res = this;
      if (res->left_) {
        res = res->left_;
        while (res->right_) {
          res = res->right_;
        }
      } else {
        while (res->parent_ && (res->parent_->left_ == res)) {
          res = res->parent_;
        }
        res = res->parent_;
      }
      return res;
    }

    enum class BalanceStatus {
      Balanced = 'E',
      LeftHeavy = 'L',
      RightHeavy = 'R',
    };

    avl_tree *left_;
    avl_tree *right_;
    avl_tree *parent_;
    int height_;
    BalanceStatus status_;

    struct node_ {
    public:
      value_type key;
      value_type value;

      node_(value_type value) noexcept: key(value), value(value) {};
    };

    node_ *data_;
    Comparator comparator_;

  public:
    struct treeIterator {
      explicit treeIterator(avl_tree *tree) : tree_(tree) {}

      treeIterator(const treeIterator &other) { *this = other; }

      reference operator*() const noexcept { return tree_->data_->key; }

      iterator &operator++() noexcept {
        tree_ = tree_->NextNode();
        return *this;
      }

      treeIterator operator++(int) noexcept {
        iterator temp{tree_};
        ++(*this);
        return temp;
      }

      iterator &operator--() noexcept {
        tree_ = tree_->PrevNode();
        return *this;
      }

      iterator operator--(int) noexcept {
        iterator temp{tree_};
        --(*this);
        return temp;
      }

      treeIterator &operator=(const treeIterator &other) {
        tree_ = other.tree_;
        return *this;
      }

      avl_tree *operator->() { return tree_; }

      bool operator==(const treeIterator &other) const noexcept {
        return tree_ == other.tree_;
      }

      bool operator!=(const treeIterator &other) const noexcept {
        return tree_ != other.tree_;
      }

    private:
      avl_tree *tree_;
    };

    struct treeConstIterator {

      treeConstIterator() = delete;

      explicit treeConstIterator(avl_tree *tree) noexcept: tree_(tree) {}

      treeConstIterator(const treeConstIterator &other) : tree_(other.tree_) {}

      reference operator*() const noexcept { return tree_->data_->key; }

      treeConstIterator &operator++() noexcept {
        tree_ = tree_->NextNode();
        return *this;
      }

      treeConstIterator operator++(int) noexcept {
        const_iterator temp{tree_};
        ++(*this);
        return temp;
      }

      treeConstIterator &operator--() noexcept {
        tree_ = tree_->PrevNode();
        return *this;
      }

      treeConstIterator operator--(int) noexcept {
        const_iterator temp{tree_};
        --(*this);
        return temp;
      }

      bool operator==(const treeConstIterator &other) const noexcept {
        return tree_ == other.tree_;
      }

      bool operator!=(const treeConstIterator &other) const noexcept {
        return tree_ != other.tree_;
      }

    private:
      avl_tree *tree_;
    };

  };
}

#endif //SRC_S21_AVLTREE_H
