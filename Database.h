#ifndef DATABASE_H
#define DATABASE_H

#include "lbst.h"
#include "Student.h"
#include "Faculty.h"
#include <fstream>

class Database {
public:
    Database();
    ~Database();

    void addStudent(const Student& student);
    void addFaculty(const Faculty& faculty);

    bool removeStudent(int studentId);
    bool removeFaculty(int facultyId);

    Student* findStudent(int studentId);
    Faculty* findFaculty(int facultyId);

    void printAllStudents();
    void printAllFaculty();

    void changeAdvisor(int studentId, int newAdvisorId);
    void removeAdvisee(int facultyId, int adviseeId);

    void saveToFile(const std::string& filename);

private:
    lbst<Student> studentTable;
    lbst<Faculty> facultyTable;
};

#endif
