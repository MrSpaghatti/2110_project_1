================================================================
Campus Resource Reservation System
Class: CSCE 2110
Instructor: Bahareh Dorri
================================================================

1. OVERVIEW
----------------------------------------------------------------
A menu-based CLI app that allows students to reserve campus resources, i.e. study rooms, laptops, tutoring appointments, etc. and lets administrators manage reservations, waiting lists, and cancellations.

2. TEAM MEMBERS
----------------------------------------------------------------
- Logan Conrad
- [NAME 2]
- [NAME 3]

3. FEATURES (Milestone 1)
----------------------------------------------------------------
- Load resource and reservation data from files
- Display all resources and their availability
- Create reservations (stored in a linked list)
- Cancel reservations (moved to a cancellation history)
- Undo the most recent cancellation (stack)
- Waiting list per resource (FIFO queue)
- Display waiting lists and cancellation history

4. FILE STRUCTURE
----------------------------------------------------------------
Project1/
|-- include/
|   |-- Resource.h
|   |-- Reservation.h
|   |-- Student.h
|   |-- LinkedList.h
|   |-- WaitingList.h
|   |-- CancellationHistory.h
|   |-- ReservationManager.h
|   `-- ReportGenerator.h
|-- src/
|   |-- main.cpp
|   |-- Resource.cpp
|   |-- Reservation.cpp
|   |-- Student.cpp
|   |-- LinkedList.cpp
|   |-- WaitingList.cpp
|   |-- CancellationHistory.cpp
|   |-- ReservationManager.cpp
|   `-- ReportGenerator.cpp
|-- data/
|   |-- resources.txt
|   `-- reservations.txt
|-- README.txt
`-- Makefile

5. DATA STRUCTURES USED
----------------------------------------------------------------
- Linked list  : active reservations (frequent insert/delete)
- Queue        : waiting lists (FIFO fairness)
- Stack        : cancellation history (undo = LIFO)
- Vector       : resource inventory (fast traversal/sort)

6. COMPILE & RUN
----------------------------------------------------------------
On the CELL machines:
    g++ -std=c++11 -Wall -I include src/*.cpp -o reservation_system
    ./reservation_system

[Alternative: make && ./reservation_system]

7. USAGE
----------------------------------------------------------------
[1-2 sentences: menu order, how to create/cancel/undo a
reservation, where data files must sit (data/)]

8. INPUT FILE FORMATS
----------------------------------------------------------------
resources.txt line format:
    ResourceID|Name|Type|Availability
reservations.txt line format:
    ReservationID|StudentID|StudentName|ResourceID|Date

[Note anything your parser assumes, e.g. one record per line.]

9. KNOWN LIMITATIONS / ASSUMPTIONS
----------------------------------------------------------------
- [e.g. one waiting list per resource enforced by the queue key]
- [e.g. undo restores only the single most recent cancellation]

10. DEVELOPMENT LOG
----------------------------------------------------------------
Per grading_note.md, individual contribution is graded separately; log work
here as it is completed so each member can accurately report their part.

format: date | member | work done | verified by

2026-09-05 | [logan] | Resource.h: full class contract (fields, ctor, setter, getters, print) | compile-check
2026-09-05 | [logan] | src/Resource.cpp: default+full ctor, 4 getters, setAvailable, print() | compile-check
2026-09-06 | [logan] | src/main.cpp: placeholder main() to prove link + run; full build works | make, "./reservation_system"
2026-09-06 | [logan] | include/FileLoader.h + src/FileLoader.cpp: pipe-separated parser loading resources.txt into Resource objects (open-check, skip blanks, 4-field guard, Availability->bool) | make check

11. GITHUB REPOSITORY
----------------------------------------------------------------
    https://github.com/MrSpaghatti/2110_project_1

================================================================
All work original unless otherwise noted.
================================================================
