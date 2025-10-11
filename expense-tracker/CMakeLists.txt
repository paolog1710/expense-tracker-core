cmake_minimum_required(VERSION 3.20)

# Add all subdirectories in dependency order
add_subdirectory(workflow-api)            # Primary ports
add_subdirectory(infrastructure-ports)    # Secondary ports
add_subdirectory(workflow-core)           # Core implementation
add_subdirectory(infrastructure-adapters) # Secondary adapters
add_subdirectory(ui-adapters)            # Primary adapters
add_subdirectory(ui)                      # UI components
add_subdirectory(composition-root)        # System composition and main entry point
