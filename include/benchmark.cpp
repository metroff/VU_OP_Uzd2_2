#include "benchmark.hpp"

void runBenchmark(int stage) {
    int stages[5] {1000,10000,100000,1000000,10000000};

    vector<Student> benchStudents;

    cout << "Entering benchmark mode." << endl;

    for(int i = 0; i < stage; i++) {
        benchStudents.reserve(stages[i]);

        cout << endl << "Pradedamas " << stages[i] << " irasu testas." << endl;

        generateFile("benchmark/bench_data"+std::to_string(stages[i])+".txt", stages[i]);

        readFromFile("benchmark/bench_data"+std::to_string(stages[i])+".txt", benchStudents);

        sort(benchStudents.begin(), benchStudents.end(), 
            [](const Student &l, const Student &r) {return l.finalMeanGrade < r.finalMeanGrade;});

        cout << "--------------------- Sorted Bench ---------------------" << endl;

        vector<Student>::iterator it = std::find_if(benchStudents.begin(), benchStudents.end(), 
                                                [](const Student &s) {return s.finalMeanGrade >= splitLimit;});

        vector<Student> coolStudents(it, benchStudents.end());
        benchStudents.erase(it, benchStudents.end());
        benchStudents.shrink_to_fit();

        cout << "--------------------- Not Cool Bench ---------------------" << endl;

        printResults(benchStudents, OutputType::BOTH, true, "benchmark/bench_vargseliai"+std::to_string(stages[i])+".txt", false);

        cout << "--------------------- Cool Bench ---------------------" << endl;

        printResults(coolStudents, OutputType::BOTH, true, "benchmark/bench_kietuoliai"+std::to_string(stages[i])+".txt", false);

        benchStudents.clear();
    }

    cout << endl << "Benchmark ended." << endl;
}