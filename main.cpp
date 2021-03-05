#include "include/myLib.hpp"
#include "include/struct.hpp"
#include "include/student.hpp"
#include "include/console.hpp"
#include "include/input.hpp"
#include "include/output.hpp"
#include "include/file.hpp"
#include <exception>

int main() {
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