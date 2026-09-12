#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <string>

// A waiting entry: one student's request for an unavailable resource.
// The waiting list stores these and hands them out first-in, first-out.
struct WaitingEntry {
  std::string studentId;
  std::string studentName;
  std::string resourceId;
  // TODO: add a date field if the queue should also track request time
};

// First-In, First-Out queue of waiting requests (one queue per resource).
//
// Required operations (from proj_1.md):
//   enqueue   -> add a student to the waiting list
//   dequeue   -> remove the next student in line
//   display   -> show the whole waiting list
class WaitingList {
public:
  // default constructor: empty queue
  WaitingList();

  // frees every node
  ~WaitingList();

  void enqueue(WaitingEntry entry);  // add a request to the back of the line
  WaitingEntry dequeue();            // remove+return the front request
  WaitingEntry front() const;        // peek at the front without removing
  void display() const;              // print requests in FIFO order
  bool isEmpty() const;              // true when nobody is waiting
  int size() const;                  // how many requests are waiting

private:
  // one node in the queue chain
  struct Node {
    WaitingEntry data;
    Node *next;
  };

  Node *front_;  // oldest request (dequeue pulls from here)
  Node *back_;   // newest request (enqueue appends here)
};

#endif