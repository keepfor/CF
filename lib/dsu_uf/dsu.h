#include <bits/stdc++.h>

struct DSU {
  std::vector<int> f, siz;
  DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
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
    f[y] = x;
    return true;
  }
  int size(int x) { return siz[leader(x)]; }
};

namespace push {
class Solver {
 public:
  void Main() const;

 private:
  void SetIO() const;
  void Run() const;
  void Solve() const;
};

struct DSU {
  std::vector<int> f, siz;
  vector<vector<int>> group;
  DSU(int n) : f(n), siz(n, 1) { 
    std::iota(f.begin(), f.end(), 0);
    group.resize(n);
    for (int i = 0; i < n; ++i) {
      group[i].push_back(i);
    }
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
    f[y] = x;
    return true;
  }

  bool unite_push(int x, int y) {
    x = leader(x);
    y = leader(y);
    if (x == y) return false;
    siz[x] += siz[y];
    f[y] = x;
    for (auto& i : group[y]) {
      group[x].push_back(i);
    }
    return true;
  }

  int size(int x) { return siz[leader(x)]; }
};

void Solver::Solve() const {
  int n, q;
  cin >> n >> q;
  DSU dsu(n);
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      if (u > v) {
        swap(u, v);
      }
      dsu.unite_push(u, v);
      u = dsu.leader(u);
      auto& g = dsu.group[u];
      sort(g.rbegin(), g.rend());
      if (g.size() > 10) {
        g.resize(10);
      }
    } else {
      int v, k;
      cin >> v >> k;
      //debug(v, k);
      --v; --k;
      int ans = -2;
      v = dsu.leader(v);
      auto g = dsu.group[v];
      //debug(g, k);
      if (k < (int) g.size()) {
        ans = g[k];
      }
      cout << ans + 1 << '\n';
    }
  }
}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

inline void Solver::SetIO() const { 
  cin.tie(0)->sync_with_stdio(0); 
}

void Solver::Main() const {
  SetIO();
  Run();
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
}
