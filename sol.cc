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
  debug(n);
  vector<int> a(n);
  int g = 0;
  for (auto& i : a) {
    cin >> i;
    g = gcd(g, i);
  }
  debug(g);
  for (auto& i : a) {
    i /= g;
    while (i % 2 == 0) {
      i /= 2;
    }
    while (i % 3 == 0) {
      i /= 3;
    }
    if (i != 1) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

signed main() {
  debug("hello\n");
  // Solver solver;
  // solver.Main();
  return 0;
}
