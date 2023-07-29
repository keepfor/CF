#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...)
#endif

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    int n, m;
    cin >> n >> m;
    vector<string> v(n);
    for (auto& i : v) cin >> i;
    vector<vector<int>> vis(n, vector<int>(m));
    vector<vector<int>> Pvis(n, vector<int>(m));
    vector<pair<int, int>> q;
    q.emplace_back(1, 1);
    Pvis[1][1] = 1;
    const vector<int> dirs{1, 0, -1, 0, 1};
    for (int i = 0; i < (int)q.size(); ++i) {
      auto [x, y] = q[i];
      vis[x][y] = 1;
      for (int j = 0; j < 4; ++j) {
        int xx = x;
        int yy = y;
        while (1) {
          int nx = xx + dirs[j];
          int ny = yy + dirs[j + 1];
          if (nx < 0 or ny < 0 or nx >= n or ny >= m) break;
          if (v[nx][ny] == '#') break;
          vis[nx][ny] = 1;
          swap(nx, xx);
          swap(ny, yy);
        }
        if (!Pvis[xx][yy]) {
          q.emplace_back(xx, yy);
          Pvis[xx][yy] = 1;
        }
      }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (v[i][j] == '.' and vis[i][j]) ++ans;
      }
    }
    cout << ans << '\n';
  };

  {
    int tt = 1;
    while (tt--) solve();
  }
  return 0;
}
