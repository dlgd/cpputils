include_directories(${GTEST_INCLUDE_DIR})

add_executable (algorithm_test algorithm_test.cpp)
target_link_libraries (algorithm_test gtest_main)

add_test(algorithm algorithm_test)
