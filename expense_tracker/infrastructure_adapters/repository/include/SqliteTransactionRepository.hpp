#pragma once

#include "TransactionRepositoryI.hpp"

namespace et::infrastructure::adapters {

class SqliteTransactionRepository : public ports::TransactionRepositoryI {
public:
    SqliteTransactionRepository() = default;
    ~SqliteTransactionRepository() override = default;

    // Prevent copying and moving
    SqliteTransactionRepository(const SqliteTransactionRepository&) = delete;
    SqliteTransactionRepository& operator=(const SqliteTransactionRepository&) = delete;
    SqliteTransactionRepository(SqliteTransactionRepository&&) = delete;
    SqliteTransactionRepository& operator=(SqliteTransactionRepository&&) = delete;

    tl::expected<void, ports::RepositoryError> storeTransactions(
        const domain::Statement& statement,
        const std::vector<domain::Transaction>& transactions) override;

    tl::expected<bool, ports::RepositoryError> hasTransaction(
        const std::string& transactionId) override;
};

} // namespace et::infrastructure::adapters
