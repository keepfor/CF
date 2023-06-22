#include<bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include"lib/debug.h"
#else 
#define debug(...) 
#endif

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    int n; cin >> n;
    long long ans = 0;
    map<long long, long long> s;
    while (n--) {
      long long k, v; cin >> k >> v;
      ans += v;
      s[k] = v;
    }
    int m; cin >> m;
    while (m--) {
      long long k, v;
      cin >> k >> v;
      ans += max(0ll, v - s[k]);
    }
    cout << ans << '\n';
  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
