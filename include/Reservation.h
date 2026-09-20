/****************************************************************
 * Program Name: Reservation.h
 * Assigned Member: Hoang Trung Le
 * Student Id: 11949817
 * Description: Header file for the Reservation class. This acts as our main data model
 *              to store details about a single booking, like the reservation ID, student
 *              info, resource ID, and date. It provides getter functions to access these
 *              private attributes and a print method to display the reservation details.
 **/

#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

class Reservation {
public:
    // Default constructor
    Reservation();

    // Constructor for creating a complete reservation
    Reservation(const std::string &reservationId,
                const std::string &studentId,
                const std::string &studentName,
                const std::string &resourceId,
                const std::string &date,
                const std::string &startTime,
                const std::string &endTime);

    // TODO (2026-09-16, professor clarification D12): the full constructor
    // will gain TWO more parameters before the closing paren:
    //     const std::string &startTime,
    //     const std::string &endTime
    // Type them into BOTH the declaration here and the definition in
    // Reservation.cpp, in the SAME ORDER. The seed file
    // data/reservations.txt currently has only 5 fields (no times), so the
    // loader may pass "" for times on file rows — that's fine, an empty
    // string just means "no time constraint" for that reservation.

    // Get reservation information
    std::string getReservationId() const;
    std::string getStudentId() const;
    std::string getStudentName() const;
    std::string getResourceId() const;
    std::string getDate() const;
    std::string getStartTime() const;
    std::string getEndTime() const;

    // TODO (2026-09-16, professor clarification D12): add two getters here,
    // typed exactly like the ones above:
    //     std::string getStartTime() const;   // returns startTime_
    //     std::string getEndTime() const;     // returns endTime_
    // The professor's M1 announcement says every node in the active-reservation
    // list contains a Start time AND an End time, and that availability checks
    // compare "resource, date, and time." We need these to make the conflict
    // check (LinkedList::hasConflict) work. Until you type them, hasConflict
    // can only compare date — so this is the field that unlocks the real rule.

    // Display reservation information
    void print() const;

private:
    std::string reservationId_;
    std::string studentId_;
    std::string studentName_;
    std::string resourceId_;
    std::string date_;
    std::string startTime_;
    std::string endTime_;

    // TODO (2026-09-16, professor clarification D12): add the two time fields
    // below date_, same type as the others (std::string):
    //     std::string startTime_;   // "HH:MM" style, e.g. "09:00"
    //     std::string endTime_;     // "HH:MM" style, e.g. "10:30"
    // Store them in the SAME text format everywhere so string comparison in
    // hasConflict() is consistent. No special time type — the seed file and
    // the CELL toolchain stay simple (C++11 std::string is fine).
};

#endif
