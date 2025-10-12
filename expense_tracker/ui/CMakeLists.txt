# Add UI implementations based on configuration
if(BUILD_UI_CLI)
    add_subdirectory(cli)
endif()

if(BUILD_UI_DESKTOP)
    add_subdirectory(desktop_qt)
endif()
