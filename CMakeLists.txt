cmake_minimum_required(VERSION 3.21)
project(expense_tracker VERSION 0.0.0 LANGUAGES CXX)

# --- C++ standard & compile database
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Make our cmake/ directory discoverable for modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(EtWarnings)

# --- Dependencies
find_package(CLI11 REQUIRED)
find_package(Boost REQUIRED)
find_package(Catch2 REQUIRED)

# --- Project Options
if(NOT DEFINED UI)
    message(FATAL_ERROR "UI variable must be set to 'cli', 'desktop', or 'both'")
endif()

# --- Core Components (Domain & Application layers)
add_subdirectory(expense-tracker/workflow-core)
add_subdirectory(expense-tracker/workflow-api)

# --- Infrastructure Components
add_subdirectory(expense-tracker/infrastructure-ports)
add_subdirectory(expense-tracker/infrastructure-adapters)

# --- UI Components
if(UI STREQUAL "cli" OR UI STREQUAL "both")
    add_subdirectory(expense-tracker/ui/cli)
    add_subdirectory(expense-tracker/ui-adapters/cli-adapters)
endif()

if(UI STREQUAL "desktop" OR UI STREQUAL "both")
    add_subdirectory(expense-tracker/ui/desktop-qt)
    add_subdirectory(expense-tracker/ui-adapters/desktop-qt-adapters)
endif()

# --- Tests
enable_testing()
add_subdirectory(tests)
