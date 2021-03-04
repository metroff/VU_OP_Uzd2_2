#include "file.hpp"

bool checkIfFileExists(string& fileName){
    struct stat buffer;
    return (stat(fileName.c_str(), &buffer)==0);
}

// Duomenų įvedimas nuskaitant iš failo
void readFromFile(string fileName, vector<Student> &students){
    if(checkIfFileExists(fileName)) {
        std::stringstream ss;
        // Nuskaitomas visas failas
        ifstream file(fileName);
        if (file.is_open()) {
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
                    lineNum++;
                    continue;
                }

                student.examGrade = student.grades.back();
                student.grades.pop_back();

                students.push_back(student);

                lineNum++;
            }
        } else throw std::runtime_error("Failo neimanoma atidaryti.");
    } else {
        throw FileNotFound();
    }
}