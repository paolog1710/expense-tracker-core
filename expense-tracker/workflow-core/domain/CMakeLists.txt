add_library(workflow-core-domain-expense OBJECT)
target_sources(workflow-core-domain-expense
    PRIVATE
        expense/*.cpp # You'll need to specify actual source files
    PUBLIC
        expense/*.hpp
)
target_include_directories(workflow-core-domain-expense
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(workflow-core-domain INTERFACE)
target_link_libraries(workflow-core-domain
    INTERFACE
        workflow-core-domain-expense)
