add_library(infrastructure-ports-persistence INTERFACE)
target_include_directories(infrastructure-ports-persistence
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
