project(statements-management-service VERSION 0.0.1 LANGUAGES CXX)

# Statement management service objects
add_library(${PROJECT_NAME}-obj OBJECT
    src/StatementsService.cpp    # Replace with actual source files
)
target_include_directories(${PROJECT_NAME}-obj
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}-obj
    PUBLIC
        statements-management-api  # implements primary ports
    PRIVATE
        infrastructure-ports     # uses secondary ports
        domain-expense           # internal domain dependency
)

# Shared library that consumes the objects
add_library(${PROJECT_NAME} SHARED)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_NAME}-obj)
