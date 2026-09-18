/**
 * Program Name: Student.cpp
 * Assigned Member: Hoang Trung Le
 * Student Id: 11949817
 * Description: Contains the function definitions for the Student class. It initializes 
 *              student objects with default or custom IDs and names, defines getter 
 *              methods for data retrieval, and handles basic console output.
 */

#include "Student.h"
#include <iostream>

// Default constructor
Student::Student()
    : id_(""), name_("")
{
    // Members initialized using member initializer list above
}

// Full constructor
Student::Student(const std::string &id, const std::string &name)
    : id_(id), name_(name)
{
    // Members assigned using member initializer list above
}

// getId()
std::string Student::getId() const
{
    return id_;
}

// getName()
std::string Student::getName() const
{
    return name_;
}

// print()
void Student::print() const
{
    std::cout << "ID: " << id_ << ", Name: " << name_ << std::endl;
}
