#include "Commands.hpp"
#include <iostream>

namespace et::ui::cli {

Commands::Commands(CLI::App& app, StatementsAdapter& adapter)
    : app(app), adapter(adapter) {}

void Commands::setupCommands() {
    // Command: Import statement
    auto* importCmd = app.add_subcommand("import", "Import a bank statement");
    importCmd->add_option("file", importFilePath, "Path to the bank statement file")->required();
    importCmd->callback([this]() { handleImport(importFilePath); });

    // Command: List statements
    auto* listCmd = app.add_subcommand("list", "List imported statements");
    listCmd->callback([this]() { handleList(); });
}

void Commands::handleImport(const std::string& filePath) {
    try {
        std::cout << "Importing statement from: " << filePath << std::endl;
        adapter.importStatement(filePath);
        std::cout << "Import successful!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Import failed: " << e.what() << std::endl;
        throw; // Propagate to main for error handling
    }
}

void Commands::handleList() {
    try {
        std::cout << "Imported statements:" << std::endl;
        auto statements = adapter.listStatements();
        for (const auto& stmt : statements) {
            std::cout << stmt << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to list statements: " << e.what() << std::endl;
        throw; // Propagate to main for error handling
    }
}

} // namespace ExpenseTracker::UI::CLI
