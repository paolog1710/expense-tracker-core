# MySQL persistence adapter object library
add_library(infrastructure-adapters-persistence-mysql-obj OBJECT)
target_sources(infrastructure-adapters-persistence-mysql-obj
    PRIVATE
        *.cpp # You'll need to specify actual source files
)
target_link_libraries(infrastructure-adapters-persistence-mysql-obj
    PUBLIC
        infrastructure-ports-persistence    # implements these interfaces
    PRIVATE
        # MySQL dependencies will be PRIVATE to not leak to consumers
)

# Shared library that consumes the object library
add_library(infrastructure-adapters-persistence-mysql SHARED)
target_link_libraries(infrastructure-adapters-persistence-mysql
    PUBLIC
        infrastructure-adapters-persistence-mysql-obj)
