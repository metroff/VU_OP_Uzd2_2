#include "output.hpp"

bool compareStudents(Student a, Student b) {
    return (a.lastName == b.lastName) ? a.firstName < b.firstName : a.lastName < b.lastName;
}

// Atspausdinama studento info
void printResults(vector<Student> &students,  OutputType type, bool useFile) {
    sort(students.begin(), students.end(), compareStudents);

    int length = 52;

    std::stringstream outputLine;

    // Išvedami stulpelių pavadinimai
    outputLine << left << fixed
        << setw(16) << "Vardas"
        << setw(16) << "Pavarde";
        
    if (type == OutputType::MEAN){
        outputLine << setw(20) << "Galutinis (Vid.)";
    } else if (type == OutputType::MEDIAN) {
        outputLine << setw(20) << "Galutinis (Med.)";
    } else {
        outputLine << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)";
        length += 20;
    }
    outputLine << endl << string(length, '-') << endl;

    // Išvedama studentų info
    for(auto &student : students){
        outputLine << setw(16) << student.firstName
            << setw(16) << student.lastName;
        if (type == OutputType::MEAN){
            outputLine << setw(20) << setprecision(2) << student.finalMeanGrade;
        } else if (type == OutputType::MEDIAN) {
            outputLine << setw(20) << setprecision(2) << student.finalMedianGrade;
        } else {
            outputLine << setw(20) << setprecision(2) << student.finalMeanGrade;
            outputLine << setw(20) << setprecision(2) << student.finalMedianGrade;
        }       
        outputLine << endl;
    }
    if (useFile){
        ofstream outf("rezultatai.txt");
        outf << outputLine.str();
        outf.close();
        cout << "Duomenys irasyti i rezultatai.txt faila." << endl;
    } else {
        cout << endl << outputLine.str();
    }
}