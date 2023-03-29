#ifndef _SRC_LIST_S21_LIST_H_
#define _SRC_LIST_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdio.h>

namespace s21 {
template <typename T> struct list_node {
  list_node<T> *next_;
  list_node<T> *prev_;
  T data_;
  list_node(const T &e) : next_(nullptr), prev_(nullptr), data_(e) {}
};

template <typename T> class list {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  list();
  list(const list &other);
  list(list &&other);
  list(std::initializer_list<value_type> const &items);
  explicit list(size_type n);
  ~list();

  list operator=(list &&other);

  void push_front(const_reference e);
  void push_back(const_reference e);
  void pop_front();
  void pop_back();
  void sort();
  void swap_data(value_type *a, value_type *b);
  void unique();
  void reverse();
  void merge(list &other);
  void swap(list &other);
  void clear();

  bool empty() const;
  size_type max_size() const noexcept;
  size_t size() const noexcept;

  const_reference front();
  const_reference back();

  class ListIterator {
    friend list;

  public:
    ListIterator(list_node<T> *p = nullptr) : pos_(p) {}

    T &operator*() { return pos_->data_; }
    T *operator->() { return &(pos_->data_); }

    T &operator*() const { return pos_->data_; }
    T *operator->() const { return &(pos_->data_); }

    bool operator!=(const ListIterator &rhs) { return this->pos_ != rhs.pos_; }
    bool operator==(const ListIterator &rhs) { return this->pos_ == rhs.pos_; }
    bool operator!=(const ListIterator &rhs) const {
      return this->pos_ != rhs.pos_;
    }

    bool operator==(const ListIterator &rhs) const {
      return this->pos_ == rhs.pos_;
    }

    ListIterator operator++() {
      pos_ = pos_->next_;

      return *this;
    }

    ListIterator operator--() {
      pos_ = pos_->prev_;

      return *this;
    }

    ListIterator operator++(int) {
      ListIterator l_tmp(*this);
      pos_ = pos_->next_;

      return l_tmp;
    }

    ListIterator operator--(int) {
      ListIterator l_tmp(*this);
      pos_ = pos_->prev_;

      return l_tmp;
    }

    ListIterator operator++() const {
      pos_ = pos_->next_;

      return *this;
    }

    ListIterator operator--() const {
      pos_ = pos_->prev_;

      return *this;
    }

    ListIterator operator++(int) const {
      ListIterator l_tmp(*this);
      pos_ = pos_->next_;

      return l_tmp;
    }

    ListIterator operator--(int) const {
      ListIterator l_tmp(*this);
      pos_ = pos_->prev_;

      return l_tmp;
    }

  private:
    list_node<T> *pos_;
  };

  class ListConstIterator {
    friend list;

  public:
    ListConstIterator() {}
    ListConstIterator(typename list<T>::ListIterator p) : pos_(p.pos_) {}

    T &operator*() const { return pos_->data_; }
    T *operator->() const { return &(pos_->data_); }

    bool operator!=(const ListConstIterator &rhs) const {
      return this->pos_ != rhs.pos_;
    }

    bool operator==(const ListConstIterator &rhs) const {
      return this->pos_ == rhs.pos_;
    }

    ListConstIterator operator++() const {
      pos_ = pos_->next_;

      return *this;
    }

    ListConstIterator operator--() const {
      pos_ = pos_->prev_;

      return *this;
    }

  protected:
    list_node<T> *pos_;
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(tail_); }

  const_iterator begin() const;
  const_iterator end() const;

  iterator insert(list<value_type>::iterator pos,
                                const_reference e);
  void erase(list<value_type>::iterator pos);
  void splice(const_iterator pos, list &other);

private:
  list_node<value_type> *head_;
  list_node<value_type> *tail_;
  size_type m_size_;
};

} // namespace s21

#include "s21_list.tpp"
#include "s21_list_core.tpp"

#endif // _SRC_LIST_S21_LIST_H_
