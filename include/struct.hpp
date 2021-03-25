#pragma once

struct Student {
    string firstName;
    string lastName;
    vector<int> grades;
    int examGrade;
    double finalMeanGrade;
    double finalMedianGrade;

    bool operator < (const Student &student) {
        return finalMeanGrade < student.finalMeanGrade;
    }
};