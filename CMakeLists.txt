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

# --- Conan-provided dependencies (via CMakeDeps + toolchain)
# Run `conan install` first so these packages are discoverable.
find_package(spdlog CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(SQLite3 REQUIRED)              # from sqlite3 package
find_package(tl-expected CONFIG REQUIRED)
# (We will use Catch2 once we add real unit tests)
# find_package(Catch2 CONFIG REQUIRED)

# --- Dummy test just to prove wiring builds & runs
enable_testing()
add_executable(dummy_test tests/dummy_test.cpp)
target_link_libraries(dummy_test PRIVATE ${ET_WARNINGS_TARGET} et_core spdlog::spdlog)
add_test(NAME dummy_runs COMMAND $<TARGET_FILE:dummy_test>)
