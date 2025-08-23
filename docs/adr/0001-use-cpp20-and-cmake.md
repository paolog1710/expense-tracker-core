# Use C++20 and CMake

*Status:* Accepted
*Date:* 2025-08-23

## Context and Problem Statement
We need a modern C++ baseline and ubiquitous build system.

## Decision Drivers
- Portability (Windows/Linux)
- Tooling ecosystem (IDEs/CI)
- Language features (ranges, chrono, coroutines later)

## Considered Options
- C++20 + CMake
- C++23 + CMake
- CMake + Meson/Ninja variants

## Decision
Choose **C++20 + CMake**. C++20 is widely supported on MSVC/Clang/GCC; C++23 adds std::expected but we can use tl::expected for now.

## Pros and Cons
+ Broad compiler support; stable
+ Rich ecosystem; easy CI
- Lacks some C++23 std additions (workarounds needed)

## Links
- Related ADRs: 0002
