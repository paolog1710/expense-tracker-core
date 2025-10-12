project(FilesystemPorts VERSION 0.0.1 LANGUAGES CXX)

set(HEADER_FILES
    include/FileSystemReaderI.hpp
)

add_library(${PROJECT_NAME} INTERFACE)
add_library("InfrastructurePorts::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add header files to the target (helps IDEs)
target_sources(${PROJECT_NAME}
    INTERFACE
        ${HEADER_FILES}
)

# Link against domain library for Transaction types
target_link_libraries(${PROJECT_NAME}
    INTERFACE
        tl::expected)
