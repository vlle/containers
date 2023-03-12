#include <gtest/gtest.h>
#include "../s21_vector.h"
#include <stdexcept>
#include <vector>

class VectorTest : public ::testing::Test {
 protected:
  s21::vector<int>* my_container_;
  std::vector<int>* original_container_;

  void SetUp() override {
     // q0_ remains empty
     my_container_ = new s21::vector<int>{1,2,4};
     original_container_ = new std::vector<int>{1,3, 5};
  }

  void TearDown() override {
    delete my_container_;
    delete original_container_;
  }
};


TEST(VectorSuite, DefaultConstructorVector) {
  auto my_vector = s21::vector<int>();
  auto expected_vector = std::vector<int>();
  EXPECT_TRUE(my_vector.empty() == expected_vector.empty());
}

TEST(VectorSuite, ZeroSizeConstructorVector) {
  auto my_vector = s21::vector<int>();
  auto expected_vector = std::vector<int>();
  EXPECT_EQ(my_vector.size(), expected_vector.size());
}

TEST(VectorSuite, NonZeroSizeConstructorVector) {
  auto my_vector = s21::vector<int>(4);
  auto expected_vector = std::vector<int>(4);
  EXPECT_EQ(my_vector.size(), expected_vector.size());
}

TEST(VectorSuite, ListConstructorVector) {
  auto my_vector = s21::vector<int>({4, 5, 6, 7});
  auto expected_vector = std::vector<int>({4, 5, 6, 7});
  EXPECT_EQ(my_vector.size(), expected_vector.size());
  for (size_t i = 0; i != expected_vector.size(); ++i) {
    EXPECT_EQ(expected_vector[i], my_vector[i]);
  }
}

TEST(VectorSuite, CopyConstructorVector) {
  auto expected_vector = s21::vector<int>({4, 5, 6, 7});
  auto my_vector = s21::vector<int>(expected_vector);
  EXPECT_EQ(my_vector.size(), expected_vector.size());
  for (size_t i = 0; i != expected_vector.size(); ++i) {
    EXPECT_EQ(expected_vector[i], my_vector[i]);
  }
}

TEST_F(VectorTest, OperatorEq) {
  auto original_vector = s21::vector<int>({4,5,1});
  *my_container_ = original_vector;
  EXPECT_EQ((*my_container_).size(), original_vector.size());
  for (size_t i = 0; i != original_vector.size(); ++i) {
    EXPECT_EQ(original_vector[i], (*my_container_)[i]);
  }
}

TEST_F(VectorTest, ThrowAtOutOfRange) {
  EXPECT_THROW((*original_container_).at(4), std::out_of_range);
}

TEST_F(VectorTest, GetAtValue) {
  EXPECT_EQ((*original_container_).at(2), 5);
}

TEST_F(VectorTest, SetAtValue) {
  (*my_container_).at(2) = 4;
  EXPECT_EQ((*my_container_).at(2), 4);
}

TEST_F(VectorTest, SetBracketsValue) {
  (*my_container_)[2] = 4;
  EXPECT_EQ((*my_container_).at(2), 4);
}

TEST_F(VectorTest, GetData) {
  ASSERT_TRUE((*my_container_).data() != nullptr);
}

TEST_F(VectorTest, GetFront) {
  (*my_container_)[0] = 10;
  (*original_container_)[0] = 10;
  EXPECT_EQ((*original_container_).front(), (*my_container_).front());
}

TEST_F(VectorTest, GetBack) {
  (*my_container_)[2] = 20;
  EXPECT_EQ((*my_container_).back(), 20);
}

TEST_F(VectorTest, GetMaxSize) {
  EXPECT_EQ((*my_container_).max_size(), (*original_container_).max_size());
}

TEST_F(VectorTest, GetBaseBeginIterator) {
  (*my_container_)[0] = 30;
  (*original_container_)[0] = 30;
  EXPECT_EQ(*((*my_container_).begin()), *((*original_container_).begin()));
}

TEST_F(VectorTest, GetBaseEndIterator) {
  EXPECT_NE(*((*my_container_).end()-1), *((*original_container_).end()-1));
}

TEST_F(VectorTest, GetCapacity) {
  EXPECT_EQ((*my_container_).capacity(), (*my_container_).size() * 2);
}

TEST_F(VectorTest, ReserveTest) {
  (*my_container_)[1] = 1;
  (*original_container_)[1] = 1;
  (*my_container_).reserve(16);
  (*original_container_).reserve(16);
  EXPECT_EQ((*original_container_).size(), (*my_container_).size());
  EXPECT_EQ((*original_container_).at(1), (*my_container_).at(1));
}

TEST_F(VectorTest, BaseShrinkTest) {
  (*my_container_).shrink_to_fit();
  EXPECT_EQ((*my_container_).size(), (*my_container_).capacity());
}

TEST_F(VectorTest, PushBackIntTest) {
  int value_to_push = 5;
  (*my_container_).push_back(value_to_push);
  (*original_container_).push_back(value_to_push);
  EXPECT_EQ((*original_container_).back(), (*my_container_).back());
}

TEST_F(VectorTest, PopBackTest) {
  auto my_vector = s21::vector<int>({1, 2, 3});
  auto expected_vector = s21::vector<int>({1, 2, 3});
  my_vector.pop_back();
  expected_vector.pop_back();
  EXPECT_EQ(expected_vector.back(), my_vector.back());
  EXPECT_EQ(expected_vector.size(), my_vector.size());
}

TEST_F(VectorTest, ClearTest) {
  (*my_container_).clear();
  (*original_container_).clear();
  EXPECT_EQ((*my_container_).size(), (*original_container_).size());
}

TEST_F(VectorTest, InsertTest) {
  *original_container_ = std::vector<int>({1,2,4});
  (*my_container_).insert((*my_container_).begin()+1, 5);
  (*original_container_).insert((*original_container_).begin()+1, 5);
  EXPECT_EQ((*my_container_).size(), (*original_container_).size());
  for (unsigned long i = 0; i != (*my_container_).size(); ++i) {
    EXPECT_EQ((*my_container_).at(i), (*original_container_).at(i));
  }
}

TEST_F(VectorTest, EraseTest) {
  *original_container_ = std::vector<int>({1,2,4});
  (*my_container_).erase((*my_container_).begin()+1);
  (*original_container_).erase((*original_container_).begin()+1);
  EXPECT_EQ((*my_container_).size(), (*original_container_).size());
  for (unsigned long i = 0; i != (*my_container_).size(); ++i) {
    EXPECT_EQ((*my_container_).at(i), (*original_container_).at(i));
  }
}

TEST(VectorSuite, SwapTest) {
  auto my_vector = s21::vector<int>({4, 5, 6, 7});
  auto expected_vector = s21::vector<int>({1, 2, 3, 4});
  auto my_vector2 = s21::vector<int>({4, 5, 6, 7});
  auto expected_vector2 = s21::vector<int>({1, 2, 3, 4});
  my_vector.swap(expected_vector);
  EXPECT_EQ(my_vector.size(), expected_vector2.size());
  for (size_t i = 0; i != expected_vector.size(); ++i) {
    EXPECT_EQ(expected_vector2[i], my_vector[i]);
  }
  EXPECT_EQ(my_vector2.size(), expected_vector.size());
  for (size_t i = 0; i != expected_vector.size(); ++i) {
    EXPECT_EQ(expected_vector[i], my_vector2[i]);
  }

}
