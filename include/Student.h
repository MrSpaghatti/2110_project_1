/**
 * Program Name: Student.h
 * Assigned Member: Hoang Trung Le
 * Student Id: 11949817
 * Description: Header file for the Student class. Acts as a simple data model to store 
 *              basic student details, including their ID and full name. Features standard 
 *              constructors, getters for accessing private member variables, and a print 
 *              method to output student info.
 */
#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
    Student();
    Student(const std::string &id, const std::string &name);

    std::string getId() const;
    std::string getName() const;

    void print() const;

private:
    std::string id_;
    std::string name_;
};

#endif