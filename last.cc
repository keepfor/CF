#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

class Solver {
 public:
  inline void Main() const {
    SetIO();
    Run();
  }

 private:
  inline void SetIO() const { 
    cin.tie(0)->sync_with_stdio(0); 
  }
  void Solve() const;
  void Run() const;
};

using ll = long long;

void Solver::Solve() const {
  int n;
  cin >> n;
  vector<ll> a(3), b(3);
  for (auto& i : a) {
    cin >> i;
  }
  for (auto& i : b) {
    cin >> i;
  }
  cout << max({0ll, a[0] + b[1] - n, a[1] + b[2] - n, a[2] + b[0] - n}) << ' ';
  cout << min(a[0], b[1]) + min(a[1], b[2]) + min(a[2], b[0]) << '\n';
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
