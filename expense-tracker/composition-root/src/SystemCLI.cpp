#include "SystemCLI.hpp"
#include <boost/di.hpp>
#include <memory>
#include <CLI/CLI.hpp>

// Workflow API
#include "workflow-api-statements-management/StatementImportAndParseI.hpp"

// Infrastructure
#include "infrastructure-ports-persistence/PersistenceI.hpp"
#include "infrastructure-adapters-persistence-mysql/MySQLAdapter.hpp"

// UI Components
#include "ui-adapters-cli/StatementsAdapter.hpp"
#include "ui/cli/Commands.hpp"

namespace di = boost::di;

namespace ExpenseTracker {

// Configure DI bindings
auto makeInjector() {
    return di::make_injector(
        // Bind infrastructure ports to adapters
        di::bind<Infrastructure::Persistence::PersistenceI>()
            .to<Infrastructure::Persistence::MySQLAdapter>(),

        // Bind workflow API to core implementations
        di::bind<Workflow::StatementsManagement::StatementImportAndParseI>()
            .to<Workflow::StatementsManagement::StatementsManagementService>(),

        // Bind concrete types as singletons
        di::bind<Infrastructure::Persistence::MySQLAdapter>().in(di::singleton),
        di::bind<Workflow::StatementsManagement::StatementsManagementService>().in(di::singleton),
        di::bind<UI::CLI::StatementsAdapter>().in(di::singleton),
        di::bind<UI::CLI::Commands>().in(di::singleton)
    );
}

class SystemCLI::Impl {
public:
    Impl() : injector_(makeInjector()) {
        // DI will resolve all dependencies automatically
        commands_ = injector_.create<std::shared_ptr<UI::CLI::Commands>>();
    }

    int run(int argc, char* argv[]) {
        try {
            CLI::App app{"Expense Tracker - Command Line Interface"};
            commands_->setupCommands(app);
            app.parse(argc, argv);
            return 0;
        } catch (const CLI::ParseError& e) {
            return 1;
        }
    }

private:
    di::injector<> injector_;
    std::shared_ptr<UI::CLI::Commands> commands_;

SystemCLI::SystemCLI() : pimpl(std::make_unique<Impl>()) {}
SystemCLI::~SystemCLI() = default;

int SystemCLI::run(int argc, char* argv[]) {
    return pimpl->run(argc, argv);
}

} // namespace ExpenseTracker
