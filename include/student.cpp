#include "student.hpp"

// Skaičiuojamas pažymių vidurkis ir mediana
void processGrades(vector<int> &array, double &mean, double &median) {
    if (array.empty()) {
        mean = 0;
        median = 0;
    }

    int index = array.size() / 2;
    double sum = 0;
    sort(array.begin(), array.end());
    // Vidurkis
    for (auto number: array) {
        sum += number;
    }
    mean = sum/array.size();
    // Mediana
    median = (array.size()%2==0) ? (double)(array[index-1]+array[index])/2.0 : (double)array[index];
}

// Skaičiuojamas galutinis pažymys
void calculateFinalGrade(Student &student) {
    double mean, median;
    processGrades(student.grades, mean, median);
    // Išvedamas galutinis pažymys
    double finalExamGrade = 0.6 * student.examGrade;
    student.finalMeanGrade = 0.4 * mean + finalExamGrade;
    student.finalMedianGrade = 0.4 * median + finalExamGrade;
}