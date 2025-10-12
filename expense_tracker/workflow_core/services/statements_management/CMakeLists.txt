project(StatementsManagementService VERSION 0.0.1 LANGUAGES CXX)

set(HEADER_FILES
    include/StatementImport.hpp
)

set(SOURCE_FILES
    src/StatementImport.cpp
)

# Statement management service objects
add_library(${PROJECT_NAME}-obj OBJECT
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME}-obj
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}-obj
    PUBLIC
        WorkflowApi::StatementsManagementApi  # implements primary ports
    PRIVATE
        InfrastructurePorts::FilesystemPorts        # file system operations
        InfrastructurePorts::ParserPorts           # statement parsing
        InfrastructurePorts::RepositoryPorts       # transaction storage
        Domain::Domain                # domain types
)

# Shared library that consumes the objects
add_library(${PROJECT_NAME} SHARED)
add_library("WorkflowCore::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_NAME}-obj)
