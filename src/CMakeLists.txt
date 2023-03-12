cmake_minimum_required(VERSION 3.14)
project(my_project)
include (CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -pedantic -g")
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

# find_program( MEMORYCHECK_COMMAND leaks )
# set( MEMORYCHECK_COMMAND_OPTIONS "-atExit -- " )

# add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer -fno-common -O1)
# link_libraries(-fsanitize=address,undefined)

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
  #s21_containers.h
  s21_vector.h
  #tests/test_vector.cc
  #tests/test_avl_tree.cc
  #tests/test_map.cc
  # tests/test_multiset.cc
  #tests/test_set.cc
  tests/test_avl_tree.cc
  tests/test_another_vector.cc
  tests/test_vector.cc
)

# ADD_LIBRARY(LibMat
#   s21_matrix_oop.h
#   S21Matrix.cc
#   )
# 
# find_library (MATRIX 
#   NAMES s21_matrix_oop.a
#   HINTS "${CMAKE_PREFIX_PATH}"
#   )
# LibMat

target_link_libraries(
  hello_test
  GTest::gtest_main
  )


include(GoogleTest)
gtest_discover_tests(hello_test)


