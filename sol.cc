#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

using ll = long long;

void Solve() {
  int n;
  cin >> n;
  vector<int> t(n);
  for (auto& i : t) {
    cin >> i;
  }
  vector<int> f(n, -1);
  vector<int> cnt(n);
  for (int i = 0; i < n; ++i) {
    cin >> f[i];
    if (!f[i]) {
      continue;
    }
    --f[i];
    ++cnt[f[i]];
  }
  vector<int> ans;
  for (int i = 0; i < n; ++i) {
    if (t[i]) {
      vector<int> tm{i};
      int u = f[i];
      while (u != -1 and !t[u] and cnt[u] == 1) {
        tm.push_back(u);
        u = f[u];
      }
      if (tm.size() > ans.size()) {
        ans = tm;
      }
    }
  }
  const int z = ans.size();
  cout << z << '\n';
  for (int i = z - 1; i >= 0; --i) {
    cout << ans[i] + 1 << " \n"[!i];
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
