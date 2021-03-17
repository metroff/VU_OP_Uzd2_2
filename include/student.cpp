#include "student.hpp"

void processGrades(Student &student) {
    double finalExam = 0.6 * student.examGrade;
    if (student.grades.size()==0){
        student.finalMeanGrade = finalExam;
        student.finalMedianGrade = finalExam;
    } else {
        student.finalMeanGrade = finalExam + 0.4 * findMean(student.grades);
        student.finalMedianGrade = finalExam + 0.4 * findMedian(student.grades);
    }
}