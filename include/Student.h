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