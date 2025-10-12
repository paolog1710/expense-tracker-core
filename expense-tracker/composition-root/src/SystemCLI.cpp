#include "SystemCLI.hpp"
#include <boost/di.hpp>
#include <memory>
#include <CLI/CLI.hpp>

// Primary ports
#include "StatementImportI.hpp"
#include "StatementImport.hpp"

// Infrastructure
#include "FileSystemReaderI.hpp"
#include "BankStatementParserI.hpp"
#include "TransactionRepositoryI.hpp"
#include "StandardFileSystemReader.hpp"
#include "BankStatementParserFactory.hpp"
#include "SqliteTransactionRepository.hpp"

namespace di = boost::di;

namespace et {

// Configure DI bindings
auto makeCliInjector() {
    auto baseInjector = makeBasicConfig();

    return di::make_injector(
        baseInjector,

        // Bind workflow services as singletons
        di::bind<workflow::statements::StatementImportI>()
            .to<workflow::services::StatementImport>()
            .in(di::singleton),

        // Bind infrastructure adapters as singletons
        di::bind<infrastructure::ports::FileSystemReaderI>()
            .to<infrastructure::adapters::StandardFileSystemReader>()
            .in(di::singleton),

        di::bind<infrastructure::ports::BankStatementParserFactoryI>()
            .to<infrastructure::adapters::BankStatementParserFactory>()
            .in(di::singleton),

        di::bind<infrastructure::ports::TransactionRepositoryI>()
            .to<infrastructure::adapters::SqliteTransactionRepository>()
            .in(di::singleton)
    );
}

class SystemCLI::Impl {
public:
    Impl() : injector_(makeCliInjector()) {
        // DI will resolve all dependencies automatically
        statementImport_ = injector_.create<std::shared_ptr<workflow::statements::StatementImportI>>();
    }

    int run(int argc, char* argv[]) {
        try {
            CLI::App app{"Expense Tracker - Command Line Interface"};

            // TODO: Setup CLI commands using statementImport_

            app.parse(argc, argv);
            return 0;
        } catch (const CLI::ParseError& e) {
            return app.exit(e);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }

    std::shared_ptr<workflow::statements::StatementImportI> getStatementImport() {
        return statementImport_;
    }

private:
    di::injector<> injector_;
    std::shared_ptr<workflow::statements::StatementImportI> statementImport_;
};

SystemCLI::SystemCLI() : pimpl(std::make_unique<Impl>()) {}
SystemCLI::~SystemCLI() = default;

int SystemCLI::run(int argc, char* argv[]) {
    return pimpl->run(argc, argv);
}

std::shared_ptr<workflow::statements::StatementImportI> SystemCLI::getStatementImport() {
    return pimpl->getStatementImport();
}

// Factory implementation for CLI system
std::unique_ptr<System> createSystem() {
    return std::make_unique<SystemCLI>();
}

} // namespace et
