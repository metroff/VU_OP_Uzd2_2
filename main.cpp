#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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
    double finalMeanGrade;
    double finalMedianGrade;
};

enum CalculationType {MEAN, MEDIAN, BOTH};

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
    clearLine();
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

// Skaičiuojamas vidurkis
double findMean(vector<int> &array) {
    if (array.empty())
        return 0;
    double sum = 0;
    for (auto number: array) {
        sum += number;
    }
    return sum/array.size();
}

// Skaičiuojama mediana
double findMedian(vector<int> &array) {
    if (array.empty())
        return 0;
    sort(array.begin(), array.end());
    int index = array.size() / 2;
    return (array.size()%2==0) ? (double)(array[index-1]+array[index])/2.0 : (double)array[index];
}

// Skaičiuojamas galutinis pažymys
void calculateFinalGrade(Student &student) {
    // Nuadojant vidurkį
    double mean = findMean(student.grades);
    // Naudojant medianą
    double median = findMedian(student.grades);

    // Išvedamas galutinis pažymys
    double finalExamGrade = 0.6 * student.examGrade;
    student.finalMeanGrade = 0.4 * mean + finalExamGrade;
    student.finalMedianGrade = 0.4 * median + finalExamGrade;
}

// Atspausdinama studento info
void printResults(vector<Student> &students, bool useFile=false) {
    std::stringstream outputLine;
    string lineString = string(54, '-');

    outputLine << left
        << setw(16) << "Vardas"
        << setw(16) << "Pavarde"
        << "Galutinis " << (true ? "(Vid.)" : "(Med.)");
    outputLine << endl << lineString << endl;

    for(auto student : students){
        calculateFinalGrade(student);
        outputLine << setw(16) << student.firstName
            << setw(16) << student.lastName
            << setw(16) << fixed << setprecision(2) << student.finalMeanGrade
            << endl;
    }
    if (useFile){
        ofstream outf("rezultatai.txt");
        outf << outputLine.rdbuf();
        outf.close();
    } else {
        cout << outputLine.str();
    }
}

// TODO: Check for better approach
bool checkIfFileExists(string fileName){
    ifstream file(fileName);
    return file.good();
}

bool isValidGrade(int grade){
    return (grade >= GRADE_MIN && grade <= GRADE_MAX);
}

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

        if (!yesNoQuestion("Ivesti dar viena studenta?"))
            cout << endl;
            break;

        cout << endl;
    }
}

void readFromFile(string fileName, vector<Student> &students){
    if(checkIfFileExists(fileName)) {
        std::stringstream ss;
        ifstream file(fileName);
        if (file.is_open())
            ss << file.rdbuf();
            file.close();

            string line;
            getline(ss, line);

            int lineNum = 1;

            while(getline(ss, line)) {
                Student student;

                std::stringstream line_stream(line);
                line_stream >> student.firstName;
                line_stream >> student.lastName;

                int grade;

                while(line_stream >> grade) {
                    if(line_stream.fail() || !isValidGrade(grade)){
                        cout << "Nuskaitymo klaida " << lineNum << " eileje.\n" 
                        << "Programa uzdaroma.\n";
                        exit(1);
                    }
                    student.grades.push_back(grade);
                }

                student.examGrade = student.grades.back();
                student.grades.pop_back();

                students.push_back(student);

                lineNum++;
            }
    } else {
        if(yesNoQuestion("Failas "+fileName+" nerastas. Pildyti rankiniu budu?")){
            manualInput(students);
        } else {
            cout << "Programa uzdaroma." << endl;
        }
    }
}

int main() {
    srand(time(NULL));

    string fileName = "kursiokai.txt";
    vector<Student> students;
    bool useFile = true;

    if(yesNoQuestion("Ar noretumete duomenis nuskaityti is failo?")){
        readFromFile(fileName, students);
    }else{
        useFile = false;
        manualInput(students);
    }

    if(students.size() > 0){

        //if (yesNoQuestion("Skaiciavimams naudoti mediana? (y-mediana, n-vidurkis)"))

        printResults(students, useFile);

        students.clear();
    }

    return 0;
}