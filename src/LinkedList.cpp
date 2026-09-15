#include "LinkedList.h"
// src/LinkedList.cpp — implement the ACTIVE RESERVATION LIST here.
//
// You already have two worked examples in this repo to mirror:
//   - WaitingList.cpp (teammate's) for the node/pointer mechanics
//   - Resource.cpp / Reservation.cpp for the style (4-space indent, brief
//     comments above each method saying WHAT it does and WHY)
//
// DESIGN (Logan, 2026-09-15): append-at-tail via a tail_ pointer, so
// insert() is O(1) like a queue's enqueue. New and undone reservations go
// to the END of the list; display order == creation order.
//
// Suggested order (each step compiles before the next):
//
// 1. struct ReservationNode { Reservation data; ReservationNode* next; };
//    — declared inside the header per D8. The .cpp only uses it.
//
// 2. Members: ReservationNode* head_;  ReservationNode* tail_;
//    Constructor sets BOTH to nullptr. (Empty list invariant: head_ ==
//    tail_ == nullptr.) Destructor walks from head_ deleting every node —
//    copy the drain pattern from WaitingList::~WaitingList(). After the
//    drain, also set head_ = tail_ = nullptr for hygiene, even though the
//    object is dying.
//
// 3. insert(): THE tail payoff. Allocate a node, copy the Reservation in.
//      - List empty (head_ == nullptr): head_ = tail_ = newNode. This is
//        the ONLY case where insert touches head_.
//      - Otherwise: tail_->next = newNode; tail_ = newNode;
//    Four lines. O(1) every time.
//
// 4. find(): walk from head_ comparing getReservationId(). Return pointer
//    to the node's data, or nullptr if you reach the end. (Unchanged by
//    the tail — tail only helps insertion.)
//
// 5. remove(): the TRICKY one, because of tail_. Walk keeping a "previous"
//    pointer so you can unlink the match. Before you delete the node, THE
//    TWO TAIL RULES:
//      - If the match IS the last node (match == tail_): move tail_ back to
//        prev (or nullptr if it was also the head). Forgetting this leaves
//        tail_ dangling, and the NEXT insert() writes through a dead pointer.
//      - If the list becomes empty after removal: head_ = tail_ = nullptr.
//    The four classic cases: empty list / match at head / match in middle /
//    match at tail (head and tail can overlap when size == 1 — handle that
//    branch cleanly, delete AFTER unlink).
//
// 6. display(): walk head -> tail calling r.print() on each Reservation —
//    Reservation::print() already exists with the nice aligned format.
//
// 7. size(): simple counter walk. (O(n) is fine — nothing hot calls this.)
//
// Sanity test once it links: insert A, B, C -> display prints A, B, C
// (append order). remove B -> A, C. remove C (the tail!) -> A, and insert
// D -> A, D — if that last one crashes or prints garbage, you missed a
// tail_ update in remove().
//
// Pitfall to check when you run `make`: if the header declares something the
// .cpp doesn't define, the LINK step fails with "undefined reference". Every
// declared method needs a definition here once you wire this into the manager.