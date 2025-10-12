#pragma once

#include <vector>
#include <tl/expected.hpp>
#include "Transaction.hpp"

namespace et::infrastructure::ports {

enum class RepositoryError {
    NotImplemented,
    ConnectionError,
    DuplicateEntry,
    ValidationError,
    StorageError,
    NotFound
};

class TransactionRepositoryI {
public:
    virtual ~TransactionRepositoryI() = default;

    /**
     * @brief Stores a batch of transactions from a statement
     *
     * @param statement Statement metadata
     * @param transactions Transactions to store
     * @return Expected void or error
     */
    virtual tl::expected<void, RepositoryError> storeTransactions(
        const et::domain::Statement& statement,
        const std::vector<et::domain::Transaction>& transactions) = 0;

    /**
     * @brief Checks if a transaction already exists
     *
     * @param transactionId ID of the transaction to check
     * @return Expected containing existence status or error
     */
    virtual tl::expected<bool, RepositoryError> hasTransaction(
        const std::string& transactionId) = 0;
};

} // namespace et::infrastructure::ports
