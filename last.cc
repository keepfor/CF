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
  int n, k;
  cin >> n >> k;
  if (n == 1) {
    cout << k << '\n';
    return;
  }
  int x = 1;
  while (((x << 1) + 1) <= k) {
    x <<= 1;
    ++x;
  }
  cout << x << ' ' << k - x;
  for (int i = 0; i < n - 2; ++i) {
    cout << ' ' << 0;
  }
  cout << '\n';
}

void Solver::Run() const {
  auto tt{1};
  cin >> tt;
  while (tt--) {
    Solve();
  }
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
