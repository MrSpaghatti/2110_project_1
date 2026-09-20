/**
 * Program Name: Reservation.cpp
 * Assigned Member: Hoang Trung Le
 * Student Id: 11949817
 * Description: Implements the member functions for the Reservation class. It sets up
 *              both constructors to initialize member variables, provides getter methods
 *              so other parts of the program can access private reservation data, and
 *              includes a print function to output formatted details to the console.
 */

#include "Reservation.h"
#include <iostream>

using namespace std;

// Default constructor:
// Initializes every reservation field to an empty string so that the object
// starts in a known state before actual reservation data is assigned.
Reservation::Reservation()
    : reservationId_(""),
      studentId_(""),
      studentName_(""),
      resourceId_(""),
      date_(""),
      startTime_(""),
      endTime_("")
{
}

// Full constructor:
// Initializes one Reservation object with all information needed to represent
// a student's booking. The values are received from the caller, such as a file
// loader or ReservationManager.
Reservation::Reservation(const string &reservationId,
                         const string &studentId,
                         const string &studentName,
                         const string &resourceId,
                         const string &date,
                         const string &startTime,
                         const string &endTime)
    : reservationId_(reservationId),
      studentId_(studentId),
      studentName_(studentName),
      resourceId_(resourceId),
      date_(date),
      startTime_(startTime),
      endTime_(endTime)
{
}

// Getter for the reservation ID:
// Returns the unique ID used to identify this reservation when searching,
// cancelling, or checking for duplicate reservations.
string Reservation::getReservationId() const
{
    return reservationId_;
}

// Getter for the student ID:
// Returns the ID of the student who made this reservation.
string Reservation::getStudentId() const
{
    return studentId_;
}

// Getter for the student name:
// Returns the name stored with this reservation for display purposes.
string Reservation::getStudentName() const
{
    return studentName_;
}

// Getter for the resource ID:
// Returns the ID of the resource associated with this reservation.
// ReservationManager can use this ID to find and update the corresponding
// resource's availability.
string Reservation::getResourceId() const
{
    return resourceId_;
}

// Getter for the reservation date:
// Returns the date stored for this reservation.
string Reservation::getDate() const
{
    return date_;
}


string Reservation::getStartTime() const {
    return startTime_;
}

string Reservation::getEndTime() const {
    return endTime_;
}

// Display method:
// Prints all reservation fields in a readable format. The order matches the
// fields used in reservations.txt so that the reservation information is easy
// to verify when testing the program.
void Reservation::print() const
{
    cout << "Reservation ID : " << reservationId_ << endl
         << "Student ID     : " << studentId_ << endl
         << "Student Name   : " << studentName_ << endl
         << "Resource ID    : " << resourceId_ << endl
         << "Date           : " << date_ << endl
         << "Start Time     : " << startTime_ << endl
         << "End Time       : " << endTime_ << endl
         << "----------------------------------------" << endl;
}
