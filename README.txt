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
- Logan Conrad - [role / components]
- [NAME 2] - [role / components]
- [NAME 3] - [role / components]

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

10. GITHUB REPOSITORY
----------------------------------------------------------------
    https://github.com/MrSpaghatti/2110_project_1

================================================================
All work original unless otherwise noted.
================================================================
