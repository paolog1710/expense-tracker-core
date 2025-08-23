cmake_minimum_required(VERSION 3.21)
project(et VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

add_library(et_core INTERFACE)
target_include_directories(et_core INTERFACE include)

# Dummy test target (to make CI pass from day 1)
add_executable(dummy_test tests/dummy_test.cpp)
target_link_libraries(dummy_test PRIVATE et_core)
add_test(NAME dummy_runs COMMAND dummy_test)
