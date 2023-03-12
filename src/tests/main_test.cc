#include <gtest/gtest.h>

#include "test_map.cc"
#include "test_multiset.cc"
#include "test_set.cc"
#include "test_vector.cc"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
