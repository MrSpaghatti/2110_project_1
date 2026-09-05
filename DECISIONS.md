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

## D9 — Zed formatting disabled for C++ (2026-09-05)
- Added a `C++` override in `~/.config/zed/settings.json` setting
  `format_on_save: "off"`.
- Why: the default clang-format (LLVM style) rewrote our header into ugly
  break-before-`{` forms (e.g. `void` on one line, `setAvailable` on the next).
  We keep our own readable formatting instead. Team members may use their own
  IDE's formatter, but they should not commit clang-format's LLVM default style.

## Conventions with no number (recording)
- Header files keep `std::` prefixes and never use `using namespace std;` —
  the alias lives in the `.cpp` files only, to avoid polluting the namespace of
  anything that includes the header.
- Comments explain the "why" behind a line or a contract, not what the code
  obviously does. Keep them sentence-length, not one-word labels.

## Still to decide (open)
- Who exactly is on the team and how we split the work — one branch per feature
  vs. one per person. (Need the team roster.)
- The file parser: the data files look pipe-separated (`R101|Study Room
  101|Study Room|Available`); confirm the split character when the loader is
  written.