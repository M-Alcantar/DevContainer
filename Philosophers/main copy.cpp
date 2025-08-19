#include<memory>
#include<string>
#include<thread>
#include<print>
#include<mutex>
#include<vector>

class Fork {
    std::mutex mutex;

public:
    void pickUp() {
        mutex.lock();
    }
    void putDown() {
        mutex.unlock();
    }
};

class Philosopher {
    std::shared_ptr<Fork> leftFork;
    std::shared_ptr<Fork> rightFork;
    std::string name;

public:
    Philosopher(std::string name) : name(name) {
    }

    void eat() {
        while(true) {
            leftFork->pickUp();
            // std::println("{} picked up left fork", name);
            rightFork->pickUp();
            // std::println("{} picked up right fork", name);

            // std::println("{} started eating", name);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            // std::println("{} finished eating", name);

            leftFork->putDown();
            // std::println("{} put left fork down", name);
            rightFork->putDown();
            // std::println("{} put right fork down", name);
        }
    } //println commented to avoid red squiggly lines

    std::shared_ptr<Fork> &LeftFork() {
        return leftFork;
    }
    std::shared_ptr<Fork> &RightFork() {
        return rightFork;
    }
};

int main() {
    // Vector initialization
    const int num = 5;
    std::vector<std::shared_ptr<Fork>> forks(num);
    std::vector<Philosopher> philosophers;
    std::vector<std::thread> threads;

    // Creation of fork pointers
    for(int i=0; i < num; i++) {
        forks[i] = std::make_shared<Fork>();
    }

    // Philosopher creation and assignation
    for(int i=0; i < num; i++) {
        philosophers.emplace_back("Esrec #" + std::to_string(i+1));
        philosophers[i].LeftFork() = forks[i]; 
        philosophers[i].RightFork() = forks[(i+1) % num]; //Philosopher 5 gets fork 1 as right fork
    }

    // Thread creation and joining
    for(auto &shrek : philosophers) {
        threads.emplace_back(&Philosopher::eat, &shrek);
    }

    for(auto &t : threads) {
        t.join();
    }

    return 0;
}