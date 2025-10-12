# Add UI adapters based on configuration
if(BUILD_UI_CLI)
    add_subdirectory(cli_adapters)
endif()

if(BUILD_UI_DESKTOP)
    add_subdirectory(desktop_qt_adapters)
endif()
