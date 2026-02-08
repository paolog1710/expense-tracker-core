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
- **Technology:** C++20, gRPC, CMake + Ninja, Conan v2, SQLite, CLI11, spdlog, nlohmann::json, tl::expected.
- **Architecture:** Clean/Hexagonal (ports & adapters). Domain must not depend on frameworks.
- **Build/CI:** GitHub Actions (Windows + Linux), formatting gates (clang-format), unit tests via ctest.
- **Privacy:** Local storage only (SQLite). No external data exfiltration.

## 3. Context & Scope (C1)
The system includes the **Core** and **UIs** (CLI today; Desktop/Web in the future). External actors/systems: file system (statements), OCR engine for PDFs, bank portals.

```plantuml
--8<-- "arc42/diagrams/C1_Context_ExpenseTracker.puml"
```

## 4. Solution Strategy
- **API-first design:** define gRPC protofiles as public contracts for external GUI development.
- **Hexagonal/Clean Architecture:** strict dependency rule (inwards).
    - gRPC protofiles are the primary API contract;
    - GUI generates client code from protofiles, to be able to interact with the core.
    - Stubs generated from protofiles are representing the Primary Ports
    - Core logic (domain + use-cases) implements the Primary Ports and orchestrates calls to Secondary Ports to implement the business logic.
    - Secondary Ports are defined as interfaces, to interact with external systems (file system, DB, OCR engine) and allow for testability and modifiability.
    - Secondary Adapters implement the Secondary Ports and allow runtime pluggability and platform-specific implementations.
- **Domain-driven design:** protofiles are organized per domains, focusing on the use-cases and workflows to be offered to the users.
- **API Versioning:** gRPC allows for backward-compatible API evolution; protofiles are versioned in the path (e.g., v1/).
- **Persistence:** is handled in the Secondary Ports/Adapters layer, allowing fast migration to different storage solutions if needed.
- **Error handling:** tl::expected<T, Error> at boundaries (Secondary Ports); domain avoids exceptions for control flow.

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
- **Logging:** ILogger (spdlog adapter). Structured logs for parse/import steps.
- **DTO mapping:** Primary port DTOs mapped to internal Domain Model.
- **Testing:** golden tests for parsers, contract tests for ports, in-memory fakes for use-cases.
- **Security/Privacy:** local storage; no external calls; AI models run locally, least-privilege file access.

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
- PDF parsing/OCR variability;
- AI Category inference (future) might require ML—out of scope for now.

## 12. Glossary
*Statement:* Bank-exported CSV/PDF with transactions.<br>
*Transaction:* (date, payee, memo, amount, account, category).<br>
*Normalization:* Mapping bank-specific fields/format to canonical domain model.<br>
*Parser:* Adapter that implements a specific parsing logic for a bank/format.<br>
