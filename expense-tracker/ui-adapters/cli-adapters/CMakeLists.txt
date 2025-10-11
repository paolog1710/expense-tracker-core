# CLI adapter object library
add_library(ui-adapters-cli-obj OBJECT
    src/StatementsAdapter.cpp
)
target_include_directories(ui-adapters-cli-obj
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(ui-adapters-cli-obj
    PUBLIC
        workflow-api-statements-management  # depends only on primary ports
)

# Shared library that consumes the object library
add_library(ui-adapters-cli SHARED)
target_link_libraries(ui-adapters-cli
    PUBLIC
        ui-adapters-cli-obj)ary(ui-adapters-cli SHARED)
target_sources(ui-adapters-cli
    PRIVATE
        *.cpp # You'll need to specify actual source files
)
target_link_libraries(ui-adapters-cli
    PUBLIC
        workflow-api # depends only on primary ports
)
