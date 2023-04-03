#include <gtest/gtest.h>

#include <array>
#include <iostream>

#include "../s21_array.h"

class ArrayTest : public ::testing::Test {
protected:
  s21::array<int, 5> arr_int{1, 2, 3, 4, 5};
  s21::array<std::string, 3> arr_str{"one", "two", "three"};
  const s21::array<int, 5> carr_int{1, 2, 3, 4, 5};
};

TEST_F(ArrayTest, InitializerListConstructor) {
  for (std::size_t i = 0; i < arr_int.size(); i++) {
    EXPECT_EQ(arr_int[i], i + 1);
    EXPECT_EQ(carr_int[i], i + 1);
  }
  std::string temp_str[3] = {"one", "two", "three"};
  for (std::size_t i = 0; i < arr_str.size(); i++)
    EXPECT_EQ(arr_str[i], temp_str[i]);
}

TEST_F(ArrayTest, InitializerListThrow) {
  EXPECT_ANY_THROW((s21::array<int, 2>{1, 2, 3, 4, 5, 6, 7, 8, 0}));
}

TEST_F(ArrayTest, CopyConstructor) {
  s21::array<int, 5> arr_copy{arr_int};
  for (std::size_t i = 0; i < arr_int.size(); i++)
    EXPECT_EQ(arr_int[i], arr_copy[i]);
}

TEST_F(ArrayTest, MoveConstructor) {
  s21::array<int, 5> arr_move{std::move(arr_int)};
  for (std::size_t i = 0; i < arr_int.size(); i++)
    EXPECT_EQ(arr_int[i], arr_move[i]);
}

TEST_F(ArrayTest, CopyAssignment) {
  s21::array<int, 5> arr_copy;
  arr_copy = arr_int;
  for (std::size_t i = 0; i < arr_int.size(); i++)
    EXPECT_EQ(arr_int[i], arr_copy[i]);
}

TEST_F(ArrayTest, MoveAssignment) {
  s21::array<int, 5> arr_move;
  arr_move = std::move(arr_int);
  for (std::size_t i = 0; i < arr_int.size(); i++)
    EXPECT_EQ(arr_int[i], arr_move[i]);
}

TEST_F(ArrayTest, Back) {
  EXPECT_EQ(arr_int.back(), 5);
  EXPECT_EQ(*(arr_int.end() - 1), 5);
  EXPECT_EQ(arr_str.back(), "three");
  EXPECT_EQ(*(arr_str.end() - 1), "three");
  EXPECT_EQ(carr_int.back(), 5);
  EXPECT_EQ(*(carr_int.end() - 1), 5);
}

TEST_F(ArrayTest, Front) {
  EXPECT_EQ(arr_int.front(), 1);
  EXPECT_EQ(*arr_int.begin(), 1);
  EXPECT_EQ(arr_str.front(), "one");
  EXPECT_EQ(*arr_str.begin(), "one");
  EXPECT_EQ(carr_int.front(), 1);
  EXPECT_EQ(*carr_int.begin(), 1);
}


// Because of -Werror it causes compilation error.
// Standard does not allow zero sized arrays
//TEST_F(ArrayTest, BackException) {
//  s21::array<int, 0> array0;
//  EXPECT_ANY_THROW(array0.back());
//  const s21::array<int, 0> carray0;
//  EXPECT_ANY_THROW(carray0.back());
//}
//
//TEST_F(ArrayTest, FrontException) {
//  s21::array<int, 0> array0;
//  EXPECT_ANY_THROW(array0.front());
//  const s21::array<int, 0> carray0;
//  EXPECT_ANY_THROW(carray0.front());
//}
//
//TEST_F(ArrayTest, Empty) {
//  EXPECT_FALSE(arr_int.empty());
//  s21::array<int, 0> empty_arr;
//  EXPECT_TRUE(empty_arr.empty());
//}

TEST_F(ArrayTest, Data) {
  for (std::size_t i = 0; i < arr_int.size(); i++) {
    EXPECT_EQ(*(arr_int.data() + i), arr_int[i]);
    EXPECT_EQ(*(carr_int.data() + i), carr_int[i]);
  }
  for (std::size_t i = 0; i < arr_str.size(); i++) {
    EXPECT_EQ(*(arr_str.data() + i), arr_str[i]);
  }
}

TEST_F(ArrayTest, At) {
  for (std::size_t i = 0; i < arr_int.size(); i++) {
    EXPECT_EQ(arr_int.at(i), i + 1);
    EXPECT_EQ(carr_int.at(i), i + 1);
  }
  std::string temp_str[3] = {"one", "two", "three"};
  for (std::size_t i = 0; i < arr_str.size(); i++) {
    EXPECT_EQ(arr_str.at(i), temp_str[i]);
  }
}

TEST_F(ArrayTest, AtException) {
  EXPECT_ANY_THROW(arr_int.at(10));
  EXPECT_ANY_THROW(carr_int.at(10));
  EXPECT_ANY_THROW(arr_str.at(10));
}

TEST_F(ArrayTest, Size) {
  EXPECT_EQ(arr_int.size(), 5);
  EXPECT_EQ(carr_int.size(), 5);
  EXPECT_EQ(arr_str.size(), 3);
}

TEST_F(ArrayTest, MaxSize) {
  EXPECT_EQ(arr_int.max_size(), 5);
  EXPECT_EQ(carr_int.max_size(), 5);
  EXPECT_EQ(arr_str.max_size(), 3);
}

TEST_F(ArrayTest, Iterator) {
  int i = 1;
  for (auto iter = arr_int.begin(); iter != arr_int.end(); ++iter, ++i) {
    EXPECT_EQ(*iter, i);
  }
  i = 1;
  for (auto iter = carr_int.begin(); iter != carr_int.end(); ++iter, ++i) {
    EXPECT_EQ(*iter, i);
  }
  i = 0;
  std::string temp_str[3] = {"one", "two", "three"};
  for (auto iter = arr_str.begin(); iter != arr_str.end(); iter++, i++) {
    EXPECT_EQ(*iter, temp_str[i]);
  }
}

TEST_F(ArrayTest, Swap) {
  s21::array<int, 5> arr1{10, 20, 30, 40, 50};
  s21::array<int, 5> arr1_copy = arr1;
  arr1.swap(arr_int);
  for (std::size_t i = 0; i < arr1_copy.size(); i++) {
    EXPECT_EQ(arr_int[i], arr1_copy[i]);
  }

  s21::array<std::string, 3> arr2{"expect", "assert", "test"};
  s21::array<std::string, 3> arr2_copy = arr2;
  arr_str.swap(arr2);
  for (std::size_t i = 0; i < arr2_copy.size(); i++) {
    EXPECT_EQ(arr_str[i], arr2_copy[i]);
  }
}

TEST_F(ArrayTest, Fill) {
  arr_int.fill(0);
  for (auto elem : arr_int) EXPECT_EQ(elem, 0);
}


