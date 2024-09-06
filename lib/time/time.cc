#include <bits/stdc++.h>

using namespace std;

class Time {
 public:
  std::chrono::time_point<std::chrono::high_resolution_clock> t1;
  std::chrono::time_point<std::chrono::high_resolution_clock> t2;
  void start() { t1 = std::chrono::high_resolution_clock::now(); }
  void end() { t2 = std::chrono::high_resolution_clock::now(); }
  void get() {
    end();
    std::chrono::duration<double, std::milli> elapsed = t2 - t1;
    std::cout << "duration: " << elapsed.count() << " ms" << std::endl;
  }
};


#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

class Solver {
 public:
  void Main() const;

 private:
  void SetIO() const;
  void Run() const;
  void Solve() const;
};

void Solver::Solve() const {
  using ll = long long;
  int n;
  string s, t;
  cin >> n >> s >> t;
  s += "..";
  t += "..";
  n += 2;
  vector<string> q{s};
  map<string, int> dis;
  dis[s] = 0;
  for (int i = 0; i < (int) q.size(); ++i) {
    auto u = q[i];
    int now = dis[u];
    for (int j = 0; j + 1 < n; ++j) {
      if (u[j] == '.' && u[j + 1] == '.') {
        for (int k = 0; k + 1 < n; ++k) {
          if (u[k] != '.' && u[k + 1] != '.') {
            swap(u[j], u[k]);
            swap(u[j + 1], u[k + 1]);
            if (!dis.count(u) || dis.count(u) && dis[u] > now + 1) {
              dis[u] = now + 1;
              q.push_back(u);
            }
            swap(u[j], u[k]);
            swap(u[j + 1], u[k + 1]);
          }
        }
        break;
      }
    }
  }
  if (!dis.count(t)) {
    dis[t] = -1;
  }
  cout << dis[t] << '\n';
}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  Time t;
  while (tt--) {
    t.start();
    Solve();
    t.get();
  }
}

inline void Solver::SetIO() const { 
  cin.tie(0)->sync_with_stdio(0); 
}

void Solver::Main() const {
  SetIO();
  Run();
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}