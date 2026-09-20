#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList(){
    head_ = nullptr;
    tail_ = nullptr;
    count_ = 0;
}

LinkedList::~LinkedList(){
    ReservationNode* current = head_;
    while (current != nullptr){
        ReservationNode *next = current->next;
        delete current;
        current = next;
    }
    tail_ = nullptr;
    head_ = tail_;
}

// O(1) tail append (D11): new node goes after tail_, then tail_ advances.
void LinkedList::insert(const Reservation& r){
    ReservationNode* newNode = new ReservationNode;
    newNode->data = r;
    if (head_ == nullptr){
        head_ = newNode;
        tail_ = newNode;
    } else {
        tail_->next = newNode;
        tail_ = newNode;
    }
    count_++;
}

// walk from head_ matching reservationId; returns pointer to the node's
// data, or nullptr if the walk ends. tail_ only helps insert, not find.
Reservation* LinkedList::find(const string& reservationId){
    ReservationNode* current = head_;
    while (current != nullptr){
        if (current->data.getReservationId() == reservationId){
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}
// unlink the match; if it WAS the tail, move tail_ back to prev (or
// nullptr) so the next insert() doesn't write through a dead pointer.
bool LinkedList::remove(const string& reservationId){
    if (head_ == nullptr){
        return false;
    }
    ReservationNode* prev = nullptr;
    ReservationNode* current = head_;

    while (current != nullptr && current->data.getReservationId() != reservationId){
        prev = current;
        current = current->next;
    }

    if (current == nullptr){
        return false;
    }

    if (prev == nullptr){
        head_ = current->next;
    } else {
        prev->next = current->next;
    }

    if (tail_ == current){
        tail_ = prev;
    }

    delete current;
    count_--;
    return true;
}
// walk head -> tail, printing each reservation in list order.
void LinkedList::display() const{
    ReservationNode* current = head_;
    while (current != nullptr){
        current->data.print();
        current = current->next;
    }
    return;
}

// live per-resource count for menu 1 (D14): walk and count matches.
int LinkedList::countFor(const string& resourceId) const {
    int n = 0;
    ReservationNode* current = head_;
    while (current != nullptr) {
        if (current->data.getResourceId() == resourceId) n++;
        current = current->next;
    }
    return n;
}

// O(1): count_ maintained counter, no walk (D11).
int LinkedList::size() const{
    return count_;
}

// same resource+date with any time overlap = conflict; empty time = no constraint (D12).
bool LinkedList::hasConflict(const std::string& resourceId,const std::string& date,const std::string& startTime,const std::string& endTime) const {
    ReservationNode* current = head_;
    while (current != nullptr){
        bool sameBooking = (current->data.getResourceId() == resourceId && current->data.getDate() == date);
        bool timeClash = (startTime == "" || endTime == "" || current->data.getStartTime() == "" || current->data.getEndTime() == "") || (current->data.getStartTime() < endTime && startTime < current->data.getEndTime());
        if (sameBooking && timeClash){
            return true;
        }
        current = current->next;
    }
    return false;
}
