// CancellationHistory.h — UNDO STACK (LIFO)
//
// When a reservation is cancelled it gets pushed here; undo pops the MOST
// RECENT one back out. Spec (proj_1.md line 78): "Only the most recently
// cancelled reservation may be restored." That's the whole job — a stack.
//
// Class declaration goes here. Required operations:
//
//   CancellationHistory();         // empty stack
//   ~CancellationHistory();        // free all nodes
//   void push(const Reservation& r);          // store a cancelled reservation
//   Reservation pop();             // remove+return the most recent (top)
//   bool isEmpty() const;          // true when nothing to undo
//   int size() const;              // how many cancellations are stored
//   void display() const;          // print history (rubric wants a display)
//
// Design questions to settle BEFORE you type:
//   1. What does pop() do on an EMPTY stack? Your teammate left the same
//      question open in WaitingList::dequeue(). Pick a convention and use
//      it in BOTH classes so ReservationManager only has to learn one rule.
//      (Options: return a default Reservation and rely on isEmpty(), or use
//      a bool success flag via reference param.)
//   2. Does undo even restore availability? No — think about it: popping a
//      cancellation means the reservation is active again, so the resource
//      becomes UNAVAILABLE again. That logic lives in ReservationManager
//      (menu option 4), not here. This class only stores and pops records.
//
// The node struct lives inside this header, same deal as D8 for LinkedList:
//   struct Node { Reservation data; Node* next; };
// Stack points at the TOP. Push = new node -> old top. Pop = unlink top.
//
// Big-O for the writeup: push O(1), pop O(1) — that's why undo is a stack.
//
// Guard + std:: style: same as the other headers.