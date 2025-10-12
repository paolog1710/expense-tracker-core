#include "BankStatementParserFactory.hpp"
#include "CsvBankStatementParser.hpp"

namespace et::infrastructure::adapters {

std::unique_ptr<ports::BankStatementParserI>
BankStatementParserFactory::getParser(const std::vector<uint8_t>& content) {
    // TODO: Implement parser selection logic
    return std::make_unique<CsvBankStatementParser>();
}

} // namespace et::infrastructure::adapters
