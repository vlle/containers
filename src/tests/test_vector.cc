#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../s21_vector.h"

TEST(VectorConstructor, DefaultConstructor) {
  const s21::vector<int> vector;
  const std::vector<int> std_vector;
  EXPECT_EQ(vector.size(), std_vector.size());
  EXPECT_EQ(vector.empty(), std_vector.empty());
  EXPECT_EQ(vector.capacity(), std_vector.capacity());
  EXPECT_EQ(vector.data(), std_vector.data());
  ASSERT_FLOAT_EQ(vector.max_size(), std_vector.max_size());
}

TEST(VectorConstructor, NullConstructor) {
  s21::vector<int> vector(0);
  std::vector<int> std_vector(0);
  EXPECT_EQ(vector.size(), std_vector.size());
  EXPECT_EQ(vector.empty(), std_vector.empty());
  EXPECT_EQ(vector.capacity(), std_vector.capacity());
  EXPECT_EQ(vector.data(), std_vector.data());
}

TEST(VectorConstructor, SizeConstructor) {
  s21::vector<int> vector(21);
  std::vector<int> std_vector(21);
  EXPECT_EQ(vector.size(), std_vector.size());
  EXPECT_EQ(vector.empty(), std_vector.empty());
  EXPECT_EQ(vector.capacity(), std_vector.capacity());
  for (size_t i = 0; i < vector.size(); i++) {
    EXPECT_EQ(vector[i], std_vector[i]);
  }
  s21::vector<std::string> str_vector(21);
  std::vector<std::string> std_str_vector(21);
  EXPECT_EQ(str_vector.size(), std_str_vector.size());
  EXPECT_EQ(str_vector.empty(), std_str_vector.empty());
  EXPECT_EQ(str_vector.capacity(), std_str_vector.capacity());
  for (size_t i = 0; i < str_vector.size(); i++) {
    EXPECT_EQ(str_vector[i], std_str_vector[i]);
  }
}

TEST(VectorConstructor, InitializerListConstructor) {
  s21::vector<int> vector{1, 2, 3, 4};
  std::vector<int> std_vector{1, 2, 3, 4};

  for (size_t i = 0; i < vector.size(); i++) {
    EXPECT_EQ(vector[i], std_vector[i]);
  }

  EXPECT_EQ(vector.size(), std_vector.size());
  EXPECT_EQ(vector.empty(), std_vector.empty());
}

TEST(VectorConstructor, CopyConstructor) {
  s21::vector<std::string> vector{"One", "Two", "Three", "Four", "Five"};
  s21::vector<std::string> vector_copy = vector;

  for (size_t i = 0; i < vector.size(); i++) {
    EXPECT_EQ(vector[i], vector_copy[i]);
  }

  EXPECT_EQ(vector.size(), vector_copy.size());
}

TEST(VectorConstructor, MoveConstructor) {
  s21::vector<int> vector1{1, 2, 3, 4};
  s21::vector<int> vector_m1{100, 200};
  vector_m1 = std::move(vector1);

  s21::vector<int> vector2{1, 2, 3, 4};
  s21::vector<int> vector_m2(std::move(vector2));

  std::vector<int> std_vector1{1, 2, 3, 4};
  std::vector<int> std_vector_m1{100, 200};
  std_vector_m1 = std::move(std_vector1);

  std::vector<int> std_vector2{1, 2, 3, 4};
  std::vector<int> std_vector_m2(std::move(std_vector2));

  for (size_t i = 0; i < vector_m1.size() && i < std_vector_m1.size(); i++) {
    EXPECT_EQ(vector_m1[i], std_vector_m1[i]);
  }

  EXPECT_EQ(vector_m1.size(), std_vector_m1.size());
  EXPECT_EQ(vector_m1.empty(), std_vector_m1.empty());

  for (size_t i = 0; i < vector_m2.size() && i < std_vector_m2.size(); i++) {
    EXPECT_EQ(vector_m2[i], std_vector_m2[i]);
  }

  EXPECT_EQ(vector_m2.size(), std_vector_m2.size());
  EXPECT_EQ(vector_m2.empty(), std_vector_m2.empty());
}

TEST(VectorConstructor, OperatorEqual) {
  const s21::vector<int> vector{100, 22, 53, 4, 2, 1, 132, 333, 101};
  s21::vector<int> vector_equal{1, 2, 3};
  vector_equal = vector;

  for (size_t i = 0; i < vector.size() && i < vector_equal.size(); i++) {
    EXPECT_EQ(vector[i], vector_equal[i]);
  }

  EXPECT_EQ(vector.size(), vector_equal.size());
  EXPECT_EQ(vector.empty(), vector_equal.empty());
}

TEST(VectorModifiers, Erase) {
  s21::vector<std::string> vector{{"One"},   {"Two"},   {"Three"},
                                  {"Four"},  {"Five"},  {"Six"},
                                  {"Seven"}, {"Eight"}, {"Nine"}};

  std::vector<std::string> std_vector{{"One"},   {"Two"},   {"Three"},
                                      {"Four"},  {"Five"},  {"Six"},
                                      {"Seven"}, {"Eight"}, {"Nine"}};

  vector.erase(vector.end() - 1);
  std_vector.erase(std_vector.end() - 1);

  EXPECT_EQ(vector.at(0), std_vector.at(0));
  EXPECT_EQ(vector.at(1), std_vector.at(1));
  EXPECT_EQ(vector.size(), std_vector.size());
  EXPECT_EQ(vector.empty(), std_vector.empty());
}
TEST(VectorModifiers, EraseThrow) {
  s21::vector<std::string> vector{{"One"}, {"Two"}, {"Three"}};
  EXPECT_ANY_THROW(vector.erase(vector.end() + 1));
}

TEST(VectorModifiers, Insert) {
  s21::vector<std::string> vector{{"One"},   {"Two"},   {"Three"},
                                  {"Four"},  {"Five"},  {"Six"},
                                  {"Seven"}, {"Eight"}, {"Nine"}};
  std::vector<std::string> std_vector{{"One"},   {"Two"},   {"Three"},
                                      {"Four"},  {"Five"},  {"Six"},
                                      {"Seven"}, {"Eight"}, {"Nine"}};

  vector.insert(vector.begin() + 1, "Hello, world!");
  std_vector.insert(std_vector.begin() + 1, "Hello, world!");
  vector.insert(vector.begin() + 2, "Moscow");
  std_vector.insert(std_vector.begin() + 2, "Moscow");
  vector.insert(vector.begin() + 3, "School21");
  std_vector.insert(std_vector.cbegin() + 3, "School21");

  EXPECT_EQ(vector.size(), std_vector.size());
  EXPECT_EQ(vector.empty(), std_vector.empty());

  for (size_t i = 0; i < std_vector.size() && i < vector.size(); i++) {
    EXPECT_EQ(vector[i], std_vector[i]);
  }
}

TEST(VectorModifiers, InsertThrow) {
  s21::vector<std::string> vector{{"One"},   {"Two"},   {"Three"},
                                  {"Four"},  {"Five"},  {"Six"},
                                  {"Seven"}, {"Eight"}, {"Nine"}};
  EXPECT_ANY_THROW(vector.insert(vector.end() + 1, "ERROR"));
}

TEST(VectorModifiers, Swap) {
  s21::vector<int> s21_first{5, 3, 22, 122};
  s21::vector<int> vector_second{1, 2, 3, 4, 5};
  s21::vector<int> std_first{5, 3, 22, 122};
  s21::vector<int> std_vector_second{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_first.size(), std_first.size());
  EXPECT_EQ(s21_first.empty(), std_first.empty());
  EXPECT_EQ(vector_second.size(), std_vector_second.size());
  EXPECT_EQ(vector_second.empty(), std_vector_second.empty());

  auto s21_p = s21_first.begin();
  auto std_p = std_first.begin();
  for (; s21_p != s21_first.end() && std_p != std_first.end(); ++s21_p, ++std_p)
    EXPECT_EQ(*s21_p, *std_p);
  s21_p = vector_second.begin();
  std_p = std_vector_second.begin();
  for (; s21_p != vector_second.end() && std_p != std_vector_second.end();
       ++s21_p, ++std_p)
    EXPECT_EQ(*s21_p, *std_p);

  s21_first.swap(vector_second);
  std_first.swap(std_vector_second);

  EXPECT_EQ(s21_first.size(), std_first.size());
  EXPECT_EQ(s21_first.empty(), std_first.empty());
  EXPECT_EQ(vector_second.size(), std_vector_second.size());
  EXPECT_EQ(vector_second.empty(), std_vector_second.empty());

  s21_p = s21_first.begin();
  std_p = std_first.begin();
  for (; s21_p != s21_first.end() && std_p != std_first.end(); ++s21_p, ++std_p)
    EXPECT_EQ(*s21_p, *std_p);
  s21_p = vector_second.begin();
  std_p = std_vector_second.begin();
  for (; s21_p != vector_second.end() && std_p != std_vector_second.end();
       ++s21_p, ++std_p)
    EXPECT_EQ(*s21_p, *std_p);
}

TEST(VectorModifiers, AtConst) {
  const s21::vector<int> vector{1, 150, 43, 4};
  const std::vector<int> std_vector{1, 150, 43, 4};
  const s21::vector<std::string> vector_str{{"One"}, {"Two"}, {"Three"}};
  const std::vector<std::string> std_vector_str{{"One"}, {"Two"}, {"Three"}};
  EXPECT_EQ(vector.at(2), std_vector.at(2));
  EXPECT_EQ(vector_str.at(2), std_vector_str.at(2));
}

TEST(VectorModifiers, Front) {
  s21::vector<int> vector{1, 150, 43, 4};
  std::vector<int> std_vector{1, 150, 43, 4};
  s21::vector<std::string> vector_str{{"One"}, {"Two"}, {"Three"}};
  std::vector<std::string> std_vector_str{{"One"}, {"Two"}, {"Three"}};
  EXPECT_EQ(vector.front(), std_vector.front());
  EXPECT_EQ(vector_str.front(), std_vector_str.front());
  const s21::vector<int> vector_c{1, 150, 43, 4};
  const std::vector<int> std_vector_c{1, 150, 43, 4};
  const s21::vector<std::string> vector_str_c{{"One"}, {"Two"}, {"Three"}};
  const std::vector<std::string> std_vector_str_c{{"One"}, {"Two"}, {"Three"}};
  EXPECT_EQ(vector_c.front(), std_vector_c.front());
  EXPECT_EQ(vector_str_c.front(), std_vector_str_c.front());
}

TEST(VectorModifiers, Back) {
  s21::vector<int> vector{1, 150, 43, 4};
  std::vector<int> std_vector{1, 150, 43, 4};
  s21::vector<std::string> vector_str{{"One"}, {"Two"}, {"Three"}};
  std::vector<std::string> std_vector_str{{"One"}, {"Two"}, {"Three"}};
  EXPECT_EQ(vector.back(), std_vector.back());
  EXPECT_EQ(vector_str.back(), std_vector_str.back());
  const s21::vector<int> vector_c{1, 150, 43, 4};
  const std::vector<int> std_vector_c{1, 150, 43, 4};
  const s21::vector<std::string> vector_str_c{{"One"}, {"Two"}, {"Three"}};
  const std::vector<std::string> std_vector_str_c{{"One"}, {"Two"}, {"Three"}};
  EXPECT_EQ(vector_c.back(), std_vector_c.back());
  EXPECT_EQ(vector_str_c.back(), std_vector_str_c.back());
}

TEST(VectorModifiers, Reserve) {
  s21::vector<int> vector(10);
  std::vector<int> std_vector(10);
  vector.reserve(100);
  std_vector.reserve(100);
  EXPECT_EQ(vector.size(), std_vector.size());
  EXPECT_EQ(vector.capacity(), std_vector.capacity());
  s21::vector<std::string> vector_str{{"One"}, {"Two"}, {"Three"}};
  std::vector<std::string> std_vector_str{{"One"}, {"Two"}, {"Three"}};
  vector_str.reserve(100);
  std_vector_str.reserve(100);
  EXPECT_EQ(vector_str.size(), std_vector_str.size());
  EXPECT_EQ(vector_str.capacity(), std_vector_str.capacity());
}

TEST(VectorModifiers, ShrinkToFit) {
  s21::vector<int> vector(100);
  std::vector<int> std_vector(100);
  vector.shrink_to_fit();
  std_vector.shrink_to_fit();
  EXPECT_EQ(vector.size(), std_vector.size());
  EXPECT_EQ(vector.capacity(), std_vector.capacity());
  s21::vector<std::string> vector_str;
  std::vector<std::string> std_vector_str;
  vector_str.shrink_to_fit();
  std_vector_str.shrink_to_fit();
  EXPECT_EQ(vector_str.size(), std_vector_str.size());
  EXPECT_EQ(vector_str.capacity(), std_vector_str.capacity());

  vector.push_back(1);
  vector.push_back(1);
  vector.push_back(1);
  std_vector.push_back(1);
  std_vector.push_back(1);
  std_vector.push_back(1);
  vector.shrink_to_fit();
  std_vector.shrink_to_fit();
  EXPECT_EQ(vector.size(), std_vector.size());
  EXPECT_EQ(vector.capacity(), std_vector.capacity());

  vector_str.push_back("Hello");
  vector_str.push_back("Hello");
  vector_str.push_back("Hello");
  std_vector_str.push_back("Hello");
  std_vector_str.push_back("Hello");
  std_vector_str.push_back("Hello");
  vector_str.shrink_to_fit();
  std_vector_str.shrink_to_fit();
  EXPECT_EQ(vector_str.size(), std_vector_str.size());
  EXPECT_EQ(vector_str.capacity(), std_vector_str.capacity());
}

TEST(VectorModifiers, PushBack) {
  s21::vector<int> vector{12, 43, 66, 11};
  std::vector<int> std_vector{12, 43, 66, 11};
  vector.push_back(100);
  vector.push_back(100);
  vector.push_back(100);
  std_vector.push_back(100);
  std_vector.push_back(100);
  std_vector.push_back(100);
  for (size_t i = 0; i < vector.size() && i < std_vector.size(); i++) {
    EXPECT_EQ(vector.at(i), std_vector.at(i));
  }
  EXPECT_EQ(vector.size(), std_vector.size());
  EXPECT_EQ(vector.capacity(), std_vector.capacity());

  s21::vector<std::string> vector_str{"One", "Two"};
  std::vector<std::string> std_vector_str{"One", "Two"};
  vector_str.push_back("Three");
  std_vector_str.push_back("Three");
  vector_str.push_back("Four");
  std_vector_str.push_back("Four");
  vector_str.push_back("Five");
  std_vector_str.push_back("Five");
  for (size_t i = 0; i < vector_str.size() && i < std_vector_str.size(); i++) {
    EXPECT_EQ(vector_str.at(i), std_vector_str.at(i));
  }
  EXPECT_EQ(vector_str.size(), std_vector_str.size());
  EXPECT_EQ(vector_str.capacity(), std_vector_str.capacity());
}

TEST(VectorModifiers, PopBack) {
  s21::vector<int> vector{12, 43, 66, 11};
  std::vector<int> std_vector{12, 43, 66, 11};
  vector.pop_back();
  vector.pop_back();
  std_vector.pop_back();
  std_vector.pop_back();
  for (size_t i = 0; i < vector.size() && i < std_vector.size(); i++) {
    EXPECT_EQ(vector.at(i), std_vector.at(i));
  }
  EXPECT_EQ(vector.size(), std_vector.size());
  EXPECT_EQ(vector.capacity(), std_vector.capacity());
  EXPECT_EQ(vector.back(), std_vector.back());

  s21::vector<std::string> vector_str{"One", "Two", "Three", "Four"};
  std::vector<std::string> std_vector_str{"One", "Two", "Three", "Four"};
  vector_str.pop_back();
  std_vector_str.pop_back();
  vector_str.pop_back();
  std_vector_str.pop_back();

  for (size_t i = 0; i < vector_str.size() && i < std_vector_str.size(); i++) {
    EXPECT_EQ(vector_str.at(i), std_vector_str.at(i));
  }
  EXPECT_EQ(vector_str.size(), std_vector_str.size());
  EXPECT_EQ(vector_str.capacity(), std_vector_str.capacity());
  EXPECT_EQ(vector_str.back(), std_vector_str.back());
}

TEST(VectorModifiers, Clear) {
  s21::vector<int> vector{12, 43, 66, 11};
  std::vector<int> std_vector{12, 43, 66, 11};
  vector.clear();
  std_vector.clear();
  EXPECT_EQ(vector.size(), std_vector.size());
  EXPECT_EQ(vector.capacity(), std_vector.capacity());
  s21::vector<std::string> vector_str{"One", "Two", "Three", "Four"};
  std::vector<std::string> std_vector_str{"One", "Two", "Three", "Four"};
  vector_str.clear();
  std_vector_str.clear();
  EXPECT_EQ(vector_str.size(), std_vector_str.size());
  EXPECT_EQ(vector_str.capacity(), std_vector_str.capacity());
}

TEST(VectorEmplace, Emplace) {
  s21::vector<std::string> vector_s21;
  std::vector<std::string> vector_std;

  vector_s21.emplace(vector_s21.begin(), "One");
  vector_std.emplace(vector_std.begin(), "One");
  vector_s21.emplace(vector_s21.begin(), "Two");
  vector_std.emplace(vector_std.begin(), "Two");
  vector_s21.emplace(vector_s21.begin(), "Three");
  vector_std.emplace(vector_std.begin(), "Three");

  for (size_t i = 0; i < vector_s21.size(); i++) {
    EXPECT_EQ(vector_s21[i], vector_std[i]);
  }

  EXPECT_EQ(vector_s21.size(), vector_std.size());
  EXPECT_EQ(vector_s21.capacity(), vector_std.capacity());
}

TEST(VectorEmplace, EmplaceBack) {
  s21::vector<int> vector_s21_1;
  s21::vector<int> vector_s21_2;

  vector_s21_1.push_back(1);
  vector_s21_1.push_back(65);
  vector_s21_1.push_back(12);

  vector_s21_2.emplace_back(1, 65, 12);

  for (size_t i = 0; i < vector_s21_1.size(); i++) {
  EXPECT_EQ(vector_s21_1[i], vector_s21_2[i]);
  }

  EXPECT_EQ(vector_s21_1.size(), vector_s21_2.size());
  EXPECT_EQ(vector_s21_1.capacity(), vector_s21_2.capacity());
}
