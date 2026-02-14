# Expense Tracker Core

Set of core libraries implementing a basic expense tracker system.

![CI](https://github.com/paolog1710/expense-tracker-core/actions/workflows/ci.yml/badge.svg)

## Features
- Parse bank statement files and normalize transactions.
- Store data locally in SQLite for offline use.
- Manage categories and assign them to transactions.
- Create statistics and reports based on transaction data.

## Getting Started

### Prerequisites
- C++20 compatible compiler (GCC, Clang, or MSVC).
- [Conan](https://conan.io) package manager.
- [CMake](https://cmake.org) >= 3.21 and [Ninja](https://ninja-build.org).

### Install Conan profiles
```bash
conan config install conan/
```

### Install dependencies
```bash
conan install . -pr windows-msvc-release --build=missing
```

### Configure & build
```bash
cmake --preset win-release
cmake --build --preset win-release
```

### Run tests
```bash
ctest --preset win-release
```

Additional presets are available for Release and Windows builds (see `CMakePresets.json`).

## Documentation
- [Project vision](docs/vision.md)
- Architecture decision records in [docs/adr](docs/adr)

## License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.

## Contributing

Pull requests are welcome. Code owner review is mandatory.
