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
    long long l, r, d;
    cin >> l >> r >> d;
    if (d < l) {
      cout << d << '\n';
    } else {
      long long ans = (d + r) / d * d;
      cout << ans << '\n';
    }
  }
  return 0;
}
