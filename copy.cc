#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include"./lib/debug.h"
#else 
#define debug(...) 
#endif

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int TESTCASE = 1;
  while (TESTCASE--) {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
      int u, v;
      cin >> u >> v;
      --u;
      --v;
      g[u].push_back(v);
      g[v].push_back(u);
      ++d[u];
      ++d[v];
    }
    vector<int> q;
    for (int i = 0; i < n; ++i) {
      if (d[i] == 1) {
        q.push_back(i);
      }
    }
    vector<bool> vis(n);
    for (int i = 0; i < (int) q.size(); ++i) {
      auto u = q[i];
      vis[u] = 1;
      for (auto& v : g[u]) {
        --d[v];
        if (d[v] == 1) {
          q.push_back(v);
        }
      }
    }
    vector<int> c(n);
    function<void(int, int, int)> dfs = [&](int u, int fa, int co) {
      c[u] = co;
      for (auto& v : g[u]) {
        if (v == fa or !vis[v]) {
          continue;
        }
        dfs(v, u, co);
      }
    };
    for (int i = 0; i < n; ++i) {
      if (!vis[i]) {
        dfs(i, -1, i + 1);
      }
    }
    int qq;
    cin >> qq;
    while (qq--) {
      int u, v;
      cin >> u >> v;
      --u;
      --v;
      cout << (c[u] == c[v] ? "Yes" : "No") << '\n';
    }
  }
  return 0;
}
