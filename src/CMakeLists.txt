cmake_minimum_required(VERSION 3.14)
project(my_project)
include (CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -pedantic -g")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  hello_test
  s21_containers.h

  #tests/test_another_vector.cc
   tests/test_avl_tree.cc
   #tests/test_lists.cc
   tests/test_map.cc
   tests/test_multiset.cc
   ##tests/test_queue.cc
   tests/test_set.cc
   #tests/test_stack.cc
   #tests/test_vector.cc
   #tests/test_array.cc
)


target_link_libraries(
  hello_test
  GTest::gtest_main
  )


include(GoogleTest)
gtest_discover_tests(hello_test)
