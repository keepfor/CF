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
    int n, x;
    cin >> n >> x;
    int c = 0;
    int s = 0;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        if (t == x) {
            ++c;
        }
        s += t;
    }
    if (c == n) {
        cout << 0 << '\n';
    } else if (s == n * x) {
        cout << 1 << '\n';
    } else {
        cout << 2 << '\n';
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