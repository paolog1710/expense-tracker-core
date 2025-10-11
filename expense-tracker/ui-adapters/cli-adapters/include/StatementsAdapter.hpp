#pragma once
#include "workflow-api-statements-management/StatementImportAndParseI.hpp"
#include <string>
#include <vector>

namespace ExpenseTracker::UI::CLI {

// The adapter translates between UI concepts and workflow concepts
class StatementsAdapter {
public:
    explicit StatementsAdapter(Workflow::StatementsManagement::StatementImportAndParseI* service);

    // UI-friendly methods that adapt to the workflow
    void importStatement(const std::string& filePath);
    std::vector<std::string> listStatements(); // Returns formatted strings for display

private:
    Workflow::StatementsManagement::StatementImportAndParseI* service;
};

} // namespace ExpenseTracker::UI::CLI
