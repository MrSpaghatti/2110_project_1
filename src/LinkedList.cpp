#include "LinkedList.h"
// src/LinkedList.cpp — implement the ACTIVE RESERVATION LIST here.
//
// You already have two worked examples in this repo to mirror:
//   - WaitingList.cpp (teammate's) for the node/pointer mechanics
//   - Resource.cpp / Reservation.cpp for the style (4-space indent, brief
//     comments above each method saying WHAT it does and WHY)
//
// Suggested order (each step compiles before the next):
//
// 1. struct ReservationNode { Reservation data; ReservationNode* next; };
//    — declared inside the header per D8. The .cpp only uses it.
//
// 2. Member: ReservationNode* head_;
//    Constructor sets head_ = nullptr. Destructor walks and deletes every
//    node — copy the drain pattern from WaitingList::~WaitingList().
//
// 3. insert(): allocate a node, copy the Reservation into data, wire it in.
//    If you chose head insertion: new node -> old head, head -> new node.
//
// 4. find(): walk from head_ comparing getReservationId(). Return pointer
//    to the node's data, or nullptr if you reach the end.
//
// 5. remove(): walk keeping a "previous" pointer so you can unlink the match.
//    Three cases: empty list, match at head, match in the middle/end.
//    Delete the node AFTER you unlink it. Return true/false.
//
// 6. display(): walk and call r.print() on each Reservation — Reservation::print()
//    already exists with the nice aligned format.
//
// 7. size(): simple counter walk. (O(n) is fine — nothing hot calls this.)
//
// Pitfall to check when you run `make`: if the header declares something the
// .cpp doesn't define, the LINK step fails with "undefined reference". Every
// declared method needs a definition here once you wire this into the manager.