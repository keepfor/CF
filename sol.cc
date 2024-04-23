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
  vector<int> a(n);
  for (auto& i : a) cin >> i;
  a.insert(a.end(), a.begin(), a.end());
  vector<int> sum(2 * n);
  for (int i = 1; i < 2 * n; ++i) {
    sum[i] = sum[i - 1] + (a[i] < a[i - 1] ? 1 : 0);
  }
  for (int i = 0; i < n; ++i) {
    if (sum[n - i] == sum[2 * n - 1 - i]) {
      cout << i << '\n';
      return;
    }
  }
  cout << -1 << '\n';
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