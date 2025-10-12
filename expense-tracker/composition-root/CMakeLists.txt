# Base system interface
add_library(composition-root-base STATIC
    src/System.cpp
)
target_include_directories(composition-root-base
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(composition-root-base
    PUBLIC
        # Primary ports (API)
        statements-management-api
    PRIVATE
        domain                      # Domain types
)

if(BUILD_UI_CLI)
    # CLI system implementation
    add_library(composition-root-cli STATIC
        src/SystemCLI.cpp
    )
    target_include_directories(composition-root-cli
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_link_libraries(composition-root-cli
        PRIVATE
            composition-root-base
            # Core services
            statements-management-service
            # Infrastructure adapters
            filesystem-adapters
            parser-adapters
            repository-adapters
            # UI Layer
            ui-cli                  # High-level UI components
            ui-adapters-cli        # UI adapters
            CLI11                  # CLI parser
            Boost::di              # Dependency injection
    )

    # CLI executable
    add_executable(expense-tracker-cli
        src/main_cli.cpp
    )
    target_link_libraries(expense-tracker-cli
        PRIVATE
            composition-root-cli
)
