#include "Database.h"
#include <algorithm>

Database::Database() {}

Database::~Database() {}

void Database::addStudent(const Student& student) {
    studentTable.insert(student);
}

void Database::addFaculty(const Faculty& faculty) {
    facultyTable.insert(faculty);
}

bool Database::removeStudent(int studentId) {
    Student* student = findStudent(studentId);
    if (student == nullptr) {
        std::cerr << "Student not found." << std::endl;
        return false;
    }
    Faculty* advisor = findFaculty(student->advisorId);
    if (advisor != nullptr) {
        advisor->adviseeIds.erase(std::remove(advisor->adviseeIds.begin(), advisor->adviseeIds.end(), studentId), advisor->adviseeIds.end());
    }
    return studentTable.deleteNode(*student);
}

bool Database::removeFaculty(int facultyId) {
    Faculty* faculty = findFaculty(facultyId);
    if (faculty == nullptr) {
        std::cerr << "Faculty not found." << std::endl;
        return false;
    }
    for (int adviseeId : faculty->adviseeIds) {
        Student* advisee = findStudent(adviseeId);
        if (advisee != nullptr) {
            advisee->advisorId = 0; // No advisor
        }
    }
    return facultyTable.deleteNode(*faculty);
}

Student* Database::findStudent(int studentId) {
    TreeNode<Student>* node = studentTable.get(Student(studentId, "", "", "", 0.0, 0));
    if (node != nullptr) {
        return &(node->key);
    }
    return nullptr;
}

Faculty* Database::findFaculty(int facultyId) {
    TreeNode<Faculty>* node = facultyTable.get(Faculty(facultyId, "", "", "", {}));
    if (node != nullptr) {
        return &(node->key);
    }
    return nullptr;
}

void Database::printAllStudents() {
    studentTable.printTree();
}

void Database::printAllFaculty() {
    facultyTable.printTree();
}

void Database::changeAdvisor(int studentId, int newAdvisorId) {
    Student* student = findStudent(studentId);
    Faculty* newAdvisor = findFaculty(newAdvisorId);
    if (student == nullptr) {
        std::cerr << "Student not found." << std::endl;
        return;
    }
    if (newAdvisor == nullptr) {
        std::cerr << "New advisor not found." << std::endl;
        return;
    }
    Faculty* oldAdvisor = findFaculty(student->advisorId);
    if (oldAdvisor != nullptr) {
        oldAdvisor->adviseeIds.erase(std::remove(oldAdvisor->adviseeIds.begin(), oldAdvisor->adviseeIds.end(), studentId), oldAdvisor->adviseeIds.end());
    }
    student->advisorId = newAdvisorId;
    newAdvisor->adviseeIds.push_back(studentId);
}

void Database::removeAdvisee(int facultyId, int adviseeId) {
    Faculty* faculty = findFaculty(facultyId);
    if (faculty == nullptr) {
        std::cerr << "Faculty not found." << std::endl;
        return;
    }
    faculty->adviseeIds.erase(std::remove(faculty->adviseeIds.begin(), faculty->adviseeIds.end(), adviseeId), faculty->adviseeIds.end());
    Student* advisee = findStudent(adviseeId);
    if (advisee != nullptr) {
        advisee->advisorId = 0; // No advisor
    }
}

void Database::saveToFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }
    outFile << "Students:\n";
    // Code to print all students to outFile
    // outFile << ...
    outFile << "Faculty:\n";
    // Code to print all faculty to outFile
    // outFile << ...
    outFile.close();
}
