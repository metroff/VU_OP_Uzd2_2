#include "output.hpp"

// Atspausdinama studento info
template <class Container>
void printResults(Container &students,  OutputType type, bool useFile, string fileName, bool log) {
    sortContainerByName(students);

    int length = 52;

    std::stringstream outputLine;

    // Išvedami stulpelių pavadinimai
    outputLine << left << fixed
        << setw(16) << "Vardas"
        << setw(16) << "Pavarde";
        
    if (type == OutputType::BOTH) {
        outputLine << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)";
        length += 20;
    } else if (type == OutputType::MEAN){
        outputLine << setw(20) << "Galutinis (Vid.)";
    } else {
        outputLine << setw(20) << "Galutinis (Med.)";
    } 
    outputLine << endl << string(length, '-') << endl;

    // Išvedama studentų info
    for(auto &student : students){
        outputLine << setw(16) << student.getFirstName()
            << setw(16) << student.getLastName();
        if (type == OutputType::BOTH) {
            outputLine << setw(20) << setprecision(2) << student.getFinalMeanGrade();
            outputLine << setw(20) << setprecision(2) << student.getFinalMedianGrade();
        } else if (type == OutputType::MEAN){
            outputLine << setw(20) << setprecision(2) << student.getFinalMeanGrade();
        } else {
            outputLine << setw(20) << setprecision(2) << student.getFinalMedianGrade();
        }     
        outputLine << endl;
    }
    if (useFile){
        ofstream outf(fileName);
        outf << outputLine.str();
        outf.close();
        if (log)
            cout << "Duomenys irasyti i rezultatai.txt faila." << endl;
    } else {
        cout << endl << outputLine.str();
    }
}

template void printResults(vector<Student> &students,  OutputType type, bool useFile, string fileName, bool log);
template void printResults(list<Student> &students,  OutputType type, bool useFile, string fileName, bool log);
template void printResults(deque<Student> &students,  OutputType type, bool useFile, string fileName, bool log);