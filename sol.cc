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
  cin >> TESTCASE;
  while (TESTCASE--) {
    int n, m, d;
    cin >> n >> m >> d;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
      int x; 
      cin >> x;
      --x;
      p[x] = i;
    }
    vector<int> a(m);
    for (auto& i : a) {
      cin >> i;
      --i;
    }
    int ans = 1e9;
    for (int i = 0; i + 1 < m; ++i) {
      int x = p[a[i + 1]] - p[a[i]];
      if (x <= 0 or d - x + 1 <= 0) {
        ans = 0;
        break;
      }
      ans = min(ans, x);
      if (d < n - 1) ans = min(ans, d - x + 1);
    }
    cout << ans << '\n';
  }
  return 0;
}
