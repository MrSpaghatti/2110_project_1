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
|   |-- FileLoader.h
|   |-- LinkedList.h
|   |-- WaitingList.h
|   |-- CancellationHistory.h
|   |-- ReservationManager.h
|   `-- ReportGenerator.h
|-- src/
|   |-- main.cpp
|   |-- FileLoader.cpp
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
Current status (Milestone 1 in progress): app builds and prints the project
title; the menu is stubbed. Resource loading (src/FileLoader.cpp) is implemented
but not yet wired into the menu. Data files must sit in data/.

8. INPUT FILE FORMATS
----------------------------------------------------------------
resources.txt line format:
    ResourceID|Name|Type|Availability
reservations.txt line format:
    ReservationID|StudentID|StudentName|ResourceID|Date

Parser assumptions: one record per line, fields split on '|', blank lines
skipped, and lines with the wrong field count are skipped with an error
printed to stderr. resources.txt Availability column maps 'Available' ->
true, anything else -> false.

9. KNOWN LIMITATIONS / ASSUMPTIONS
----------------------------------------------------------------
- Only resource data loading is implemented so far; reservations loading is
  WIP (FileLoader::loadReservations), and the menu/linked-list/queue/stack
  features are not built yet (see DEVELOPMENT LOG).
- FileLoader prints an error and returns an empty list if the data file
  cannot be opened or every line fails validation.

10. DEVELOPMENT LOG
----------------------------------------------------------------
Per grading_note.md, individual contribution is graded separately; log work
here as it is completed so each member can accurately report their part.

format: date | member | work done | verified by

2026-09-05 | [logan] | Resource.h: full class contract (fields, ctor, setter, getters, print) | compile-check
2026-09-05 | [logan] | src/Resource.cpp: default+full ctor, 4 getters, setAvailable, print() | compile-check
2026-09-06 | [logan] | src/main.cpp: placeholder main() to prove link + run; full build works | make, "./reservation_system"
2026-09-06 | [logan] | include/FileLoader.h + src/FileLoader.cpp: pipe-separated parser loading resources.txt into Resource objects (open-check, skip blanks, 4-field guard, Availability->bool) | make check
2026-09-06 | [logan] | src/main.cpp: wired FileLoader::loadResources into main; app now loads + prints all resources from data/resources.txt | make check, "./reservation_system"

11. GITHUB REPOSITORY
----------------------------------------------------------------
    https://github.com/MrSpaghatti/2110_project_1

================================================================
All work original unless otherwise noted.
================================================================
