#pragma once

#include <string>
#include <tl/expected.hpp>

namespace et::workflow::statements {

enum class StatementImportError {
    // File System Errors (1-99)
    FileNotFound = 1,
    PermissionDenied = 2,
    InvalidPath = 3,

    // Format/Parsing Errors (100-199)
    InvalidFileFormat = 100,
    CorruptedContent = 101,
    UnsupportedStatementFormat = 102,
    MissingRequiredFields = 103,

    // Validation Errors (200-299)
    InvalidDateFormat = 200,
    InvalidAmountFormat = 201,
    DuplicateEntry = 202,
    InvalidTransactionType = 203,

    // Business Rule Errors (300-399)
    StatementPeriodMismatch = 300,
    BalanceInconsistency = 301,
    CurrencyMismatch = 302
};

struct ImportError {
    StatementImportError code;
    std::string message;
    std::string context;  // Additional context (e.g., file path, field name)
};

// Convenience type alias for tl::expected with ImportError
template<typename T>
using ImportResult = tl::expected<T, ImportError>;

} // namespace et::workflow::statements
