#pragma once

#include <memory>

namespace ExpenseTracker {

class System {
public:
    System();
    ~System();

    // Prevent copying and moving
    System(const System&) = delete;
    System& operator=(const System&) = delete;
    System(System&&) = delete;
    System& operator=(System&&) = delete;

    int run(int argc, char* argv[]);

private:
    class Impl;
    std::unique_ptr<Impl> pimpl;  // Hide implementation details
};

} // namespace ExpenseTracker
