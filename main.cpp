#include "Database.h"
#include <iostream>
#include <limits> // For std::numeric_limits

void printMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Print all students and their information (sorted by ascending id #)\n";
    std::cout << "2. Print all faculty and their information (sorted by ascending id #)\n";
    std::cout << "3. Find and display student information given the student id\n";
    std::cout << "4. Find and display faculty information given the faculty id\n";
    std::cout << "5. Add a new student\n";
    std::cout << "6. Delete a student given the id\n";
    std::cout << "7. Add a new faculty member\n";
    std::cout << "8. Delete a faculty member given the id\n";
    std::cout << "9. Change a student’s advisor given the student id and the new faculty id\n";
    std::cout << "10. Remove an advisee from a faculty member given the ids\n";
    std::cout << "11. Exit\n";
}

int main() {
    Database db;
    int choice;

    while (true) {
        printMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Handle invalid input
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cerr << "Invalid input. Please enter a number between 1 and 11." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                db.printAllStudents();
                break;
            case 2:
                db.printAllFaculty();
                break;
            case 3: {
                int studentId;
                std::cout << "Enter student ID: ";
                std::cin >> studentId;
                Student* student = db.findStudent(studentId);
                if (student != nullptr) {
                    std::cout << *student << std::endl;
                } else {
                    std::cerr << "Student not found." << std::endl;
                }
                break;
            }
            case 4: {
                int facultyId;
                std::cout << "Enter faculty ID: ";
                std::cin >> facultyId;
                Faculty* faculty = db.findFaculty(facultyId);
                if (faculty != nullptr) {
                    std::cout << *faculty << std::endl;
                } else {
                    std::cerr << "Faculty not found." << std::endl;
                }
                break;
            }
            case 5: {
                int id, advisorId;
                std::string name, level, major;
                double gpa;
                std::cout << "Enter student ID: ";
                std::cin >> id;
                std::cout << "Enter name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter level: ";
                std::getline(std::cin, level);
                std::cout << "Enter major: ";
                std::getline(std::cin, major);
                std::cout << "Enter GPA: ";
                std::cin >> gpa;
                std::cout << "Enter advisor ID: ";
                std::cin >> advisorId;
                db.addStudent(Student(id, name, level, major, gpa, advisorId));
                break;
            }
            case 6: {
                int studentId;
                std::cout << "Enter student ID to delete: ";
                std::cin >> studentId;
                if (db.removeStudent(studentId)) {
                    std::cout << "Student deleted successfully." << std::endl;
                }
                break;
            }
            case 7: {
                int id;
                std::string name, level, department;
                std::vector<int> adviseeIds;
                std::cout << "Enter faculty ID: ";
                std::cin >> id;
                std::cout << "Enter name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter level: ";
                std::getline(std::cin, level);
                std::cout << "Enter department: ";
                std::getline(std::cin, department);
                db.addFaculty(Faculty(id, name, level, department, adviseeIds));
                break;
            }
            case 8: {
                int facultyId;
                std::cout << "Enter faculty ID to delete: ";
                std::cin >> facultyId;
                if (db.removeFaculty(facultyId)) {
                    std::cout << "Faculty deleted successfully." << std::endl;
                }
                break;
            }
            case 9: {
                int studentId, newAdvisorId;
                std::cout << "Enter student ID: ";
                std::cin >> studentId;
                std::cout << "Enter new advisor ID: ";
                std::cin >> newAdvisorId;
                db.changeAdvisor(studentId, newAdvisorId);
                break;
            }
            case 10: {
                int facultyId, adviseeId;
                std::cout << "Enter faculty ID: ";
                std::cin >> facultyId;
                std::cout << "Enter advisee ID to remove: ";
                std::cin >> adviseeId;
                db.removeAdvisee(facultyId, adviseeId);
                break;
            }
            case 11:
                db.saveToFile("runLog.txt");
                std::cout << "Data saved to runLog.txt. Exiting." << std::endl;
                return 0;
            default:
                std::cerr << "Invalid choice. Please enter a number between 1 and 11." << std::endl;
        }
    }

    return 0;
}
