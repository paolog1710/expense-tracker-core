#include "StatementsAdapter.hpp"
#include <stdexcept>

namespace ExpenseTracker::UI::CLI {

StatementsAdapter::StatementsAdapter(Workflow::StatementsManagement::StatementImportAndParseI* service)
    : service(service) {
    if (!service) {
        throw std::invalid_argument("Statement service cannot be null");
    }
}

void StatementsAdapter::importStatement(const std::string& filePath) {
    // Here we would:
    // 1. Convert the filepath to whatever format the workflow expects
    // 2. Call the workflow service
    // 3. Convert any workflow exceptions to UI-appropriate exceptions
    // service->import(filePath);
}

std::vector<std::string> StatementsAdapter::listStatements() {
    // Here we would:
    // 1. Call the workflow service to get statements
    // 2. Convert the workflow's statement objects to formatted strings
    // 3. Return strings ready for display
    return {"Statement 1", "Statement 2"}; // Placeholder
}

} // namespace ExpenseTracker::UI::CLI
