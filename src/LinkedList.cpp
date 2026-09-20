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

// 4. find(): walk from head_ comparing getReservationId(). Return pointer
//    to the node's data, or nullptr if you reach the end. (Unchanged by
//    the tail — tail only helps insertion.)
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
//      - If the match IS the last node (match == tail_): move tail_ back to
//        prev (or nullptr if it was also the head). Forgetting this leaves
//        tail_ dangling, and the NEXT insert() writes through a dead pointer.
//      - If the list becomes empty after removal: head_ = tail_ = nullptr.
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
// 6. display(): walk head -> tail calling r.print() on each Reservation —
//    Reservation::print() already exists with the nice aligned format.
void LinkedList::display() const{
    ReservationNode* current = head_;
    while (current != nullptr){
        current->data.print();
        current = current->next;
    }
    return;
}

// 7. size() O(1)
int LinkedList::size() const{
    return count_;
}

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
