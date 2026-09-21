/********************************************************************************
 * Program Name: Student.h
 * Assigned Member: Hoang Trung Le
 * Student Id: 11949817
 * Description: Header file for the Student class. This stores basic information
 *              about a student, including their student ID and full name. It
 *              provides constructors, getter functions, and a print method
 *              to access and display student information.
 *******************************************************************************/

#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
    // Default constructor
    Student();

    // Constructor for creating a student with an ID and name
    Student(const std::string &id, const std::string &name);

    // Get student information
    std::string getId() const;
    std::string getName() const;

    // Display student information
    void print() const;

private:
    std::string id_;
    std::string name_;
};

#endif