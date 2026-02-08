cmake_minimum_required(VERSION 3.22)
project(ExpenseTrackerCore VERSION 1.0.0 LANGUAGES CXX)

# --- C++ standard & compile database
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)



# Make our cmake/ directory discoverable for modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CMakeFolderConfig)
include(GlobalSettings)
include(EtWarnings)

# Setup suffix for libraries and binaries to satisfy Visual Studio
if(MSVC)
	set(CMAKE_DEBUG_POSTFIX d)
endif()

# GUI type options
option(PYTHON_GUI "Build Python GUI" OFF)
option(QT_GUI "Build Qt GUI" OFF)
option(GRPC_GUI "Build gRPC server" OFF)

find_package(tl-expected REQUIRED)

# Core libraries (always built)
add_subdirectory(source/app.ports)
add_subdirectory(source/app)
add_subdirectory(source/domain)
add_subdirectory(source/infra.ports)
add_subdirectory(source/infra.adapters)
add_subdirectory(source/system.root)

# GUI-specific subdirectories
if(PYTHON_GUI)
    add_subdirectory(source/gui.python/adapters)
endif()

if(QT_GUI)
    add_subdirectory(source/gui.qt)
endif()

if(GRPC_GUI)
    add_subdirectory(source/gui.grpc)
endif()
