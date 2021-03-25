#include "file.hpp"

bool checkIfFileExists(const string& fileName){
    struct stat buffer;
    return (stat(fileName.c_str(), &buffer)==0);
}

// Duomenų įvedimas nuskaitant iš failo
template <class Container>
void readFromFile(string fileName, Container &students){
    std::stringstream ss;
    // Nuskaitomas visas failas
    ifstream file(fileName);
    if (file) {
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

            try{                
                while(line_stream >> grade || !line_stream.eof()) {
                    if(line_stream.fail() || !isValidGrade(grade)){
                        throw GradeException();
                    }
                    student.grades.push_back(grade);
                }
            } catch (GradeException) {
                cout << "Nuskaitymo klaida " << lineNum << " eileje. Studentas praleistas.\n";
                student.grades.clear();
                lineNum++;
                continue;
            }

            student.examGrade = student.grades.back();
            student.grades.pop_back();

            processGrades(student);

            students.push_back(student);

            lineNum++;
        }
    } else throw std::runtime_error("Failo neimanoma atidaryti.");
}

template void readFromFile(string fileName, vector<Student> &students);
template void readFromFile(string fileName, list<Student> &students);
template void readFromFile(string fileName, deque<Student> &students);

// Sukuriamas failas su studentų info
void generateFile(string fileName, int index) {
    RandInt rng{1, 10};

    std::stringstream outputLine;

    // Išvedami stulpelių pavadinimai
    outputLine << left
        << setw(20) << "Vardas"
        << setw(20) << "Pavarde"
        << setw(20) << "Pazymiai";

    // Išvedama studentų info į buffer'į
    for(int i = 1; i <= index; i++) {
        outputLine << endl
            << setw(20) << ("Vardas" + std::to_string(i))
            << setw(20) << ("Pavarde" + std::to_string(i));
        
        int gradeCount = rng();
        for(int j=0; j <= gradeCount; j++){
            outputLine << setw(10) << rng();
        }
    }
    
    ofstream outf(fileName);
    outf << outputLine.str();
    outf.close();
}