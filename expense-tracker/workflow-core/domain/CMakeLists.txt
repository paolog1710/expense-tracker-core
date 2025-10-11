project(domain VERSION 0.0.1 LANGUAGES CXX)

# Expense domain objects
add_library(${PROJECT_NAME}-expense-obj OBJECT
    src/expense/Expense.cpp    # Replace with actual source files
)
target_include_directories(${PROJECT_NAME}-expense-obj
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Interface library that aggregates all domain components
add_library(${PROJECT_NAME}-expense SHARED)
target_link_libraries(${PROJECT_NAME}-expense
    PUBLIC
        ${PROJECT_NAME}-expense-obj)
