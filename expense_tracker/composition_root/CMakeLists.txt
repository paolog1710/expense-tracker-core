project(CompositionRootBase VERSION 0.0.1 LANGUAGES CXX)

# Base system interface
add_library(CompositionRootBase STATIC
    src/System.cpp
)
target_include_directories(CompositionRootBase
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(CompositionRootBase
    PUBLIC
        # Primary ports (API)
        WorkflowApi::StatementsManagementApi
    PRIVATE
        Domain::Domain                      # Domain types
)

if(BUILD_UI_CLI)
    # CLI system implementation
    add_library(CompositionRootCli STATIC
        src/SystemCLI.cpp
    )
    target_include_directories(CompositionRootCli
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_link_libraries(CompositionRootCli
        PRIVATE
            CompositionRootBase
            # Core services
            WorkflowCore::StatementsManagementService
            # Infrastructure adapters
            InfrastructureAdapters::FilesystemAdapters
            InfrastructureAdapters::ParserAdapters
            InfrastructureAdapters::RepositoryAdapters
            # UI Layer
            UiCli                  # High-level UI components
            UiAdapters::CliAdapters        # UI adapters
            CLI11::CLI11                  # CLI parser
            Boost::di              # Dependency injection
    )

    # CLI executable
    add_executable(ExpenseTrackerCli
        src/main_cli.cpp
    )
    target_link_libraries(ExpenseTrackerCli
        PRIVATE
            CompositionRootCli
)
