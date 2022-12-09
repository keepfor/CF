#ifndef CP
#define CP
#include<bits/stdc++.h>
using namespace std;
#endif

#ifdef LOCAL
#include"./lib/debug.h"
#else 
#define debug(...) 0
#endif

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt = 1;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto& i : a) cin >> i;
    for (auto& i : b) cin >> i;
    long long ans = 0;
    for (int i = 0; i + 1 < n; ++i) {
      long long x = abs(a[i] - a[i + 1]) + abs(b[i] - b[i + 1]);
      long long y = abs(a[i] - b[i + 1]) + abs(b[i] - a[i + 1]);
      ans += min(x, y);
    }
    cout << ans << '\n';
  }
  return 0;
}
