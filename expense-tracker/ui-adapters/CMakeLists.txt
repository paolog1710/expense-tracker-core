# Add UI adapters based on configuration
if(BUILD_UI_CLI)
    add_subdirectory(cli-adapters)
endif()

if(BUILD_UI_DESKTOP)
    add_subdirectory(desktop-qt-adapters)
endif()
