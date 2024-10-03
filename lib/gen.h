#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

uint64_t random_address() { char *p = new char; delete p; return uint64_t(p); }

const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);

mt19937_64 rng(SEED);

class Solver {
 public:
  void Main() const;

 private:
  void SetIO() const;
  void Run() const;
  void Solve() const;
};

void Solver::Solve() const {
  int t = 100;
  cout << t << '\n';
  while (t--) {
    int n = 5000;
    cout << n << '\n';
    int z = 1e6 + 1;
    for (int i = 0; i < n; ++i) {
      cout << (rng() % z) << " \n"[i + 1 == n];
    }
  }

}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
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
