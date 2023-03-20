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
    long long l;
    int n, m;
    cin >> l >> n >> m;
    vector<int> a(n), b(m);
    for (auto& i : a) cin >> i;
    for (auto& i : b) cin >> i;
    int ai = 0, bi = 0;
    long long ans = 0;
    while (ai < n) {
      auto& [v1, l1] = a[ai];
      auto& [v2, l2] = b[bi];
      if (!l1) ++ai;
      if (!l2) ++bi;
      int mn = min(l1, l2);
      l1 -= mn;
      l2 -= mn;
      if (v1 == v2) ++ans;
    }
    cout << ans << '\n';
  }
  return 0;
}
