#include <gtest/gtest.h>
#include <map>
#include "../s21_tree.h"
#include <stdexcept>
#include <vector>

class AvlTreeTest: public ::testing::Test {
  protected:
    s21::BinaryTree<int, std::less<int>>* my_container;

    void SetUp() override {
      my_container = new s21::BinaryTree<int, std::less<int>>(5);
      std::vector<int> val = std::vector<int>{2, 1};
      for (int value: val) {
        my_container->insert(value);
      }
    }

    void TearDown() override {
      delete my_container;
    }
};


TEST_F(AvlTreeTest, SingleInsertValueTree) {
  my_container->insert(8);
  auto it = my_container->find(8);
  EXPECT_EQ((*it), 8);
  EXPECT_TRUE(my_container->find(1).value());
  EXPECT_TRUE(my_container->find(9).is_null());
}

TEST_F(AvlTreeTest, RightRotate) {
  bool endl = false;
  std::string expected = "1:0,2:1,5:0,";
  std::string my_data = my_container->inorder_traversal(endl);
  EXPECT_EQ(expected, my_data);
}

TEST_F(AvlTreeTest, LeftRotate) {
  my_container->insert(7);
  my_container->insert(9);
  bool endl = false;
  std::string expected = "1:0,2:2,5:0,7:1,9:0,";
  std::string my_data = my_container->inorder_traversal(endl);
  EXPECT_EQ(expected, my_data);
}
 
 
TEST(AvlTreeSuite, LeftRightRotate) {
  s21::BinaryTree my_container = s21::BinaryTree<int, std::less<int>>(5);
  my_container.insert(1);
  my_container.insert(2);
  bool endl = false;
  std::string expected = "1:0,2:1,5:0,";
  std::string my_data = my_container.inorder_traversal(endl);
  EXPECT_EQ(expected, my_data);
  EXPECT_EQ(my_container.find(5).value(), 5);
  EXPECT_EQ(my_container.find(2).value(), 2);
  EXPECT_EQ(my_container.find(1).value(), 1);
}
 
TEST_F(AvlTreeTest, SimpleDeleteTest) {
  my_container->del(1);
  EXPECT_TRUE(my_container->find(1).is_null());
}

TEST_F(AvlTreeTest, DeleteNodeWithChildTest) {
  my_container->insert(3);
  my_container->insert(8);
  my_container->del(5);
  EXPECT_TRUE(my_container->find(5).is_null());
  EXPECT_EQ(my_container->find(3).value(), 3);
  EXPECT_EQ(my_container->find(8).value(), 8);
  EXPECT_EQ(my_container->find(2).value(), 2);
  EXPECT_EQ(my_container->find(1).value(), 1);
} 

TEST_F(AvlTreeTest, DeleteRootNode) {
  my_container->del(5);
  my_container->del(2);
  my_container->del(1);
  EXPECT_TRUE(my_container->find(5).is_null());
  EXPECT_TRUE(my_container->find(2).is_null());
  EXPECT_TRUE(my_container->find(1).is_null());
  my_container->insert(3);
  my_container->insert(8);
  my_container->insert(10);
  my_container->insert(12);
  EXPECT_EQ(my_container->find(3).value(), 3);
  EXPECT_EQ(my_container->find(8).value(), 8);
  EXPECT_EQ(my_container->find(12).value(), 12);
  EXPECT_EQ(my_container->find(10).value(), 10);
  my_container->del(10);
  EXPECT_TRUE(my_container->find(10).is_null());
  EXPECT_EQ(my_container->find(3).value(), 3);
  EXPECT_EQ(my_container->find(8).value(), 8);
  EXPECT_EQ(my_container->find(12).value(), 12);
}
 
TEST_F(AvlTreeTest, SingleIteratorTest) {
  auto it = my_container->begin();
  ASSERT_FALSE(it.is_null());
  EXPECT_EQ((*it), 1);
  it++;
  EXPECT_EQ((*it), 2);
}

TEST_F(AvlTreeTest, IterateMapCompare) {
 std::map<int, int> original_container;
 original_container[5] = 5;
 original_container[2] = 2;
 original_container[1] = 1;
 original_container[10] = 10;
 original_container[15] = 15;
 original_container[20] = 20;
 original_container[30] = 30;
 original_container[40] = 40;
 original_container[3] = 3;
 original_container[4] = 4;
 my_container->insert(10);
 my_container->insert(15);
 my_container->insert(20);
 my_container->insert(30);
 my_container->insert(40);
 my_container->insert(3);
 my_container->insert(4);
 auto it = my_container->begin();
 ASSERT_FALSE(it.is_null());
 for (auto &value: original_container) {
   EXPECT_EQ((*it), value.first);
   it++;
 }
}
 
 
TEST_F(AvlTreeTest, DecrementIteratorCompare) {
  my_container->insert(10);
  my_container->insert(15);
  my_container->insert(20);
  auto it = my_container->end();
  --it;
  EXPECT_EQ((*it), 20);
  --it;
  EXPECT_EQ((*it), 15);
  --it;
  EXPECT_EQ((*it), 10);
  --it;
  EXPECT_EQ((*it), 5);
  --it;
  EXPECT_EQ((*it), 2);
  it--;
  EXPECT_EQ((*it), 1);
}

TEST_F(AvlTreeTest, IteratorBeginEnd) {
  EXPECT_NO_THROW(
      auto it = my_container->begin();
      while (it != my_container->end()) {
        it++;
      }
      );
}

TEST(AvlIterate, IteratorBeginEnd) {

  s21::BinaryTree<int> mc;
  mc.insert(1);
  mc.insert(2);
  mc.insert(3);
  mc.insert(4);
  EXPECT_NO_THROW(
      auto it = mc.cbegin();
      while (it != mc.cend()) {
        it++;
      }
      );

}
