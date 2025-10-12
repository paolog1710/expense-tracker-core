#pragma once

#include "BankStatementParserI.hpp"
#include <memory>

namespace et::infrastructure::adapters {

class BankStatementParserFactory : public ports::BankStatementParserFactoryI {
public:
    BankStatementParserFactory() = default;
    ~BankStatementParserFactory() override = default;

    // Prevent copying and moving
    BankStatementParserFactory(const BankStatementParserFactory&) = delete;
    BankStatementParserFactory& operator=(const BankStatementParserFactory&) = delete;
    BankStatementParserFactory(BankStatementParserFactory&&) = delete;
    BankStatementParserFactory& operator=(BankStatementParserFactory&&) = delete;

    std::unique_ptr<ports::BankStatementParserI> getParser(
        const std::vector<uint8_t>& content) override;
};

} // namespace et::infrastructure::adapters
