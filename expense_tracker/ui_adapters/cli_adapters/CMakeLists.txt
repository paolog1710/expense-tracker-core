project(CliAdapters VERSION 0.0.1 LANGUAGES CXX)

# CLI adapter object library
add_library(${PROJECT_NAME}-obj OBJECT
    src/StatementsAdapter.cpp
)
target_include_directories(${PROJECT_NAME}-obj
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}-obj
    PUBLIC
        WorkflowApi::StatementsManagementApi  # depends only on primary ports
        di::di                                # for dependency injection
)

# Shared library that consumes the object library
add_library(${PROJECT_NAME} SHARED)
add_library("UiAdapters::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_NAME}-obj
)
