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
    long long n;
    int k;
    cin >> n >> k;
    const long long inf = 1e18;
    long long mn = inf;
    long long type = 1;
    long long cnt = 0;
    for (int i = 1; i <= k; ++i) {
      long long t; cin >> t;
      if (t > n) {
         continue;
      }
      if (n % t < mn) {
        mn = n % t;
        type = i;
        cnt = n / t;
      }
    }
    cout << type << ' ' << cnt << '\n';
  };

  {
    int TC = 1;

    for (int i = 1; i <= TC; ++i) {
      solve();
    }
  }

  return 0;
}
