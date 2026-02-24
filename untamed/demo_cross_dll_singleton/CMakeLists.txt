cmake_minimum_required(VERSION 3.10)

project(cross_dll_singleton_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_BUILD_RPATH "$ORIGIN")

# -----------------------------
# Bad case: singleton in header
# -----------------------------
add_library(plugin_bad SHARED bad/plugin_bad.cpp)
target_include_directories(plugin_bad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/bad)

add_executable(app_bad bad/app_bad.cpp)
target_include_directories(app_bad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/bad)
target_link_libraries(app_bad PRIVATE plugin_bad)

# --------------------------------
# Good case: singleton owned by core
# --------------------------------
add_library(core_good SHARED good/core_good.cpp)
target_include_directories(core_good PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/good)

add_library(plugin_good SHARED good/plugin_good.cpp)
target_include_directories(plugin_good PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/good)
target_link_libraries(plugin_good PRIVATE core_good)

add_executable(app_good good/app_good.cpp)
target_include_directories(app_good PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/good)
target_link_libraries(app_good PRIVATE plugin_good core_good)
