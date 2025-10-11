#pragma once
#include <CLI/CLI.hpp>
#include "StatementsAdapter.hpp"

namespace ExpenseTracker::UI::CLI {

class Commands {
public:
    Commands(CLI::App& app, StatementsAdapter& adapter);

    // Add commands to the app
    void setupCommands();

private:
    // Command handlers
    void handleImport(const std::string& filePath);
    void handleList();

    // Store command options
    std::string importFilePath;

    // References to dependencies
    CLI::App& app;
    StatementsAdapter& adapter;
};

} // namespace ExpenseTracker::UI::CLI
