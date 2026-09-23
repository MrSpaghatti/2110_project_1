#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Reservation.h"
#include <functional>
#include <vector>

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

    // quickSort: sort the nodes in place (no new nodes). Takes a
    // comparator so one sort works for any key - the menu passes a
    // lambda for date, name, etc. Recursive. Average O(n log n),
    // worst O(n^2). Pivot on the tail node so sorted input doesn't
    // hit the worst case.
    void quickSort(std::function<bool(const Reservation&, const Reservation&)> before);

    // filter: walk the list, return every reservation the predicate
    // accepts. Used by findReservationsByStudent and the reports.
    // The list itself is not changed. O(n).
    std::vector<Reservation> filter(const std::function<bool(const Reservation&)>& keep) const;

private:
    struct ReservationNode { Reservation data; ReservationNode* next = nullptr; };

    ReservationNode* head_;
    ReservationNode* tail_;

    // counter for O(1) size()
    int count_;

    // partition: relink nodes around the pivot, return the new head.
    // concatenate: join two sorted chains back together.
    ReservationNode* partition(ReservationNode* head,
                               ReservationNode* pivot,
                               std::function<bool(const Reservation&, const Reservation&)> before);
    ReservationNode* concatenate(ReservationNode* left, ReservationNode* right);
};

#endif