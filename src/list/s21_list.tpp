using namespace s21;
#include <iostream>

template <typename value_type> list<value_type>::list() : m_size_(0) {
  head_ = new list_node(value_type{});
  tail_ = head_;
}

template <typename value_type> list<value_type>::list(list &&other) : list() {
  *this = (list<value_type> &&) other;
}

template <typename value_type>
list<value_type> list<value_type>::operator=(list &&other) {
  if (this != &other) {
    std::swap(m_size_, other.m_size_);
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
  }

  return *this;
}

template <typename value_type>
list<value_type>::list(const list &other) : list() {
  list_node<value_type> *curr = other.head_;

  for (size_t i = 0; i < other.m_size_; i++) {
    this->push_back(curr->data_);
    curr = curr->next_;
  }
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items)
    : list() {
  for (auto p = items.begin(); p != items.end(); p++) {
    push_back(*p);
  }
}

template <typename value_type> list<value_type>::list(size_type n) {
  for (size_type i = 0; i < n; i++) {
    push_back(0);
  }
}

template <typename value_type> list<value_type>::~list() {
  if (m_size_ > 0) {
    this->clear();
  }

  if (tail_ != nullptr) {
    delete tail_;
  }
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(list<value_type>::iterator pos,
                                                const_reference e) {
  if (pos.pos_ == nullptr) {
    throw std::out_of_range("Iterator dose not exist");
  }

  list_node<value_type> *n = new list_node<value_type>(e);
  m_size_++;
  n->next_ = pos.pos_;

  if (pos.pos_) {
    n->prev_ = pos.pos_->prev_;
    pos.pos_->prev_ = n;
  } else {
    n->next_ = tail_;
  }

  if (n->prev_) {
    n->prev_->next_ = n;
  } else {
    head_ = n;
  }

  return n;
}

template <typename value_type> void list<value_type>::clear() {
  list_node<value_type> *curr = head_;

  while (curr != tail_) {
    list_node<value_type> *tmp = curr;

    curr = curr->next_;
    delete tmp;
  }

  head_ = tail_;
  head_ = nullptr;

  m_size_ = 0;
}

template <typename value_type>
void list<value_type>::erase(list<value_type>::iterator pos) {
  if (pos == end()) {
    throw std::out_of_range("Double free");
  }

  if (pos == begin()) {
    list_node<value_type> *tmp = head_;
    head_ = head_->next_;

    delete tmp;
  } else {
    list_node<value_type> *next = pos.pos_->next_;
    list_node<value_type> *prev = pos.pos_->prev_;

    pos.pos_->prev_->next_ = next;
    pos.pos_->next_->prev_ = prev;

    delete pos.pos_;
  }

  this->m_size_--;
}

template <typename value_type> void list<value_type>::sort() {
  list_node<value_type> *curr = head_;
  int swaped = 0;

  while (1) {
    while (curr->next_ != tail_) {
      if (curr->data_ > curr->next_->data_) {
        swap_data(&(curr->data_), &(curr->next_->data_));
        swaped = 1;
      } else {
        curr = curr->next_;
      }
    }
    curr = head_;

    if (swaped == 0) {
      break;
    }
    swaped = 0;
  }
}

template <typename value_type>
void list<value_type>::swap_data(value_type *a, value_type *b) {
  value_type tmp = *a;
  *a = *b;
  *b = tmp;
}

template <typename value_type> void list<value_type>::unique() {
  list_node<value_type> *curr = head_;

  while (curr->next_ != tail_) {
    if (curr->next_ != nullptr) {
      if (curr->data_ == curr->next_->data_) {
        if (curr->next_->next_ == nullptr) {
          delete curr->next_;
          curr->next_ = nullptr;
        } else {
          list_node<value_type> *tmp = curr->next_;
          curr->next_ = tmp->next_;
          tmp->next_->prev_ = tmp;

          delete tmp;
        }

        m_size_--;
      } else {
        curr = curr->next_;
      }
    }
  }
}

template <typename value_type> void list<value_type>::reverse() {
  list_node<value_type> *ptr_1 = head_;
  list_node<value_type> *ptr_2 = ptr_1->next_;

  ptr_1->next_ = nullptr;
  ptr_1->prev_ = ptr_2;

  while (ptr_2->next_ != nullptr) {
    ptr_2->prev_ = ptr_2->next_;
    ptr_2->next_ = ptr_1;
    ptr_1 = ptr_2;
    ptr_2 = ptr_2->prev_;
  }

  tail_ = ptr_2->next_;
  head_ = ptr_1;
}

template <typename value_type> void list<value_type>::merge(list &other) {
  for (list<value_type>::iterator p = other.begin(); p != other.end(); p++) {
    this->push_back(*p);
  }

  other.clear();
}

template <typename value_type> void list<value_type>::swap(list &other) {
  size_type tmp_size = this->m_size_;
  list_node<value_type> *tmp_head = this->head_;
  list_node<value_type> *tmp_tail = this->tail_;

  this->m_size_ = other.m_size_;
  this->head_ = other.head_;
  this->tail_ = other.tail_;

  other.m_size_ = tmp_size;
  other.head_ = tmp_head;
  other.tail_ = tmp_tail;
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  if (other.head_ != tail_ || pos.pos_ != end().pos_) {
    pos.pos_->prev_->next_ = other.head_;
    other.head_->prev_ = pos.pos_->prev_;

    other.tail_->prev_->next_ = pos.pos_;
    pos.pos_->prev_ = other.tail_->prev_;

    m_size_ += other.m_size_;

    delete[] other.tail_;

    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.m_size_ = 0;
  }
}

template <typename value_type> size_t list<value_type>::size() const noexcept {
  return m_size_;
}

template <typename value_type> bool list<value_type>::empty() const {
  // std::cout << m_size_ << std::endl;
  return m_size_ ? false : true;
}
/**
 * This value typically reflects the theoretical limit on the size of
 *  the container, at most std::numeric_limits<difference_type>::max().
 *  At runtime, the size of the container may be limited to a value smaller
 *  than max_size() by the amount of RAM available.
 */
template <typename value_type>
size_t list<value_type>::max_size() const noexcept {
  return std::numeric_limits<std::ptrdiff_t>().max() /
         sizeof(list_node<value_type>);
}

template <typename value_type> const value_type &list<value_type>::front() {
  return head_->data_;
}

template <class value_type> const value_type &list<value_type>::back() {
  return tail_ == head_ ? head_->data_ : tail_->prev_->data_;
}
