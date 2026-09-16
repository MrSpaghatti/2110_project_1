// ReservationManager.h — THE BRAIN
//
// This is the class that connects everything. DECISIONS.md D7: "the 'brain'
// that connects everything — the resource vector, the reservation list, the
// waiting list, and the cancellation stack." Every menu option 2-6 calls a
// method on this class. It OWNS the data; main.cpp only talks to it.
//
// It owns FOUR pieces:
//   1. std::vector<Resource> resources_          (already loaded in main.cpp —
//      you'll pass it in or load it here)
//   2. LinkedList activeReservations_            (the list you just wrote)
//   3. WaitingList waitingLists_[...]            (ONE queue PER resource —
//      see design question 2)
//   4. CancellationHistory undoStack_            (the stack you just wrote)
//
// Required operations (from proj_1.md + the menu):
//
//   ReservationManager();                          // load data, build structures
//   void createReservation(...);                   // menu 2
//   void cancelReservation(const std::string& reservationId);  // menu 3
//   void undoLastCancellation();                   // menu 4
//   void displayWaitingLists() const;              // menu 5
//   void displayCancellationHistory() const;       // menu 6
//   void displayAllResources() const;              // menu 1 (already works —
//                                                  //   move the print here)
//   Reservation* findReservation(const std::string& id);        // spec: find by ID
//   void displayReservationsByStudent(const std::string& studentId) const;  // spec
//
// Design questions to settle BEFORE you type:
//
// 1. WaitingList-per-resource: how do you map "R101" -> its queue? Simplest
//    C++11 answer that matches this codebase: a std::vector<WaitingList> in
//    the SAME ORDER as resources_, and a helper `int indexOfResource(id)`
//    that walks resources_ matching getId(). Then waitingLists_[i] is the
//    queue for resources_[i]. No map needed, and the code stays explainable.
//
// 2. createReservation flow: find the resource by ID -> if available,
//    setAvailable(false) + insert into the active list. If NOT available,
//    enqueue a WaitingEntry (studentId, studentName, resourceId) into that
//    resource's queue. That's the entire reservation business rule.
//
// 3. cancelReservation flow: find in active list -> remove -> push the
//    Reservation onto the undo stack -> setAvailable(true) again. THEN the
//    open question: should the first student on that resource's waiting list
//    get the slot automatically? The spec has waiting lists but doesn't
//    explicitly demand auto-promotion. Decide, and write it in DECISIONS.md.
//
// 4. undoLastCancellation: if the stack is empty, say so. Otherwise pop,
//    re-insert into active list, setAvailable(false).
//
// Guard + std:: style: same as the other headers. Forward-declare or include
// the four owned types. You'll need <vector>.