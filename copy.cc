#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

#include <bits/stdc++.h>

using namespace std;

void SolveOne() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> a(n, vector<int>(m));
  vector<vector<int>> b(n, vector<int>(m));
  vector<vector<int>> c(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j] >> b[i][j] >> c[i][j];
    }
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      vector<int> t;
      for (int x = 0; x < m; ++x) {
        for (int y = 0; y < c[i][x]; ++y) {
          t.push_back(b[j][x] - a[i][x]);
        }
      }
      sort(t.rbegin(), t.rend());
      t.resize(k);
      int tmp = 0;
      for (auto& i : t) {
        if (i <= 0) {
          break;
        }
        tmp += i;
      }
      ans = max(ans, tmp);
    }
  }
  cout << ans << '\n';
};

void SolveAll() {
  auto t{1};
  // cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

signed main() {
  SetIO();
  SolveAll();
  return 0;
}
