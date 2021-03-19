#include "include/myLib.hpp"
#include "include/struct.hpp"
#include "include/student.hpp"
#include "include/console.hpp"
#include "include/input.hpp"
#include "include/output.hpp"
#include "include/file.hpp"
#include "include/benchmark.hpp"
#include <exception>

int main(int argc, char* argv[]) {
    if(argc>=2) {
        if(string(argv[1]) == "-bench") {    
            if(argc < 3) {
                cout << "Usage: " << argv[0] << "-bench (stage [1-5])" << endl;
                return 0;
            }        
            int stage = atoi(argv[2]);
            if (stage > 0 && stage < 6)
                runBenchmark(stage);
            else cout << "Usage: " << argv[0] << "-bench (stage [1-5])" << endl;
            return 0;
        }
    }

    string message = "";
    string fileName = "kursiokai.txt";
    vector<Student> students;

    if(yesNoQuestion("Ar noretumete duomenis nuskaityti is failo?")){
        bool error = false;

        try{
            readFromFile(fileName, students);
        } catch (FileNotFound) {
            error = true;
            message = "Failas "+fileName+" nerastas. Pildyti rankiniu budu?";
        } catch (std::exception& e){
            error = true;
            cout << "Klaida: " << e.what();
            message = "\nPildyti rankiniu budu?";
        }

        if(error) {
            if(yesNoQuestion(message)){
                students.clear();
                manualInput(students);
            } else {
                cout << "Programa uzdaroma." << endl;
            }
        }
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