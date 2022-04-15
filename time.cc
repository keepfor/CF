#include<bits/stdc++.h>
using namespace std;

class RunTime {
private:
    std::chrono::high_resolution_clock::time_point pre_time;
    std::chrono::high_resolution_clock::time_point cur_time;
public:
    void record() {
        pre_time = cur_time;
        cur_time = std::chrono::high_resolution_clock::now();
    } 
    void print() {
        std::chrono::duration<double, std::milli> elapsed = cur_time - pre_time;
        std::cout << "Used time: " << elapsed.count() << " ms" << std::endl;
    }
};

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0); 
  RunTime timer = RunTime();
  timer.record();
  vector<int> a(1e9);
  timer.record();
  timer.print();
  return 0;
}

