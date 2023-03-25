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
    int n, m;
    cin >> n >> m;
    vector<int> d(n);
    vector<pair<int, int>> e(m);
    for (int i = 0; i < m; ++i) {
      cin >> e[i].first >> e[i].second;
      --e[i].first;
      --e[i].second;
    }
    int k;
    cin >> k;
    vector<int> vis(m);
    while (k--) {
      int x;
      cin >> x;
      --x;
      ++d[e[x].first];
      ++d[e[x].second];
      vis[x] = 1;
    }
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    function<int(int)> find = [&](int x) -> int {
      return p[x] == x ? x : p[x] = find(p[x]);
    };
    auto unite = [&](int u, int v) -> void {
      u = find(u);
      v = find(v);
      if (u == v) return;
      d[u] += d[v];
      p[v] = u;
    };
    for (int i = 0; i < m; ++i) {
      if (!vis[i]) {
        unite(e[i].first, e[i].second);
      }
    }
    int c = 0;
    for (int i = 0; i < n; ++i) {
      if (find(i) == i and d[i] & 1) {
        ++c;
      }
    }
    if (c <= 2) cout << "Yes";
    else cout << "No";
    cout << '\n';
  }
  return 0;
}
