#pragma once

#define GRADE_MIN 1
#define GRADE_MAX 10

#include "myLib.hpp"
#include "math.hpp"
#include "rng.hpp"

// Exception, kuris yra išmetamas
class GradeException{};

class Student {
    private:
        string firstName;
        string lastName;
        vector<int> grades;
        int examGrade;
        double finalMeanGrade;
        double finalMedianGrade;

    public:
        Student() : examGrade(0), finalMedianGrade(0), finalMeanGrade(0) {}
        Student(const string &, const string &);
        Student(std::stringstream &);

        // Getter'iai
        string getFirstName() const;
        string getLastName() const;
        int getExamGrade() const;
        double getFinalMeanGrade() const;
        double getFinalMedianGrade() const;

        // Setter'iai
        void setExamGrade(int);
        void addGrade(int);

        // Student funkcijos
        void readStudent(std::stringstream &);
        void processGrades();
        void clearGrades();
        void generateGrades(int);

        // Palyginimas
        bool operator < (const Student &);
        bool compareByFullName(const Student &);
};

// Utility funkcija
bool isValidGrade(int grade);