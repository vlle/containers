#ifndef SRC_S21_SET_H
#define SRC_S21_SET_H

#include "s21_tree.h"
//#include "s21_AVL_tree.h"

namespace s21 {
template <class T>
class set : public tree<T> {
//class set : public BinaryTree<T> {
 public:
  using tree<T>::tree;
//  using BinaryTree<T>::BinaryTree;
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename tree<T>::treeIterator;
  using const_iterator = typename tree<T>::treeConstIterator;
//  using iterator = typename BinaryTree<T>::treeIterator;
//  using const_iterator = typename BinaryTree<T>::treeConstIterator;
  using size_type = std::size_t;
};
}  // namespace s21

#endif  // SRC_S21_SET_H
