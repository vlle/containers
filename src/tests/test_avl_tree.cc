#include <gtest/gtest.h>
#include "../s21_avltree.h"
#include <stdexcept>
#include <vector>

class AvlTreeTest: public ::testing::Test {
  protected:
    s21::avl_tree<int>* my_container;

    void SetUp() override {
      my_container = new s21::avl_tree<int>(5);
      std::vector<int> val = std::vector<int>{2, 1};
      for (int value: val) {
        my_container->insert(value);
      }
    }

    void TearDown() override {
      delete my_container;
    }
};


TEST_F(AvlTreeTest, DefaultConstructor) {
  EXPECT_NO_THROW(s21::avl_tree<int>());
}

TEST_F(AvlTreeTest, SizeConstructorTree) {
  EXPECT_NO_THROW(s21::avl_tree<int>(5));
}

TEST_F(AvlTreeTest, GetValueTree) {
  EXPECT_EQ(*(my_container->find(5)), 5);
}

TEST_F(AvlTreeTest, SingleInsertValueTree) {
  my_container->insert(8);
  EXPECT_EQ(*(my_container->find(8)), 8);
  EXPECT_TRUE(my_container->find(1));
  EXPECT_FALSE(my_container->find(9));
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
  s21::avl_tree my_container = s21::avl_tree<int>(5);
  my_container.insert(1);
  my_container.insert(2);
  bool endl = false;
  std::string expected = "1:0,2:1,5:0,";
  std::string my_data = my_container.inorder_traversal(endl);
  EXPECT_EQ(expected, my_data);
  EXPECT_EQ(*my_container.find(5), 5);
  EXPECT_EQ(*my_container.find(2), 2);
  EXPECT_EQ(*my_container.find(1), 1);
}

TEST_F(AvlTreeTest, SimpleDeleteTest) {
  my_container->del(1);
  EXPECT_FALSE(my_container->find(1));
}

TEST_F(AvlTreeTest, DeleteNodeWithChildTest) {
  my_container->insert(3);
  my_container->insert(8);
  my_container->del(5);
  EXPECT_FALSE(my_container->find(5));
  EXPECT_TRUE(my_container->find(3));
  EXPECT_TRUE(my_container->find(8));
  EXPECT_TRUE(my_container->find(2));
  EXPECT_TRUE(my_container->find(1));
} 

TEST_F(AvlTreeTest, DeleteRootNode) {
  my_container->del(5);
  my_container->del(2);
  my_container->del(1);
  EXPECT_FALSE(my_container->find(5));
  EXPECT_FALSE(my_container->find(2));
  EXPECT_FALSE(my_container->find(1));
  my_container->insert(3);
  my_container->insert(8);
  my_container->insert(10);
  my_container->insert(12);
  EXPECT_TRUE(my_container->find(3));
  EXPECT_TRUE(my_container->find(8));
  EXPECT_TRUE(my_container->find(12));
  EXPECT_TRUE(my_container->find(10));
  my_container->del(10);
  EXPECT_FALSE(my_container->find(10));
  EXPECT_TRUE(my_container->find(3));
  EXPECT_TRUE(my_container->find(8));
  EXPECT_TRUE(my_container->find(12));
}
 
