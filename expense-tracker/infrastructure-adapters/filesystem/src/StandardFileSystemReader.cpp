#include "StandardFileSystemReader.hpp"

namespace et::infrastructure::adapters {

tl::expected<std::vector<uint8_t>, ports::FileError>
StandardFileSystemReader::readFile(const std::filesystem::path& path) {
    // TODO: Implement actual file reading
    return tl::unexpected(ports::FileError::NotFound);
}

tl::expected<bool, ports::FileError>
StandardFileSystemReader::exists(const std::filesystem::path& path) {
    // TODO: Implement file existence check
    return tl::unexpected(ports::FileError::NotFound);
}

} // namespace et::infrastructure::adapters
