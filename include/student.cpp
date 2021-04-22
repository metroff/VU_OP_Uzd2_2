#include "student.hpp"

Student::Student(const string & firstName, const string & lastName) {
    this->firstName = firstName;
    this->lastName = lastName;
}

string Student::getFirstName() const {
    return firstName;
}

string Student::getLastName() const {
    return lastName;
}

int Student::getExamGrade() const {
    return examGrade;
}

double Student::getFinalMeanGrade() const {
    return finalMeanGrade;
}

double Student::getFinalMedianGrade() const {
    return finalMedianGrade;
}

void Student::setExamGrade(int examGrade) {
    this->examGrade = examGrade;
}

void Student::addGrade(int grade) {
    grades.push_back(grade);
}

void Student::processGrades() {
    double finalExam = 0.6 * examGrade;
    if (grades.size()==0){
        finalMeanGrade = finalExam;
        finalMedianGrade = finalExam;
    } else {
        finalMeanGrade = finalExam + 0.4 * findMean(grades);
        finalMedianGrade = finalExam + 0.4 * findMedian(grades);
    }
}

void Student::clearGrades() {
    grades.clear();
};

void Student::setExamGradeFromGrades() {
    examGrade = grades.back();
    grades.pop_back();
};

bool Student::operator < (const Student &student) {
    return finalMeanGrade < student.finalMeanGrade;
}
