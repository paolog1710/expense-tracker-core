# Composition root library (contains System class)
add_library(composition-root-lib STATIC
    src/System.cpp
)
target_include_directories(composition-root-lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(composition-root-lib
    PRIVATE
        # Core API and Implementation
        workflow-api-statements-management
        workflow-core-services-statements-management

        # Infrastructure
        infrastructure-ports-persistence
        infrastructure-adapters-persistence-mysql

        # UI Layer
        ui-cli                  # High-level UI components
        ui-adapters-cli        # UI adapters
        CLI11                  # CLI parser
)

# Main executable
add_executable(expense-tracker-cli
    src/main.cpp
)
target_link_libraries(expense-tracker-cli
    PRIVATE
        composition-root-lib
)
