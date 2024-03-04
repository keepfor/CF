#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

using ll = long long;
const int inf = 1e9;
const vector<int> dirs{1, 0, -1, 0, 1};

void Solve() {
  int r, c;
  cin >> r >> c;
  vector<string> v(r);
  int ex, ey;
  for (int i = 0; i < r; ++i) {
    cin >> v[i];
    for (int j = 0; j < c; ++j) {
      if (v[i][j] == 'E') {
        ex = i;
        ey = j;
      }
    }
  }
  queue<pair<int, int>> q{{{ex, ey}}};
  vector<vector<int>> d(r, vector<int>(c, inf));
  d[ex][ey] = 0;
  auto ok = [&](int x, int y) -> bool {
    if (x < 0 or y < 0 or x >= r or y >= c or v[x][y] == 'T' or
        d[x][y] != inf) {
      return false;
    }
    return true;
  };
  while (q.size()) {
    auto [x, y] = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
      int nx = x + dirs[i];
      int ny = y + dirs[1 + i];
      if (!ok(nx, ny)) {
        continue;
      }
      d[nx][ny] = d[x][y] + 1;
      q.emplace(nx, ny);
    }
  }
  int need = -1;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if (v[i][j] == 'S') {
        need = d[i][j];
      }
    }
  }
  assert(need != -1);
  assert(need != inf);
  int ans = 0;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if (isdigit(v[i][j]) and d[i][j] <= need) {
        ans += v[i][j] - '0';
      }
    }
  }
  cout << ans << '\n';
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
