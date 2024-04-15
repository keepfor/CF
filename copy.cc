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
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += (2 * i - 1) * i;
  }
  cout << ans << ' ';
  cout << 2 * n << '\n';
  for (int j = n; j >= 1; --j) {
    for (int k : {1, 2}) {
      cout << k << ' ' << j << ' ';
      for (int x = 1; x <= n; ++x) {
        cout << x << " \n"[x == n];
      }
    }
  }
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
