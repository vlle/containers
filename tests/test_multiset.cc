#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "../s21_multiset.h"

TEST(MultisetConstructor, DefaultConstructor) {
  const s21::multiset<int> multiset;
  const std::multiset<int> std_multiset;
  EXPECT_EQ(multiset.size(), std_multiset.size());
  EXPECT_EQ(multiset.empty(), std_multiset.empty());
}

TEST(MultisetConstructor, InitializerListConstructor) {
  s21::multiset<int> multiset{1, 2, 3, 4, 1};
  std::multiset<int> std_multiset{1, 2, 3, 4, 1};

  auto multiset_p = multiset.begin();
  auto std_multiset_p = std_multiset.begin();
  EXPECT_EQ(*multiset_p, *std_multiset_p);

  multiset_p = --(multiset.end());
  std_multiset_p = --(std_multiset.end());
  EXPECT_EQ(*multiset_p, *std_multiset_p);

  EXPECT_EQ(multiset.size(), std_multiset.size());
  EXPECT_EQ(multiset.empty(), std_multiset.empty());
}

TEST(MultisetConstructor, CopyConstructor) {
  const s21::multiset<std::string> multiset{"public", "private", "protected",
                                            "private"};
  s21::multiset<std::string> multiset_copy{"Hello"};
  multiset_copy = multiset;

  const std::multiset<std::string> std_multiset{"public", "private",
                                                "protected", "private"};
  std::multiset<std::string> std_multiset_copy{"Hello"};
  std_multiset_copy = std_multiset;

  EXPECT_TRUE(multiset_copy.contains("public") && multiset.contains("public"));
  EXPECT_TRUE(multiset_copy.contains("private") &&
              multiset.contains("private"));
  EXPECT_TRUE(multiset_copy.contains("protected") &&
              multiset.contains("protected"));
  EXPECT_EQ(multiset_copy.size(), std_multiset_copy.size());
  EXPECT_EQ(multiset_copy.empty(), std_multiset_copy.empty());
}

TEST(MultisetConstructor, MoveConstructor) {
  s21::multiset<int> multiset{1, 2, 3, 4};
  s21::multiset<int> multiset_moved{100, 29};
  multiset_moved = std::move(multiset);

  std::multiset<int> std_multiset{1, 2, 3, 4};
  std::multiset<int> std_multiset_moved{100, 29};
  std_multiset_moved = std::move(std_multiset);

  auto multiset_p = multiset_moved.begin();
  auto std_multiset_p = std_multiset_moved.begin();

  for (; multiset_p != multiset_moved.end() &&
         std_multiset_p != std_multiset_moved.end();
       ++multiset_p, ++std_multiset_p)
    EXPECT_EQ(*multiset_p, *std_multiset_p);

  EXPECT_EQ(multiset_moved.size(), std_multiset_moved.size());
  EXPECT_EQ(multiset_moved.empty(), std_multiset_moved.empty());
}

TEST(MultisetConstructor, OperatorEqual) {
  s21::multiset<int> multiset{100, 22, 53, 4, 4, 4, 132, 333, 100};
  s21::multiset<int> multiset_equal = multiset;

  auto multiset_pe = --multiset.end();
  auto multiset_pb = multiset.begin();
  do {
    ++multiset_pb;
    EXPECT_EQ(*multiset_pe, *multiset_pe);
  } while (*multiset_pe != *multiset_pb);

  EXPECT_EQ(multiset.size(), multiset_equal.size());
  EXPECT_EQ(multiset.empty(), multiset_equal.empty());
}

TEST(MultisetModifiers, Erase) {
  s21::multiset<std::string> multiset{{"One"},  {"One"},   {"Two"},   {"Three"},
                                      {"Four"}, {"Five"},  {"Six"},   {"Four"},
                                      {"Five"}, {"Six"},   {"Four"},  {"Five"},
                                      {"Six"},  {"Seven"}, {"Eight"}, {"Nine"}};

  std::multiset<std::string> std_multiset{
      {"One"}, {"One"},   {"Two"},   {"Three"}, {"Four"}, {"Five"},
      {"Six"}, {"Four"},  {"Five"},  {"Six"},   {"Four"}, {"Five"},
      {"Six"}, {"Seven"}, {"Eight"}, {"Nine"}};

  // multiset.erase(--multiset.end());
  // std_multiset.erase(--std_multiset.end());
  auto multiset_p = multiset.begin();
  auto std_multiset_p = std_multiset.begin();

  for (; multiset_p != multiset.end() && std_multiset_p != std_multiset.end();
       ++multiset_p, ++std_multiset_p)
    EXPECT_EQ(*multiset_p, *std_multiset_p);

  EXPECT_EQ(multiset.size(), std_multiset.size());
  EXPECT_EQ(multiset.empty(), std_multiset.empty());
}

TEST(MultisetLookup, Find) {
  s21::multiset<std::string> multiset{{"One"},   {"Two"},   {"Three"},
                                      {"Four"},  {"Five"},  {"Six"},
                                      {"Seven"}, {"Eight"}, {"Nine"}};

  std::multiset<std::string> std_multiset{{"One"},   {"Two"},   {"Three"},
                                          {"Four"},  {"Five"},  {"Six"},
                                          {"Seven"}, {"Eight"}, {"Nine"}};

  EXPECT_EQ(*multiset.find("One"), *std_multiset.find("One"));
  EXPECT_EQ(*multiset.find("Nine"), *std_multiset.find("Nine"));
}

TEST(MultisetLookup, Contains) {
  s21::multiset<std::string> multiset{{"One"},   {"Two"},   {"Three"},
                                      {"Four"},  {"Five"},  {"Six"},
                                      {"Seven"}, {"Eight"}, {"Nine"}};

  EXPECT_EQ(multiset.contains("One"), true);
  EXPECT_EQ(multiset.contains("Hello, world!"), false);
}

TEST(MultisetModifiers, Insert) {
  s21::multiset<std::string> multiset{{"One"},   {"Two"},   {"Three"},
                                      {"Four"},  {"Five"},  {"Six"},
                                      {"Seven"}, {"Eight"}, {"Nine"}};
  std::multiset<std::string> std_multiset{{"One"},   {"Two"},   {"Three"},
                                          {"Four"},  {"Five"},  {"Six"},
                                          {"Seven"}, {"Eight"}, {"Nine"}};

  multiset.insert("Hello, world!");
  std_multiset.insert("Hello, world!");
  multiset.insert("Moscow");
  std_multiset.insert("Moscow");
  multiset.insert("School21");
  std_multiset.insert("School21");

  EXPECT_EQ(multiset.size(), std_multiset.size());
  EXPECT_EQ(multiset.empty(), std_multiset.empty());

  auto multiset_p = multiset.begin();
  auto std_multiset_p = std_multiset.begin();

  for (; multiset_p != multiset.end() && std_multiset_p != std_multiset.end();
       ++multiset_p, ++std_multiset_p)
    EXPECT_EQ(*multiset_p, *std_multiset_p);
}

TEST(MultisetModifiers, Swap) {
  s21::multiset<std::string> multiset1{
      {"One"},   {"Two"},  {"Three"}, {"Three"}, {"Two"}, {"One"},
      {"Four"},  {"Five"}, {"Four"},  {"Three"}, {"Two"}, {"One"},
      {"Three"}, {"Two"},  {"One"},   {"Three"}, {"Two"}, {"One"}};
  s21::multiset<std::string> multiset2{{"Ivan"}, {"Alex"}, {"Ivan"}, {"Elena"}};
  s21::multiset<std::string> std_multiset1{
      {"One"},   {"Two"},  {"Three"}, {"Three"}, {"Two"}, {"One"},
      {"Four"},  {"Five"}, {"Four"},  {"Three"}, {"Two"}, {"One"},
      {"Three"}, {"Two"},  {"One"},   {"Three"}, {"Two"}, {"One"}};
  s21::multiset<std::string> std_multiset2{
      {"Ivan"}, {"Alex"}, {"Ivan"}, {"Elena"}};

  ASSERT_EQ(std_multiset2.size(), 4);
  EXPECT_EQ(multiset1.size(), std_multiset1.size());
  EXPECT_EQ(multiset1.empty(), std_multiset1.empty());
  EXPECT_EQ(multiset2.size(), std_multiset2.size());
  EXPECT_EQ(multiset2.empty(), std_multiset2.empty());

  auto multiset_p = multiset1.begin();
  auto std_multiset_p = std_multiset1.begin();
  for (; multiset_p != multiset1.end() && std_multiset_p != std_multiset1.end();
       ++multiset_p, ++std_multiset_p)
    EXPECT_EQ(*multiset_p, *std_multiset_p);
  multiset_p = multiset2.begin();
  std_multiset_p = std_multiset2.begin();
  for (; multiset_p != multiset2.end() && std_multiset_p != std_multiset2.end();
       ++multiset_p, ++std_multiset_p)
    EXPECT_EQ(*multiset_p, *std_multiset_p);

  multiset1.swap(multiset2);
  std_multiset1.swap(std_multiset2);

  EXPECT_EQ(multiset1.size(), std_multiset1.size());
  EXPECT_EQ(multiset1.empty(), std_multiset1.empty());
  EXPECT_EQ(multiset2.size(), std_multiset2.size());
  EXPECT_EQ(multiset2.empty(), std_multiset2.empty());

  multiset_p = multiset1.begin();
  std_multiset_p = std_multiset1.begin();
  for (; multiset_p != multiset1.end() && std_multiset_p != std_multiset1.end();
       ++multiset_p, ++std_multiset_p)
    EXPECT_EQ(*multiset_p, *std_multiset_p);
  multiset_p = multiset2.begin();
  std_multiset_p = std_multiset2.begin();
  for (; multiset_p != multiset2.end() && std_multiset_p != std_multiset2.end();
       ++multiset_p, ++std_multiset_p)
    EXPECT_EQ(*multiset_p, *std_multiset_p);
}

TEST(MultisetModifiers, Merge) {
  s21::multiset<int> multiset1{1, 150, 43, 4};
  s21::multiset<int> multiset2{10, 22, 43, 8, 1};

  std::multiset<int> std_multiset1{1, 150, 43, 4};
  std::multiset<int> std_multiset2{10, 22, 43, 8, 1};

  multiset1.merge(multiset2);
  std_multiset1.merge(std_multiset2);

  ASSERT_EQ(multiset1.size(), std_multiset1.size());
  ASSERT_EQ(multiset1.empty(), std_multiset1.empty());

  auto multiset_p = multiset1.begin();
  auto std_multiset_p = std_multiset1.begin();
  for (; multiset_p != multiset1.end() && std_multiset_p != std_multiset1.end();
       ++multiset_p, ++std_multiset_p)
    EXPECT_EQ(*multiset_p, *std_multiset_p);
}

TEST(MultisetExtraTests, test1) {
  const s21::multiset<int> multiset{1, 150, 43, 4, 1, 43};
  const std::multiset<int> std_multiset{1, 150, 43, 4, 1, 43};
  auto multiset_p = multiset.end();
  auto std_multiset_p = std_multiset.end();
  EXPECT_EQ(*(--multiset_p), *(--std_multiset_p));
  EXPECT_EQ(*(--multiset_p), *(--std_multiset_p));
  EXPECT_EQ(*(--multiset_p), *(--std_multiset_p));
  EXPECT_EQ(*(--multiset_p), *(--std_multiset_p));
  EXPECT_EQ(*(--multiset_p), *(--std_multiset_p));
  EXPECT_EQ(*(--multiset_p), *(--std_multiset_p));
  EXPECT_TRUE(multiset_p == multiset.begin());
}

TEST(MultisetExtraTests, test2) {
  const s21::multiset<int> multiset{1, 150, 43, 1, 23, 55, 43};
  auto multiset_p = multiset.end();
  EXPECT_EQ(*(--multiset_p), 150);
  EXPECT_EQ(*(--multiset_p), 55);
  EXPECT_EQ(*(--multiset_p), 43);
  EXPECT_EQ(*(--multiset_p), 43);
  EXPECT_EQ(*(--multiset_p), 23);
  EXPECT_EQ(*(--multiset_p), 1);
  EXPECT_EQ(*(--multiset_p), 1);
  EXPECT_EQ(multiset_p, multiset_p.begin());
}

TEST(MultisetLookup, Count) {
  s21::multiset<int> multiset{1, 150, 43, 1, 23, 1, 55, 43};
  ASSERT_EQ(multiset.size(), 8);
  auto res1 = multiset.count(1);
  auto res2 = multiset.count(43);
  EXPECT_EQ(res1, 3);
  EXPECT_EQ(res2, 2);
}

TEST(MultisetLookup, EqualRange) {
  s21::multiset<int> multiset{1, 150, 43, 1, 23, 1, 55, 43};
  std::multiset<int> std_multiset{1, 150, 43, 1, 23, 1, 55, 43};
  auto iter = multiset.equal_range(43);
  auto std_iter = std_multiset.equal_range(43);
  EXPECT_EQ(*(iter).first, *(std_iter).first);
  EXPECT_EQ(*(iter).second, *(std_iter).second);
}

TEST(MultisetLookup, LowerBound) {
  s21::multiset<int> multiset{1, 150, 43, 1, 23, 1, 55, 43};
  std::multiset<int> std_multiset{1, 150, 43, 1, 23, 1, 55, 43};
  auto iter = multiset.lower_bound(43);
  auto std_iter = std_multiset.lower_bound(43);
  EXPECT_EQ(*(iter), *(std_iter));
}

TEST(MultisetLookup, UpperBound) {
  s21::multiset<int> multiset{1, 150, 43, 1, 23, 1, 55, 43};
  std::multiset<int> std_multiset{1, 150, 43, 1, 23, 1, 55, 43};
  auto iter = multiset.upper_bound(43);
  auto std_iter = std_multiset.upper_bound(43);
  EXPECT_EQ(*(iter), *(std_iter));
}

TEST(MultisetModifiers, Emplace) {
  s21::multiset<int> ad{132, 120, 122, 121, 118, 119,
                        140, 135, 134, 138, 137, 136};
  ad.emplace(12, 999, 133);
  bool find = ad.contains(12);
  EXPECT_TRUE(find);
  find = ad.contains(999);
  EXPECT_TRUE(find);
  find = ad.contains(133);
  EXPECT_TRUE(find);
}
