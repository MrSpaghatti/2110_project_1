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
                const std::string &date);

    // Get reservation information
    std::string getReservationId() const;
    std::string getStudentId() const;
    std::string getStudentName() const;
    std::string getResourceId() const;
    std::string getDate() const;

    // Display reservation information
    void print() const;

private:
    std::string reservationId_;
    std::string studentId_;
    std::string studentName_;
    std::string resourceId_;
    std::string date_;
};

#endif