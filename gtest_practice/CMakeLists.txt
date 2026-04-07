# CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(GTestTutorial)

# 要求 C++14 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 自动下载和配置 Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# 创建测试可执行文件
add_executable(run_tests test_calculator.cpp)

# 链接 gtest_main 和你的其他相关库
target_link_libraries(run_tests gtest gtest_main pthread)