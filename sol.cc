#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "lib/debug.h"
#else 
#define debug(...) 0
#endif

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < m; ++i) {
      int u, v;
      long long w;
      cin >> u >> v >> w;
      --u; --v;
      g[u].emplace_back(v, w);
      g[v].emplace_back(u, w);
    }
    int k; cin >> k;
    vector<int> ans(n, -1);
    priority_queue<array<long long, 3>, vector<array<long long, 3>>, greater<>> q;
    for (int i = 0; i < k; ++i) {
      int a; cin >> a; --a;
      ans[a] = 0;
      for (auto& [v, w] : g[a]) {
        q.push({w, v, -1});
      }
    }
    int d; cin >> d;
    for (int i = 0; i < d; ++i) {
      long long x; cin >> x;
      vector<array<long long, 3>> nex;
      while (q.size() and q.top()[0] <= x) {
        auto [w, u, t] = q.top(); q.pop();
        if (t != -1 and t < i) continue;
        if (ans[u] != -1) continue;
        ans[u] = 1 + i;
        for (auto& [v, ww] : g[u]) {
          if (ans[v] != -1) continue;
          q.push({w + ww, v, i});
          nex.push_back({ww, v, -1});
        }
      }
      for (auto& t : nex) q.push(t);
    }
    for (int i = 0; i < n; ++i) {
      cout << ans[i] << "\n";
    }
  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
