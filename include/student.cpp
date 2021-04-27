#include "student.hpp"

// Konstruktoriai
Student::Student(const string & firstName, const string & lastName) {
    this->firstName = firstName;
    this->lastName = lastName;
}

Student::Student(std::stringstream &stream) {
    readStudent(stream);
}

Student::Student(const Student& newStudent) {
    firstName = newStudent.firstName;
    lastName = newStudent.lastName;
    grades = newStudent.grades;
    examGrade = newStudent.examGrade;
    finalMeanGrade = newStudent.finalMeanGrade;
    finalMedianGrade = newStudent.finalMedianGrade;
}

Student::~Student() = default;

Student& Student::operator = (const Student& newStudent) {
    if (&newStudent == this)
        return *this;

    firstName = newStudent.firstName;
    lastName = newStudent.lastName;
    grades = newStudent.grades;
    examGrade = newStudent.examGrade;
    finalMeanGrade = newStudent.finalMeanGrade;
    finalMedianGrade = newStudent.finalMedianGrade;

    return *this;
}

// Getter'iai
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

// Setter'iai
void Student::setExamGrade(int examGrade) {
    this->examGrade = examGrade;
}

void Student::addGrade(int grade) {
    grades.push_back(grade);
}

// Student funkcijos
// Nuskaitymas į klasę
void Student::readStudent(std::stringstream &stream) {
    stream >> firstName;
    stream >> lastName;

    int grade;
                          
    while(stream >> grade || !stream.eof()) {
        if(stream.fail() || !isValidGrade(grade)){
            throw GradeException();
        }
        grades.push_back(grade);
    }

    examGrade = grades.back();
    grades.pop_back();

    processGrades();
}

// Pažymių apdorojimas
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

// Pažymių išvalymas
void Student::clearGrades() {
    grades.clear();
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

// Palygynimas
bool Student::operator < (const Student &student) {
    return finalMeanGrade < student.finalMeanGrade;
}

bool Student::compareByFullName(const Student &student) {
    return (lastName == student.lastName) ? firstName < student.firstName : lastName < student.lastName;
}

// Utility funkcija
bool isValidGrade(int grade){
    return (grade >= GRADE_MIN && grade <= GRADE_MAX);
}