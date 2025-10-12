#pragma once

#include <filesystem>
#include "StatementImportError.hpp"

namespace et::workflow::statements {

struct ImportStatementRequest {
    std::filesystem::path statementPath;
};

struct ImportStatementResponse {
    std::size_t transactionCount;
    // Could add more metadata like:
    // DateRange period;
    // std::string bankName;
    // Money totalCredits;
    // Money totalDebits;
};

} // namespace et::workflow::statements
