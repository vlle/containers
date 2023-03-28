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
#include <utility>

namespace s21 {
  template<class T, class Comparator = std::less<T>, bool duplicate_allowance = false>
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

    BinaryTree() noexcept: parent_(nullptr) {
      init_empty_node();
    };

    BinaryTree(BinaryTree* node) noexcept: parent_(node) {
      init_empty_node();
    };

    BinaryTree(const_reference value) noexcept: parent_(nullptr) {
      init_node(value);
    };

    ~BinaryTree() noexcept {
      delete_node();
    }

    tree_iterator find(const value_type value) {
      if (!data_) return end();
      if (comparator_(value, data_->value)) {
        return left_->find(value);
      } else if (comparator_(data_->value, value)) {
        return right_->find(value);
      } else {
        return tree_iterator(this);
      }
    }

    BinaryTree *find_node(const value_type value) {
      if (!data_) return nullptr;
      if (comparator_(value, data_->value)) {
        return left_->find_node(value);
      } else if (comparator_(data_->value, value)) {
        return right_->find_node(value);
      } else {
        return this;
      }
    }

    size_type count(const value_type value) {
      BinaryTree* node = find_node(value);
      if (node != nullptr) {
        return node->data_->count;
      }
      return 0;
    }

    value_type& value() {
      return data_->value;
    }

    size_type del(const_reference value) {
      BinaryTree *node = find_node(value);
      BinaryTree *to_delete = nullptr;
      size_type count_delete = 0;
      if (!node) return count_delete;
      if (!node->left_->data_ && !node->right_->data_) {
        count_delete = node->data_->count;
        node->delete_node();
        node->init_empty_node();
      } else {
        to_delete = search_and_swap(node);
        count_delete = to_delete->data_->count;
        to_delete->delete_node();
        to_delete->init_empty_node();
      }
      update_heights();
      return count_delete;
    }

    size_type erase(iterator pos) {
      BinaryTree *node = pos.data();
      BinaryTree *to_delete = nullptr;
      size_type count_delete = 0;
      if (!node) return count_delete;
      if (!node->left_->data_ && !node->right_->data_) {
        count_delete = node->data_->count;
        size_type count = node->remove_node();
        if (count == 0) node->init_empty_node();
      } else if (node->data_ && node->data_->count == 1) {
        to_delete = search_and_swap(node);
        count_delete = to_delete->data_->count;
        to_delete->remove_node();
        to_delete->init_empty_node();
      } else if (node->data_ && node->data_->count > 1) {
        node->data_->count--;
      }
      update_heights();
      return count_delete;
    }

    size_type max_size() {
      return std::numeric_limits<size_type>::max();   
    }


    tree_iterator insert(const value_type &pair) {
      auto r = insert_value(pair);
      return tree_iterator(r);
    }

    void merge(BinaryTree* other) {
      if (!other) return;
      if (left_) 
        left_->merge(other->left_);
      if (right_) 
        right_->merge(other->right_);
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
      if (status_ == BalanceStatus::kBalanced) {
        p = 'B';
      } else if (status_ == BalanceStatus::kLeftHeavy) {
        p = 'L';
      } else if (status_ == BalanceStatus::kRightHeavy) {
        p = 'R';
        std::cout << data_->value << ' ' << height_ << p << std::endl;
      }
      right_->height_print();
    }

    iterator begin() {
      tree_iterator it(this);
      return it.left_node_iterator(this);
    }

    iterator end() {
      tree_iterator it(this);
      return it.right_node_iterator(this);
    }

    const_iterator cbegin() {
      const_iterator it(this);
      return it.left_node_iterator(this);
    }

    const_iterator cend() {
      const_iterator it(this);
      return it.right_node_iterator(this);
    }


    friend std::ostream &operator<<(std::ostream &o, const BinaryTree &node) {
      if(node.left_ && node.right_ && node.data_) {
        return o << &node << ' ' << node.left_ << ' ' << node.right_ << ' ' << node.data_->value;
      } else {
        return o << &node << ' ' << node.left_ << ' ' << node.right_ << ' ' << node.data_;
      }
    }

  private:

    void init_node(const_reference value) {
      left_ = new BinaryTree(this);
      right_ = new BinaryTree(this);
      height_ = 0;
      data_ = new node_(value);
    }

    void init_empty_node() {
      left_ = nullptr;
      right_ = nullptr;
      height_ = -1;
      data_ = nullptr;
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

    size_type remove_node() {
      if (data_ && data_->count > 1) {
        data_->count--;
        return data_->count;
      } else {
        delete_node();
        return 0;
      }
    }


    void assign_balance_status() {
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

    BinaryTree *right_rotate() {
      std::swap(data_, left_->data_);
      std::swap(left_, right_);
      std::swap(left_, right_->left_);
      left_->parent_ = this;
      right_->left_->parent_ = right_;
      std::swap(right_->left_, right_->right_);
      right_->update_heights();
      this->update_heights();
      return this;
    }

    BinaryTree *left_rotate() {
      std::swap(data_, right_->data_);
      std::swap(left_, right_);
      std::swap(right_, left_->right_);
      right_->parent_ = this;
      left_->right_->parent_ = left_;
      std::swap(left_->left_, left_->right_);
      left_->update_heights();
      this->update_heights();
      return this;
    }

    void balance_node() {
      if (!is_node_unbalanced()) return;

      if (status_ == BalanceStatus::kLeftHeavy) {
        if (left_->left_->height_ < left_->right_->height_) {
          left_->left_rotate();
        }
        right_rotate();
      } else if (status_ == BalanceStatus::kRightHeavy) {
        if (right_->right_->height_ < right_->left_->height_) {
          right_->right_rotate();
        }
        left_rotate();
      }
    }

    bool is_node_unbalanced() {
      int l = left_ ? left_->height_ : 0;
      int r = right_ ? right_->height_ : 0;
      return std::abs(l - r) > 1;
    }

    void update_heights() {
      int l = left_ ? left_->height_ : 0;
      int r = right_ ? right_->height_ : 0;
      height_ = std::max(l, r) + 1;
    }

    BinaryTree *search_and_swap(BinaryTree *node) {
      BinaryTree *to_delete = nullptr;
      if (!node) return to_delete;
      if (node->right_->data_) {
        to_delete = node->right_;
        while (to_delete->right_->data_) {
          to_delete = to_delete->right_;
        }
        std::swap(node->data_, to_delete->data_);
      } else {
        to_delete = node->left_;
        std::swap(node->data_, to_delete->data_);
      }
      return to_delete;
    }


    BinaryTree *insert_value(const_reference value) {
      if (!data_) {
        data_ = new node_(value);
        left_ = new BinaryTree(this);
        right_ = new BinaryTree(this);
        height_ = 0;
        assign_balance_status();
        return this;
      } else if (comparator_(value, data_->value) || comparator_(data_->value, value)) {
        BinaryTree *ret = nullptr;
        if (comparator_(value, data_->value)) {
          ret = left_->insert_value(value);
        } else if (comparator_(data_->value, value)) {
          ret = right_->insert_value(value);
        } 
        height_++;
        update_heights();
        assign_balance_status();
        balance_node();
        return ret;
      } else if (duplicate_allowance == true) {
        data_->count++;
      } 
      return this;
    }

    BinaryTree *next_node() {
      BinaryTree *res = this;
      if (res->right_ && !res->right_->data_) {
        while (res && res->parent_ && res->parent_->left_ != res) {
          res = res->parent_;
        }
        if (res->parent_) res = res->parent_;
      } else {
        res = res->right_;
        while (res && res->left_ && res->left_->data_) {
          res = res->left_;
        }
      }
      return res;
    }

    BinaryTree *prev_node() {
      BinaryTree *res = this;
      if (res->left_ && res->left_->data_) {
        res = res->left_;
        while (res->right_->data_) {
          res = res->right_;
        }
      } else {
        if (!res->parent_) return this;
        if (res->parent_->right_ == res) {
          return res->parent_;
        } else if (res->parent_->left_ == res) {
          while (res->parent_->right_ != res) {
            if (!res->parent_) {
              return nullptr;
            }
            res = res->parent_;
          }
        }
      }
      return res;
    }

    enum class BalanceStatus {
      kBalanced = 'E',
      kLeftHeavy = 'L',
      kRightHeavy = 'R',
    };

    BinaryTree *left_;
    BinaryTree *right_;
    BinaryTree *parent_;
    int height_;
    BalanceStatus status_;

    struct node_ {
      public:
        value_type value;
        size_type count;

        node_(value_type value) noexcept: value(value), count(1) {};
    };

    node_ *data_;
    Comparator comparator_;

  public:
    struct tree_iterator {
      using iterator_category = std::bidirectional_iterator_tag;
      using difference_type = std::ptrdiff_t;

      using value_type = value_type;
      using pointer = value_type*;
      using reference = value_type&;

      explicit tree_iterator(BinaryTree *tree) {
        tree_ = tree;
      }

      tree_iterator(const tree_iterator &other) { *this = other; }

      tree_iterator(tree_iterator &&other) { 
        tree_ = other.tree_; 
        other.tree_ = nullptr;
      }

      ~tree_iterator() {
        tree_ = nullptr;
      }

      tree_iterator begin() {
        return left_node_iterator(tree_);
      }

      tree_iterator end() {
        return right_node_iterator(tree_);
      }

      tree_iterator left_node_iterator(BinaryTree *tree) {
        tree = left_most_tree(tree);
        return tree_iterator(tree);
      }

      tree_iterator right_node_iterator(BinaryTree *tree) {
        tree = right_most_tree(tree);
        return tree_iterator(tree);
      }

      bool is_null() {
        return tree_ == nullptr || tree_->data_ == nullptr;
      }

      BinaryTree* data() {
        return tree_;
      }


      value_type operator*() noexcept { 
        return tree_ && tree_->data_ ? tree_->data_->value : value_type{};
      }

      value_type& value() const noexcept { return tree_->data_->value; }

      tree_iterator &operator++() noexcept {
        BinaryTree* next = tree_->next_node();
        BinaryTree* next_next = next->next_node();
        if (tree_ == next_next && !tree_->right_->data_) {
          *this = end();
        } else {
          tree_ = next;
        }
        return *this;
      }

      tree_iterator operator++(int) noexcept {
        tree_iterator temp{tree_};
        ++(*this);
        return temp;
      }

      tree_iterator &operator--() noexcept {
        tree_ = tree_->prev_node();
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

      BinaryTree* left_most_tree(BinaryTree *tree) {
        while (tree->left_ && tree->left_->data_) {
          tree = tree->left_;
        }
        return tree;
      }

      BinaryTree* right_most_tree(BinaryTree *tree) {
        while (tree && tree->right_ && tree->right_->data_) {
          tree = tree->right_;
        }
        if (tree && tree->right_) tree = tree->right_;
        return tree;
      }

      BinaryTree *tree_;

    };

    struct tree_const_iterator {
      using iterator_category = std::bidirectional_iterator_tag;
      using difference_type = std::ptrdiff_t;

      using value_type = const value_type;
      using pointer = value_type*;
      using reference = value_type&;

      explicit tree_const_iterator(BinaryTree *tree) {
        tree_ = tree;
      }

      tree_const_iterator(const tree_const_iterator &other) { *this = other; }

      tree_const_iterator(tree_const_iterator &&other) { 
        tree_ = other.tree_; 
        other.tree_ = nullptr;
      }

      ~tree_const_iterator() {
        tree_ = nullptr;
      }

      tree_const_iterator begin() {
        return left_node_iterator(tree_);
      }

      tree_const_iterator end() {
        return right_node_iterator(tree_);
      }

      tree_const_iterator left_node_iterator(BinaryTree *tree) {
        tree = left_most_tree(tree);
        return tree_const_iterator(tree);
      }

      tree_const_iterator right_node_iterator(BinaryTree *tree) {
        tree = right_most_tree(tree);
        return tree_const_iterator(tree);
      }

      bool is_null() {
        return tree_ == nullptr || tree_->data_ == nullptr;
      }


      value_type operator*() noexcept { 
        return tree_ && tree_->data_ ? tree_->data_->value : value_type{};
      }

      value_type value() const noexcept { return tree_->data_->value; }

      tree_const_iterator &operator++() noexcept {
        BinaryTree* next = tree_->next_node();
        BinaryTree* next_next = next->next_node();
        if (tree_ == next_next && !tree_->right_->data_) {
          *this = end();
        } else {
          tree_ = next;
        }
        return *this;
      }

      tree_const_iterator operator++(int) noexcept {
        tree_const_iterator temp{tree_};
        ++(*this);
        return temp;
      }

      tree_const_iterator &operator--() noexcept {
        tree_ = tree_->prev_node();
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

      BinaryTree* left_most_tree(BinaryTree *tree) {
        while (tree->left_ && tree->left_->data_) {
          tree = tree->left_;
        }
        return tree;
      }

      BinaryTree* right_most_tree(BinaryTree *tree) {
        while (tree && tree->right_ && tree->right_->data_) {
          tree = tree->right_;
        }
        if (tree && tree->right_) tree = tree->right_;
        return tree;
      }

      BinaryTree *tree_;

    };

  };
}

#endif //SRC_S21_AVLTREE_H
