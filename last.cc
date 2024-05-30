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
  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vector<int> sz(n, 1);
  auto D = [&](auto&& self, int u, int pa) -> void {
    for (auto& v : g[u]) {
      if (v != pa) {
        self(self, v, u);
        sz[u] += sz[v];
      }
    }
  };
  D(D, 0, -1);
  int ans = n;
  for (auto& v : g[0]) {
    ans = min(ans, n - sz[v]);
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
