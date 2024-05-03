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
  int x = n;
  
  vector<int> d;
  bool ok = true;
  while (x) {
    int y = x % 3;
    if (y > 1) {
      ok = false;
    }
    d.push_back(y);
    x /= 3;
  }
  if (ok) {
    cout << n << '\n';
    return;
  }
  const int m = d.size();
  int pos = -1;
  for (int i = m - 1; i >= 0; --i) {
    if (d[i] == 2) {
      pos = i;
      break;
    }
  }
  if (pos == -1) {
    d.push_back(1);
  } else {
    d[pos] = 0;
    if (pos == m - 1) {
      d.push_bac
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
  