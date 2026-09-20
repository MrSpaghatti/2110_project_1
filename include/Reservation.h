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

    // Get reservation information
    std::string getReservationId() const;
    std::string getStudentId() const;
    std::string getStudentName() const;
    std::string getResourceId() const;
    std::string getDate() const;
    std::string getStartTime() const;
    std::string getEndTime() const;

    // Display reservation information
    void print() const;

private:
    std::string reservationId_;
    std::string studentId_;
    std::string studentName_;
    std::string resourceId_;
    std::string date_;
    // "HH:MM" style, e.g. "09:00"; empty string = no time constraint
    // (seed file rows have no times, loader passes "")
    std::string startTime_;
    std::string endTime_;
};

#endif
