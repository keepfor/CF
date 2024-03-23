#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

struct Solver {
  using ll = long long;

  void Solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i : a) {
      cin >> i;
    }
    sort(a.begin(), a.end());
    int x = a[n / 2];
    int ans = 0;
    for (int i = (n - 1) / 2; i < n; ++i) {
      ans += i == x;
    }
    cout << ans << '\n';
  }

  void Run() {
    auto t{1};
    cin >> t;
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
