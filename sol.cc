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

struct DSU {
  std::vector<int> f, siz, mn, mx;
  DSU(int n) : f(n), siz(n, 1) {
    std::iota(f.begin(), f.end(), 0), mn = mx = f;
  }
  int leader(int x) {
    while (x != f[x]) x = f[x] = f[f[x]];
    return x;
  }
  bool same(int x, int y) { return leader(x) == leader(y); }
  bool merge(int x, int y) {
    x = leader(x);
    y = leader(y);
    if (x == y) return false;
    siz[x] += siz[y];
    mn[x] = std::min(mn[x], mn[y]);
    mx[x] = std::max(mx[x], mx[y]);
    f[y] = x;
    return true;
  }
  int size(int x) { return siz[leader(x)]; }
  int min(int x) { return mn[leader(x)]; }
  int max(int x) { return mx[leader(x)]; }
};

void Solver::Solve() const {
  int h, w;
  cin >> h >> w;
  vector<string> s(h);
  for (auto& i : s) {
    cin >> i;
  }
  DSU ds(h * w);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (s[i][j] != '#') {
        continue;
      }
      int u = i * w + j;
      for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
          if (!x and !y) {
            continue;
          }
          int nx = i + x;
          int ny = j + y;
          if (nx < 0 or ny < 0 or nx >= h or ny >= w or s[nx][ny] == '.') {
            continue;
          }
          int v = nx * w + ny;
          ds.merge(u, v);
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < h * w; ++i) {
    int x = i / w;
    int y = i % w;
    if (s[x][y] != '#') {
      continue;
    }
    if (i == ds.leader(i)) {
      ++ans;
    }
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
