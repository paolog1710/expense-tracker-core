#pragma once
#include "workflow-api-statements-management/StatementImportAndParseI.hpp"
#include <boost/di.hpp>
#include <memory>
#include <string>
#include <vector>

namespace ExpenseTracker::UI::CLI {

// The adapter translates between UI concepts and workflow concepts
class StatementsAdapter {
public:
    // Constructor injection of dependencies
    BOOST_DI_INJECT(StatementsAdapter,
        (std::shared_ptr<Workflow::StatementsManagement::StatementImportAndParseI>) service
    );

    ~StatementsAdapter() = default;

    // UI-friendly methods that adapt to the workflow
    void importStatement(const std::string& filePath);
    std::vector<std::string> listStatements(); // Returns formatted strings for display

private:
    std::shared_ptr<Workflow::StatementsManagement::StatementImportAndParseI> service_;

} // namespace ExpenseTracker::UI::CLI
