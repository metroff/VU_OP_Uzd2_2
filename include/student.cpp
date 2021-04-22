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
}

void Student::setExamGradeFromGrades() {
    examGrade = grades.back();
    grades.pop_back();
}

// Sugeneruojami pažymiai
void Student::generateGrades(int numOfGrades) {
    RandInt rnd{1, 10};
    // Nustatomas pažymių kiekis
    if (numOfGrades == -1) {
        numOfGrades = rnd();
    }
    // Sugeneruojami ir išspausdinami pažymaiai
    cout << "Sugeneruoti " << numOfGrades << " pazymiai: ";
    for (int i = 0; i < numOfGrades; i++) {
        int grade = rnd();
        grades.push_back(grade);
        cout << grade << " ";
    }
    examGrade = rnd();
    cout << "\nSugeneruotas galutinis pazymys: " << examGrade << endl;
}

bool Student::operator < (const Student &student) {
    return finalMeanGrade < student.finalMeanGrade;
}

bool Student::compareByFullName(const Student &student) {
    return (lastName == student.lastName) ? firstName < student.firstName : lastName < student.lastName;
}