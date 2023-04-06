#ifndef SRC_S21_TREE_ITERATOR_H_
#define SRC_S21_TREE_ITERATOR_H_

#include "s21_tree.h"

namespace s21 {
template <typename T, class Comparator = std::less<T>>
  struct tree_iterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    using BinaryTree = BinaryTree<T, Comparator>;
    using value_type = typename BinaryTree::value_type;
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

    tree_iterator left_node_iterator(BinaryTree *tree) {
      return tree_iterator(MinimumNode(tree));
    }

    tree_iterator right_node_iterator(BinaryTree *tree) {
      tree = right_most_tree(tree);
      return tree_iterator(tree);
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

    local_value_type& operator*() {
      if (!tree_ || !tree_->data_) {
        throw std::runtime_error("No value");
      }
      return tree_->data_->value;
    }

    local_value_type &value() const noexcept { return tree_->data_->value; }

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
    BinaryTree *left_most_tree(BinaryTree *tree) {
      while (tree->left_ && tree->left_->data_) {
        tree = tree->left_;
      }
      return tree;
    }

    BinaryTree *right_most_tree(BinaryTree *tree) {
      while (tree && tree->right_ && tree->right_->data_) {
        tree = tree->right_;
      }
      if (tree && tree->right_) tree = tree->right_;
      return tree;
    }

    BinaryTree *tree_;
  };
}

#endif // SRC_S21_TREE_ITERATOR_H_
