#include "CancellationHistory.h"
// src/CancellationHistory.cpp — implement the UNDO STACK here.
//
// This is the second data structure you own, and it's the EASIEST one:
// the mechanics are WaitingList's, minus the back pointer. Don't overthink it.
//
// Suggested order:
//
// 1. Node struct + Node* top_ member (declared in the header).
//    Constructor: top_ = nullptr.
//
// 2. push(): allocate, copy the Reservation in, point it at old top_, move
//    top_. That's it. One direction, no tail to maintain.
//
// 3. pop(): if top_ == nullptr, apply your empty-stack convention (decided
//    in the header comment). Otherwise save the data, unlink top_, delete
//    the node, return the saved Reservation.
//
// 4. isEmpty(): top_ == nullptr. size(): walk-and-count.
//
// 5. display(): walk top to bottom calling r.print(). Note the order: the
//    MOST RECENT cancellation prints FIRST — that's the stack semantics the
//    rubric checks.
//
// After this compiles, the dependency chain from DECISIONS.md D7 puts you
// at ReservationManager: LinkedList + CancellationHistory + WaitingList all
// exist, so the "brain" class can start wiring them together.