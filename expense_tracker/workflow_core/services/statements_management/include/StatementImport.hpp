#pragma once

#include <statement_management/StatementImportI.hpp>

namespace et::workflow::statements {

class StatementImport : public StatementImportI {
public:
    StatementImport() = default;
    ~StatementImport() override = default;

    // Prevent copying and moving
    StatementImport(const StatementImport&) = delete;
    StatementImport& operator=(const StatementImport&) = delete;
    StatementImport(StatementImport&&) = delete;
    StatementImport& operator=(StatementImport&&) = delete;

    ImportResult<ImportStatementResponse> importStatement(const ImportStatementRequest& request) override;
};

} // namespace et::workflow_core::statements
