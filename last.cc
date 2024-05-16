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
const int inf = 1e9;
const vector<int> dirs{1, 0, -1, 0, 1};

void Solver::Solve() const {
  int n;
  cin >> n;
  vector<string> a(n);
  for (auto& i : a) {
    cin >> i;
  }
  function<int(int, int, char)> D = [&](int s, int t, char c) -> int {
    set<pair<int, int>> mn;
    vector<int> dis(n * n, inf);
    mn.emplace(0, s);
    dis[s] = 0;
    while (mn.size()) {
      auto [d, u] = *mn.begin();
      mn.erase(mn.begin());
      if (d > dis[u]) {
        continue;
      }
      int x = u / n;
      int y = u % n;
      for (int i = 0; i < 4; ++i) {
        int nx = x + dirs[i];
        int ny = y + dirs[i + 1];
        if (nx < 0 or ny < 0 or nx >= n or ny >= n) {
          continue;
        }
        int nd = d;
        int v = nx * n + ny;
        if (a[nx][ny] == c) {
          ++nd;          
        } 
        if (dis[v] > nd) {
          mn.emplace(nd, v);
          dis[v] = nd;
        }
      }
    }
    return dis[t];
  };
  cout << D(0, n * n - 1, 'B') + D(n - 1, n * (n - 1), 'R') << '\n'; 
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