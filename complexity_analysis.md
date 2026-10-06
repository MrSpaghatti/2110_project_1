# Complexity Analysis — Campus Resource Reservation System

Milestone 1 + Final | Team: Logan Conrad, Matthew Ojeh Jr., Hoang Trung Le | 2026-09-19

Short report on the operations the M1 and final rubrics ask about. Each answer:
Big-O in worst case + 2-3 sentences explaining _why_, citing the code.

Who fills what (each member explains their own code — grader note says
everyone must be able to explain the code they submit):

- Section 1 (insertion): Logan — done
- Section 2 (removal): Logan — you wrote LinkedList::remove, worst/best case
- Section 3 (waiting list): Matthew (OJ)
- Section 4 (undo): Hoang — you wrote CancellationHistory
- Section 5 (bonus, live display): Logan

Line numbers below are current as of commit 79e28b4.

Definitions used:

- n = number of active reservations
- m = number of resources
- w = number of entries in a waiting list

---

## 1. Reservation insertion — Logan

Operation: `LinkedList::insert()` — src/LinkedList.cpp, line 23.

- insert() has a complexity of O(1) because the tail\_ pointer is cached and new nodes simply are appended after said tail node. So there is no need to traverse the entire list to find the end.

## 2. Reservation removal — Logan

Operation: `LinkedList::remove()` — src/LinkedList.cpp, line 50.

- remove() has a complexity of O(n) because if the node it's looking for is at the end of the list, it will have to traverse the entire list of nodes to find the correct one to remove.

## 3. Waiting-list processing — Matthew (OJ)

Operations: `WaitingList::enqueue()` / `WaitingList::dequeue()` —
src/WaitingList.cpp, lines 26 and 41, and
`ReservationManager::processWaitingList()` — src/ReservationManager.cpp,
line 158.

- enqueue() has a complexity of O(1) because the back\_ pointer is cached, so a new waiting-list entry can be added directly to the end without traversing the list.

- dequeue() has a complexity of O(1) because the front\_ pointer points directly to the first entry, so removing it does not require scanning the list.

- processWaitingList() has a complexity of O(1) per call because it promotes exactly ONE waiting-list entry: one dequeue() (O(1)) followed by one LinkedList::insert() (O(1)). It is not a loop — there is no "for each entry" in the function. Across repeated calls, draining all w entries would take w calls, so the whole queue drains in O(w) total, but any single call is constant-time.

## 4. Undo cancellation — Hoang Trung Le

Operation: `ReservationManager::undoCancellation()` —
src/ReservationManager.cpp, line 127.

- undoCancellation() has a complexity of O(1) when undoing a cancellation because history\_ is a stack, so the most recent cancellation can be removed directly using pop() without scanning the stack.

- If undoing the cancellation promotes a student from the waiting list, processWaitingList() is called once. Each call is O(1) (see Section 3: one dequeue + one insert, no loop), so the worst case stays O(1) even with a promotion.

## 5. Bonus — live availability display (extra depth) — Logan

Operation: menu option 1 display path — `ReservationManager::displayResources()` (src/ReservationManager.cpp, line 43),
which calls `LinkedList::hasConflict()` (O(n) walk, src/LinkedList.cpp, line 107) once per resource row.

- displayResources() has a complexity of O(m x n) because it calls hasConflict(), and for every m resources, n steps are performed to check if it conflicts with any other reservations.

---

## 6. Search by student ID — Logan

Operation: `ReservationManager::findReservationsByStudent()` (src/ReservationManager.cpp, line ~195), which calls `LinkedList::filter()` (src/LinkedList.cpp, line ~120).

- findReservationsByStudent() has a complexity of O(n) because filter() walks the active-reservation list once from head to tail, pushing every reservation whose studentId matches the lambda predicate. The caller then uses the returned vector directly, so no extra pass is added.

## 7. Sorting resources — Logan

Operations: `ReservationManager::sortResources()` (src/ReservationManager.cpp, line ~203) and the private `quickSort()` it calls (line ~225).

- sortResources() picks a comparator lambda for the requested criteria ("name", "type", or "availability") and hands it to quickSort(). No copy is made; quickSort reorders resources_ in place.
- quickSort() has an average complexity of O(m log m) where m = number of resources: each partition pass is O(m), and the recursion splits the vector roughly in half each time (log m levels). Worst case is O(m^2) on an already-sorted vector because the pivot is always the tail element, so the partition does no real splitting. We accepted this worst case because the resource catalog is small and the code is the hand-written sort the spec requires (instead of std::sort).

## 8. Reports — Logan

Operations: `ReportGenerator::mostRequestedReport()` (src/ReportGenerator.cpp, line 31) and its private pair `quickSort()` (line 69).

- mostRequestedReport() is O(m x n): it loops over m resources and, for each one, calls LinkedList::countFor() which walks all n active reservations. It then sorts the m (resourceId, count) pairs with the same Lomuto quickSort as Section 7 — average O(m log m), worst O(m^2). The other three reports are dominated by this same m x n pattern (utilizationReport) or one O(m) pass (waitingStatsReport, which uses map::find per resource).
- waitingStatsReport() uses map::find() (O(log r), r = queues in the map) rather than operator[] because operator[] would silently create an empty WaitingList entry for every resource that never had a queued request — growing the map on a read-only report call.
