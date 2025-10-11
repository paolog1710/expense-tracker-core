# CLI UI components
add_library(ui-cli STATIC
    src/Commands.cpp
)
target_include_directories(ui-cli
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(ui-cli
    PRIVATE
        CLI11                # UI implementation detail
        ui-adapters-cli      # Adapter for workflow communication
)
