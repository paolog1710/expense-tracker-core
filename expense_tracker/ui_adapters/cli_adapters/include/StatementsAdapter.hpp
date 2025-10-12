#pragma once
#include <statement_management/StatementImportI.hpp>
#include <boost/di.hpp>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

namespace et::ui::cli {

// The adapter translates between UI concepts and workflow concepts
class StatementsAdapter {
public:
    // Constructor injection of dependencies
    BOOST_DI_INJECT(StatementsAdapter,
                   std::shared_ptr<et::workflow::statements::StatementImportI> service)
        : service_(service) {
        if (!service_) {
            throw std::invalid_argument("Statement service cannot be null");
        }
    }

    ~StatementsAdapter() = default;

    // UI-friendly methods that adapt to the workflow
    void importStatement(const std::string& filePath);
    std::vector<std::string> listStatements(); // Returns formatted strings for display

private:
    std::shared_ptr<et::workflow::statements::StatementImportI> service_;
};

} // namespace et::ui::cli
