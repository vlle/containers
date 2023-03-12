//#include <gtest/gtest.h>
//
//#include <iostream>
//#include <map>
//
//#include "../s21_map.h"
//
//TEST(MapConstructor, InitializerListConstructor) {
//  s21::map<int, int> map{{15, 1500}, {12, 4823}, {22, 232}, {1, 43}, {4, 54}};
//  std::map<int, int> std_map{
//      {15, 1500}, {12, 4823}, {22, 232}, {1, 43}, {4, 54}};
//  EXPECT_EQ(map.size(), std_map.size());
//  EXPECT_EQ(map.empty(), std_map.empty());
//  EXPECT_EQ(map.at(15), std_map.at(15));
//  EXPECT_EQ(map.at(1), std_map.at(1));
//  EXPECT_EQ(map[12], std_map[12]);
//  EXPECT_EQ(map[4], std_map[4]);
//  EXPECT_EQ(map[100], std_map[100]);
//
//  auto map_p = map.begin();
//  auto std_map_p = std_map.begin();
//  for (; map_p != map.end() && std_map_p != std_map.end(); ++map_p, ++std_map_p)
//    EXPECT_TRUE((*map_p).second == (*std_map_p).second);
//}
//
//TEST(MapConstructor, EmptyConstructor) {
//  s21::map<int, int> map{};
//  std::map<int, int> std_map{};
//  EXPECT_EQ(map.size(), std_map.size());
//  EXPECT_EQ(map.empty(), std_map.empty());
//  ASSERT_FLOAT_EQ(map.max_size(), std_map.max_size());
//}
//
//TEST(MapConstructor, CopyConstructor) {
//  s21::map<int, int> map{{15, 1500}, {12, 4823}, {22, 232}, {1, 43}, {4, 54}};
//  s21::map<int, int> map_copy{{1, 2}, {3, 4}};
//  map_copy = map;
//  std::map<int, int> std_map{
//      {15, 1500}, {12, 4823}, {22, 232}, {1, 43}, {4, 54}};
//  std::map<int, int> std_map_copy{{1, 2}, {3, 4}};
//  std_map_copy = std_map;
//  EXPECT_EQ(map_copy.size(), std_map_copy.size());
//  EXPECT_EQ(map_copy.empty(), std_map_copy.empty());
//
//  auto map_p = map_copy.begin();
//  auto std_map_p = std_map_copy.begin();
//  for (; map_p != map_copy.end() && std_map_p != std_map_copy.end();
//       ++map_p, ++std_map_p)
//    EXPECT_TRUE((*map_p).second == (*std_map_p).second);
//}
//
//TEST(MapConstructor, MoveConstructor) {
//  s21::map<int, int> map{{15, 1500}, {12, 4823}, {22, 232}, {1, 43}, {4, 54}};
//  s21::map<int, int> map_move{{1, 2}, {3, 4}};
//  map_move = std::move(map);
//  std::map<int, int> std_map{
//      {15, 1500}, {12, 4823}, {22, 232}, {1, 43}, {4, 54}};
//  std::map<int, int> std_map_move{{1, 2}, {3, 4}};
//  std_map_move = std::move(std_map);
//  EXPECT_EQ(map_move.size(), std_map_move.size());
//  EXPECT_EQ(map_move.empty(), std_map_move.empty());
//
//  auto map_p = map_move.begin();
//  auto std_map_p = std_map_move.begin();
//  for (; map_p != map_move.end() && std_map_p != std_map_move.end();
//       ++map_p, ++std_map_p)
//    EXPECT_TRUE((*map_p).second == (*std_map_p).second);
//}
//
//TEST(MapElementAccess, at_throw) {
//  s21::map<int, int> map{{1, 1500}};
//  EXPECT_ANY_THROW(map.at(2));
//}
//
//TEST(MapElementAccess, braces_throw) {
//  s21::map<int, int> map{{1, 1500}};
//  map[2];
//  EXPECT_EQ(map.at(2), 0);
//}
//
//TEST(MapConstructor, OperatorEqual) {
//  s21::map<int, int> s21_m{{15, 1500}, {12, 4823}, {22, 232}, {1, 43}, {4, 54}};
//  s21::map<int, int> s21_se = s21_m;
//
//  auto s21_pe = --s21_m.end();
//  auto s21_pb = s21_m.begin();
//  do {
//    ++s21_pb;
//    EXPECT_EQ((*s21_pe).second, (*s21_pe).second);
//  } while ((*s21_pe).second != (*s21_pb).second);
//
//  EXPECT_EQ(s21_m.size(), s21_se.size());
//  EXPECT_EQ(s21_m.empty(), s21_se.empty());
//}
//
//TEST(MapModifiers, Erase) {
//  s21::map<std::string, int> s21_m{
//      {"Ivan", 20}, {"Alex", 28}, {"Nikolay", 65}, {"Elena", 43}};
//  std::map<std::string, int> std_m{
//      {"Ivan", 20}, {"Alex", 28}, {"Nikolay", 65}, {"Elena", 43}};
//
//  s21_m.erase(++s21_m.begin());
//  std_m.erase(++std_m.begin());
//  EXPECT_EQ(s21_m.size(), std_m.size());
//  EXPECT_EQ(s21_m.empty(), std_m.empty());
//
//  auto map_p = s21_m.begin();
//  auto std_map_p = std_m.begin();
//  for (; map_p != s21_m.end() && std_map_p != std_m.end(); ++map_p, ++std_map_p)
//    EXPECT_TRUE((*map_p).second == (*std_map_p).second);
//}
//
//TEST(MapLookup, Contains) {
//  s21::map<std::string, int> s21_m{{"One", 1},  {"Two", 2},  {"Three", 3},
//                                   {"Four", 4}, {"Five", 5}, {"Six", 6}};
//
//  EXPECT_EQ(s21_m.contains("One"), true);
//  EXPECT_EQ(s21_m.contains("Hello, world!"), false);
//}
//
//TEST(MapModifiers, Insert) {
//  s21::map<std::string, int> s21_m{{"One", 1},  {"Two", 2},  {"Three", 3},
//                                   {"Four", 4}, {"Five", 5}, {"Six", 6}};
//  s21_m.insert({"Seven", 7});
//  EXPECT_EQ(s21_m.at("Seven"), 7);
//  s21_m.insert("FiveFourFour", 544);
//  EXPECT_EQ(s21_m.at("FiveFourFour"), 544);
//}
//
//TEST(MapModifiers, InsertOrAssign) {
//  s21::map<std::string, int> s21_m{{"One", 1},  {"Two", 2},  {"Three", 3},
//                                   {"Four", 4}, {"Five", 5}, {"Six", 6}};
//  s21_m.insert_or_assign("Seven", 7);
//  EXPECT_EQ(s21_m.at("Seven"), 7);
//  s21_m.insert_or_assign("Seven", 544);
//  EXPECT_EQ(s21_m.at("Seven"), 544);
//}
//
//TEST(MapModifiers, Swap) {
//  s21::map<std::string, int> s21_first{{"One", 1},   {"Two", 2},   {"Three", 3},
//                                       {"Four", 4},  {"Five", 5},  {"Six", 6},
//                                       {"Seven", 7}, {"Eight", 8}, {"Nine", 9}};
//  s21::map<std::string, int> s21_second{
//      {"Ivan", 20}, {"Alex", 28}, {"Nikolay", 65}, {"Elena", 43}};
//  std::map<std::string, int> std_first{{"One", 1},   {"Two", 2},   {"Three", 3},
//                                       {"Four", 4},  {"Five", 5},  {"Six", 6},
//                                       {"Seven", 7}, {"Eight", 8}, {"Nine", 9}};
//  std::map<std::string, int> std_second{
//      {"Ivan", 20}, {"Alex", 28}, {"Nikolay", 65}, {"Elena", 43}};
//
//  EXPECT_EQ(s21_first.size(), std_first.size());
//  EXPECT_EQ(s21_first.empty(), std_first.empty());
//  EXPECT_EQ(s21_second.size(), std_second.size());
//  EXPECT_EQ(s21_second.empty(), std_second.empty());
//
//  auto s21_p = s21_first.begin();
//  auto std_p = std_first.begin();
//  for (; s21_p != s21_first.end() && std_p != std_first.end(); ++s21_p, ++std_p)
//    EXPECT_TRUE((*s21_p).second == (*std_p).second);
//  s21_p = s21_second.begin();
//  std_p = std_second.begin();
//  for (; s21_p != s21_second.end() && std_p != std_second.end();
//       ++s21_p, ++std_p)
//    EXPECT_TRUE((*s21_p).second == (*std_p).second);
//
//  s21_first.swap(s21_second);
//  std_first.swap(std_second);
//
//  EXPECT_EQ(s21_first.size(), std_first.size());
//  EXPECT_EQ(s21_first.empty(), std_first.empty());
//  EXPECT_EQ(s21_second.size(), std_second.size());
//  EXPECT_EQ(s21_second.empty(), std_second.empty());
//
//  s21_p = s21_first.begin();
//  std_p = std_first.begin();
//  for (; s21_p != s21_first.end() && std_p != std_first.end(); ++s21_p, ++std_p)
//    EXPECT_TRUE((*s21_p).second == (*std_p).second);
//  s21_p = s21_second.begin();
//  std_p = std_second.begin();
//  for (; s21_p != s21_second.end() && std_p != std_second.end();
//       ++s21_p, ++std_p)
//    EXPECT_TRUE((*s21_p).second == (*std_p).second);
//}
//
//TEST(MapModifiers, Merge) {
//  s21::map<int, std::string> s21_m1{
//      {1, "phone"}, {2, "TV"}, {3, "computer"}, {4, "microwave"}};
//  s21::map<int, std::string> s21_m2{
//      {6, "Banana"}, {8, "Apple"}, {3, "Pear"}, {1, "Pineapple"}};
//
//  std::map<int, std::string> std_m1{
//      {1, "phone"}, {2, "TV"}, {3, "computer"}, {4, "microwave"}};
//  std::map<int, std::string> std_m2{
//      {6, "Banana"}, {8, "Apple"}, {3, "Pear"}, {1, "Pineapple"}};
//
//  s21_m1.merge(s21_m2);
//  std_m1.merge(std_m2);
//
//  EXPECT_EQ(s21_m1.size(), std_m1.size());
//  EXPECT_EQ(s21_m1.empty(), std_m1.empty());
//
//  auto s21_p = s21_m1.begin();
//  auto std_p = std_m1.begin();
//  for (; s21_p != s21_m1.end() && std_p != std_m1.end(); ++s21_p, ++std_p)
//    EXPECT_TRUE((*s21_p).second == (*std_p).second);
//}
//
//TEST(MapExtraTests, test1) {
//  const s21::map<int, int> s21_m{{5, 100},  {5, 101},  {14, 102}, {6, 103},
//                                 {78, 104}, {23, 105}, {65, 106}};
//  auto s21_p = s21_m.end();
//  EXPECT_TRUE((*(--s21_p)).first == 78);
//  EXPECT_TRUE((*(--s21_p)).first == 65);
//  EXPECT_TRUE((*(--s21_p)).first == 23);
//  EXPECT_TRUE((*(--s21_p)).first == 14);
//  EXPECT_TRUE((*(--s21_p)).first == 6);
//  EXPECT_TRUE((*(--s21_p)).first == 5);
//  EXPECT_TRUE(s21_p == s21_m.begin());
//}
