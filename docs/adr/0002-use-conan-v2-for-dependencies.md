# Use Conan v2 for C++ Dependency Management

*Status:* Accepted
*Date:* 2025-08-23
*Decision ID:* 0002

## Context and Problem Statement
We need a reliable, cross-platform, reproducible way to manage third-party C/C++ libraries (e.g., spdlog, CLI11, toml++, sqlite3, tl::expected, Catch2/GoogleTest) for Windows and Linux. The solution must integrate cleanly with CMake, support per-configuration/per-platform builds, enable offline/local development, and be CI-friendly with lockfiles.

## Decision Drivers
- **Reproducibility:** pin exact package revisions and build options with lockfiles.
- **Portability:** developers on Windows and Linux can bootstrap a consistent environment quickly.
- **Isolation:** avoid “system package drift” and undefined ABI mixes.
- **Ergonomics:** simple developer flow (configure → build) + transparent CMake integration.
- **Security/Compliance:** retrieve license metadata; enable SBOM generation in releases.
- **Scalability:** support future private packages (internal utilities, parsers) and binary caching.

## Considered Options
1. **Conan v2** (with CMake toolchain & lockfiles)
2. **vcpkg** (manifest mode, binary caching)
3. **CMake FetchContent** (source-embed)
4. **Git submodules** (vendor sources in repo)
5. **System package managers** (apt, pacman, vcpkg-msi, Homebrew, choco)

## Decision
Adopt **Conan v2** as the primary dependency manager. Use the **conan.cmake toolchain** in “full-declarative” mode, with **lockfiles** committed to the repo for deterministic resolution. CI will run `conan lock create` on the default branch when dependency graphs change and use the lockfile for PR builds. Enable a **binary cache** (local and/or remote) to speed up CI and dev builds.

## Consequences
**Positive**
- Reproducible builds via lockfiles & package revisions (RREV/PKGREV).
- Cleaner CMake integration with generated toolchain, minimizing bespoke Find*.cmake code.
- Per-profile customization (Release/Debug, static/shared, compiler flags) without polluting CMakeLists.
- Straightforward path to internal/private packages (e.g., in-house plugins).
- Good license metadata exposure and SBOM support (CycloneDX generator).

**Negative**
- Requires developers to install Conan v2 and understand basics (profiles, cache).
- Initial setup time for profiles/lockfiles/binary cache.
- Some libraries may require writing or tweaking recipes (though center covers most).

**Rejected Tradeoffs**
- **vcpkg:** strong choice but less flexible for per-project lockfile workflows; mixing triplets with nuanced compiler fl
