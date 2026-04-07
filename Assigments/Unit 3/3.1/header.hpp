#ifndef STUDENT_HPP
#define STUDENT_HPP
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;
class Student {
private:
    string name;
    int studentID;
    vector<int> grades;
    int initialGrade;

public:
    Student(const string& name, int initialGrade, int studentID) : name(name), initialGrade(initialGrade), studentID(studentID) {
        grades.push_back(initialGrade);
    }

    void addGrade(int grade) {
        grades.push_back(grade);
    }

    void printReportCard() const {
        cout << "Student: " << name << endl;
        cout << "ID: " << studentID << endl;
        cout << "Grades: ";
        for (int grade : grades) {
            cout << grade << " ";
        }
        cout << endl;

        double average = 0;
        for (int grade : grades) {
            average += grade;
        }
        average /= grades.size();

        cout << fixed << setprecision(2);
        cout << "Average: " << average << endl;
    }
};

#endif