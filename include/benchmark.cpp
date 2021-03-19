#include "benchmark.hpp"

void runBenchmark(int stage) {
    Timer timer;
    double totalTime = 0;
    double partTime;

    int stages[5] {1000,10000,100000,1000000,10000000};

    vector<Student> benchStudents;

    if(std::system("mkdir benchmark") == 0) {
        cout << "Created benchmark folder." << endl;
    }

    cout << "Entering benchmark mode." << endl;

    for(int i = 0; i < stage; i++) {
        benchStudents.reserve(stages[i]);

        cout << endl << "Pradedamas " << stages[i] << " irasu testas." << endl;

        timer.reset();

        generateFile("benchmark/bench_data"+std::to_string(stages[i])+".txt", stages[i]);

        partTime = timer.elapsed();
        totalTime += partTime;
        cout << stages[i] << " irasu failo generavimas uztruko: " << partTime << endl;
        timer.reset();

        readFromFile("benchmark/bench_data"+std::to_string(stages[i])+".txt", benchStudents);
        
        partTime = timer.elapsed();
        totalTime += partTime;
        cout << stages[i] << " irasu nuskaitymas is failo uztruko: " << partTime << endl;
        timer.reset();

        sort(benchStudents.begin(), benchStudents.end(), 
            [](const Student &l, const Student &r) {return l.finalMeanGrade < r.finalMeanGrade;});

        vector<Student>::iterator it = std::find_if(benchStudents.begin(), benchStudents.end(), 
                                                [](const Student &s) {return s.finalMeanGrade >= splitLimit;});

        vector<Student> coolStudents(it, benchStudents.end());
        benchStudents.erase(it, benchStudents.end());
        benchStudents.shrink_to_fit();

        partTime = timer.elapsed();
        totalTime += partTime;
        cout << stages[i] << " irasu skirstymas uztruko: " << partTime << endl;
        timer.reset();

        printResults(benchStudents, OutputType::BOTH, true, "benchmark/bench_varguoliai"+std::to_string(stages[i])+".txt", false);

        partTime = timer.elapsed();
        totalTime += partTime;
        cout << stages[i] << " irasu 'varguoliu' isvedimas i faila uztruko: " << partTime << endl;
        timer.reset();

        printResults(coolStudents, OutputType::BOTH, true, "benchmark/bench_kietuoliai"+std::to_string(stages[i])+".txt", false);

        partTime = timer.elapsed();
        totalTime += partTime;
        cout << stages[i] << " irasu 'kietuoliu' isvedimas i faila uztruko: " << partTime << endl;

        cout << stages[i] << " irasu testo visas laikas: " << totalTime << endl;

        benchStudents.clear();

        totalTime = 0;
    }

    cout << endl << "Benchmark ended." << endl;
}