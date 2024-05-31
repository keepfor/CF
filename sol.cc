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
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (auto& i : a) {
    cin >> i;
  }
  sort(a.begin(), a.end());
  int ans = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    while (j < n and a[j] - a[i] < m) {
      ++j;
    }
    ans = max(ans, j - i);
  }
  cout << ans << '\n';
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
