// LinkedList.h — ACTIVE RESERVATION LIST (append-at-tail, O(1) insert)
//
// This class stores the currently-active reservations. The spec REQUIRES
// a linked list here (proj_1.md "Linked List Implementation", line 338):
// frequent insert/remove, dynamic size.
//
// DECISION (Logan, 2026-09-15): the list tracks BOTH a head AND a tail
// node, and insert() appends at the TAIL in O(1) — the same queue-like
// insert-at-back convenience the WaitingList gets from its back_ pointer.
// Payoff: new/undone reservations land at the end, so display order matches
// creation order, and nothing ever pays an O(n) walk just to append.
//
// Per DECISIONS.md D8, the node type lives INSIDE this header:
//   struct ReservationNode { Reservation data; ReservationNode* next; };
// Only the list itself touches nodes.
//
// The class declaration goes here. Required operations (proj_1.md says the
// implementation "must support"):
//
//   LinkedList();                 // empty list (head_ == tail_ == nullptr)
//   ~LinkedList();                // delete every node (no leaks)
//   void insert(const Reservation& r);  // APPEND at tail, O(1) — the design choice
//   bool remove(const std::string& reservationId);  // delete first match, true if found
//   Reservation* find(const std::string& reservationId);  // pointer to match or nullptr
//   void display() const;         // print all reservations head -> tail
//   int size() const;             // count of nodes (O(n) walk, or track a counter)
//
// Members: ReservationNode* head_;  ReservationNode* tail_;
//
// The tail makes insert() trivial but it makes remove() bug-prone — read
// the tail-maintenance rules in src/LinkedList.cpp before you type. Rule of
// thumb: EVERY mutation of the list must leave head_ and tail_ both valid.
//
// Big-O to remember for the writeup: insert O(1) (tail pointer), remove
// O(n) for the find, display/size O(n).
//
// Guard style, same as the other headers:
//   #ifndef LINKEDLIST_H
//   #define LINKEDLIST_H
//   ... class ...
//   #endif
// Fully qualify std:: in headers (no `using namespace std;` here).