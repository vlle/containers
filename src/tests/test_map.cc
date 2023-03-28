#include <gtest/gtest.h>

#include <vector>
#include <iostream>
#include <map>

#include "../s21_map.h"

class MapTest: public::testing::Test {
  protected:
    s21::map<int, int> my_container;
    std::map<int, int> expected_container;

    void SetUp() override {
      std::vector<std::pair<int, int > > val = {{15, 1500}, {12, 4823}, {22, 232}, {1, 43}, {4, 54}};
      for (auto&v: val) {
        my_container.insert(v);
        expected_container.insert(v);
      }
    }
};


TEST_F(MapTest, Empty) {
  EXPECT_EQ(my_container.empty(), expected_container.empty());
}

TEST_F(MapTest, EndIterator) {
  EXPECT_EQ(my_container.end(), my_container.end());
}

TEST_F(MapTest, AtValue) {
  EXPECT_EQ(my_container.at(15), expected_container.at(15));
  EXPECT_EQ(my_container.at(1), expected_container.at(1));
}

TEST_F(MapTest, AtValueThrow) {
  EXPECT_ANY_THROW(my_container.at(18));
}

TEST_F(MapTest, HardBracketsCheck) {
  EXPECT_EQ(my_container[12] , expected_container[12]);
  EXPECT_EQ(my_container[4]  , expected_container[4]);
  EXPECT_EQ(my_container[100], expected_container[100]);
}

TEST_F(MapTest, EmptyConstructor) {
  EXPECT_EQ(my_container.size(), expected_container.size());
}

TEST_F(MapTest, Insert) {
  my_container[1] = 1;
  expected_container[1] = 1;
  EXPECT_EQ(my_container[1], expected_container[1]);
}

TEST_F(MapTest, InsertNE) {
  my_container[1] = 1;
  expected_container[1] = 2;
  EXPECT_NE(my_container[1], expected_container[1]);
}

TEST_F(MapTest, IteratorMap) {
  auto map_p = my_container.begin();
  ASSERT_EQ(my_container[4], expected_container[4]);
  for (auto std_map_p = expected_container.begin(); std_map_p != expected_container.end(); ++std_map_p) {
    ASSERT_NO_THROW(my_container.at(std_map_p->first));
  }
  for (auto std_map_p = expected_container.begin(); map_p != my_container.end() && std_map_p != expected_container.end(); ++map_p, ++std_map_p)
    EXPECT_EQ((*map_p).second, (std_map_p)->second);
}

TEST(MapSuite, IteratorCounter) {
  s21::map<int, int> my;
  std::map<int, int> expected;

  std::vector<std::pair<int, int > > val = {{15, 1500}, {12, 100}};
  for (auto&v: val) {
    my.insert(v);
    expected.insert(v);
  }
  ASSERT_EQ(my.size(), expected.size());
  size_t counter = 0;
  size_t original_counter = 0;
  for (auto c: my) {
    counter++;
    (void) c;
  }
  for (auto c: expected) {
    original_counter++;
    (void) c;
  }
  ASSERT_EQ(counter, original_counter);
}


TEST(MapSuite, IteratorCounterRight) {
  s21::map<int, int> my;
  std::map<int, int> expected;

  std::vector<std::pair<int, int > > val = {{15, 1500}, {16, 100}};
  for (auto&v: val) {
    my.insert(v);
    expected.insert(v);
  }
  ASSERT_EQ(my.size(), expected.size());

  size_t counter = 0;
  size_t original_counter = 0;
  for (auto c: my) {
    counter++;
    (void) c;
  }
  for (auto c: expected) {
    original_counter++;
    (void) c;
  }
  ASSERT_EQ(counter, original_counter);
}

TEST_F(MapTest, CopyConstructor) {
  s21::map<int, int> map_copy{{1, 2}, {3, 4}};
  std::map<int, int> std_map_copy{{1, 2}, {3, 4}};
  map_copy = my_container;
  std_map_copy = expected_container;
  EXPECT_EQ(map_copy.size(), std_map_copy.size());
  EXPECT_EQ(map_copy.empty(), std_map_copy.empty());

  auto map_p = map_copy.begin();
  auto std_map_p = std_map_copy.begin();
  for (; map_p != map_copy.end() && std_map_p != std_map_copy.end();
      ++map_p, ++std_map_p)
    EXPECT_EQ((*map_p).second , (std_map_p)->second);  
}
 
 TEST_F(MapTest, Size) {
   EXPECT_EQ(my_container.size(), expected_container.size());
 }
 
 TEST_F(MapTest, Count) {
   EXPECT_EQ(my_container.count(15), expected_container.count(15));
   EXPECT_NE(my_container.count(999), expected_container.count(15));
   EXPECT_EQ(my_container.count(18), expected_container.count(18));
 }
 
 TEST_F(MapTest, Erase) {
   ASSERT_EQ(my_container.size(), expected_container.size());
   EXPECT_NO_THROW(
       my_container.clear();
       expected_container.clear();
       );
   EXPECT_EQ(expected_container.size(), my_container.size());
   EXPECT_EQ(my_container.size(), 0);
   EXPECT_EQ(expected_container.size(), 0);
 }
 
 TEST(MapElementAccess, braces_throw) {
   s21::map<int, int> map{{1, 1500}};
   map[2];
   EXPECT_EQ(map.at(2), 0);
 }
 
 TEST(MapLookup, Contains) {
   s21::map<std::string, int> s21_m{{"One", 1},  {"Two", 2},  {"Three", 3},
                                    {"Four", 4}, {"Five", 5}, {"Six", 6}};
 
   EXPECT_EQ(s21_m.contains("One"), true);
   EXPECT_EQ(s21_m.contains("Hello, world!"), false);
 }
 
 TEST(MapModifiers, Insert) {
   s21::map<std::string, int> s21_m{{"One", 1},  {"Two", 2},  {"Three", 3},
                                    {"Four", 4}, {"Five", 5}, {"Six", 6}};
   s21_m.insert({"Seven", 7});
   EXPECT_EQ(s21_m.at("Seven"), 7);
   s21_m.insert("FiveFourFour", 544);
   EXPECT_EQ(s21_m.at("FiveFourFour"), 544);
 }
 
 TEST(MapModifiers, InsertOrAssign) {
   s21::map<std::string, int> s21_m{{"One", 1},  {"Two", 2},  {"Three", 3},
                                    {"Four", 4}, {"Five", 5}, {"Six", 6}};
   s21_m.insert_or_assign("Seven", 7);
   EXPECT_EQ(s21_m.at("Seven"), 7);
   s21_m.insert_or_assign("Seven", 544);
   EXPECT_EQ(s21_m.at("Seven"), 544);
 }
 
 TEST(MapConstructor, MoveConstructor) {
   s21::map<int, int> map{{15, 1500}, {12, 4823}, {22, 232}, {1, 43}, {4, 54}};
   s21::map<int, int> map_move{{1, 2}, {3, 4}};
   map_move = std::move(map);
   std::map<int, int> std_map{
       {15, 1500}, {12, 4823}, {22, 232}, {1, 43}, {4, 54}};
   std::map<int, int> std_map_move{{1, 2}, {3, 4}};
   std_map_move = std::move(std_map);
   EXPECT_EQ(map_move.size(), std_map_move.size());
   EXPECT_EQ(map_move.empty(), std_map_move.empty());
 
   auto map_p = map_move.begin();
   auto std_map_p = std_map_move.begin();
   for (; map_p != map_move.end() && std_map_p != std_map_move.end();
        ++map_p, ++std_map_p)
     EXPECT_EQ((*map_p).second, std_map_p->second);
 }

TEST(MapConstructor, OperatorEqual) {
  s21::map<int, int> s21_m{{15, 1500}, {12, 4823}, {22, 232}, {1, 43}, {4, 54}};
  s21::map<int, int> s21_se = s21_m;

  auto s21_pe = --s21_m.end();
  auto s21_pb = s21_m.begin();
  do {
    ++s21_pb;
    EXPECT_EQ((*s21_pe).second, (*s21_pe).second);
  } while ((*s21_pe).second != (*s21_pb).second);

  EXPECT_EQ(s21_m.size(), s21_se.size());
  EXPECT_EQ(s21_m.empty(), s21_se.empty());
}

TEST(MapModifiers, Erase) {
  s21::map<std::string, int> s21_m{
      {"Ivan", 20}, {"Alex", 28}, {"Nikolay", 65}, {"Elena", 43}};
  std::map<std::string, int> std_m{
      {"Ivan", 20}, {"Alex", 28}, {"Nikolay", 65}, {"Elena", 43}};

  s21_m.erase(++s21_m.begin());
  std_m.erase(++std_m.begin());
  EXPECT_EQ(s21_m.size(), std_m.size());
  EXPECT_EQ(s21_m.empty(), std_m.empty());

  auto map_p = s21_m.begin();
  auto std_map_p = std_m.begin();
  for (; map_p != s21_m.end() && std_map_p != std_m.end(); ++map_p, ++std_map_p)
    EXPECT_TRUE((*map_p).second == (*std_map_p).second);
}


TEST(MapModifiers, Merge) {
  s21::map<int, std::string> s21_m1{
      {1, "phone"}, {2, "TV"}, {3, "computer"}, {4, "microwave"}};
  s21::map<int, std::string> s21_m2{
      {6, "Banana"}, {8, "Apple"}, {3, "Pear"}, {1, "Pineapple"}};

  std::map<int, std::string> std_m1{
      {1, "phone"}, {2, "TV"}, {3, "computer"}, {4, "microwave"}};
  std::map<int, std::string> std_m2{
      {6, "Banana"}, {8, "Apple"}, {3, "Pear"}, {1, "Pineapple"}};
  auto s21_p = s21_m1.begin();
  auto std_p = std_m1.begin();

  for (; s21_p != s21_m1.end() && std_p != std_m1.end(); ++s21_p, ++std_p)
    EXPECT_EQ((*s21_p).first , (std_p)->first);

  s21_m1.merge(s21_m2);
  std_m1.merge(std_m2);
  s21_p = s21_m1.begin();
  std_p = std_m1.begin();

  EXPECT_EQ(s21_m1.size(), std_m1.size());
  EXPECT_EQ(s21_m1.empty(), std_m1.empty());
  EXPECT_EQ(s21_m2.size(),  std_m2.size());
  EXPECT_EQ(s21_m2.empty(), std_m2.empty());

  for (; s21_p != s21_m1.end() && std_p != std_m1.end(); ++s21_p, ++std_p)
    EXPECT_EQ((*s21_p).first , (std_p)->first);
}

