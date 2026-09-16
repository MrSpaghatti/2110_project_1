#include "WaitingList.h"
#include <iostream>
using namespace std;
// implementation of the WaitingList class declared in WaitingList.h

// Constructor: build an empty queue
WaitingList::WaitingList() {
  front_ = nullptr;
  back_ = nullptr;
}

// Destructor: drain the queue freeing every node
WaitingList::~WaitingList() {
  Node *current = front_;
  while (current != nullptr) {
    Node *next = current->next;
    delete current;
    current = next;
}
front_ = nullptr;
  back_ = nullptr;
}

// Append a request at the back. If the queue was empty the new node
// is BOTH the front and the back.
void WaitingList::enqueue(WaitingEntry entry) {
  Node* node = new Node;
  node->data = entry;
  node->next = nullptr;
  if (back_ == nullptr) {
    front_ = node;
    back_ = node;
  } else {
    back_->next = node;
    back_ = node;
  }
}

// Pull the front request off and return it. The queue must not be empty.
// Decide how to signal an empty deque (return a placeholder / print an error).
WaitingEntry WaitingList::dequeue() {
  if (front_ == nullptr) {
    // Queue is empty, return a placeholder 
    WaitingEntry empty;
    return empty;
  }
  WaitingEntry entry = front_->data;
  Node* temp = front_;
  front_ = front_->next;
  if (front_ == nullptr) {
    back_ = nullptr; // Queue is now empty
  }
  delete temp;
  return entry;
}

// Peek at the front request without removing it.
WaitingEntry WaitingList::front() const {
  if (front_ == nullptr) {
    // Queue is empty, return a placeholder
    WaitingEntry empty;
    return empty;
  }
  return front_->data;
}

// Print every request from front to back so the order reads like the line.
void WaitingList::display() const {
    if (front_ == nullptr) {
        cout << "The waiting list is empty." << endl;
        return;
    }
    Node* current = front_;
    while (current != nullptr) {
        std::cout << "Student ID: " << current->data.studentId
                  << ", Name: " << current->data.studentName
                  << ", Resource ID: " << current->data.resourceId << std::endl;
        current = current->next;
    }
}

bool WaitingList::isEmpty() const {
  return front_ == nullptr;
}

int WaitingList::size() const {
  int count = 0;
  Node* current = front_;
  while (current != nullptr) {
    count++;
    current = current->next;
  }
  return count;
}