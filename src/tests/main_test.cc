#include <gtest/gtest.h>

#include "test_lists.cc"
#include "test_map.cc"
#include "test_set.cc"
#include "test_stack.cc"
#include "test_queue.cc"
#include "test_vector.cc"
#include "test_multiset.cc"
#include "test_array.cc"
#include "test_another_vector.cc"


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
