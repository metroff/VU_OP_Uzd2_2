#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <fstream>


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
using std::ifstream;
using std::ofstream;

struct Student {
    string firstName;
    string lastName;
    vector<int> grades;
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

// Skaičiuojamas galutinis pažymys
void calculateFinalGrade(Student &student, bool useMean) {
    int numOfGrades = student.grades.size();
    // Patikrinama ar yra pažymių
    if (numOfGrades != 0) {
        if (useMean) {
            // Nuadojant vidurkį
            double sum = 0;
            for (auto grade: student.grades) {
                sum += grade;
            }
            student.processedGrades = sum / numOfGrades;
        } else {
            // Naudojant medianą
            sort(student.grades.begin(), student.grades.end());
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
    // Išvedamas galutinis pažymys
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


bool checkIfFileExists(string fileName){
    ifstream file(fileName);
    return file.good();
}

bool shouldReadFromFile(string fileName){
    if (checkIfFileExists(fileName)) {
        if (yesNoQuestion("Ar noretumete duomenis nuskaityti is failo?")){
            cout << "Duomenys nuskaitomi is failo.\n";
            clearLine();
            return true;
        } else {
            cout << "Pereinama prie rankinio duomenu ivedimo.\n";
            clearLine();
            return false;
        }
    } else {
        cout << "Failas "+fileName+" nerastas. Pereinama prie rankinio duomenu ivedimo.\n";
        return false;
    }
}

void readFromFile(string fileName, vector<Student> &students){
    std::stringstream ss;
    ifstream file(fileName);
    if (file.is_open())
        ss << file.rdbuf();
        file.close();

        string line;
        getline(ss, line);

        while(getline(ss, line)) {
            Student student;

            std::stringstream line_stream(line);
            line_stream >> student.firstName;
            line_stream >> student.lastName;

            int grade;

            while(!line_stream.eof()) {
                line_stream >> grade;
                student.grades.push_back(grade);
            }

            student.examGrade = student.grades.back();
            student.grades.pop_back();

            students.push_back(student);
        }
}

int main() {
    srand(time(NULL));

    string fileName = "kursiokai.txt";
    vector<Student> students;
    bool useMean = true;

    if(shouldReadFromFile(fileName)) {
        readFromFile(fileName, students);
    } else {

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

            if (!yesNoQuestion("Ivesti dar viena studenta?"))
                break;

            cout << endl;

            clearLine();
        }

    }

    if (yesNoQuestion("Skaiciavimams naudoti mediana? (y-mediana, n-vidurkis)"))
        useMean = false;

    // Atspausdinami lenteles stulpelių pavadinimai
    string lineString = string(50, '-');
    cout << endl << left
         << setw(15) << "Vardas"
         << setw(16) << "Pavarde"
         << "Galutinis " << (useMean ? "(Vid.)" : "(Med.)");
    cout << endl << lineString << endl;

    // Perrenkamas kiekvienas studentas
    for (auto student : students) {
        calculateFinalGrade(student, useMean);
        printResults(student);
    }

    return 0;
}