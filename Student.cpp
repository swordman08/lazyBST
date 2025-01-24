#include "Student.h"
#include <string>

Student::Student() : id(0), gpa(0.0), advisorId(0) {}

Student::Student(int id, std::string name, std::string level, std::string major, double gpa, int advisorId)
    : id(id), name(name), level(level), gpa(gpa), advisorId(advisorId) {
        major = major;
    }


bool Student::operator==(const Student& other) const {
    return id == other.id;
}

bool Student::operator!=(const Student& other) const {
    return id != other.id;
}

bool Student::operator<(const Student& other) const {
    return id < other.id;
}

bool Student::operator>(const Student& other) const {
    return id > other.id;
}

bool Student::operator<=(const Student& other) const {
    return id <= other.id;
}

bool Student::operator>=(const Student& other) const {
    return id >= other.id;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "ID: " << student.id << ", Name: " << student.name << ", Level: " << student.level
       << ", Major: " << student.major << ", GPA: " << student.gpa << ", Advisor ID: " << student.advisorId;
    return os;
}
