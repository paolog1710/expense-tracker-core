# Vision

## Purpose
Parse bank documents (CSV/PDF/…)-> normalize transactions -> store locally -> query via CLI.

## Primary users
- Me (architecture playground) now; maybe power users later.

## Non-goals
- No cloud sync, no PII upload, no GUI (for now).

## Constraints 
- C++20, portable (Win/Linux), offline-first, local SQLite, plugin parsers.

## Quality attributes (ranked)

### Correctness
*Scenario:* Given a known statement file, parsing produces a canonical JSON matching the golden file byte-for-byte.  
*Stimulus/Env:* CI on PR.  
*Response:* Test passes; diff shows no drift.

### Testability
*Scenario:* Replace SQLite repo with an in-memory fake in unit tests.  
*Response measure:* Unit test runtime < 2s for repo suite.

### Extensibility
*Scenario:* Add a new parser implementing IParser.  
*Response measure:* Total changes ≤ 300 LOC; no changes to domain; all tests green.

### Portability
*Scenario:* Build on Windows & Linux in CI.  
*Response measure:* Matrix succeeds; artifacts produced.

### Observability
*Scenario:* Enable `--log-level=debug` and capture structured logs to a file.  
*Response measure:* Logs include parse decisions and field counts.

## Success metrics
- >90% unit coverage in domain; reproducible parsing for supported banks; add-a-parser ≤ 1 day; full build & tests ≤ 5 min CI.

## High-level scope
- Commands: `parse`, `import`, `list`, `stats`.  
- Entities: Transaction, Account, Category.  
- Storage: SQLite with migrations.  
- Parsers: CSV first; bank-specific later; eventually PDF/OCR.

## Risks
- PDF/OCR variability; locale/currency edge cases; money precision.

## Policies
- Never use floating-point for money.  
- Domain is pure (no I/O).  
- All external deps behind interfaces.  
- Golden tests for parsers.