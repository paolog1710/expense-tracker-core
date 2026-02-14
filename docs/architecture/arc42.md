# Expense Tracker System — arc42 (draft)
*Version:* 0.1

> This document follows the **arc42** template and uses **C4** model diagrams (PlantUML) to describe structure.

---

## 1. Introduction & Goals
- **Goals:**
    - **Functional:**
        - Deliver a flexible system to track the expenses and net-worth of an individual, with AI-assisted insights.
        - Parse bank and broker statements automatically, allowing manual corrections and adjustments.
        - Guarantee data privacy by keeping all information and processing local.
        - Show statistics about expenses on a desired time period, making use of a customized categorization.
        - Show the net-worth evolution.
    - **Non-functional:**
        - Experiment with Software Architecture principles, best practices and processes.
        - Experiment with Hexagonal architecture.
        - Experiment a contract-first approach using gRPC.
        - Experiment with AI for the software development.
        - Experiment with local AI models

- **Key quality attributes:**
    - Modifiability (plug new parsers),
    - Confidentiality (local storage only, AI models run locally),
    - Testability (use-cases run without I/O),
    - Reliability (deterministic parsing with golden tests),
    - Portability (Windows/Linux),
    - Maintainability (clean boundaries, contract-first approach, ADRs).
- **Primary stakeholders:** Personal user (you), future contributors.

## 2. Constraints
- **Technology:** gRPC for API contracts; C++20 for core logic; SQLite for local storage; spdlog for logging; tl::expected for error handling.
- **Tooling:** CMake + Conan for build and dependency management; GitHub Actions for CI; PlantUML for diagrams; GitHub Copilot for AI assisted development.
- **Architecture:** Clean/Hexagonal (ports & adapters). Domain must not depend on frameworks.
- **Build/CI:** GitHub Actions (Windows + Linux), formatting gates (clang-format), unit tests via ctest.
- **Privacy:** Local storage only (SQLite). No external data exfiltration.

## 3. Context & Scope (C1)

```plantuml
--8<-- "arc42/diagrams/C1_Context_ExpenseTracker.puml"
```

## 4. Solution Strategy
- **API-first design:** define gRPC protofiles as public contracts for external GUI development.
- **GUI/Core separation:** GUI is a separate process that interacts with the Core via gRPC, allowing for different frontends (desktop, web, mobile) and different technologies without changing the core logic;
- **Hexagonal/Clean Architecture:**
    - gRPC protofiles are the primary API contract;
    - GUI generates client code from protofiles, to be able to interact with the core;
    - Stubs generated from protofiles are representing the Primary Ports;
    - Core logic (domain + use-cases) implements the Primary Ports and orchestrates calls to Secondary Ports to implement the business logic;
    - Secondary Ports are defined as interfaces, to interact with external systems (file system, DB, OCR engine) and allow for testability and modifiability;
    - Secondary Adapters implement the Secondary Ports and allow runtime pluggability and platform-specific implementations;
- **Domain-driven design:** protofiles are organized per domains, focusing on the use-cases and workflows to be offered to the users;
- **API Versioning:** gRPC allows for backward-compatible API evolution; protofiles are versioned in the path (e.g., v1/);
- **Interaction with external systems:** modeled in the Secondary Ports and implemented in the Secondary Adapters, allowing fast migration to different technologies if needed (e.g. Persistence, Parsing, Categorization, Logging);
- **Logging:** Any major event (e.g., statement parsed, transaction normalized, category assigned) is logged with spdlog, allowing for troubleshooting and usage analytics without compromising user data privacy; The logging system is designed to be pluggable, allowing for different logging backends or formats if needed;
Logging is abstracted behind a Secondary Port, allowing for testability and modifiability without coupling the domain logic to a specific logging library;
No public API is offered for logging, as it's an internal concern; logs are stored locally and can be accessed by the user for troubleshooting or analytics purposes, but are not exposed externally by default;
- **Error handling:** tl::expected<T, Error> at boundaries (Secondary Ports); domain avoids exceptions for control flow;
- **Folder structure:** organized according to the principles stated above. Here is a high-level overview of the folder structure:

```
root
│   README.md
│   LICENSE
│   CMakeLists.txt
│   CMakePresets.json
│   conanfile.py
├───build                            # out-of-source build artifacts
│   ├───Debug
│   │   └───...
│   └───... (other build artifacts)
├───cmake                                       # CMake helper files
│   └───...
├───conan
│   └───profiles                                # Conan profiles for different platforms and configurations
│       ├───windows-msvc-release
│       └───...
├───docs                                        # Architectural documentation, architecture decision records, diagrams, etc.
│   ├───adr
│   ├───architecture
│   │   └───arc42.md                            # main architectural documentation following the arc42 template
│   └───diagrams                                # diagrams in PlantUML format (C4 and others)
│       └───C1_Context_ExpenseTracker.puml
├───source
│   ├───gui.python.grpc                         # separate process, interacts with core via gRPC
│   ├───system.root                             # entry point, initializes the system and starts the gRPC server
│   ├───protofiles                              # gRPC protofiles defining the API contract
│   │   ├───<domain>                            # protofiles organized by domain (and eventually sub-domains)
│   │   │   ├───v1                              # versioned API for backward compatibility and evolution
│   │   │   │   ├───proto_file.proto
│   │   │   │   └───... (other protofiles)
│   │   │   └───... (other versions)
│   │   └───...
│   ├───apps                                    # implements the Primary Ports defined by protofiles, orchestrates domain logic and calls to Secondary Infra Ports
│   │   ├───<domain>                            # application logic organized by domain, it follows the structure of the protofiles, just omitting the versioning
│   │   │   ├───include
│   │   │   │   └───apps/<domain>/<appImplementation>.hpp # header file for the application layer, different version differs in namespace
│   │   │   ├───src
│   │   │   │   └───<appImplementation>.cpp
│   │   │   └───CMakeLists.txt                  # build file for the application layer of the domain, of type STATIC or SHARED library depending on the case
│   │   └───...
│   ├───domain.model                            # domain entities, value objects, domain services, use-cases; no dependencies on frameworks or external systems
│
│   ├───infra.ports                             # Secondary Ports (interfaces) for interacting with external systems (file system, DB, OCR, logging)
│   │   ├───<domain>                            # application logic organized by domain, it follows the structure of the protofiles
│   │   │   ├───include
│   │   │   └───CMakeLists.txt                  # build file for the infra ports of the domain, of type INTERFACE
│   │   └───...
│   └───infra.adapters                          # Secondary Adapters implementing Secondary Ports, allowing pluggable implementations and platform-specific code
│       ├───<domain>                            # infra adapters organized by domain/sub-domain, optionally mock as additional sub-domain for testing purposes
│       │   ├───include
│       │   ├───src
│       │   └───CMakeLists.txt                  # build file for the infra adapters, of type STATIC or SHARED library depending on the case
│       └───...
├───.github                                     # GitHub config files, including CI pipeline definitions and AI-assisted context development configuration
│   ├───workflows
│   │   └───ci.yml                              # CI pipeline definition, including build and test steps for Windows and Linux

TODO specify AI context files

```



## 5. Building Block View

### Container Diagram (C2)

```plantuml
--8<-- "arc42/diagrams/C2_Containers_ExpenseTracker.puml"
```

### Component Diagram (C3)

**Application Core**

```plantuml
--8<-- "arc42/diagrams/C3_Components_ApplicationCore.puml"
```

## 6. Runtime View
TODO

## 7. Deployment View
TODO

## 8. Cross-cutting Concepts
TODO

## 9. Architecture Decisions (ADRs)
TODO

## 10. Quality Requirements

### Scenarios
- **Modifiability:** Add a new bank parser in ≤ 1 day without touching domain/use-cases.
- **Testability:** Run all use-cases with fakes in < 1s without I/O.
- **Reliability:** Golden tests prevent regressions on sample statements.
- **Performance:** Parse & import 10k rows in < 2s on a mid-range laptop.
- **Portability:** Build and test on Windows/Linux via CI.

## 11. Risks & Technical Debt
TODO

## 12. Glossary
*Statement:* Bank-exported CSV/PDF with transactions.<br>
*Transaction:* (date, payee, memo, amount, account, category).<br>
*Normalization:* Mapping bank-specific fields/format to canonical domain model.<br>
*Parser:* Adapter that implements a specific parsing logic for a bank/format.<br>
