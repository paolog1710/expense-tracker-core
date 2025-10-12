project(repository-adapters VERSION 0.0.1 LANGUAGES CXX)

set(HEADER_FILES
    include/SqliteTransactionRepository.hpp
)

set(SOURCE_FILES
    src/SqliteTransactionRepository.cpp
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

# Link against the port it implements and other dependencies
target_link_libraries(${PROJECT_NAME}-obj
    PUBLIC
        repository-ports   # implements this port
        domain            # uses domain types directly
    PRIVATE
        sqlite3  # actual database implementation - use target name from Conan
)

# Create shared library that consumes the objects
add_library(${PROJECT_NAME} SHARED)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_NAME}-obj)
