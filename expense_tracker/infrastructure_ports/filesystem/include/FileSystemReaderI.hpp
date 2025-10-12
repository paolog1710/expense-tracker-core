#pragma once

#include <filesystem>
#include <vector>
#include <tl/expected.hpp>

namespace et::infrastructure::ports {

enum class FileError {
    NotFound,
    PermissionDenied,
    InvalidPath,
    ReadError
};

class FileSystemReaderI {
public:
    virtual ~FileSystemReaderI() = default;

    /**
     * @brief Reads the entire content of a file
     *
     * @param path Path to the file to read
     * @return Expected containing file content or error
     */
    virtual tl::expected<std::vector<uint8_t>, FileError> readFile(
        const std::filesystem::path& path) = 0;

    /**
     * @brief Checks if a file exists and is accessible
     *
     * @param path Path to check
     * @return Expected containing existence status or error
     */
    virtual tl::expected<bool, FileError> exists(
        const std::filesystem::path& path) = 0;
};

} // namespace et::infrastructure::ports
