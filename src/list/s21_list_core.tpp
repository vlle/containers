using namespace s21;

template <typename T> void list<T>::push_front(const T &e) {
  list::iterator it = begin();
  insert(it, e);
}

template <typename T> void list<T>::push_back(const T &e) {
  list::iterator it = end();
  insert(it, e);
}

template <typename T> void list<T>::pop_back() {
  list_node<T> *tmp = tail_->prev_;
  tail_->prev_ = tmp->prev_;

  if (tmp->prev_ == nullptr) {
    head_ = tail_;
  } else {
    tmp->prev_->next_ = tail_;
  }

  delete tmp;
  m_size_--;
}

template <typename T> void list<T>::pop_front() {
  list::iterator it = begin();
  erase(it);
}
