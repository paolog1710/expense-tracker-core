# Shared services objects
add_library(workflow-core-services-shared-obj OBJECT)
target_sources(workflow-core-services-shared-obj
    PRIVATE
        *.cpp # You'll need to specify actual source files
    PUBLIC
        *.hpp
)
target_include_directories(workflow-core-services-shared-obj
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Shared libraries that consume the objects
add_library(workflow-core-services-shared SHARED)
target_link_libraries(workflow-core-services-shared
    PUBLIC
        workflow-core-services-shared-obj)
