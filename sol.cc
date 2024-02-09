#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

#include <bits/stdc++.h>

using namespace std;

void SolveOne() {
  string s;
  cin >> s;
  const int n = s.size();
  auto G = [&]() -> vector<int> {
    const int m = 2 * n - 1;
    vector<int> ans(m);
    int l = -1;
    int r = -1;
    for (int i = 0; i < m; ++i) {
      int x = (i + 1) / 2;
      int y = (i) / 2;
      int d = 0;
      if (x < r) {
        d = min(r - x, ans[2 * (l + r) - i]);
      }
      while (x - d - 1 >= 0 and y + d + 1 < n) {
        if (s[x - d - 1] != s[y + d + 1]) {
          break;
        }
        ++d;
      }
      if (y + d > r) {
        r = y + d;
        l = x - d;
      }
      ans[i] = d;
    }
    return ans;
  };
  vector<int> ma = G();
  int vis = 0;
  while (2 * vis + 2 <= n and s[vis] == s[n - 1 - vis]) {
    ++vis;
  }
  int len = 0;
  int st = 0;
  for (int i = 0; i < (int)ma.size(); ++i) {
    int x = (i + 1) / 2;
    int y = (i) / 2;
    if (x > y and !ma[i]) {
      continue;
    }
    int l = x - ma[i];
    int r = y + ma[i];
    if (l < vis) {
      int d = vis - l;
      l += d;
      r -= d;
    }
    if (r > n - vis - 1) {
      int d = r - n + vis + 1;
      l += d;
      r -= d;
    }
    if (l != vis and r != n - vis - 1) {
      continue;
    }
    if (r - l + 1 > len) {
      len = r - l + 1;
      st = l;
    }
  }
  cout << s.substr(0, vis) + s.substr(st, len) + s.substr(n - vis, vis) << '\n';
}

void SolveAll() {
  auto t{1};
  cin >> t;
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
