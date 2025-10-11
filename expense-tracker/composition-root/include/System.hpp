#pragma once

#include <memory>

namespace ExpenseTracker {

// Base interface for all system variants
class System {
public:
    virtual ~System() = default;
    virtual int run(int argc, char* argv[]) = 0;

    // Prevent copying and moving
    System(const System&) = delete;
    System& operator=(const System&) = delete;
    System(System&&) = delete;
    System& operator=(System&&) = delete;

protected:
    System() = default;
};

// Factory function to create the appropriate system
std::unique_ptr<System> createSystem();

} // namespace ExpenseTracker
