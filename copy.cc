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
    int n, k; cin >> n >> k;
    for (int i = 0, l = 1, r = n; i < n; ++i) {
      if (i & 1) {
        cout << l << ' ';
        ++l;
      } else {
        cout << r << ' ';
        --r;
      }
    }
    cout << '\n';
  }
  return 0;
}
