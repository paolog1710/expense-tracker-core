#pragma once

#include <vector>
#include <memory>
#include <tl/expected.hpp>
#include "Transaction.hpp"

namespace et::infrastructure::ports {

enum class ParserError {
    NotImplemented,
    InvalidFormat,
    CorruptedContent,
    UnsupportedFormat,
    ValidationError,
    MissingRequiredFields
};

struct StatementParseResult {
    et::domain::Statement statement;
    std::vector<et::domain::Transaction> transactions;
};

class BankStatementParserI {
public:
    virtual ~BankStatementParserI() = default;

    /**
     * @brief Parses bank statement content into domain objects
     *
     * @param content Raw content of the statement file
     * @return Expected containing parsed statement and transactions or error
     */
    virtual tl::expected<StatementParseResult, ParserError> parse(
        const std::vector<uint8_t>& content) = 0;

    /**
     * @brief Checks if this parser can handle the given content
     *
     * @param content Raw content to check
     * @return true if this parser can handle the content
     */
    virtual bool canParse(const std::vector<uint8_t>& content) = 0;
};

/**
 * @brief Factory interface for obtaining appropriate parser for content
 */
class BankStatementParserFactoryI {
public:
    virtual ~BankStatementParserFactoryI() = default;

    virtual std::unique_ptr<BankStatementParserI> getParser(
        const std::vector<uint8_t>& content) = 0;
};

} // namespace et::infrastructure::ports
