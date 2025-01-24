#include "Faculty.h"

// Default constructor
Faculty::Faculty() : id(0) {}

// Parameterized constructor
Faculty::Faculty(int id, std::string name, std::string level, std::string department, std::vector<int> adviseeIds)
    : id(id), name(name), level(level), department(department), adviseeIds(adviseeIds) {}

// Overloaded operators
bool Faculty::operator==(const Faculty& other) const {
    return id == other.id;
}

bool Faculty::operator!=(const Faculty& other) const {
    return id != other.id;
}

bool Faculty::operator<(const Faculty& other) const {
    return id < other.id;
}

bool Faculty::operator>(const Faculty& other) const {
    return id > other.id;
}

bool Faculty::operator<=(const Faculty& other) const {
    return id <= other.id;
}

bool Faculty::operator>=(const Faculty& other) const {
    return id >= other.id;
}

// Friend function for output
std::ostream& operator<<(std::ostream& os, const Faculty& faculty) {
    os << "ID: " << faculty.id << ", Name: " << faculty.name << ", Level: " << faculty.level
       << ", Department: " << faculty.department << ", Advisee IDs: ";
    for (const int& adviseeId : faculty.adviseeIds) {
        os << adviseeId << " ";
    }
    return os;
}
