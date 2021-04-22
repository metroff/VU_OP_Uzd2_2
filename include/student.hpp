#pragma once

#include "myLib.hpp"
#include "math.hpp"
#include "rng.hpp"

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

        string getFirstName() const;
        string getLastName() const;
        int getExamGrade() const;
        double getFinalMeanGrade() const;
        double getFinalMedianGrade() const;

        void setExamGrade(int);
        void addGrade(int);

        void processGrades();
        void clearGrades();
        void setExamGradeFromGrades();
        // Sugeneruojami pažymiai
        void generateGrades(int);

        bool operator < (const Student &);
        bool compareByFullName(const Student &);
};