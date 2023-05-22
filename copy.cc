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
  while (TESTCASES--) {
    int n, k;
    cin >> n >> k;
    vector<int> c(k);
    for (int i = 0; i < n; ++i) {
      int t;
      cin >> t;
      ++c[t - 1];
    }
    int odd = 0;
    int ans = 0;
    for (auto& i : c) {
      if (!i) {
        continue;
      }
      if (i & 1) {
        ++odd;
        --i;
      }
      ans += i;
    }
    ans += (odd + 1) / 2;
    cout << ans << '\n';
  }
  return 0;
}
