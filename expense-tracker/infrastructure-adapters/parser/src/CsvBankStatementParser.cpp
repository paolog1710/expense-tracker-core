#include "CsvBankStatementParser.hpp"

namespace et::infrastructure::adapters {

tl::expected<ports::StatementParseResult, ports::ParserError>
CsvBankStatementParser::parse(const std::vector<uint8_t>& content) {
    // TODO: Implement CSV parsing
    return tl::unexpected(ports::ParserError::NotImplemented);
}

bool CsvBankStatementParser::canParse(const std::vector<uint8_t>& content) {
    // TODO: Implement format detection
    return false;
}

} // namespace et::infrastructure::adapters
