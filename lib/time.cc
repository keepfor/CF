#include<bits/stdc++.h>
using namespace std;

class Time {
public:
    std::chrono::time_point<std::chrono::high_resolution_clock> t1;
    std::chrono::time_point<std::chrono::high_resolution_clock> t2;
    void start() {
        t1 = std::chrono::high_resolution_clock::now();
    }
    void end() {
        t2 = std::chrono::high_resolution_clock::now();
    }
    void get() {
        std::chrono::duration<double, std::milli> elapsed = t2 - t1;
        std::cout << "duration: " << elapsed.count() << " ms" << std::endl;
    }
};


