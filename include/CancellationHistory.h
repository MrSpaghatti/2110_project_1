/**********************************************************************************************
 * Program name: CancellationHistory.h
 * Assigned Member: Hoang Trung Le
 * Id: 11949817
 * Description: Header file for the CancellationHistory class. I built this using a custom 
 *              linked-list stack (LIFO) so we can track cancelled reservations as they happen. 
 *              It lets us push new cancellations onto the top, pop or view the latest one, 
 *              and print out the full history from most recent to oldest.
 /**********************************************************************************************
*/
#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include "Reservation.h"

// Node used to store one cancelled reservation.
struct CancellationNode
{
    // Stored cancelled Reservation object
    Reservation data;

    // Pointer to the next CancellationNode down in the stack
    CancellationNode* next;

    // Constructor to quickly initialize a node
    CancellationNode(const Reservation& res, CancellationNode* nextNode = nullptr)
        : data(res), next(nextNode) {}
};


class CancellationHistory
{
public:

    // Constructor: Initializes the stack so it starts empty.
    CancellationHistory();

    // Destructor: Deletes all nodes currently in the stack to prevent memory leaks.
    ~CancellationHistory();

    // Push: Adds a cancelled reservation to the TOP of the stack.
    void push(const Reservation &reservation);

    // Pop: Removes the most recently cancelled reservation (TOP).
    // Returns true if successfully popped, false if stack was empty.
    bool pop();

    // Top: Looks at the most recently cancelled reservation without removing it.
    // Returns a pointer to the top Reservation, or nullptr if empty.
    Reservation* top();

    // IsEmpty: Determines whether the stack is empty.
    bool isEmpty() const;

    // Display: Displays cancellation history from TOP to BOTTOM.
    void display() const;

    // Size: Returns the number of cancelled reservations stored.
    int size() const;

private:

    // Pointer to the top node of the stack.
    CancellationNode* topNode;

    // Running count of nodes in the stack.
    int count;
};

#endif