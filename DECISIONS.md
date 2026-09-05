# Project Decisions Log

Living document of design decisions for CSCE 2110 Project 1: Campus Resource
Reservation System. Update this file whenever the team makes a choice that
affects the implementation. Date each entry.

---

## D1 (2026-09-05): Repository & hosting
- Repo: `MrSpaghatti/2110_project_1` (private), default branch `main`.
- Invite all team members as collaborators. Private repo satisfies the GitHub
  rubric (repo + members + branches + commits) without exposing unrelated work.
- README shipped as `README.txt` — the assignment spec's file tree explicitly
  lists `README.txt`; graders diff the submitted zip against that tree.

## D2 (2026-09-05): Build & environment
- Compiler: `g++ -std=c++11 -Wall -Wextra -I include src/*.cpp -o reservation_system`
- Target: must compile on the UNT CSE CELL machines → C++11 only. No C++14/17
  features (`auto` returns, structured bindings, `make_unique`).
- `main()` lives in its own source file (`src/main.cpp`).

## D3 (2026-09-05): File structure
- Mirror the class design: `include/` + `src/` per class (8 headers, 9 cpps).
  More granular than the spec's minimal tree; aligns with the "Suggested
  Object-Oriented Design" section.
- Build artifacts gitignored (`reservation_system`, `*.o`).

## D4 (2026-09-05): Resource identifier stays a STRING
- `Resource::id` is `std::string` (`"R101"`), NOT an int.
- Rationale: `data/reservations.txt` references resources by the exact string
  `"R101"`. Storing an int would require a conversion every time a reservation
  is matched to its resource. The ID is a cross-file key, never used in
  arithmetic. Prefixes carry meaning (`L101` laptop vs room 101).
- Availability is a `bool` internally, mapped to/from `"Available"/"Unavailable"`
  at load and display (file text stays round-trippable).

## D5 (2026-09-05): Implementation order (dependency-driven)
1. `Resource` (nothing) → 2. `Reservation`, `Student` → 3. `LinkedList`,
   `WaitingList`, `CancellationHistory` → 4. `ReservationManager` → 5.
   `ReportGenerator`, then `main`.
- Compile after each stage; only debug the current stage's errors.
- Start `main` as a minimal "hello + return 0" to prove linking early.

## D6 (2026-09-05): Class contracts
- `Resource`: id, name, type, avail - 2 ctors, getters, setter, print.
- `Reservation`: id, studentId, studentName, resourceId, date + getters + print.
- `Student`: id, name.
- `LinkedList`: active reservations (insert, removeById, findById, displayAll,
  size) with `ReservationNode` defined in the header.
- `WaitingList`: FIFO node queue (enqueue, dequeue, peek, displayAll).
- `CancellationHistory`: LIFO stack (push, pop, peek, displayAll).
- `ReservationManager`: vector<Resource>, LinkedList, WaitingList, history;
  loadResources/loadReservations/create/cancel/undo.
- `ReportGenerator`: report methods over the manager.

## TODO / OPEN
- Does `Reservation` hold the resource ID string (lookup at display) or a
  pointer/copy of Resource? — OPEN (affects ReservationManager).
- Where does `ReservationNode` struct live? (in LinkedList.h) — OPEN.
- Team member list + branch plan (one branch per feature vs per person).
- Whether `data/` files are pipe-separated (they are, visually) & parser split
  on `|` — confirmed by file inspection when the parser lands.