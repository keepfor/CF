#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

using ll = long long;
const ll inf = 1e18;

template <typename T>
struct TreeDiameter {
  T d;
  vector<vector<int>> g;
  vector<int> par;
  vector<int> dep;
  int n;

  TreeDiameter(vector<vector<int>> g_) : g{g_} {
    n = g.size();
    par.resize(n);
    dep.resize(n);
  }

  void Dfs(int u) {
    for (auto& v : g[u]) {
      if (v != par[u]) {
        par[v] = u;
        dep[v] = dep[u] + 1;
        Dfs(v);
      }
    }
  }

  void GetD(int u) {
    par[u] = -1;
    dep[u] = 0;
    Dfs(u);
  }

  vector<int> Get() {
    GetD(0);
    array<int, 2> p{0, 0};
    for (int i = 0; i < n; ++i) {
      if (dep[i] > dep[p[0]]) {
        p[0] = i;
      }
    }
    GetD(p[0]);
    for (int i = 0; i < n; ++i) {
      if (dep[i] > dep[p[1]]) {
        p[1] = i;
      }
    }
    vector<int> ans{p[1]};
    while (ans.back() != p[0]) {
      ans.push_back(par[ans.back()]);
    }
    return ans;
  }
};

void Solve() {
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
  TreeDiameter<int> td{g};
  vector<int> d = td.Get();
  const int z = d.size();
  vector<pair<int, int>> ans;
  if (z % 4 == 0) {
    for (int i = 1; i < z / 2; i += 2) {
      ans.emplace_back(d[z / 2], i);
      ans.emplace_back(d[z / 2 - 1], i);
    }
  } else {
    for (int i = 0; i < z / 2 + 1; ++i) {
      ans.emplace_back(d[z / 2], i);
    }
  }
  cout << ans.size() << '\n';
  for (auto& [i, j] : ans) {
    cout << i + 1 << ' ' << j << '\n';
  }
}

void Main() {
  auto t{1};
  cin >> t;
  while (t--) {
    Solve();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

signed main() {
  SetIO();
  Main();
  return 0;
}
