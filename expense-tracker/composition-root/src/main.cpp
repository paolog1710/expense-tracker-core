#include <iostream>
#include "System.hpp"

int main(int argc, char* argv[]) {
    try {
        ExpenseTracker::System system;
        return system.run(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}
