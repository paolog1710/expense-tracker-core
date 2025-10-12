# CLI UI components
add_library(UiCli STATIC
    src/Commands.cpp
)
target_include_directories(UiCli
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
find_package(CLI11 CONFIG REQUIRED)

target_link_libraries(UiCli
    PRIVATE
        CLI11::CLI11                # UI implementation detail
        UiAdapters::CliAdapters  # Adapter for workflow communication
)
