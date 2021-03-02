#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

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

enum class OutputType {MEAN, MEDIAN, BOTH};

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

// Sužinoma kokį skaičiavimo budą naudoti
OutputType getOutputType() {
    int answer = 0;
    while (answer < 1 || answer > 3) {
        cout << "Skaiciuoti naudojant (1) Vidurki, (2) Mediana, (3) Abu.\nPasirinkite (1-3): ";
        cin >> answer;
        if (cin.fail())
            clearLine();
    }
    clearLine();

    if(answer == 1){
        return OutputType::MEAN;
    } else if (answer == 2) {
        return OutputType::MEDIAN;
    }
    return OutputType::BOTH;
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

bool compareStudents(Student a, Student b) {
    return (a.lastName == b.lastName) ? a.firstName < b.firstName : a.lastName < b.lastName;
}

// Atspausdinama studento info
void printResults(vector<Student> &students,  OutputType type, bool useFile=false) {
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
    for(auto student : students){
        calculateFinalGrade(student);
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
        outf << outputLine.rdbuf();
        outf.close();
        cout << "Duomenys irasyti i rezultatai.txt faila." << endl;
    } else {
        cout << endl << outputLine.str();
    }
}

bool checkIfFileExists(string& fileName){
    struct stat buffer;
    return (stat(fileName.c_str(), &buffer)==0);
}

bool isValidGrade(int grade){
    return (grade >= GRADE_MIN && grade <= GRADE_MAX);
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

// Duomenų įvedimas nuskaitant iš failo
void readFromFile(string fileName, vector<Student> &students){
    if(checkIfFileExists(fileName)) {
        std::stringstream ss;
        // Nuskaitomas visas failas
        ifstream file(fileName);
        if (file.is_open())
            ss << file.rdbuf();
            file.close();

            string line;
            getline(ss, line);

            int lineNum = 1;
            // Dalinama eilutėmis
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

    if(yesNoQuestion("Ar noretumete duomenis nuskaityti is failo?")){
        readFromFile(fileName, students);
    }else{
        manualInput(students);
    }

    if(students.size() > 0){

        OutputType outputType = getOutputType();

        bool useFile = yesNoQuestion("Rezultatus pateikti faile?");

        printResults(students, outputType, useFile);

        students.clear();
    }

    return 0;
}