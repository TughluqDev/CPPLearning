#include <iostream>
#include <vector>
#include "header.hpp"

int main() {
    Student student("John Doe", 85, 12345);
    
    student.addGrade(90);
    student.addGrade(85);
    student.addGrade(88);
    student.addGrade(92);
    
    student.printReportCard();
    
}