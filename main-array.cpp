#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#define GRADE_MIN 1
#define GRADE_MAX 10

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::getline;
using std::left;
using std::numeric_limits;
using std::setprecision;
using std::setw;
using std::sort;
using std::streamsize;
using std::string;
using std::vector;

struct Student {
    string firstName;
    string lastName;
    int numOfGrades;
    int *grades;
    int examGrade;
    double finalGrade;
    double processedGrades;
};

// Išvalomi įvesti simboliai
void clearLine() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Funkcija skaičiaus nuskaitymui
int readNumber() {
    int number;
    while (!(cin >> number)) {
        cout << "Ne skaicius. Bandykite dar karta: ";
        clearLine();
    }
    clearLine();
    return number;
}

// Funkcija pažymių kiekio nuskaitymui
int getNumOfGrades() {
    int numOfGrades;
    while (true) {
        cout << "Iveskite ne neigiama pazymiu kieki: ";
        numOfGrades = readNumber();
        if (numOfGrades >= 0) {
            return numOfGrades;
        }
    }
}

// Funkcija pažymio nuskaitymui
int getGrade(bool exit_state = false) {
    int grade;
    while (true) {
        grade = readNumber();
        if (exit_state && grade == -1) {
            return grade;
        } else if (grade < GRADE_MIN || grade > GRADE_MAX) {
            cout << "Pazymys turi buti tarp (" << GRADE_MIN << " - " << GRADE_MAX << "): ";
        } else {
            return grade;
        }
    }
}

// Funkcija taip/ne klausimui
bool yesNoQuestion(string question) {
    string answer;
    while (answer != "y" && answer != "n") {
        cout << question << " (y/n): ";
        cin >> answer;
    }
    return answer == "y";
}

// Funkcija skaičiaus pridėjimui į dinaminį masyvą
void pushArray(int *&array, int size, int number) {
    int *temp = new int[size + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = array[i];
    }
    temp[size] = number;
    delete[] array;
    array = temp;
}

// Funkcija Studento įrašo pridėjimui į dinaminį masyvą
void pushStudent(Student *&array, int &size, Student student) {
    Student *temp = new Student[size + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = array[i];
    }
    temp[size] = student;
    delete[] array;
    array = temp;
    size++;
}

// Sugeneruojami pažymiai
void generateGrades(Student &student) {
    // Nustatomas pažymių kiekis
    int numOfGrades = student.numOfGrades;
    if (numOfGrades == -1) {
        numOfGrades = (rand() % 10) + 1;
        student.numOfGrades = numOfGrades;
    }
    student.grades = new int[numOfGrades];
    // Sugeneruojami ir išspausdinami pažymaiai
    cout << "Sugeneruoti " << numOfGrades << " pazymiai: ";
    for (int i = 0; i < numOfGrades; i++) {
        int grade = (rand() % 10) + 1;
        student.grades[i] = grade;
        cout << grade << " ";
    }
    student.examGrade = (rand() % 10) + 1;
    cout << "\nSugeneruotas galutinis pazymys: " << student.examGrade << endl;
}

// Pažymių įvedimas rankiniu budu
void inputGrades(Student &student) {
    // Nustatoma ar žinomas pažymių kiekis
    if (student.numOfGrades == -1) {
        int numOfGrades = 0;
        student.grades = new int[numOfGrades];
        //Pateikiama užklausa pažymių įvedimui.
        cout << "Iveskite pazymius. (Iveskite -1, jei norite pabaigti).\n";
        while (true) {
            cout << "Iveskite " << numOfGrades + 1 << " pazymi (-1 jei baigti): ";
            int grade = getGrade(true);
            if (grade == -1)
                break;
            pushArray(student.grades, numOfGrades, grade);
            numOfGrades++;
        }
        student.numOfGrades = numOfGrades;
    } else {
        //Pateikiama užklausa pažymių įvedimui.
        student.grades = new int[student.numOfGrades];
        for (int i = 0; i < student.numOfGrades; i++) {
            cout << "Iveskite " << i + 1 << " pazymi: ";
            student.grades[i] = getGrade();
        }
    }
    cout << "Iveskite egzamino pazymi: ";
    student.examGrade = getGrade();
}

// Skaičiuojamas galutinis pazymys
void calculateFinalGrade(Student &student, bool useMean) {
    int numOfGrades = student.numOfGrades;
    // Patikrinama ar yra pažymių
    if (numOfGrades != 0) {
        if (useMean) {
            // Nuadojant vidurkį
            double sum = 0;
            for (int i = 0; i < numOfGrades; i++) {
                sum += student.grades[i];
            }
            student.processedGrades = sum / numOfGrades;
        } else {
            // Naudojant medianą
            sort(student.grades, student.grades + numOfGrades);
            int index = numOfGrades / 2;
            if (numOfGrades % 2 == 0) {
                student.processedGrades = (double)(student.grades[index - 1] + student.grades[index]) / 2.0;
            } else {
                student.processedGrades = (double)student.grades[index];
            }
        }
    } else {
        student.processedGrades = 0;
    }
    // Išvedamas galutinis pazymys
    student.finalGrade = 0.4 * student.processedGrades + 0.6 * student.examGrade;
}

// Atspausdinama studento info
void printResults(Student &student) {
    cout << left
         << setw(15) << student.firstName
         << setw(16) << student.lastName
         << fixed << setprecision(2) << student.finalGrade;
    cout << endl;
}

int main() {
    srand(time(NULL));

    int numOfStudents = 0;
    Student *students = new Student[numOfStudents];
    
    bool useMean = true;

    while (true) {
        Student student;

        cout << "Iveskite studento varda: ";
        getline(cin, student.firstName);

        cout << "Iveskite studento pavarde: ";
        getline(cin, student.lastName);

        student.numOfGrades = -1;
        if (yesNoQuestion("Ar zinote pazymiu kieki?"))
            student.numOfGrades = getNumOfGrades();

        if (student.numOfGrades != 0) {
            if (yesNoQuestion("Ar norite atsitiktinai sugeneruoti pazymius?"))
                generateGrades(student);
            else
                inputGrades(student);
        } else {
            cout << "Iveskite egzamino pazymi: ";
            student.examGrade = getGrade();
        }

        pushStudent(students, numOfStudents, student);

        cout << endl;

        if (!yesNoQuestion("Ivesti dar viena studenta?"))
            break;

        cout << endl;

        clearLine();
    }

    if (yesNoQuestion("Skaičiavimams naudoti mediana? (y-mediana, n-vidurkis)"))
        useMean = false;

    // Atspausdinami lenteles stulpelių pavadinimai
    string lineString = string(50, '-');
    cout << endl << left
         << setw(15) << "Vardas"
         << setw(16) << "Pavarde"
         << "Galutinis " << (useMean ? "(Vid.)" : "(Med.)");
    cout << endl << lineString << endl;

    // Perrenkamas kiekvienas studentas
    for (int i = 0; i < numOfStudents; i++) {
        Student student = students[i];
        calculateFinalGrade(student, useMean);
        printResults(student);
        delete[] student.grades;
    }

    delete[] students;

    return 0;
}