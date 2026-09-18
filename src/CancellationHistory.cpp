/***********************************************************************************
 * Program Name: CancellationHistory.cpp
 * Assigned Member: Hoang Trung Le
 * Student Id: 11949817

Decription:
// src/CancellationHistory.cpp — implement the UNDO STACK here.
//
// This is the second data structure you own, and it's the EASIEST one:
// the mechanics are WaitingList's, minus the back pointer. Don't overthink it.
//
// Suggested order:
//
// 1. Node struct + Node* top_ member (declared in the header).
//    Constructor: top_ = nullptr.
//
// 2. push(): allocate, copy the Reservation in, point it at old top_, move
//    top_. That's it. One direction, no tail to maintain.
//
// 3. pop(): if top_ == nullptr, apply your empty-stack convention (decided
//    in the header comment). Otherwise save the data, unlink top_, delete
//    the node, return the saved Reservation.
//
// 4. isEmpty(): top_ == nullptr. size(): walk-and-count.
//
// 5. display(): walk top to bottom calling r.print(). Note the order: the
//    MOST RECENT cancellation prints FIRST — that's the stack semantics the
//    rubric checks.
//
// After this compiles, the dependency chain from DECISIONS.md D7 puts you
// at ReservationManager: LinkedList + CancellationHistory + WaitingList all
// exist, so the "brain" class can start wiring them together.
#include "CancellationHistory.h"
#include <iostream>

 * *******************************************************************************
 */
#include "CancellationHistory.h"
#include <iostream>
// Constructor
CancellationHistory::CancellationHistory()
    : topNode(nullptr), count(0)
{
    // Initialize topNode to nullptr so stack starts empty
}

// Destructor
CancellationHistory::~CancellationHistory()
{
    CancellationNode* current = topNode;
    while (current != nullptr)
    {
        CancellationNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    topNode = nullptr;
}

// push
void CancellationHistory::push(const Reservation &reservation)
{
    // Create new node pointing to current topNode
    CancellationNode* newNode = new CancellationNode(reservation, topNode);

    // Update topNode to point to new node
    topNode = newNode;

    // Increment stack size
    count++;
}

// pop
bool CancellationHistory::pop()
{
    // Check whether stack is empty
    if (isEmpty())
    {
        return false;
    }

    // 1. Remember current top node
    CancellationNode* temp = topNode;

    // 2. Move top pointer to next node down
    topNode = topNode->next;

    // 3. Delete old top node
    delete temp;

    // 4. Update size
    count--;
    return true;
}

// top
Reservation* CancellationHistory::top()
{
    if (isEmpty())
    {
        return nullptr;
    }

    return &(topNode->data);
}

// isEmpty
bool CancellationHistory::isEmpty() const
{
    return topNode == nullptr;
}

// display
void CancellationHistory::display() const
{
    if (isEmpty())
    {
        std::cout << "Cancellation history is empty." << std::endl;
        return;
    }

    CancellationNode* current = topNode;
    while (current != nullptr)
    {
        current->data.print();
        current = current->next;
    }
}

// size
int CancellationHistory::size() const
{
    return count;
}