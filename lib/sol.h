#include <bits/stdc++.h>

using namespace std;

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

void Solver::Solve() const {}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

inline void Solver::SetIO() const { cin.tie(0)->sync_with_stdio(0); }

void Solver::Main() const {
  SetIO();
  Run();
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}