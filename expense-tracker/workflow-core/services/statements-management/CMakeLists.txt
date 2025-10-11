# Statement management service objects
add_library(workflow-core-services-statements-management-obj OBJECT)
target_sources(workflow-core-services-statements-management-obj
    PRIVATE
        *.cpp # You'll need to specify actual source files
    PUBLIC
        *.hpp
)
target_include_directories(workflow-core-services-statements-management-obj
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(workflow-core-services-statements-management-obj
    PUBLIC
        workflow-api-statements-management  # implements primary ports
        infrastructure-ports                # uses secondary ports
        workflow-core-domain-expense        # internal domain dependency
        workflow-core-services-shared-obj   # internal shared dependency
)

# Shared library that consumes the objects
add_library(workflow-core-services-statements-management SHARED)
target_link_libraries(workflow-core-services-statements-management
    PUBLIC
        workflow-core-services-statements-management-obj)
