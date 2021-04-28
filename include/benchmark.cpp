#include "benchmark.hpp"

void runBenchmarkWizard() {
    int stage = getInt("Pasirinkite maksimalu irasu kieki (1 - 1000, 2 - 10000, 3 - 100000, 4 - 1000000, 5 - 10000000): ", 1, 5);
    int type = getInt("Pasirinkite duomenu konteinerio tipa (1 - Vector, 2 - Deque, 3 - List ): ", 1, 3);
    int strategy = getInt("Pasirinkite duomenu konteinerio skirstymo strategija (1-4): ", 1, 4);

    switch(type) {
        case 1: runBenchmark<vector<Student>>(stage, "VECTOR", strategy); break;
        case 2: runBenchmark<deque<Student>>(stage, "DEQUE", strategy); break;
        case 3: runBenchmark<list<Student>>(stage, "LIST", strategy); break;
        default: cout << "Type: 1-Vector, 2-Deque, 3-List" << endl; break;
    }
}

template <class Container>
void runBenchmark(int stage, string containerCode, int strategyType) {
    Timer timer;
    double totalTime = 0;
    double partTime;

    int stages[5] {1000,10000,100000,1000000,10000000};

    Container benchStudents;

    if (!checkIfFileExists("benchmark")) {
        if(std::system("mkdir benchmark") == 0) {
            cout << "Created benchmark folder." << endl;
        }
    }

    cout << "Entering benchmark mode. Using " << containerCode << ", strategy: " << strategyType << "." << endl;

    for(int i = 0; i < stage; i++) {
        cout << endl << "Pradedamas " << stages[i] << " irasu " << containerCode << " testas." << endl;

        timer.reset();

        if (!checkIfFileExists("benchmark/bench_data"+std::to_string(stages[i])+".txt")){
            generateFile("benchmark/bench_data"+std::to_string(stages[i])+".txt", stages[i]);

            partTime = timer.elapsed();
            totalTime += partTime;
            cout << stages[i] << " irasu failo generavimas uztruko: " << partTime << endl;
        }
        timer.reset();

        readFromFile("benchmark/bench_data"+std::to_string(stages[i])+".txt", benchStudents);
        
        partTime = timer.elapsed();
        totalTime += partTime;
        cout << stages[i] << " irasu nuskaitymas is failo uztruko: " << partTime << endl;
        timer.reset();

        sortContainer(benchStudents);

        partTime = timer.elapsed();
        totalTime += partTime;
        cout << stages[i] << " irasu rusiavimas uztruko: " << partTime << endl;
        
        
        Container coolStudents;
        Container badStudents;

        Container *_coolStudents = &coolStudents;
        Container *_badStudents = &badStudents;
        
        timer.reset();

        typename Container::iterator it = std::find_if(benchStudents.begin(), benchStudents.end(), 
                                                [](const Student &s) {return s.getFinalMeanGrade() >= splitLimit;});

        switch(strategyType) {
            case 1: 
                coolStudents.assign(it, benchStudents.end());
                badStudents.assign(benchStudents.begin(), it);
                break;
            case 2:
                while(it != benchStudents.end()) {
                    coolStudents.push_back(*it);
                    it = benchStudents.erase(it);
                }
                benchStudents.resize(benchStudents.size());
                _badStudents = &benchStudents;
                break;
            case 3: 
                coolStudents.assign(it, benchStudents.end());
                benchStudents.erase(it, benchStudents.end());
                benchStudents.resize(benchStudents.size());
                _badStudents = &benchStudents;
                break;
            case 4:
                if (containerCode != "VECTOR") {
                    cout << "Naudokite Vector klasę." << endl;
                    exit(1);
                }
                std::copy(it, benchStudents.end(), std::back_inserter(coolStudents));
                benchStudents.erase(it, benchStudents.end());
                benchStudents.resize(benchStudents.size());
                _badStudents = &benchStudents;
        }

        partTime = timer.elapsed();
        totalTime += partTime;
        cout << stages[i] << " irasu skirstymas uztruko: " << partTime << endl;
        timer.reset();

        printResults(*_badStudents, OutputType::BOTH, true, "benchmark/bench_varguoliai"+std::to_string(stages[i])+".txt", false);

        partTime = timer.elapsed();
        totalTime += partTime;
        cout << stages[i] << " irasu 'varguoliu' isvedimas i faila uztruko: " << partTime << endl;
        timer.reset();

        printResults(*_coolStudents, OutputType::BOTH, true, "benchmark/bench_kietuoliai"+std::to_string(stages[i])+".txt", false);

        partTime = timer.elapsed();
        totalTime += partTime;
        cout << stages[i] << " irasu 'kietuoliu' isvedimas i faila uztruko: " << partTime << endl;

        cout << stages[i] << " irasu testo visas laikas: " << totalTime << endl;

        benchStudents.clear();
        coolStudents.clear();
        badStudents.clear();

        totalTime = 0;
    }

    cout << endl << "Benchmark ended." << endl;
}

template void runBenchmark<vector<Student>>(int stage, string containerCode, int strategyType);
template void runBenchmark<list<Student>>(int stage, string containerCode, int strategyType);
template void runBenchmark<deque<Student>>(int stage, string containerCode, int strategyType);