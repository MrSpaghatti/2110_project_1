// LinkedList.h — ACTIVE RESERVATION LIST
//
// This class stores the currently-active reservations. The spec REQUIRES
// a linked list here (proj_1.md "Linked List Implementation", line 338):
// frequent insert/remove, dynamic size.
//
// Per DECISIONS.md D8, the node type lives INSIDE this header:
//   struct ReservationNode { Reservation data; ReservationNode* next; };
// Only the list itself touches nodes.
//
// The class declaration goes here. Required operations (proj_1.md says the
// implementation "must support"):
//
//   LinkedList();                       // empty list
//   ~LinkedList();                      // delete every node (no leaks)
//   void insert(const Reservation& r);  // add a reservation to the list
//   bool remove(const std::string& reservationId);  // delete first match, true if found
//   Reservation* find(const std::string& reservationId);  // pointer to match or nullptr
//   void display() const;               // print all reservations in order
//   int size() const;                   // count of nodes (O(n) walk, or track a counter)
//
// Design questions to settle BEFORE you type:
//   1. Where does insert() put new nodes — head or tail? (Head is O(1).
//      Tail keeps display order matching creation order but costs an O(n)
//      walk unless you also keep a tail pointer.)
//   2. find() returns a pointer so the caller can read fields. For the
//      manager to MODIFY a found node later, a pointer (not a copy) is
//      the right shape. Do NOT return by value here.
//   3. remove() takes the ID string, matching the undo flow: the stack pops
//      a Reservation, then the manager calls remove(thatReservation.getReservationId()).
//
// Big-O to remember for the writeup: insert O(1) at head, find/remove O(n),
// display O(n), size O(n) without a counter.
//
// Guard style, same as the other headers:
//   #ifndef LINKEDLIST_H
//   #define LINKEDLIST_H
//   ... class ...
//   #endif
// Fully qualify std:: in headers (no `using namespace std;` here).