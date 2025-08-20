#include<algorithm>
#include<iostream>
#include<random>
#include<thread>
#include<vector>

// SumMachine class definition
class SumMachine {
    int id;
    int total;

public:
    SumMachine(int id) : id(id) {
    }

    // Task for summing random numbers
    void randomSum() {
        // Making use of <random> to seed number generation
        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_int_distribution<int> dist(1, 1000);

        total = 0;
        for(int i=0; i < 100; i++) {
            total += dist(gen);
        }
    }

    int Id() const {
        return id;
    }
    int Total() const {
        return total;
    }
};

int main() {
    const int num = 10;
    std::vector<SumMachine> sumMachines;
    std::vector<std::thread> threads;

    // Initializing each SumMachine and respective thread
    for(int i=0; i < num; i++) {
        sumMachines.emplace_back(i+1);
    }
    for(auto &sM : sumMachines) {
        threads.emplace_back(&SumMachine::randomSum, &sM);
    }
    for(auto &t : threads) {
        t.join();
    }

    std::cout << "Thread #\tTotal" << std::endl;
    for(auto &sM : sumMachines) {
        std::cout << sM.Id() << "\t\t" << sM.Total() << std::endl;
    }

    // Using std::sort with a custom function to sort SumMachines in descending order
    std::sort(sumMachines.begin(), sumMachines.end(), [](const SumMachine& a, const SumMachine& b) {
        return a.Total() > b.Total();
    });
    std::cout << "\nThread with highest total: Thread #" << sumMachines[0].Id() << std::endl;

    return 0;
}