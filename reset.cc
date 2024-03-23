#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

class Solver {
 public:
  inline void Main() {
    SetIO();
    Run();
  }

 private:
  using ll = long long;

  inline void SetIO() const {
    cin.tie(0)->sync_with_stdio(0);
  }

  void Solve() const;
  void Run() const;
};

void Solver::Solve() const {

}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
