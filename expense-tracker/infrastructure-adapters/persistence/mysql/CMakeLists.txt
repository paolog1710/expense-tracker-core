project(persistence-adapter-mysql VERSION 0.0.1 LANGUAGES CXX)

# MySQL persistence adapter object library
add_library(${PROJECT_NAME}-obj OBJECT)
target_sources(${PROJECT_NAME}-obj
    PRIVATE
        *.cpp # You'll need to specify actual source files
)
target_link_libraries(${PROJECT_NAME}-obj
    PUBLIC
        persistence-port    # implements these interfaces
    PRIVATE
        # MySQL dependencies will be PRIVATE to not leak to consumers
)

# Shared library that consumes the object library
add_library(${PROJECT_NAME} SHARED)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_NAME}-obj)
