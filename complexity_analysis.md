# Complexity Analysis — Campus Resource Reservation System

Milestone 1 | Team: Logan Conrad, Matthew Ojeh Jr., Hoang Trung Le | 2026-09-19

Short report on the operations the M1 rubric asks about. Each answer:
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
