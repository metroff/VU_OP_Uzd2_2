#include "console.hpp"

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
int getGrade(bool exit_state) {
    int grade;
    while (true) {
        grade = readNumber();
        if (exit_state && grade == -1) {
            return grade;
        } else if (!isValidGrade(grade)) {
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

// Integer klausimas
int getInt(string message, int low, int high) {
    int answer = -10;
    while (answer < low || answer > high) {
        cout << message;
        cin >> answer;
        if (cin.fail())
            clearLine();
    }
    clearLine();
    return answer;
}