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
  inline void SetIO() const { cin.tie(0)->sync_with_stdio(0); }
  void Solve() const;
  void Run() const;
};

using ll = long long;

void Solver::Solve() const {
  int n, c, d;
  cin >> n >> c >> d;
  multiset<int> vis;
  for (int i = 0; i < n * n; ++i) {
    int t;
    cin >> t;
    vis.insert(t);
  }
  for (int i = 0; i < n; ++i) {
    int t = 1 + i * c;
    for (int j = 0; j < n; ++j) {
      if (!vis.count(t)) {
        cout << "NO\n";
        return;
      }
      vis.erase(vis.find(t));
      t  += d;
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
