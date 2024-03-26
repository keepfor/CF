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
  using ll = long long;

  inline void SetIO() const {
    cin.tie(0)->sync_with_stdio(0);
  }

  void Solve() const;
  void Run() const;
};

void Solver::Solve() const {
  int n, k;
  cin >> n >> k;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int l = 1;
  int r = n;
  auto Can = [&](int mid) -> bool {
    int cnt = 0;
    auto Dfs = [&](auto&& self, int u, int pa) -> int {
      int z = 1;
      for (auto& v : g[u]) {
        if (v == pa) {
          continue;
        }
        z += self(self, v, u);
      }
      if (z >= mid) {
        ++cnt;
        return 0;
      }
      return z;
    };
    Dfs(Dfs, 0, -1);
    return cnt >= k + 1;
  };
  while (l < r) {
    int mid = 1 + l + r >> 1;
    if (Can(mid)) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  cout << r << '\n';
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
