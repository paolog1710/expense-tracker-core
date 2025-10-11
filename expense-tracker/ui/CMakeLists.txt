# CLI UI
add_subdirectory(cli)

# Export all targets
add_library(ui INTERFACE)
target_link_libraries(ui
    INTERFACE
        ui-cli
)
