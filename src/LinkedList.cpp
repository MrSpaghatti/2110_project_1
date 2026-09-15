#include "LinkedList.h"
#include <cstddef>
#include <optional>
using namespace std;

LinkedList::LinkedList(){
    head_ = nullptr;
    tail_ = nullptr;
    count_ = 0;
}

LinkedList::~LinkedList(){
    ReservationNode *current = head_;
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
    while (ReservationNode* current != nullptr){
        if (current->data.getReservationId() == reservationId){
            return &current->data;
        }
        if (current->next == nullptr){
            return nullptr;
        }
        current = current->next;
    }
}
// 5. remove(): the TRICKY one, because of tail_. Walk keeping a "previous"
//    pointer so you can unlink the match. Before you delete the node, THE
//    TWO TAIL RULES:
//      - If the match IS the last node (match == tail_): move tail_ back to
//        prev (or nullptr if it was also the head). Forgetting this leaves
//        tail_ dangling, and the NEXT insert() writes through a dead pointer.
//      - If the list becomes empty after removal: head_ = tail_ = nullptr.
//    The four classic cases: empty list / match at head / match in middle /
//    match at tail (head and tail can overlap when size == 1 — handle that
//    branch cleanly, delete AFTER unlink).
bool LinkedList::remove(const string& reservationId){

}
// 6. display(): walk head -> tail calling r.print() on each Reservation —
//    Reservation::print() already exists with the nice aligned format.
//
// 7. size(): simple counter walk. (O(n) is fine — nothing hot calls this.)
//
// Sanity test once it links: insert A, B, C -> display prints A, B, C
// (append order). remove B -> A, C. remove C (the tail!) -> A, and insert
// D -> A, D — if that last one crashes or prints garbage, you missed a
// tail_ update in remove().
//
// Pitfall to check when you run `make`: if the header declares something the
// .cpp doesn't define, the LINK step fails with "undefined reference". Every
// declared method needs a definition here once you wire this into the manager.
