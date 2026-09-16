#include "ReservationManager.h"
// src/ReservationManager.cpp — implement THE BRAIN here.
//
// This is the biggest file in the project, but it's mostly GLUE: it calls
// methods on the four structures you and your teammates already wrote. If
// you find yourself writing a loop over linked-list nodes here, stop —
// that logic belongs in LinkedList. The manager delegates.
//
// Suggested order:
//
// 1. Constructor: load data/resources.txt and data/reservations.txt into
//    the member structures. FileLoader::loadResources() already exists
//    (returns vector<Resource>). You'll write the reservations load (or
//    add a loadReservations() to FileLoader — your call, keep it consistent).
//    Stub the four members to empty first; get it COMPILING before you wire
//    file loading.
//
// 2. indexOfResource(id): walk resources_, return index or -1. This one
//    helper makes create/cancel/display clean everywhere.
//
// 3. displayAllResources(): just iterate resources_ and call print(). This
//    is what menu option 1 currently does inline in main.cpp — move it here.
//
// 4. createReservation(...): the availability check from the header design.
//    Print a clear message for both outcomes (created / queued-waiting).
//
// 5. cancelReservation(id): find + remove + push + flip availability.
//    Handle "not found" with a message instead of crashing.
//
// 6. undoLastCancellation(): pop + re-insert + flip back. Empty stack ->
//    "Nothing to undo."
//
// 7. displayWaitingLists() / displayCancellationHistory(): call the
//    .display() methods you wrote. If a queue is empty, WaitingList::display
//    already prints "The waiting list is empty." — good enough.
//
// 8. Reservations-by-student: walk the active list, print matches. This is
//    the traversal from the spec ("Finding reservations associated with a
//    specific student").
//
// Compile after every step: `make check` (syntax) then `make` (link). The
// linker is your friend here — an undefined reference tells you exactly which
// method the manager calls that doesn't exist yet. Write them in that order,
// and you'll never see a wall of errors at once.