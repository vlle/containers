#include <gtest/gtest.h>

#include <stack>

#include "../s21_stack.h"

using namespace s21;

TEST(stack_test_0, stack) {
  stack<int> tmp;
  std::stack<int> s21_tmp;

  tmp.push(1);
  s21_tmp.push(1);
  EXPECT_EQ(tmp.top(), s21_tmp.top());

  tmp.push(21);
  s21_tmp.push(21);
  EXPECT_EQ(tmp.top(), s21_tmp.top());

  tmp.pop();
  s21_tmp.pop();
  EXPECT_EQ(tmp.top(), s21_tmp.top());

  EXPECT_EQ(tmp.empty(), s21_tmp.empty());
  tmp.pop();
  s21_tmp.pop();

  EXPECT_EQ(tmp.empty(), s21_tmp.empty());
}

TEST(stack_test_1, stack) {
  stack<int> s21_tmp_0 = {1, 2, 3, 4};
  stack<int> s21_tmp_1 = {5, 6, 7, 8};

  std::stack<int> tmp_0({1, 2, 3, 4});
  std::stack<int> tmp_1({5, 6, 7, 8});

  tmp_0.swap(tmp_1);
  s21_tmp_0.swap(s21_tmp_1);

  EXPECT_EQ(s21_tmp_0.top(), tmp_0.top());
  EXPECT_EQ(s21_tmp_1.top(), tmp_1.top());

  stack<int> s21_tmp_2 = std::move(s21_tmp_1);

  EXPECT_EQ(s21_tmp_2.top(), tmp_1.top());
  EXPECT_EQ(tmp_1.size(), s21_tmp_2.size());
}

TEST(stack_test_2, stack) {
  stack<int> s21_tmp_0 = {1, 2, 3, 4};
  stack<int> s21_tmp_1 = s21_tmp_0;

  EXPECT_EQ(s21_tmp_1.top(), s21_tmp_0.top());
}

// -- TODO move operator