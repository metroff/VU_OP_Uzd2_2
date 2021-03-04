#include "input.hpp"

// Sugeneruojami pažymiai
void generateGrades(Student &student, int numOfGrades) {
    // Nustatomas pažymių kiekis
    if (numOfGrades == -1) {
        numOfGrades = (rand() % 10) + 1;
    }
    // Sugeneruojami ir išspausdinami pažymaiai
    cout << "Sugeneruoti " << numOfGrades << " pazymiai: ";
    for (int i = 0; i < numOfGrades; i++) {
        int grade = (rand() % 10) + 1;
        student.grades.push_back(grade);
        cout << grade << " ";
    }
    student.examGrade = (rand() % 10) + 1;
    cout << "\nSugeneruotas galutinis pazymys: " << student.examGrade << endl;
}

// Pažymių įvedimas rankiniu budu
void inputGrades(Student &student, int numOfGrades) {
    // Nustatoma ar žinomas pažymių kiekis
    if (numOfGrades == -1) {
        int numOfGrades = 0;
        //Pateikiama užklausa pažymių įvedimui.
        cout << "Iveskite pazymius. (Iveskite -1, jei norite pabaigti).\n";
        while (true) {
            cout << "Iveskite " << numOfGrades + 1 << " pazymi (-1 jei baigti): ";
            int grade = getGrade(true);
            if (grade == -1)
                break;
            student.grades.push_back(grade);
            numOfGrades++;
        }
    } else {
        //Pateikiama užklausa pažymių įvedimui.
        for (int i = 0; i < numOfGrades; i++) {
            cout << "Iveskite " << i + 1 << " pazymi: ";
            student.grades.push_back(getGrade());
        }
    }
    cout << "Iveskite egzamino pazymi: ";
    student.examGrade = getGrade();
}

// Duomenų įvedimas rankiniu būdu
void manualInput(vector<Student> &students) {
    while (true) {
        Student student;

        cout << "Iveskite studento varda: ";
        getline(cin, student.firstName);

        cout << "Iveskite studento pavarde: ";
        getline(cin, student.lastName);
        
        int numOfGrades = -1;
        if (yesNoQuestion("Ar zinote pazymiu kieki?"))
            numOfGrades = getNumOfGrades();

        if (numOfGrades != 0) {
            if (yesNoQuestion("Ar norite atsitiktinai sugeneruoti pazymius?"))
                generateGrades(student, numOfGrades);
            else
                inputGrades(student, numOfGrades);
        } else {
            cout << "Iveskite egzamino pazymi: ";
            student.examGrade = getGrade();
        }

        students.push_back(student);

        cout << endl;

        if (!yesNoQuestion("Ivesti dar viena studenta?")) {
            cout << endl;
            break;
        }  

        cout << endl;
    }
}