cmake_minimum_required(VERSION 3.21)
project(et VERSION 0.0.0 LANGUAGES CXX)

# --- C++ standard & compile database
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Make our cmake/ directory discoverable for modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(EtWarnings)

# --- Public headers (placeholder include/ tree)
add_library(et_core INTERFACE)
target_include_directories(et_core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# --- Dependencies
# None currently required; add find_package calls here as libraries are added

# --- Dummy test just to prove wiring builds & runs
enable_testing()
add_executable(dummy_test tests/dummy_test.cpp)
target_link_libraries(dummy_test PRIVATE ${ET_WARNINGS_TARGET} et_core)
add_test(NAME dummy_runs COMMAND $<TARGET_FILE:dummy_test>)
