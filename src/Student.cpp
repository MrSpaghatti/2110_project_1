/**
 * Program Name: Student.cpp
 * Assigned Member: Hoang Trung Le
 * Student Id: 11949817
 * Description: Contains the function definitions for the Student class. It initializes 
 *              student objects with default or custom IDs and names, defines getter 
 *              methods for data retrieval, and handles basic console output.
 */

#include "Student.h"
#include <cctype>
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

bool Student::isValidId(const std::string &id)
{
    if (id.empty()) {
        return false;
    }
    for (unsigned char character : id) {
        if (!std::isdigit(character)) {
            return false;
        }
    }
    return true;
}

bool Student::isValidName(const std::string &name)
{
    bool containsLetter = false;
    for (unsigned char character : name) {
        if (std::isdigit(character)) {
            return false;
        }
        if (std::isalpha(character)) {
            containsLetter = true;
        }
    }
    return containsLetter;
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
