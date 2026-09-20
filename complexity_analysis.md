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

Line numbers below are current as of commit 32aafc0.

Definitions used:

- n = number of active reservations
- m = number of resources
- w = number of entries in a waiting list

---

## 1. Reservation insertion — Logan

Operation: `LinkedList::insert()` — src/LinkedList.cpp, line 22.

- insert() has a complexity of O(1) because the tail_ pointer is cached and new nodes simply are appended after said tail node. So there is no need to traverse the entire list to find the end.

## 2. Reservation removal — Logan

Operation: `LinkedList::remove()` — src/LinkedList.cpp, line 52.

[Your answer: Big-O + why. Two phases: finding the node, then the
pointer surgery. Which phase dominates? Note the special case when the
removed node is the tail — the loop has to find the new last node.]

## 3. Waiting-list processing — Matthew (OJ)

Operations: `WaitingList::enqueue()` / `WaitingList::dequeue()` —
src/WaitingList.cpp, lines 26 and 41, and
`ReservationManager::processWaitingList()` — src/ReservationManager.cpp,
line 142.

[Your answer: Big-O for (a) one enqueue, (b) one dequeue, (c) one full
processWaitingList cycle. Note the queue is FIFO with front_/back_
pointers — does it ever scan the whole list?]

## 4. Undo cancellation — Hoang

Operation: `ReservationManager::undoCancellation()` —
src/ReservationManager.cpp, line 118.

[Your answer: Big-O + why. history_ is your CancellationHistory stack
(push/pop) — does popping the last entry scan anything? Undo also calls
processWaitingList() when a waiting student is promoted — does that
change the cost?]

## 5. Bonus — live availability display (extra depth) — Logan

Operation: menu option 1 display path — `ReservationManager::displayResources()`,
which calls `LinkedList::hasConflict()` (O(n) walk) once per resource row.

[Your answer: worst case here is O(m * n) — m resources, each row pays an
O(n) hasConflict walk to compute its live status word. Optional but shows
you understand the D13/D14 change: availability is derived, not stored.]