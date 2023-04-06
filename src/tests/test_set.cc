#include <gtest/gtest.h>

#include <iostream>
#include <set>
#include <stdexcept>

#include "../s21_set.h"

TEST(SetConstructor, DefaultConstructor) {
  const s21::set<int> s21_s;
  const std::set<int> std_s;
  EXPECT_EQ(s21_s.size(), std_s.size());
  EXPECT_EQ(s21_s.empty(), std_s.empty());
}

TEST(SetConstructor, InitializerListConstructor) {
  s21::set<int> s21_s{1, 2, 3, 4};
  std::set<int> std_s{1, 2, 3, 4};

  auto s21_p = s21_s.begin();
  auto std_p = std_s.begin();
  EXPECT_EQ(*s21_p, *std_p);

  s21_p = --(s21_s.end());
  std_p = --(std_s.end());
  EXPECT_EQ(*s21_p, *std_p);

  EXPECT_EQ(s21_s.size(), std_s.size());
  EXPECT_EQ(s21_s.empty(), std_s.empty());
}

TEST(SetConstructor, CopyConstructor) {
  const s21::set<int> s21_s{1, 2, 3, 4};
  s21::set<int> s21_sc{1};
  s21_sc = s21_s;

  const std::set<int> std_s{1, 2, 3, 4};
  std::set<int> std_sc = std_s;

  auto s21_p = s21_sc.begin();
  auto std_p = std_sc.begin();

  for (; s21_p != s21_sc.end() && std_p != std_sc.end(); s21_p++, std_p++)
    EXPECT_EQ(*s21_p, *std_p);

  EXPECT_EQ(s21_s.size(), std_s.size());
  EXPECT_EQ(s21_s.empty(), std_s.empty());
}

TEST(SetConstructor, MoveConstructor) {
  s21::set<int> s21_s{1, 2, 3, 4};
  s21::set<int> s21_sm{44, 33};
  s21_sm = std::move(s21_s);

  s21::set<int> s21_s1{1, 2, 3, 4};
  s21::set<int> s21_s2{1, 2, 3, 4};
  s21::set<int> s21_sm1(std::move(s21_s1));

  auto s21_p1 = s21_s2.begin();
  auto s21_p2 = s21_sm1.begin();

  for (; s21_p1 != s21_s2.end() && s21_p2 != s21_sm1.end(); ++s21_p1, ++s21_p2)
    EXPECT_EQ(*s21_p1, *s21_p2);

  std::set<int> std_s{1, 2, 3, 4};
  std::set<int> std_sm{44, 33};
  std_sm = std::move(std_s);

  auto s21_p = s21_sm.begin();
  auto std_p = std_sm.begin();

  for (; s21_p != s21_sm.end() && std_p != std_sm.end(); ++s21_p, ++std_p)
    EXPECT_EQ(*s21_p, *std_p);

  EXPECT_EQ(s21_sm.size(), std_sm.size());
  EXPECT_EQ(s21_sm.empty(), std_sm.empty());
}

TEST(SetConstructor, OperatorEqual) {
  s21::set<int> s21_s{100, 22, 53, 4, 2, 1, 132, 333, 101};
  s21::set<int> s21_se = s21_s;

  auto s21_pe = --s21_s.end();
  auto s21_pb = s21_s.begin();
  do {
    ++s21_pb;
    EXPECT_EQ(*s21_pe, *s21_pe);
  } while (*s21_pe != *s21_pb);

  EXPECT_EQ(s21_s.size(), s21_se.size());
  EXPECT_EQ(s21_s.empty(), s21_se.empty());
}

TEST(SetModifiers, Erase) {
  s21::set<std::string> s21_s{{"One"}, {"Two"},   {"Three"}, {"Four"}, {"Five"},
                              {"Six"}, {"Seven"}, {"Eight"}, {"Nine"}};

  std::set<std::string> std_s{{"One"}, {"Two"},   {"Three"}, {"Four"}, {"Five"},
                              {"Six"}, {"Seven"}, {"Eight"}, {"Nine"}};

  s21_s.erase(--s21_s.end());
  std_s.erase(--std_s.end());

  EXPECT_EQ(s21_s.size(), std_s.size());
  EXPECT_EQ(s21_s.empty(), std_s.empty());

  auto s21_p = s21_s.begin();
  auto std_p = std_s.begin();

  for (; s21_p != s21_s.end() && std_p != std_s.end(); ++s21_p, ++std_p) {
    EXPECT_EQ(*s21_p, *std_p);
  }
}

TEST(SetLookup, Find) {
  s21::set<std::string> s21_s{{"One"}, {"Two"},   {"Three"}, {"Four"}, {"Five"},
                              {"Six"}, {"Seven"}, {"Eight"}, {"Nine"}};

  std::set<std::string> std_s{{"One"}, {"Two"},   {"Three"}, {"Four"}, {"Five"},
                              {"Six"}, {"Seven"}, {"Eight"}, {"Nine"}};

  EXPECT_EQ(*s21_s.find("One"), *std_s.find("One"));
  EXPECT_EQ(*s21_s.find("Nine"), *std_s.find("Nine"));
}

TEST(SetLookup, Contains) {
  s21::set<std::string> s21_s{{"One"}, {"Two"},   {"Three"}, {"Four"}, {"Five"},
                              {"Six"}, {"Seven"}, {"Eight"}, {"Nine"}};

  EXPECT_EQ(s21_s.contains("One"), true);
  EXPECT_EQ(s21_s.contains("Hello, world!"), false);
}

TEST(SetModifiers, Insert) {
  s21::set<std::string> s21_s{{"One"}, {"Two"},   {"Three"}, {"Four"}, {"Five"},
                              {"Six"}, {"Seven"}, {"Eight"}, {"Nine"}};
  std::set<std::string> std_s{{"One"}, {"Two"},   {"Three"}, {"Four"}, {"Five"},
                              {"Six"}, {"Seven"}, {"Eight"}, {"Nine"}};

  s21_s.insert("Hello, world!");
  std_s.insert("Hello, world!");
  s21_s.insert("Moscow");
  std_s.insert("Moscow");
  s21_s.insert("School21");
  std_s.insert("School21");

  EXPECT_EQ(s21_s.size(), std_s.size());
  EXPECT_EQ(s21_s.empty(), std_s.empty());

  auto s21_p = s21_s.begin();
  auto std_p = std_s.begin();

  for (; s21_p != s21_s.end() && std_p != std_s.end(); ++s21_p, ++std_p)
    EXPECT_EQ(*s21_p, *std_p);
}

TEST(SetModifiers, Swap) {
  s21::set<std::string> s21_first{{"One"},   {"Two"},   {"Three"},
                                  {"Four"},  {"Five"},  {"Six"},
                                  {"Seven"}, {"Eight"}, {"Nine"}};
  s21::set<std::string> s21_second{{"Ivan"}, {"Alex"}, {"Nikolay"}, {"Elena"}};
  s21::set<std::string> std_first{{"One"},   {"Two"},   {"Three"},
                                  {"Four"},  {"Five"},  {"Six"},
                                  {"Seven"}, {"Eight"}, {"Nine"}};
  s21::set<std::string> std_second{{"Ivan"}, {"Alex"}, {"Nikolay"}, {"Elena"}};

  EXPECT_EQ(s21_first.size(), std_first.size());
  EXPECT_EQ(s21_first.empty(), std_first.empty());
  EXPECT_EQ(s21_second.size(), std_second.size());
  EXPECT_EQ(s21_second.empty(), std_second.empty());

  auto s21_p = s21_first.begin();
  auto std_p = std_first.begin();
  for (; s21_p != s21_first.end() && std_p != std_first.end(); ++s21_p, ++std_p)
    EXPECT_EQ(*s21_p, *std_p);
  s21_p = s21_second.begin();
  std_p = std_second.begin();
  for (; s21_p != s21_second.end() && std_p != std_second.end();
       ++s21_p, ++std_p)
    EXPECT_EQ(*s21_p, *std_p);

  s21_first.swap(s21_second);
  std_first.swap(std_second);

  EXPECT_EQ(s21_first.size(), std_first.size());
  EXPECT_EQ(s21_first.empty(), std_first.empty());
  EXPECT_EQ(s21_second.size(), std_second.size());
  EXPECT_EQ(s21_second.empty(), std_second.empty());

  s21_p = s21_first.begin();
  std_p = std_first.begin();
  for (; s21_p != s21_first.end() && std_p != std_first.end(); ++s21_p, ++std_p)
    EXPECT_EQ(*s21_p, *std_p);
  s21_p = s21_second.begin();
  std_p = std_second.begin();
  for (; s21_p != s21_second.end() && std_p != std_second.end();
       ++s21_p, ++std_p)
    EXPECT_EQ(*s21_p, *std_p);
}

TEST(SetModifiers, Merge) {
  s21::set<int> s21_s1{1, 150, 43, 4};
  s21::set<int> s21_s2{10, 22, 43, 8, 1};

  std::set<int> std_s1{1, 150, 43, 4};
  std::set<int> std_s2{10, 22, 43, 8, 1};

  s21_s1.merge(s21_s2);
  std_s1.merge(std_s2);

  EXPECT_EQ(s21_s1.size(), std_s1.size());
  EXPECT_EQ(s21_s1.empty(), std_s1.empty());

  auto s21_p = s21_s1.begin();
  auto std_p = std_s1.begin();
  for (; s21_p != s21_s1.end() && std_p != std_s1.end(); ++s21_p, ++std_p) {
    EXPECT_EQ(*s21_p, *std_p);
  }
  for (; s21_p != s21_s1.end() && std_p != std_s1.end(); ++s21_p, ++std_p)
    EXPECT_EQ(*s21_p, *std_p);
}

TEST(SetExtraTests, test1) {
  const s21::set<int> s21_s{1, 150, 43, 4};
  const std::set<int> std_s{1, 150, 43, 4};
  auto s21_p = s21_s.end();
  auto std_p = std_s.end();
  EXPECT_TRUE(*(--s21_p) == *(--std_p));
  EXPECT_TRUE(*(--s21_p) == *(--std_p));
  EXPECT_TRUE(*(--s21_p) == *(--std_p));
  EXPECT_TRUE(*(--s21_p) == *(--std_p));
  EXPECT_TRUE(s21_p == s21_s.begin());
}

TEST(SetExtraTests, test2) {
  const s21::set<int> s21_s{1, 150, 43, 4};
  auto s21_p = s21_s.end();
  EXPECT_TRUE(*(--s21_p) == 150);
  EXPECT_TRUE(*(--s21_p) == 43);
  EXPECT_TRUE(*(--s21_p) == 4);
  EXPECT_TRUE(*(--s21_p) == 1);
  EXPECT_TRUE(s21_p == s21_s.begin());
}

TEST(Set, 1) {
  s21::set<int> a{-120, 55, 5};
  a.insert(5);
  a.insert(5);
  a.insert(3);
  a.insert(8);
  a.insert(5);
  a.insert(10);
  a.insert(1);
  a.insert(2);
  a.insert(52);
  a.insert(13);
  a.insert(-5);
  a.insert(0);
  a.insert(22);
  a.insert(-21);
  a.insert(99);
  a.insert(6);

  int ca = 105;
  a.insert(ca);
}

TEST(Set, 2_test_size) {
  s21::set<int> a{-120, 55, 5};

  ASSERT_EQ(3, a.size());
}

TEST(Set, 3_test_empty) {
  s21::set<int> a;

  ASSERT_EQ(true, a.empty());
  ASSERT_EQ(0, a.size());
}

TEST(Set, 3_test_not_empty) {
  s21::set<int> a{1};

  ASSERT_EQ(false, a.empty());
}

TEST(Set, 4_iterator) {
  s21::set<int> a{1, 2, 3, -2, 0};
  s21::set<int>::iterator it = a.begin();
  ASSERT_EQ(*it, -2);
}

TEST(Set, 5_increment) {
  s21::set<int> a{1, 2, 3, -2, 0};
  s21::set<int>::iterator it = a.begin();
  ASSERT_EQ(*it, -2);
  it++;
  ASSERT_EQ(*it, 0);
  it++;
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
}

TEST(Set, 6_float) {
  s21::set<float> a;
  a.insert(4.5);
  auto it = a.begin();
  ASSERT_EQ(*it, 4.5);
}

TEST(Set, 7_string) {
#include <string>
  s21::set<std::string> a;
  a.insert("aboba");
  s21::set<std::string>::iterator it = a.begin();
  ASSERT_EQ(*it, "aboba");
}
TEST(Set, 8_for) {
  s21::set<int> a{1, 2, 3, 4, 5};

  int b = 1;
  for (auto it = a.begin(); it != a.end(); it++) {
    ASSERT_EQ(*it, b);
    b++;
  }
}

TEST(Set, 10_nullptr) {
  s21::set<int> a;
  auto it = a.begin();

  ASSERT_THROW(*it, std::runtime_error);
}

TEST(Set, 11_find) {
  s21::set<std::string> a{"aboba", "flex"};
  auto it = a.find("flex");

  ASSERT_EQ(*it, "flex");
}

TEST(Set, 12_find) {
  s21::set<std::string> a{"aboba", "flex"};
  auto it = a.find("cringe");

  ASSERT_THROW(*it, std::runtime_error);
}

TEST(Set, 13_contains) {
  s21::set<std::string> a;
  a.insert("meow");

  bool res = a.contains("meow");
  ASSERT_EQ(res, true);
}

TEST(Set, 14_contains) {
  s21::set<std::string> a;
  a.insert("meow\n");

  bool res = a.contains("meow");
  ASSERT_EQ(res, false);
  res = a.contains("meow\n");
  ASSERT_EQ(res, true);
}

TEST(Set, 15_erase) {
  s21::set<int> a{5, 2, 3, 10, 9, 12, 8};

  auto it = a.find(9);
  a.erase(it);
  ASSERT_THROW(*a.find(9), std::runtime_error);
  int tmp[6] = {2, 3, 5, 8, 10, 12};

  int i = 0;
  for (auto it = a.begin(); it != a.end(); it++) {
    ASSERT_EQ(*it, tmp[i]);
    i++;
  }

  it = a.find(3);
  a.erase(it);
  int tmp2[5] = {2, 5, 8, 10, 12};
  i = 0;
  for (auto it = a.begin(); it != a.end(); it++) {
    ASSERT_EQ(*it, tmp2[i]);
    i++;
  }
}

TEST(Set, 16_erase_root) {
  s21::set<int> a{5, 2, 3};

  a.erase(a.find(5));

  int tmp[2] = {2, 3};
  int i = 0;
  for (auto it = a.begin(); it != a.end(); ++it) {
    ASSERT_EQ(*it, tmp[i]);
    i++;
  }
}

TEST(Set, 17_erase) {
  s21::set<int> a{5, 2, 3};

  a.erase(a.find(3));

  ASSERT_EQ(*a.find(2), 2);
  ASSERT_EQ(*a.find(5), 5);
  int tmp[2] = {2, 5};
  int i = 0;
  for (auto it = a.begin(); it != a.end(); it++) {
    ASSERT_EQ(*it, tmp[i]);
    i++;
  }
}

TEST(Set, 18_clear) {
  s21::set<int> a{1, 2};

  a.clear();
  auto it = a.begin();

  ASSERT_THROW(*it, std::runtime_error);
}

TEST(Set, 19_clear) {
  s21::set<int> a{1, 2};

  a.clear();
  auto it = a.begin();

  ASSERT_THROW(*it, std::runtime_error);
}

TEST(Set, 20_clear_empty) {
  s21::set<int> a;

  a.clear();
  auto it = a.begin();

  ASSERT_THROW(*it, std::runtime_error);
}

TEST(Set, 21_swap) {
  s21::set<int> a{1, 2, 3};
  s21::set<int> b{4, 5, 6};

  a.swap(b);
  auto it = a.begin();

  ASSERT_EQ(*it, 4);
  it++;
  ASSERT_EQ(*it, 5);
  it++;
  ASSERT_EQ(*it, 6);
}

TEST(Set, 22_swap) {
  s21::set<int> a{1, 2, 3};
  s21::set<int> b{4, 5, 6};

  a.swap(b);
  auto it = b.begin();

  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
}

TEST(Set, 23_merge) {
  s21::set<int> a{1, 2, 3};
  s21::set<int> b{4, 5, 6};

  a.merge(b);

  int i = 1;
  for (auto it = a.begin(); it != a.end(); it++) {
    ASSERT_EQ(*it, i);
    i++;
  }

  ASSERT_EQ(a.size(), 6);
}

TEST(Set, 24_merge_empty) {
  s21::set<int> a{1, 2, 3};
  s21::set<int> b;

  a.merge(b);

  int i = 1;
  for (auto it = a.begin(); it != a.end(); it++) {
    ASSERT_EQ(*it, i);
    i++;
  }
}

TEST(Set, 25_merge_empty_2) {
  s21::set<int> a;
  s21::set<int> b{1, 2, 3};

  a.merge(b);

  int i = 1;
  for (auto it = a.begin(); it != a.end(); it++) {
    ASSERT_EQ(*it, i);
    i++;
  }
}

TEST(Set, 26_size) {
  s21::set<int> a{1, 2, 3};
  a.erase(a.find(2));
  ASSERT_EQ(a.size(), 2);
  a.clear();
  ASSERT_EQ(a.size(), 0);
}

TEST(Set, 27_copy) {
  s21::set<int> a{1, 2, 3};
  s21::set<int> b(a);
  int i = 1;
  for (auto it = b.begin(); it != b.end(); it++) {
    ASSERT_EQ(*it, i);
    i++;
  }
}

TEST(Set, 28_copy_empty) {
  s21::set<int> a;
  s21::set<int> b(a);

  auto it = b.begin();

  ASSERT_THROW(*it, std::runtime_error);
}

TEST(Set, 28_move) {
  s21::set<int> a{1, 2, 3};
  s21::set<int> b(std::move(a));

  int i = 1;
  for (auto it = b.begin(); it != b.end(); it++) {
    ASSERT_EQ(*it, i);
    i++;
  }
}

TEST(Set, 29_equal) {
  s21::set<int> a{1, 2, 3};
  s21::set<int> b;
  b = std::move(a);

  int i = 1;
  for (auto it = b.begin(); it != b.end(); it++) {
    ASSERT_EQ(*it, i);
    i++;
  }
}

TEST(Set, 31_increments) {
  s21::set<int> a{1, 0, -1};

  auto it = a.begin();
  it++;
  ASSERT_EQ(*it, 0);
  ++it;
  ASSERT_EQ(*it, 1);
  --it;
  ASSERT_EQ(*it, 0);
  it--;
  ASSERT_EQ(*it, -1);
}

TEST(Set, 35_insert) {
  s21::set<int> aboba;
  auto pr = aboba.insert(5);
  ASSERT_EQ(pr.second, true);
  auto pr1 = aboba.insert(5);
  ASSERT_EQ(pr1.second, false);
}

TEST(Set, 36_additional) {
  s21::set<int> ad{132, 120, 122, 121, 118, 119, 140, 135, 134, 138, 137, 136};

  int arr[12] = {118, 119, 120, 121, 122, 132, 134, 135, 136, 137, 138, 140};
  auto it = ad.begin();

  ASSERT_EQ(*it, arr[0]);
  it++;
  ASSERT_EQ(*it, arr[1]);
  it++;
  ASSERT_EQ(*it, arr[2]);
  it++;
  ASSERT_EQ(*it, arr[3]);
  it++;
  ASSERT_EQ(*it, arr[4]);
  it++;
  ASSERT_EQ(*it, arr[5]);
  it++;
  ASSERT_EQ(*it, arr[6]);
  it++;
  ASSERT_EQ(*it, arr[7]);
  it++;
  ASSERT_EQ(*it, arr[8]);
  it++;
  ASSERT_EQ(*it, arr[9]);
  it++;
  ASSERT_EQ(*it, arr[10]);
  it++;
  ASSERT_EQ(*it, arr[11]);
  it++;
}

TEST(Set, 37_emplace) {
  s21::set<int> ad{132, 120, 122, 121, 118, 119, 140, 135, 134, 138, 137, 136};
  ad.emplace(12, 999, 133);
  bool find = ad.contains(12);
  EXPECT_TRUE(find);
  find = ad.contains(999);
  EXPECT_TRUE(find);
  find = ad.contains(133);
  EXPECT_TRUE(find);
}
