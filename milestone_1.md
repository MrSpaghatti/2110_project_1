# Milestone 1 – Core System Development
## Objectives

Develop the core functionality of the Campus Resource Reservation System and establish the team's collaboration workflow.

By the end of this milestone, the system should support resource management, reservations, waiting lists, cancellation tracking, and team collaboration through GitHub.

##Required Features

###Resource Management

The system shall:
- Load resource information from a file.
- Store resource information.
- Display all resources.
- Display resource availability.

### Reservation Management

The system shall:
- Create reservations.
- Cancel reservations.
-  Display active reservations.
- Validate reservation requests.

### Linked List Implementation

A linked list must be used to store active reservations.

The implementation must support:
- Insert reservation
- Remove reservation
- Traverse reservation records
- Display reservation information

### Waiting List Management

A queue must be used for waiting lists.

The implementation must support:
- Add student to waiting list
- Remove student from waiting list
- Display waiting list

### Cancellation History

A stack must be used for cancellation tracking.

The implementation must support:
- Store cancelled reservations
- Restore the most recently cancelled reservation
- Display cancellation history

### Complexity Analysis

Provide a short report discussing:
- Reservation insertion complexity
- Reservation removal complexity
- Waiting-list processing complexity
- Undo cancellation complexity

Include Big-O notation and brief explanations.

### GitHub Collaboration

After the Project Management module, teams must:
- Create a GitHub repository
- Add all team members
- Maintain project code in the repository
- Use meaningful commit messages
- Create and merge at least one feature branch

## Deliverables

Submit a zip file containing following files:
- Source code
- Header files
- README
- Complexity analysis document
- GitHub repository URL

The README, source code, and header files should match those that we find in your GitHub code repository. 

## Testing Expectations

Teams should demonstrate:
- File input works correctly
- Reservations can be created
- Reservations can be cancelled
- Waiting lists function correctly
- Undo functionality works correctly
- Invalid input is handled properly

Your project must compile and run successfully on the UNT CSE CELL machines before submission.
You may develop your project on your personal computer or another development environment, but you are responsible for verifying that your final code compiles and runs correctly on CELL.
Milestone 1 Rubric (100 Points)

## Milestone 1 Rubric (100 Points)

Resource Management Functionality - 15

Reservation Functionality - 20

Linked List Implementation - 20

Queue Implementation - 15

Stack Implementation - 15

Complexity Analysis - 5

GitHub Collaboration - 5

Documentation and Code Quality - 5
