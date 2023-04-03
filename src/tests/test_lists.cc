#include <gtest/gtest.h>

#include <iostream>
#include <list>

#include "../s21_list.h"

using namespace s21;

TEST(insert_test_0, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  std::list<int>::iterator it = tmp.begin();
  list<int>::iterator s21_it = s21_tmp.begin();

  for (int i = 0; i < 5; i++) {
    list<int>::iterator s21_ref = s21_tmp.insert(s21_it, i);
    std::list<int>::iterator ref = tmp.insert(it, i);

    EXPECT_EQ(*ref, *s21_ref);
  }

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(push_test_0, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  for (int i = 0; i < 5; i++) {
    s21_tmp.push_front(i);
    tmp.push_front(i);
  }

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(push_test_1, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  for (int i = 2; i < 7; i++) {
    tmp.push_back(i);
    s21_tmp.push_back(i);
  }

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(push_test_2, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  for (int i = 2; i < 7; i++) {
    tmp.push_back(i);
    s21_tmp.push_back(i);
  }

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(constructor_test_0, list) {
  list<int> tmp;

  for (int i = 1; i < 5; i++) {
    tmp.push_back(i);
  }

  list<int> tmp_copy(tmp);

  list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = tmp_copy.begin(); i != tmp_copy.end();
       i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(constructor_test_1, list) {
  list<int> s21_tmp({1, 2, 3, 4});
  std::list<int> tmp({1, 2, 3, 4});

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(constructor_test_2, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  for (int i = 1; i < 5; i++) {
    tmp.push_back(i);
    s21_tmp.push_back(i);
  }

  std::list<int> curr(std::move(tmp));
  list<int> s21_curr(std::move(s21_tmp));

  std::list<int>::iterator j = curr.begin();
  for (list<int>::iterator i = s21_curr.begin(); i != s21_curr.end();
       i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(pop_test_0, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  for (int i = 0; i < 4; i++) {
    tmp.push_back(i);
    s21_tmp.push_back(i);
  }
  tmp.pop_back();
  s21_tmp.pop_back();

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(pop_test_1, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  for (int i = 0; i < 4; i++) {
    tmp.push_back(i);
    s21_tmp.push_back(i);
  }

  tmp.pop_back();
  s21_tmp.pop_back();

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(pop_test_2, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  for (int i = 3; i < 4; i++) {
    tmp.push_front(i);
    s21_tmp.push_front(i);
  }

  tmp.pop_back();
  s21_tmp.pop_back();

  std::list<int>::iterator j = tmp.begin();
  list<int>::iterator i = s21_tmp.begin();

  EXPECT_EQ(*i, *j);
}

TEST(pop_test_3, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  for (int i = 3; i < 4; i++) {
    tmp.push_front(i);
    s21_tmp.push_front(i);
  }

  tmp.pop_front();
  s21_tmp.pop_front();

  std::list<int>::iterator j = tmp.begin();
  list<int>::iterator i = s21_tmp.begin();

  EXPECT_EQ(*i, *j);
}

TEST(erase_test_0, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  for (int i = 1; i < 3; i++) {
    tmp.push_front(i);
    s21_tmp.push_front(i);
  }

  list<int>::iterator s21_it = s21_tmp.begin();
  std::list<int>::iterator it = tmp.begin();

  tmp.erase(it);
  s21_tmp.erase(s21_it);

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(erase_test_1, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  for (int i = 3; i < 4; i++) {
    tmp.push_front(i);
    s21_tmp.push_front(i);
  }

  list<int>::iterator s21_it = s21_tmp.begin();
  std::list<int>::iterator it = tmp.begin();

  tmp.erase(it);
  s21_tmp.erase(s21_it);

  std::list<int>::iterator j = tmp.begin();
  list<int>::iterator i = s21_tmp.begin();

  EXPECT_EQ(*i, *j);
}

TEST(erase_test_2, list) {
  list<int> s21_tmp;

  for (int i = 3; i < 4; i++) {
    s21_tmp.push_front(i);
  }

  list<int>::iterator s21_it = s21_tmp.end();

  try {
    s21_tmp.erase(s21_it);
  } catch (const std::out_of_range &err) {
    EXPECT_EQ(err.what(), std::string("Double free"));
  }
}

TEST(sort_test_0, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  tmp.push_front(-1);
  tmp.push_front(-500);
  tmp.push_front(0);
  tmp.push_front(-4);
  tmp.push_front(1);
  tmp.push_front(55);
  tmp.push_front(20);
  tmp.push_front(-40000);

  s21_tmp.push_front(-1);
  s21_tmp.push_front(-500);
  s21_tmp.push_front(0);
  s21_tmp.push_front(-4);
  s21_tmp.push_front(1);
  s21_tmp.push_front(55);
  s21_tmp.push_front(20);
  s21_tmp.push_front(-40000);

  tmp.sort();
  s21_tmp.sort();

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(unique_test_0, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  tmp.push_front(-1);
  tmp.push_front(500);
  tmp.push_front(500);
  tmp.push_front(-4);
  tmp.push_front(1);
  tmp.push_front(4);
  tmp.push_front(4);
  tmp.push_front(4);

  s21_tmp.push_front(-1);
  s21_tmp.push_front(500);
  s21_tmp.push_front(500);
  s21_tmp.push_front(-4);
  s21_tmp.push_front(1);
  s21_tmp.push_front(4);
  s21_tmp.push_front(4);
  s21_tmp.push_front(4);

  tmp.unique();
  s21_tmp.unique();

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(reverse_test_0, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  tmp.push_front(-1);
  tmp.push_front(500);
  tmp.push_front(500);
  tmp.push_front(-4);
  tmp.push_front(1);
  tmp.push_front(4);
  tmp.push_front(4);
  tmp.push_front(4);

  s21_tmp.push_front(-1);
  s21_tmp.push_front(500);
  s21_tmp.push_front(500);
  s21_tmp.push_front(-4);
  s21_tmp.push_front(1);
  s21_tmp.push_front(4);
  s21_tmp.push_front(4);
  s21_tmp.push_front(4);

  tmp.reverse();
  s21_tmp.reverse();

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(merge_test_0, list) {
  std::list<int> tmp = {1, 2, 3}, other = {4, 5, 6};
  list<int> s21_tmp = {1, 2, 3}, s21_other = {4, 5, 6};

  s21_tmp.merge(s21_other);
  tmp.merge(other);

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(swap_test_0, list) {
  list<int> s21_list_1 = {5, 6, 3};
  list<int> s21_list_2 = {1, 2, 3, 4, 5, 6};
  s21_list_1.swap(s21_list_2);

  std::list<int> list_1 = {5, 6, 3};
  std::list<int> list_2 = {1, 2, 3, 4, 5, 6};
  list_1.swap(list_2);

  std::list<int>::iterator j = list_1.begin();
  for (list<int>::iterator i = s21_list_1.begin(); i != s21_list_1.end();
       i++, j++) {
    EXPECT_EQ(*i, *j);
  }

  j = list_2.begin();
  for (list<int>::iterator i = s21_list_2.begin(); i != s21_list_2.end();
       i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(erase_test_3, list) {
  list<int> s21_tmp = {1, 2, 3, 4, 5, 6};
  std::list<int> tmp = {1, 2, 3, 4, 5, 6};

  list<int>::iterator s21_it = s21_tmp.begin();
  std::list<int>::iterator it = tmp.begin();

  it++;
  s21_it++;

  tmp.erase(it);
  s21_tmp.erase(s21_it);

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(splice_test_0, list) {
  std::list<int> tmp = {1, 2, 3}, other = {4, 5, 6};
  list<int> s21_tmp = {1, 2, 3}, s21_other = {4, 5, 6};

  list<int>::iterator s21_it = s21_tmp.begin();
  std::list<int>::iterator it = tmp.begin();

  s21_it++;
  it++;

  s21_tmp.splice(s21_it, s21_other);
  tmp.splice(it, other);

  std::list<int>::iterator j = tmp.begin();
  for (list<int>::iterator i = s21_tmp.begin(); i != s21_tmp.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(capacity_test_0, list) {
  std::list<int> tmp = {1, 2, 3};
  list<int> s21_tmp = {1, 2, 3};

  EXPECT_EQ(s21_tmp.empty(), tmp.empty());
  EXPECT_EQ(s21_tmp.size(), tmp.size());
  EXPECT_EQ(s21_tmp.max_size(), tmp.max_size());
}

TEST(list_access_test_0, list) {
  std::list<int> tmp = {1, 2, 3};
  list<int> s21_tmp = {1, 2, 3};

  EXPECT_EQ(s21_tmp.front(), tmp.front());
  EXPECT_EQ(s21_tmp.back(), tmp.back());
}

TEST(list_access_test_1, list) {
  std::list<int> tmp;
  list<int> s21_tmp;

  EXPECT_EQ(s21_tmp.front(), tmp.front());
  EXPECT_EQ(s21_tmp.back(), tmp.back());
}
