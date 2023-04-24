#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include"lib/debug.h"
#else
#define debug(...) 
#endif

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int TESTCASES = 1;
  while (TESTCASES--) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& i : a) {
      cin >> i;
    }
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
      int u, v;
      cin >> u >> v;
      --u;
      --v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    vector<int> cnt(n, 1), p(n, -1);
    vector<long long> sum(n);
    vector<set<pair<int, int>>> ch(n);
    function<void(int, int)> dfs = [&](int u, int fa) -> void {
      sum[u] = a[u];
      for (auto& v : g[u]) {
        if (v != fa) {
          p[v] = u;
          dfs(v, u);
          sum[u] += sum[v];
          cnt[u] += cnt[v];
          ch[u].emplace(-cnt[v], v);
        }
      }
    };
    dfs(0, -1);
    while (m--) {
      int t, x;
      cin >> t >> x;
      --x;
      if (t == 1) {
        cout << sum[x] << '\n';
      } else {
        if (ch[x].empty()) {
          continue;
        }
        int c = ch[x].begin()->second;
        ch[p[x]].erase({-cnt[x], x});
        ch[x].erase({-cnt[c], c});
        sum[x] -= sum[c];
        sum[c] += sum[x];
        cnt[x] -= cnt[c];
        cnt[c] += cnt[x];
        ch[p[x]].emplace(-cnt[c], c);
        ch[c].emplace(-cnt[x], x);
        p[c] = p[x];
        p[x] = c;
      }
    }
  }
  return 0;
}