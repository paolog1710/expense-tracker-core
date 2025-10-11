cmake_minimum_required(VERSION 3.20)

project(my_hex_app LANGUAGES CXX)

# ---- UI selection ----
set(UI "desktop" CACHE STRING "Choose UI: cli, desktop, or both")
set_property(CACHE UI PROPERTY STRINGS cli desktop both)

# Convenience booleans
set(BUILD_UI_CLI     OFF)
set(BUILD_UI_DESKTOP OFF)
if(UI STREQUAL "cli" OR UI STREQUAL "both")
  set(BUILD_UI_CLI ON)
endif()
if(UI STREQUAL "desktop" OR UI STREQUAL "both")
  set(BUILD_UI_DESKTOP ON)
endif()

# Add all subdirectories in dependency order
add_subdirectory(workflow-api)            # Primary ports
add_subdirectory(infrastructure-ports)    # Secondary ports
add_subdirectory(workflow-core)           # Core implementation
add_subdirectory(infrastructure-adapters) # Secondary adapters
add_subdirectory(ui-adapters)            # Primary adapters
add_subdirectory(ui)                      # UI components
add_subdirectory(composition-root)        # System composition and main entry point
