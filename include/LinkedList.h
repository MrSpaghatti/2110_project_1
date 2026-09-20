#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Reservation.h"

class LinkedList {
public:
    //empty list
    LinkedList();

    //delete each node
    ~LinkedList();

    //insert a reservation into the list
    void insert(const Reservation& r);

    //delete first found match, returns true if found
    bool remove(const std::string& reservationId);

    //pointer to match or nullptr
    Reservation* find(const std::string& reservationId);

    //print all reservations in order
    void display() const;

    // count how many active reservations reference this resource (D14:
    // lets menu 1 show a live count per resource). O(n) walk.
    int countFor(const std::string& resourceId) const;

    // O(1) — maintained counter (DECIDED: count_ member, see below).
    // insert() ++, remove() --, ctor = 0. Keep it in sync in BOTH places.
    int size() const;

    // OJ's ReservationManager calls this in createReservation; do not rename
    // it once it's in (log in DECISIONS.md, not just chat, if it changes).
    bool hasConflict(   const std::string& resourceId,
                        const std::string& date,
                        const std::string& startTime,
                        const std::string& endTime) const;

private:
    struct ReservationNode { Reservation data; ReservationNode* next = nullptr; };

    ReservationNode* head_;
    ReservationNode* tail_;

    // counter for O(1) size()
    int count_;
};

#endif