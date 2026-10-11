================================================================
Campus Resource Reservation System
Class: CSCE 2110
Instructor: Bahareh Dorri
================================================================

QUICK START
----------------------------------------------------------------
Build:  g++ -std=c++11 -Wall -I include src/*.cpp -o reservation_system
        (or: make)
Run:    ./reservation_system          (run from the project root; data/ must exist)
Try it:
    1) menu 1  -> view resources with live availability
    2) menu 2 -> create a reservation (student, resource, date, times)
    5,8,10    -> display waiting lists / search (by resource, reservation,
                 or student) / generate reports
   11         -> quit

1. OVERVIEW
----------------------------------------------------------------
A menu-based CLI app that allows students to reserve campus resources, i.e. study rooms, laptops, tutoring appointments, etc. and lets administrators manage reservations, waiting lists, and cancellations.

2. TEAM MEMBERS
----------------------------------------------------------------
- Logan Conrad
- Matthew Ojeh Jr.
- Hoang Trung Le

Primary contributions (see section 11 DEVELOPMENT LOG for the dated detail):

- Logan Conrad      : Resource, FileLoader, LinkedList (insert/find/remove/
                      display/size/hasConflict/quickSort/filter), main menu
                      loop, D12/D13 rewire (active_ = LinkedList, history_ =
                      CancellationHistory), ReportGenerator, sorting, and
                      merge coordination.
- Matthew Ojeh Jr.  : WaitingList (FIFO queue), ReservationManager redesign,
                      hand-written linear search (LinearSearch.h/.cpp) +
                      integration, and fixes for empty waiting list, queue
                      head-of-line blocking, and report output.
- Hoang Trung Le    : Reservation, Student, CancellationHistory (stack),
                      wiring menu create/cancel/undo/display/search, CLI input
                      hardening, and reservation-slot (date/time) validation.

3. FEATURES (Milestone 1 + Final)
----------------------------------------------------------------
- Load resource and reservation data from files
- Display all resources and their availability
- Create reservations (stored in a linked list)
- Cancel reservations (moved to a cancellation history)
- Undo the most recent cancellation (stack)
- Waiting list per resource (FIFO queue); on a cancel/undo the manager
  promotes the first waiter whose requested slot is actually free (skips a
  blocked front waiter instead of letting the whole line starve)
- Display waiting lists (prints "No waiting lists." when all queues are
  empty) and cancellation history
- Search (menu 8): find a resource by ID, a reservation by ID, and all
  reservations for a student. Backed by a hand-written LINEAR SEARCH in
  include/LinearSearch.h + src/LinearSearch.cpp
  (findResourceIndex / findReservationIndex / findReservationIndexesByStudent).
  No std::find / std::find_if / std::binary_search in the search path -- the
  traversal and comparison are our own code. Linear (not binary) because the
  inventory and active list are in file order, not sorted by ID.
- Sort: reorder resources by name/type/availability with a hand-written
  quick sort (no std::sort)
- Reports (menu 10): active reservations (with total count), resource
  utilization (per-resource bookings + % share of all bookings), most-requested
  resources, and waiting-list statistics (ReportGenerator). Report output is
  distinct from the raw menu 1 / menu 7 listings.

4. FILE STRUCTURE
----------------------------------------------------------------
Project1/
|-- include/
|   |-- Resource.h
|   |-- Reservation.h
|   |-- Student.h
|   |-- FileLoader.h
|   |-- LinkedList.h
|   |-- WaitingList.h
|   |-- CancellationHistory.h
|   |-- LinearSearch.h
|   |-- ReportGenerator.h
|   `-- ReservationManager.h
|-- src/
|   |-- main.cpp
|   |-- FileLoader.cpp
|   |-- Resource.cpp
|   |-- Reservation.cpp
|   |-- Student.cpp
|   |-- LinkedList.cpp
|   |-- WaitingList.cpp
|   |-- CancellationHistory.cpp
|   |-- LinearSearch.cpp
|   |-- ReportGenerator.cpp
|   `-- ReservationManager.cpp
|-- data/
|   |-- resources.txt
|   `-- reservations.txt
|-- DECISIONS.md          design decisions log (why the code looks like this)
|-- complexity_analysis.md  Big-O write-up for the graded operations
|-- README.txt
`-- Makefile

5. DATA STRUCTURES & ALGORITHMS USED
----------------------------------------------------------------
Structures:
- Linked list  : active reservations (frequent insert/delete)
- Queue        : waiting lists (FIFO fairness)
- Stack        : cancellation history (undo = LIFO)
- Vector       : resource inventory (fast traversal/sort)

Hand-written algorithms (no std::find / std::sort):
- Linear search (include/LinearSearch.h): findResourceIndex,
  findReservationIndex, findReservationIndexesByStudent. One O(n) walk with
  direct element access; returns the FIRST match. Backs menu 8.
- Quick sort (Lomuto partition + comparator lambdas): LinkedList::quickSort
  for reservations and ReportGenerator::quickSort for most-requested.
  Average O(n log n), worst O(n^2).
- Waiting-list promotion: processWaitingList scans the whole queue for the
  first waiter whose slot is free (not just the front) so a blocked front
  waiter cannot starve the rest. O(n) per promotion.

See DECISIONS.md for the design rationale (D1-D14) and
complexity_analysis.md for the full Big-O write-up.

6. COMPILE & RUN
----------------------------------------------------------------
On the CELL machines:
    g++ -std=c++11 -Wall -I include src/*.cpp -o reservation_system
    ./reservation_system

[Alternative: make && ./reservation_system]

7. USAGE
----------------------------------------------------------------
Current status (Milestone 1 + Final complete): full menu-driven app — load data from
files, display resources with live availability, create reservations (linked
list), cancel with undo (stack), per-resource waiting lists (FIFO queue),
display active reservations / waiting lists / cancellation history, search by
reservation/resource/student, sort resources with a hand-written quick sort,
and generate utilization/waiting reports.
Data files must sit in data/.

8. TESTING / SAMPLE RUN
----------------------------------------------------------------
Compile check (clean, no warnings):
    g++ -std=c++11 -Wall -Wextra -I include src/*.cpp -o reservation_system
Interactive smoke tests are driven by piping menu choices on stdin. Excerpt
from a run against the seed data:

    $ ./reservation_system
    Choice: 5
    No waiting lists.                      <- empty waiting list message

    Choice: 8
    --- Search ---
    1. By resource ID
    2. By reservation ID
    3. By student ID
    Choice: 1
    Enter resource ID: R101
    Resource found.                        <- hand-written linear search

    Choice: 10
    --- Reports ---
    ...
    Choice: 4
    ===== Waiting List Statistics =====
    Total: 0 students waiting

    Choice: 11
    Goodbye.

Head-of-line blocking check (R110): book 10:00-11:00 and 11:00-12:00, then
queue Cara (11:00-12:00) then Dan (10:00-11:00, behind her). Cancel the
10:00 holder: Dan is promoted even though Cara is still blocked at the front,
and Cara stays queued. (Before the fix, the front-blocked Cara starved Dan.)

9. INPUT FILE FORMATS
----------------------------------------------------------------
resources.txt line format:
    ResourceID|Name|Type|Availability
reservations.txt line format:
    ReservationID|StudentID|StudentName|ResourceID|Date

Parser assumptions: one record per line, fields split on '|', blank lines
skipped, and lines with the wrong field count are skipped with an error
printed to stderr. resources.txt Availability column maps 'Available' ->
true, anything else -> false.

10. KNOWN LIMITATIONS / ASSUMPTIONS
----------------------------------------------------------------
- Seed data (data/reservations.txt) is date-only; reservations loaded from
  file carry empty start/end times. Empty times mean "no time constraint":
  LinkedList::hasConflict skips the overlap check when any time is empty.
- ReservationManager stores active reservations in a LinkedList and
  cancellation history in a CancellationHistory stack (D13, 2026-09-19);
  both graded structures are exercised by the runtime flow.
- The create-reservation menu path collects student/name/resource plus
  date/start/end (type 0 for "no constraint"); availability is derived from
  LinkedList::hasConflict against the active list, and menu 1 reflects it
  ("Unavailable (in use right now)" when a reservation covers the current
  date/time).
- FileLoader prints an error and returns an empty list if the data file
  cannot be opened or every line fails validation.

11. DEVELOPMENT LOG
----------------------------------------------------------------
Individual contribution is graded separately per the professor's grading
note; log work here as it is completed so each member can accurately
report their part.

format: date | member | work done | verified by

2026-09-05 | [logan] | Resource.h: full class contract (fields, ctor, setter, getters, print) | compile-check
2026-09-05 | [logan] | src/Resource.cpp: default+full ctor, 4 getters, setAvailable, print() | compile-check
2026-09-06 | [logan] | src/main.cpp: placeholder main() to prove link + run; full build works | make, "./reservation_system"
2026-09-08 | [logan] | include/FileLoader.h + src/FileLoader.cpp: pipe-separated parser loading resources.txt into Resource objects (open-check, skip blanks, 4-field guard, Availability->bool) | make check
2026-09-08 | [logan] | src/main.cpp: wired FileLoader::loadResources into main; app now loads + prints all resources from data/resources.txt | make check, "./reservation_system"
2026-09-08 | [logan] | src/main.cpp: full menu loop (display all resources, standby stubs for 2-6, quit; cin.clear/ignore guards bad input like letters) | make, "./reservation_system"
2026-09-15 | [logan] | LinkedList: full implementation (ctor/dtor/insert/find/remove/display/size) with tail_ for O(1) append; O(1) count_ counter; remove() fixes tail_ on last-node match | make check, /tmp runtime harness (insert A,B,C, remove mid+tail, insert after tail, empty guards)
2026-09-12 | [Hoang Trung Le] | include/Reservation.h + src/Reservation.cpp: implemented the Reservation class with default/full constructors, getReservationId(), getStudentId(), getStudentName(), getResourceId(), getDate(), and print() | g++ -Wall, full project build
2026-09-15 | [Hoang Trung Le] | include/Student.h + src/Student.cpp: implemented the Student class with default/full constructors, getId(), getName(), and print() | g++ -Wall, full project build
2026-09-17 | [Hoang Trung Le] | include/CancellationHistory.h + src/CancellationHistory.cpp: implemented cancellation history stack with push, pop, top, isEmpty, and display operations for storing and retrieving cancelled reservations | g++ -Wall, full project build, cancellation/undo runtime test
2026-09-18 | [Hoang Trung Le] | src/main.cpp: integrated reservation loading with ReservationManager and connected menu options for creating, cancelling, displaying active reservations, searching by reservation ID, and undoing cancellations | full project build, loaded 20 reservations, runtime menu testing
2026-09-18 | [Hoang Trung Le] | include/Reservation.h, include/Student.h, include/CancellationHistory.h, src/Reservation.cpp, src/Student.cpp, src/CancellationHistory.cpp: added explanatory comments to class declarations and member functions to improve code readability | full project build
2026-09-19 | [Hoang Trung Le] | include/FileLoader.h + src/FileLoader.cpp: added loadReservations() to parse reservations.txt using pipe-separated fields and create Reservation objects from ReservationID, StudentID, StudentName, ResourceID, and Date | g++ -Wall, full project build, loaded 20 reservations
2026-09-19 | [logan] | LinkedList::hasConflict(resourceId, date, startTime, endTime): O(n) walk, same resource+date test, time-overlap check, skips check when any time is empty ("" = no constraint) | make check, /tmp hasconflict harness (overlap -> TRUE, diff date -> FALSE)
2026-09-19 | [logan] | Reservation: added D12 time fields startTime_/endTime_ ("HH:MM" style, "" = no constraint), 7-param full ctor, getStartTime()/getEndTime() | make check
2026-09-19 | [logan] | src/main.cpp: wired menu cases 2-6 to ReservationManager (create/cancel/undo/search/display) | make check, full build
2026-09-19 | [logan] | FileLoader.h renamed loadReservations doc comment + dropped WIP marker; DECISIONS.md consolidated (resolved D12 threads, roster status); README roster completed | make check
2026-09-19 | [logan] | Merge-chain coordination: test-merged teammate branches before merging (PRs #6/#12/#13/#14 all green), drafted the ReservationData->vector<Reservation> refactor brief for OJ, cleaned stray roster line on feature/load-data | test merges + make check
2026-09-17 | [matthew] | WaitingList: full FIFO queue implementation (ctor/dtor/enqueue/dequeue/front/display/isEmpty/size) with front_/back_ pointers; handles empty enqueue (sets both ends) and last-item dequeue (clears back_) | g++ -Wall, runtime harness (enqueue A,B,C, dequeue order, empty guards)
2026-09-17 | [matthew] | ReservationManager: redesigned without LinkedList/Reservation deps; stores ReservationData struct in vectors (active_/history_) + map<resourceId, WaitingList>; implemented create/cancel/undo/processWaitingList/find/search/sort w/ merge conflict resolution | g++ -Wall, full project syntax check
2026-09-17 | [matthew] | Set up local MinGW (g++ 16.1.0) toolchain on Windows; project compiles and links locally; pushed commits to origin/main after rebasing onto teammate work | build + run, git push
2026-09-19 | [matthew] | ReservationManager refactor: rebased feature/load-data onto main; deleted ReservationData struct, active_/history_ are now std::vector<Reservation>; loadData and menu ops updated to Reservation getters (getReservationId, getStudentId, getStudentName, getResourceId, getDate); isAvailable() marking kept | make check, full build + smoke test
2026-09-19 | [logan] | D13 root-cause + rewire (PR #16): diagnosed R113 bug (menu showed Available but createReservation rejected) as TWO copies of the resource list in main + loadData flag-flipping every reserved resource regardless of date. Rewired ReservationManager: active_ = LinkedList (graded structure), history_ = CancellationHistory stack (graded structure); createReservation now takes date/startTime/endTime and gates on LinkedList::hasConflict(resourceId, date, start, end) before accepting — loadData no longer flips Resource availability flags, availability is derived from the active list | make check, E2E smoke (R113 bookable 09/19, rejected 09/21 conflict, cancel/undo OK)
2026-09-19 | [logan] | DECISIONS.md: recorded D13 (availability derived, not a flag), resolved the spec-conformance thread (graded LinkedList/stack now exercised) and the ReservationData/vector type-mismatch thread | git log, doc review
2026-09-19 | [logan] | src/main.cpp: added menu option 7 "Display active reservations" (manager.displayActiveReservations) so reservation IDs are visible before cancelling; Quit moved to 8 (PR #17) | make check, E2E (create -> view -> cancel by shown ID)
2026-09-19 | [logan] | D14 live display, part 1 (PR #18): LinkedList::countFor() + Resource::print(activeCount) — menu 1 now shows "(N active reservations)" per resource, updating on book/cancel. Reservation IDs are now numeric and continue the seed sequence (321, 322, ...) via nextReservationId_ instead of "RES"+size, which reused IDs after a cancellation shrank the list | make check, E2E (R113 count 2->3 on book, cancel by 321)
2026-09-19 | [logan] | D14 live display, part 2 (PR #19): menu 1 status word is live — displayResources computes hasConflict(resourceId, today, now, now) each refresh, so a resource with a reservation covering the current time shows "Unavailable (in use right now)". File "Unavailable" (equipment out of service) still wins; date-gated so other-day seeds don't false-positive | make check, E2E (R113 12:00-24:00 today -> in-use now)
2026-09-20 | [logan] | Availability gate + waiting-list slot (R112 fix): createReservation routes file-marked-Unavailable resources to the waiting list instead of accepting an active booking; WaitingEntry gained date/startTime/endTime so a promoted student keeps their requested slot (processWaitingList no longer books empty times). Completed OJ's complexity_analysis.md §3 + fixed stale "menu stubbed" README claim | make check, 3 smoke runs (R112 queues, R101 conflict queues, cancel 301 promotes with 09/15/2026)
2026-10-06 | [logan] | ReportGenerator: implemented all four final-submission reports (active reservations, resource utilization, most-requested with hand-written quick sort, waiting-list stats) + fixed constructor reference-member init | make check, harness run (R101 2 active; sort descending by count)
2026-10-06 | [logan] | Sorting: replaced std::sort in sortResources with a private hand-written quick sort (Lomuto partition, comparator lambda) so the final-submission spec's "implement the sort ourselves" is met | make check, sort harness (resources reorder A-Z by name, PASS)
2026-10-06 | [logan] | Searching: LinkedList::filter (predicate walk) + findReservationsByStudent (lambda delegation), closing the last declared-but-empty final-submission method | make check, find harness (student 1016 -> 1 reservation, absent id -> 0, PASS)
2026-10-07 | [Hoang Trung Le] | Reported CELL/Linux compile failure in displayResources() caused by localtime_r portability and FIFO waiting-list conflict fix  
2026-10-07 | [Hoang Trung Le] | Requested CLI input hardening in main.cpp: line-based input, strict menu-choice parsing, clean EOF exit, and clear unknown-resource handling  
2026-10-07 | [Hoang Trung Le] | Follow-up review of main.cpp input-hardening revision; requested regression checks for alphabetic and malformed menu choices, submenu recovery, end-of-input, unknown resource IDs, and valid reservation creation 
2026-10-07 | [Hoang Trung Le] | Added reservation-slot validation for calendar dates and paired 24-hour times; rejects malformed, reversed, and incomplete time ranges before they can be booked or queued  
2026-10-11 | [matthew] | Searching: implemented hand-written linear search (include/LinearSearch.h + src/LinearSearch.cpp: findResourceIndex, findReservationIndex, findReservationIndexesByStudent) and integrated it into ReservationManager (findResource, findReservation, findReservationsByStudent) so menu 8 searches run through our own algorithm, not std::find | g++ -std=c++11 -Wall -Wextra build clean; smoke runs (search R101 -> found, reservation 301 -> found, student 1001 -> 1 hit, unknown id -> not found)
2026-10-11 | [matthew] | Fixes: (1) displayWaitingLists prints "No waiting lists." when all queues empty; (2) processWaitingList scans the whole queue for the first free slot (head-of-line blocking fix) instead of only the front; (3) Reports now give real report output (active-reservations total summary; utilization shows booking share %) so submenu 10 no longer duplicates menu 7 / menu 1 | g++ -std=c++11 -Wall -Wextra build clean; smoke runs (menu 5 empty -> "No waiting lists."; R110 queue: cancel 10:00 holder while 11:00 waiter still blocks -> 10:00 waiter promoted, 11:00 waiter stays queued; reports 1/2 show summaries)
2026-10-11 | [Hoang Trung Le] | ReservationManager::undoCancellation: reject restoration when the cancelled reservation's slot now conflicts with an active reservation, preserving cancellation history | conflict regression test
2026-10-11 | [Hoang Trung Le] | ReservationManager::createReservation: derive bookability from active slot conflicts instead of the resource file availability flag | unavailable-resource booking test
2026-10-11 | [Hoang Trung Le] | src/main.cpp: stop startup with an error when loadData() cannot load resources | missing/empty resources-file test
12. GITHUB REPOSITORY
----------------------------------------------------------------
    https://github.com/MrSpaghatti/2110_project_1

================================================================
All work original unless otherwise noted.
================================================================
