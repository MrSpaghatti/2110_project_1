# Project Decisions Log

This file is the team's memory. Every time we make a design choice that affects
how the code works, we write it down here so we don't have to re-litigate it
later — and so any team member who opens the code base knows why it looks the
way it does. If you change something that's written here, update this file in
the same commit.

---

## D1 — Where the code lives (2026-09-05)

- Repository: `MrSpaghatti/2110_project_1`, kept private for now.
- All team members get added as collaborators ("Settings → Collaborators").
- Why private: the assignment only requires the repo to exist and show our
  collaboration. Privacy keeps unrelated personal repos invisible to the class
  while still satisfying the rubric.

## D2 — How we compile (2026-09-05)

- We compile with `g++ -std=c++11` plus `-Wall -Wextra` for warnings.
- Why C++11: the assignment must run on the UNT CSE CELL machines, which are
  running an older toolchain. Sticking to C++11 means the code compiles
  there with zero surprises. No modern-only features (`auto` return types,
  structured bindings, `std::make_unique`, etc.).
- `main()` stays in its own file (`src/main.cpp`) as the assignment requires.

## D3 — Project folder layout (2026-09-05)

- Code is split into `include/` (headers) and `src/` (implementation), mirroring
  the suggested class design from the assignment.
- Build artifacts (the compiled binary, `.o` files) are gitignored so they never
  get committed.

## D4 — Resource IDs are text, not numbers (2026-09-05)

- A resource's ID (like `R101`) is stored as a **string**, not an integer.
- Why: the reservations file refers to resources by the exact text `"R101"`.
  If we turned that into the number `101`, we'd have to convert back and forth
  every time we matched a reservation to its resource — and if a future
  resource had a different prefix (`L101` for a laptop), the number `101` would
  be ambiguous. The ID is a label we match between files, not a value we do
  math on, so it stays a string.
- Availability, however, is stored as a true/false `bool` internally. We convert
  `"Available"`/`"Unavailable"` from the file into the bool when loading, and
  back into text when printing — the on-screen output always shows the words.

## D5 — The order we write and test the code (2026-09-05)

- We build the classes in dependency order: the ones that stand alone first,
  then the ones that use them.
    1. `Resource` (needs nothing)
    2. `Reservation`, `Student` (each needs nothing)
    3. `LinkedList`, `WaitingList`, `CancellationHistory` (need Reservation/Student)
    4. `ReservationManager` (needs all of the above)
    5. `ReportGenerator`, then `main`.
- After each step we compile. That way, when there's an error, it's almost
  always in the code we just wrote — not something from two files ago.
- `main` starts as a tiny placeholder (prints the title, returns 0) just to
  prove the project links and runs before we build the real menu.

## D6 — What each class is responsible for (2026-09-05)

- `Resource`: one campus resource (id, name, type, availability).
- `Reservation`: one booking (id, student id + name, resource id, date).
- `Student`: a student (id, name) — deliberately small.
- `LinkedList`: the list of active reservations. Supports insert, remove,
  find, display, size.
- `WaitingList`: a FIFO queue of students waiting for a resource.
- `CancellationHistory`: a LIFO stack of cancelled reservations for undo.
- `ReservationManager`: the "brain" that connects everything — the resource
  vector, the reservation list, the waiting list, and the cancellation stack.
- `ReportGenerator`: produces the reports the assignment asks for.

## D7 — Reservations refer to resources by ID string only (2026-09-05)

- A Reservation stores the resource's ID string (e.g. `R101`) instead of holding
  the whole Resource object or a pointer to it.
- The ReservationManager owns the list of Resources and looks up the details
  when it needs to display them. A Reservation is therefore a small, portable
  record — easy to store in the linked list and the cancellation stack.

## D8 — The linked list's node lives inside LinkedList.h (2026-09-05)

- The node type that the linked list is made of (`ReservationNode`) is defined
  inside `LinkedList.h`. Only the list itself ever manipulates nodes, so it
  doesn't need to exist anywhere else.

## Conventions with no number (recording)

- Header files keep `std::` prefixes and never use `using namespace std;` —
  the alias lives in the `.cpp` files only, to avoid polluting the namespace of
  anything that includes the header.
- Comments explain the "why" behind a line or a contract, not what the code
  obviously does. Keep them sentence-length, not one-word labels.

## D10 — Team of 3, how we share the code (2026-09-05)
- Team has 3 members. Work is split by functional area so each member owns a
  piece end-to-end.
- Each member works on their own branch and opens a pull request to `main`.
  Pull requests get reviewed before merging, which keeps `main` always in a
  compiling state.
- This gives every member commits that show up in the collaboration history
  while keeping review overhead small.
- Everyone must be able to explain their own code (academic-integrity rule).

## D11 — LinkedList tracks a tail node for O(1) appends (2026-09-15)
- The active-reservation `LinkedList` keeps both a `head_` and a `tail_`
  pointer. `insert()` appends at the **tail** in O(1), same as a queue's
  enqueue.
- Why: new and undone reservations land at the end, so display order matches
  creation order, and no insert ever pays an O(n) walk to reach the back.
- Consequence: `remove()` must maintain `tail_` when the match is the last
  node (and reset both pointers when the list empties) — every mutation
  leaves `head_` and `tail_` both valid.
- `size()` uses a maintained counter (`count_`), so it is O(1) instead of an
  O(n) walk. Cost: insert() increments, remove() decrements — keep both in
  sync; a drift here silently corrupts every size-based report.

## D12 — Milestone 1 data-structure clarification from professor (2026-09-16)

Professor clarified the required M1 structures in a class announcement:

- **ONE linked list** stores ALL active reservations across the whole system —
  NOT one list per resource. The same resource can appear in many nodes
  (different dates/times). List ops required: insert, remove, traverse,
  display.
- **A FIFO queue** manages the waiting list for a resource. Students wait for
  a specific resource; the one who has waited longest is processed first.
  The waiting list is separate from the active-reservation list.
- **A LIFO stack** tracks cancelled reservations. Undo/restore pops the MOST
  RECENT cancellation first. Also separate from the list and the queues.
- **Availability checking** traverses the single active-reservation list and
  compares resource + date + time for conflicts.

This matches the design already in place (D6, D11, and the WaitingList /
CancellationHistory contracts). Two points from the announcement are NOT yet
in the code, see open threads below.

## D13 — Availability is derived, not a flag (2026-09-19)

Root cause of the R113 bug seen 2026-09-19: main.cpp kept TWO copies of the
resource list — one loaded directly from data/resources.txt for menu
display, and the manager's copy — and loadData() flipped the manager's
Resource::available_ to false for ANY resource that appeared in
reservations.txt, regardless of date. So R113 (two seed reservations, both
on dates OTHER than today) showed "Available" in the menu yet
createReservation rejected it. Display and logic disagreed by construction.

Fix (matching D12's "availability checking traverses the active list"):

- One source of truth: the menu reads resources from the manager only
  (manager.displayResources()), not a second file load in main.cpp.
- No flag flipping in loadData: loading a reservation does NOT set the
  resource's availability bool. That flag now means only what the file says
  (display metadata), and nothing in the code flips it at runtime.
- The gate is LinkedList::hasConflict(resourceId, date, start, end):
  createReservation accepts iff no ACTIVE reservation conflicts on
  resource + date + time. Otherwise the request goes on the waiting list.
- Manager rewire (was OPEN 2026-09-19): active_ is now a LinkedList and
  history_ is a CancellationHistory stack — the graded structures are the
  real storage, not a vector. createReservation gained date, startTime,
  endTime params; menu prompts for them ("0" = no constraint).

Consequences to remember:
- The 6 resources marked "Unavailable" in data/resources.txt (R103 R106
  R109 R112 R115 R118) are unavailable because the FILE says so. Everything
  else is available for any date/time with no conflicting reservation.
- processWaitingList still hands out reservations with empty times
  ("" = no time constraint) until the waiting list gains a date field — see
  WaitingList TODO. Open thread, not blocking M1.

## Still to decide (open)

- Roster + lane ownership. (Status 2026-09-19: all lanes LANDED and merged —
    Hoang: Student.cpp, CancellationHistory.h/.cpp, FileLoader::loadReservations (PR #12)
    OJ:    ReservationManager.h/.cpp (in flight: loadData + type change on feature/load-data)
    Logan: LinkedList + hasConflict + Reservation time fields (PR #6) + ReportGenerator + main
  README team list still has placeholder name for OJ — fill before submission.)
- Documentation pass (was DEFERRED 2026-09-15): comment hygiene flagged by Copilot
  review. DONE 2026-09-19: stale "struct goes here" line fixed in LinkedList.h
  (ASan commit), D12 TODO scaffolds removed from Reservation.h, WIP comment
  removed from FileLoader.h, loadReservations doc comment added. Residual:
  WaitingList.h "add a date field" TODO is a real open question, kept in code.
- RESOLVED (2026-09-19, from D12): `Reservation` extended with
  `startTime_`/`endTime_` ("HH:MM" strings, "" = no constraint). Loader passes
  "" for file rows — seed data stays date-only. Landed in PR #6.
- RESOLVED (2026-09-19, from D12): conflict rule lives in
  `LinkedList::hasConflict(resourceId, date, startTime, endTime)` — O(n) walk,
  same resource+date overlap check, skips when any time is empty. Landed in
  PR #6. WAITING ON: manager actually calling it (see next item).
- RESOLVED (2026-09-19, spec conformance): ReservationManager now stores
  active reservations in a LinkedList and cancellation history in a
  CancellationHistory stack — the graded classes are wired in (D13).
  M1 rubric items "linked list stores active reservations" and "stack for
  cancellation tracking" are satisfied.
- RESOLVED (2026-09-19): the ReservationData/vector mismatch is gone with the
  D13 rewire — active_ is a LinkedList of Reservation, loadData inserts each
  loaded Reservation.
