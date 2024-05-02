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
  vector<int> a(4 * n);
  for (int i = 0; i < 4 * n; ++i) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());
  for (int i = 0; i + 1 < 4 * n; i += 2) {
    if (a[i] != a[i + 1]) {
      cout << "NO\n";
      return ;
    }
  }
  int b = a[0] * a.back();
  debug(b);
  for (int i = 2; i < n; i += 4) {
    if (a[i] * a[4 * n - 2 * i] != b) {
      cout << "NO\n";
      return ;
    }
  }
  cout << "YES\n";
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
