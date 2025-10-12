project(StatementsManagementApi VERSION 0.0.1 LANGUAGES CXX)

# Statement Management API interface library
add_library(${PROJECT_NAME} INTERFACE)
add_library("WorkflowApi::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/include
)

# Link dependencies
target_link_libraries(${PROJECT_NAME}
    INTERFACE
        tl::expected      # For error handling
)
