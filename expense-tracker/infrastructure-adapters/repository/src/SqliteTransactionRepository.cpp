#include "SqliteTransactionRepository.hpp"

namespace et::infrastructure::adapters {

tl::expected<void, ports::RepositoryError>
SqliteTransactionRepository::storeTransactions(
    const domain::Statement& statement,
    const std::vector<domain::Transaction>& transactions) {
    // TODO: Implement transaction storage
    return tl::unexpected(ports::RepositoryError::NotImplemented);
}

tl::expected<bool, ports::RepositoryError>
SqliteTransactionRepository::hasTransaction(const std::string& transactionId) {
    // TODO: Implement transaction lookup
    return tl::unexpected(ports::RepositoryError::NotImplemented);
}

} // namespace et::infrastructure::adapters
