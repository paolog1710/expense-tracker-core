project(FilesystemAdapters VERSION 0.0.1 LANGUAGES CXX)

set(HEADER_FILES
    include/StandardFileSystemReader.hpp
)

set(SOURCE_FILES
    src/StandardFileSystemReader.cpp
)

# Create object library
add_library(${PROJECT_NAME}-obj OBJECT
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME}-obj
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link against the port it implements
target_link_libraries(${PROJECT_NAME}-obj
    PUBLIC
        InfrastructurePorts::FilesystemPorts    # implements this port
)

# Create shared library that consumes the objects
add_library(${PROJECT_NAME} SHARED)
add_library("InfrastructureAdapters::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_NAME}-obj)
