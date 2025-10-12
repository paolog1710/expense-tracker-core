#pragma once

#include "FileSystemReaderI.hpp"

namespace et::infrastructure::adapters {

class StandardFileSystemReader : public ports::FileSystemReaderI {
public:
    StandardFileSystemReader() = default;
    ~StandardFileSystemReader() override = default;

    // Prevent copying and moving
    StandardFileSystemReader(const StandardFileSystemReader&) = delete;
    StandardFileSystemReader& operator=(const StandardFileSystemReader&) = delete;
    StandardFileSystemReader(StandardFileSystemReader&&) = delete;
    StandardFileSystemReader& operator=(StandardFileSystemReader&&) = delete;

    tl::expected<std::vector<uint8_t>, ports::FileError> readFile(
        const std::filesystem::path& path) override;

    tl::expected<bool, ports::FileError> exists(
        const std::filesystem::path& path) override;
};

} // namespace et::infrastructure::adapters
