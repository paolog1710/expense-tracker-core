#include "StatementImport.hpp"

namespace et::workflow::statements {

ImportResult<ImportStatementResponse> StatementImport::importStatement(const ImportStatementRequest& request) {
    return tl::unexpected(ImportError{
        .code = StatementImportError::UnsupportedStatementFormat,
        .message = "Statement import not implemented",
        .context = request.statementPath.string()
    });
}

} // namespace et::workflow::statements
