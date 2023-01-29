#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include"lib/debug.h"
#else
#define debug(...) 
#endif

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int TESTCASES = 1;
  cin >> TESTCASES;
  auto f = [&](auto self, long long x, long long y) -> long long {
    if (x > y) swap(x, y);
    return !x ? y : self(self, y % x, x);
  };
  while (TESTCASES--) {
    int n; cin >> n;
    vector<int> v(n);
    for (auto& i : v) cin >> i;
    vector<long long> pre(n + 1);
    for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] + v[i];
    long long ans = 1;
    for (int i = 1; i < n; ++i) {
      long long x = pre[i];
      long long y = pre[n] - pre[i];
      ans = max(ans, f(f, x, y));
    }
    cout << ans << '\n';
  }
  return 0;
}
