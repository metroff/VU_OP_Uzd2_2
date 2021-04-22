#include "utils.hpp"

bool compareStudents(Student a, Student b) {
    return (a.getLastName() == b.getLastName()) ? a.getFirstName() < b.getFirstName() : a.getLastName() < b.getLastName();
}

bool isValidGrade(int grade){
    return (grade >= GRADE_MIN && grade <= GRADE_MAX);
}

void sortContainer(list<Student> &students){
    students.sort();
}

void sortContainer(vector<Student> &students){
    std::sort(students.begin(), students.end());
}

void sortContainer(deque<Student> &students){
    std::sort(students.begin(), students.end());
}

void sortContainerByName(list<Student> &students){
    students.sort(compareStudents);
}

void sortContainerByName(vector<Student> &students){
    std::sort(students.begin(), students.end(), compareStudents);
}

void sortContainerByName(deque<Student> &students){
    std::sort(students.begin(), students.end(), compareStudents);
}