#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

class Student {
public:
    int id;
    std::string major;
    std::string name;
    std::string level;
   
    double gpa;
    int advisorId;

    Student();
    Student(int id, std::string name, std::string level, std::string major, double gpa, int advisorId);

    // Overload comparison operators
    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;
    bool operator<(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator<=(const Student& other) const;
    bool operator>=(const Student& other) const;

    // Friend function for output
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};

#endif
