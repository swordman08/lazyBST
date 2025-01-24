#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <string>
#include <vector>

class Faculty {
public:
    int id;
    std::string name;
    std::string level;
    std::string department;
    std::vector<int> adviseeIds;

    Faculty();
    Faculty(int id, std::string name, std::string level, std::string department, std::vector<int> adviseeIds);

    // Overload comparison operators
    bool operator==(const Faculty& other) const;
    bool operator!=(const Faculty& other) const;
    bool operator<(const Faculty& other) const;
    bool operator>(const Faculty& other) const;
    bool operator<=(const Faculty& other) const;
    bool operator>=(const Faculty& other) const;

    // Friend function for output
    friend std::ostream& operator<<(std::ostream& os, const Faculty& faculty);
};

#endif
