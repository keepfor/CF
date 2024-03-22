#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

struct Solver {
  using ll = long long;

  void Solve() { debug(1); }

  void Run() {
    auto t{1};
    // cin >> t;
    while (t--) {
      Solve();
    }
  }

  inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

  void Main() {
    SetIO();
    Run();
  }
};

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
