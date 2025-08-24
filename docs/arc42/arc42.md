# Expense Tracker System — arc42 (draft)
*Version:* 0.1

> This document follows the **arc42** template and uses **C4** model diagrams (PlantUML) to describe structure.

---

## 1. Introduction & Goals
- **Goal:** Parse bank statements (CSV/PDF) from multiple banks, **normalize** transactions, and **store** them locally for querying and analysis.
- **Key quality attributes:** Modifiability (plug new parsers), Testability (use-cases run without I/O), Reliability (deterministic parsing with golden tests), Portability (Windows/Linux), Maintainability (clean boundaries, ADRs).
- **Primary stakeholders:** Personal user (you), future contributors.

## 2. Constraints
- **Technology:** C++20, CMake + Ninja, Conan v2, SQLite, CLI11, spdlog, nlohmann::json, tl::expected.
- **Architecture:** Clean/Hexagonal (ports & adapters). Domain must not depend on frameworks.
- **Build/CI:** GitHub Actions (Windows + Linux), formatting gates (clang-format), unit tests via ctest.
- **Privacy:** Local storage only (SQLite). No external data exfiltration.

## 3. Context & Scope (C1)
The system includes the **Core** and **UIs** (CLI today; Desktop/Web in the future). External actors/systems: file system (statements), OCR engine for PDFs, bank portals.

```plantuml
--8<-- "arc42/diagrams/C1_Context_ExpenseTracker.puml"
```

## 4. Solution Strategy
- **Hexagonal/Clean Architecture:** strict dependency rule (inwards). Core defines ports; adapters implement them.
- **Façade for UIs:** IExpenseTrackerService exposes use-cases to CLI/Desktop/Web.
- **Pluggable parsers:** CSV/PDF adapters per bank behind IParser port; optional OCR adapter.
- **Persistence:** ITransactionRepository with SQLite adapter (migrations runner); DB is replaceable.
- **Error handling:** tl::expected<T, Error> at boundaries; domain avoids exceptions for control flow.
- **Deterministic time:** IClock port enables reproducible tests.
- **Configuration:** IConfig calibrated by TOML; registries define bank profiles.

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

### Scenario: Parse + Import CSV

1. CLI calls IExpenseTrackerService::parse_statement(file, bank).
2. ParseStatementUseCase loads bank profile via IConfig, calls IParser adapter (CSV for that bank).
3. Adapter returns RawTransactionDTO[]; NormalizeTransactionsService maps to Transaction (domain).
4. CLI then calls ImportTransactionsUseCase with normalized transactions.
5. Use-case writes via ITransactionRepository (SQLite adapter).

### Scenario: Parse + Import PDF
Same as above; PdfParserAdapter_* may use OcrAdapter_Tesseract to extract text.

## 7. Deployment View
- **Local machine (Windows/Linux):** single process (et-cli) linked to Core libs + adapters; SQLite file on disk.
- **Future:** a Web API container hosting the same Core; DB remains local or moves to server path. Possible change of overall architecture for scalability.

## 8. Cross-cutting Concepts
- **Logging:** ILogger (spdlog adapter). Structured logs for parse/import steps.
- **Configuration:** IConfig (TOML). Bank profiles define column/date formats, amount sign conventions.
- **DTO mapping:** Edge DTOs (RawTransactionDTO) mapped to domain Transaction.
- **Validation:** domain invariants (Money arithmetic, non-nullable fields).
- **Testing:** golden tests for parsers, contract tests for ports, in-memory fakes for use-cases.
- **Security/Privacy:** local storage; no external calls except optional OCR; least-privilege file access.
- **Observability:** (optional) counters per parser; timing via IClock.

## 9. Architecture Decisions (ADRs)



## 10. Quality Requirements

### Scenarios
- **Modifiability:** Add a new bank parser in ≤ 1 day without touching domain/use-cases.
- **Testability:** Run all use-cases with fakes in < 1s without I/O.
- **Reliability:** Golden tests prevent regressions on sample statements.
- **Performance:** Parse & import 10k rows in < 2s on a mid-range laptop.
- **Portability:** Build and test on Windows/Linux via CI.

## 11. Risks & Technical Debt
- PDF parsing/OCR variability; consider centralized text extraction helpers.
- Plugin ABI stability (if dynamic loading is introduced); prefer static linking initially.
- Category inference (future) might require ML—out of scope for now.
- Timezone/currency edge cases; define behavior in specs.

## 12. Glossary
*Statement:* Bank-exported CSV/PDF with transactions.<br>
*Transaction:* (date, payee, memo, amount, account, category).<br>
*Normalization:* Mapping bank-specific fields/format to canonical domain model.<br>
*Parser:* Adapter that implements IParser for a bank/format.<br>
*Repository:* Adapter that implements ITransactionRepository for persistence.<br>
