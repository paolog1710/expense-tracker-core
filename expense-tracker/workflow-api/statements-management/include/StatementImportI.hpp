#pragma once

#include "StatementImportTypes.hpp"

namespace et::workflow::statements {

class StatementImportI {
public:
    virtual ~StatementImportI() = default;

    /**
     * @brief Imports a single bank statement from the given path.
     *        The operation includes validation of the statement format and content.
     *
     * @param request Contains the path to the statement file to import
     * @return ImportResult<ImportStatementResponse>
     *         Success: ImportStatementResponse containing metadata about the imported statement
     *         Failure: ImportError with error details (e.g., invalid format, parsing error,
     *                 validation failure, system errors)
     */
    virtual ImportResult<ImportStatementResponse> importStatement(const ImportStatementRequest& request) = 0;
};

} // namespace et::workflow::statements
