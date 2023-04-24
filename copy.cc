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
    vector<vector<long long>> v(m);
    for (int i = 0; i < n; ++i) {
      long long s;
      cin >> s;
      int j = i + 1;
      s += j;
      int cnt = 0;
      if (s < 0) {
        int c = (int) (-s + j - 1) / j;
        cnt = c;
        s += 1ll * c * j;
      }
      while (s < n and cnt < m) {
        v[cnt++].push_back(s);
        s += 1ll * j;
      }
    }
    for (auto& i : v) {
      vector<bool> vis(n + 1);
      for (auto& j : i) {
        if (j < n) {
          vis[j] = 1;
        }
      }
      for (int j = 0;j <= n; ++j) {
        if (!vis[j]) {
          cout << j << '\n';
          break;
        }
      }
    }
  }
  return 0;
}
