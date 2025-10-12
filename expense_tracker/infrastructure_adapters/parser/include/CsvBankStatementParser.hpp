#pragma once

#include "BankStatementParserI.hpp"

namespace et::infrastructure::adapters {

class CsvBankStatementParser : public ports::BankStatementParserI {
public:
    CsvBankStatementParser() = default;
    ~CsvBankStatementParser() override = default;

    // Prevent copying and moving
    CsvBankStatementParser(const CsvBankStatementParser&) = delete;
    CsvBankStatementParser& operator=(const CsvBankStatementParser&) = delete;
    CsvBankStatementParser(CsvBankStatementParser&&) = delete;
    CsvBankStatementParser& operator=(CsvBankStatementParser&&) = delete;

    tl::expected<ports::StatementParseResult, ports::ParserError> parse(
        const std::vector<uint8_t>& content) override;

    bool canParse(const std::vector<uint8_t>& content) override;
};

} // namespace et::infrastructure::adapters
