#include<iostream>
#include<random>
#include<thread>
#include<vector>

class SumMachine {
    int total;

public:
    void randomSum() {
        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_int_distribution<int> dist(1, 1000);

        total = 0;
        for(int i=0; i < 100; i++) {
            total += dist(gen);
        }
    }

    int Total() const {
        return total;
    }
};

int main() {
    const int num = 10;
    std::vector<SumMachine> sumMachines(num);
    std::vector<std::thread> threads;
    int highestTotal = 0;
    int highestThread = 0;

    for(auto &sM : sumMachines) {
        threads.emplace_back(&SumMachine::randomSum, &sM);
    }
    for(auto &t : threads) {
        t.join();
    }

    std::cout << "Thread #\tTotal" << std::endl;
    for(int i=0; i < sumMachines.size(); i++) {
        auto thisTotal = sumMachines[i].Total();
        std::cout << i+1 << "\t\t" << thisTotal << std::endl;
        if(thisTotal > highestTotal) {
            highestTotal = thisTotal;
            highestThread = i;
        }
    }

    std::cout << "\nThread with highest total: Thread #" << highestThread+1 << std::endl;

    return 0;
}