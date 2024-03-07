#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

using ll = long long;

void Solve() {
  int n, k;
  cin >> n >> k;
  vector<int> v(k);
  for (auto& i : v) {
    cin >> i;
    --i;
  }
  vector<vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    for (int j = 0; j < t; ++j) {
      int p;
      cin >> p;
      --p;
      g[i].push_back(p);
    }
  }
  vector<int> co(n);
  vector<int> ans;
  function<void(int)> Dfs = [&](int u) -> void {
    co[u] = 1;
    for (auto& v : g[u]) {
      if (co[v] == 1) {
        cout << -1 << '\n';
        exit(0);
      } else if (!co[v]) {
        Dfs(v);
      }
    }
    co[u] = 2;
    ans.push_back(u);
  };
  for (int i = 0; i < k; ++i) {
    if (co[v[i]]) {
      continue;
    }
    Dfs(v[i]);
  }
  const int z = ans.size();
  cout << z << '\n';
  for (int i = 0; i < z; ++i) {
    cout << ans[i] + 1 << " \n"[i + 1 == z];
  }
}

void Main() {
  auto t{1};
  // cin >> t;
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
