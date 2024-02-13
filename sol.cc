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
  vector<bool> vis(n + 1);
  for (int i = 2; i <= n; ++i) {
    bool p = true;
    for (int j = 2; j * j <= i; ++j) {
      if (i % j == 0) {
        p = false;
        break;
      }
    }
    if (p) {
      if (2 * i > n) {
        continue;
      }
      for (int j = i; j <= n; j += i) {
        vis[j] = 1;
      }
    }
  }
  int p = count(vis.begin(), vis.end(), true);
  vector<int> cnt(26);
  for (auto& i : s) {
    ++cnt[i - 'a'];
  }
  for (int i = 0; i < 26; ++i) {
    if (cnt[i] >= p) {
      string ans(n, '?');
      for (int j = 0; j < n; ++j) {
        if (vis[j + 1]) {
          ans[j] = char('a' + i);
          --cnt[i];
        }
      }
      for (int j = 0; j < n; ++j) {
        if (!vis[j + 1]) {
          for (int k = 0; k < 26; ++k) {
            if (cnt[k]) {
              ans[j] = char('a' + k);
              --cnt[k];
              break;
            }
          }
        }
      }
      cout << "YES\n";
      cout << ans << '\n';
      exit(0);
    }
  }
  cout << "NO\n";
}

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
