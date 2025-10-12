#include <iostream>
#include "System.hpp"

int main(int argc, char* argv[]) {
    try {
        // Create system using factory (will return CLI or GUI system based on build configuration)
        auto system = et::createSystem();
        if (!system) {
            std::cerr << "Failed to create system" << std::endl;
            return 1;
        }

        // Run the system
        return system->run(argc, argv);
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error occurred" << std::endl;
        return 1;
    }
}
