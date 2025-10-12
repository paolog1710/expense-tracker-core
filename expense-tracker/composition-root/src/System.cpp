#include "System.hpp"
#include "SystemCLI.hpp"
#include <memory>

namespace et {

std::unique_ptr<System> createSystem() {
#ifdef BUILD_UI_CLI
    // Create CLI system when CLI UI is enabled
    return std::make_unique<SystemCLI>();
#else
    // For now, return nullptr if no UI is enabled
    // Later we can add other system types (GUI, Web, etc.)
    return nullptr;
#endif
}

} // namespace et
