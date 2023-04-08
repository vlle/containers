#include <gtest/gtest.h>

#include <iostream>
#include <queue>

#include "../s21_queue.h"

using namespace s21;

TEST(queue_test_0, queue) {
  queue<int> s21_tmp;
  std::queue<int> tmp;

  tmp.push(1);
  tmp.push(2);
  tmp.push(3);

  s21_tmp.push(1);
  s21_tmp.push(2);
  s21_tmp.push(3);

  EXPECT_EQ(s21_tmp.front(), tmp.front());
  EXPECT_EQ(s21_tmp.back(), tmp.back());

  s21_tmp.pop();
  tmp.pop();

  EXPECT_EQ(s21_tmp.front(), tmp.front());
  EXPECT_EQ(s21_tmp.empty(), tmp.empty());

  s21_tmp.pop();
  s21_tmp.pop();
  tmp.pop();
  tmp.pop();

  EXPECT_EQ(s21_tmp.empty(), tmp.empty());
}

TEST(queue_test_1, queue) {
  queue<int> s21_tmp_0 = {1, 2, 3};
  std::queue<int> tmp({1, 2, 3});

  EXPECT_EQ(s21_tmp_0.size(), tmp.size());

  queue<int> s21_tmp_1 = s21_tmp_0;

  EXPECT_EQ(s21_tmp_0.front(), tmp.front());
  EXPECT_EQ(tmp.back(), s21_tmp_1.back());

  queue<int> s21_tmp_2 = {5, 6, 7};
  s21_tmp_1.swap(s21_tmp_2);

  EXPECT_EQ(s21_tmp_0.front(), tmp.front());
  EXPECT_EQ(tmp.back(), s21_tmp_2.back());
}

TEST(queue_test_2, queue) {
  queue<int> s21_tmp_0 = {1, 2, 3};
  queue<int> s21_tmp_1(s21_tmp_0);

  EXPECT_EQ(s21_tmp_0.front(), s21_tmp_1.front());
  EXPECT_EQ(s21_tmp_0.back(), s21_tmp_1.back());
}

TEST(queue_emplace_back, queue) {
  queue<int> queue{52, 12, 34};
  queue.emplace_back(1, 5, 3);
  EXPECT_TRUE(queue.back() == 3);
  queue.pop();
  queue.pop();
  queue.pop();
  EXPECT_TRUE(queue.front() == 1);
}
