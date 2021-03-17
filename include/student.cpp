#include "student.hpp"

double calculateFinalGrade(int examGrade, double grade){
    return 0.6 * examGrade + 0.4 * grade;
}

double calculateFinalGrade(int examGrade, vector<int> &grades, 
                            double (*calcType)(vector<int>&) = findMean){
    return calculateFinalGrade(examGrade, calcType(grades));
}

void processGrades(Student &student) {
    student.finalMeanGrade = calculateFinalGrade(student.examGrade, student.grades);
    student.finalMedianGrade = calculateFinalGrade(student.examGrade, student.grades, findMedian);
}