#include "System.hpp"

#include <memory>
#include <CLI/CLI.hpp>

// Workflow API
#include "workflow-api-statements-management/StatementImportAndParseI.hpp"

// Workflow Core
#include "workflow-core-services-statements-management/StatementsManagementService.hpp"

// Infrastructure
#include "infrastructure-ports-persistence/PersistenceI.hpp"
#include "infrastructure-adapters-persistence-mysql/MySQLAdapter.hpp"

// UI Components
#include "ui-adapters-cli/StatementsAdapter.hpp"
#include "ui/cli/Commands.hpp"

namespace ExpenseTracker {

class System::Impl {
public:
    Impl() {
        // Wire up all components in dependency order
        setupPersistence();
        setupWorkflowCore();
        setupUserInterface();
    }

    int run(int argc, char* argv[]) {
        try {
            // Create CLI app
            CLI::App app{"Expense Tracker - Command Line Interface"};

            // Create UI components with adapters
            ExpenseTracker::UI::CLI::Commands commands(app, *statementsAdapter);
            commands.setupCommands();

            // Parse and run
            app.parse(argc, argv);
            return 0;
        } catch (const CLI::ParseError& e) {
            return 1;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }

private:
    void setupPersistence() {
        // Create and configure persistence adapter
        mysqlAdapter = std::make_unique<Infrastructure::Persistence::MySQLAdapter>();
    }

    void setupWorkflowCore() {
        // Create and configure workflow services with persistence
        statementsService = std::make_unique<Workflow::StatementsManagement::StatementsManagementService>(
            mysqlAdapter.get()
        );
    }

    void setupUserInterface() {
        // Create UI adapters with workflow services
        statementsAdapter = std::make_unique<UI::CLI::StatementsAdapter>(
            statementsService.get()
        );
    }

    // Secondary adapters (implements infrastructure ports)
    std::unique_ptr<Infrastructure::Persistence::MySQLAdapter> mysqlAdapter;

    // Workflow core services (implements workflow API)
    std::unique_ptr<Workflow::StatementsManagement::StatementsManagementService> statementsService;

    // Primary adapters (implements UI-workflow translation)
    std::unique_ptr<UI::CLI::StatementsAdapter> statementsAdapter;
};

System::System() : pimpl(std::make_unique<Impl>()) {}
System::~System() = default;

int System::run(int argc, char* argv[]) {
    return pimpl->run(argc, argv);
}

} // namespace ExpenseTracker
