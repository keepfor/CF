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
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cout << i << ' ';
      for (int j = n; j >= 1; --j) {
        if (j != i) {
          cout << j << ' ';
        }
      }
      cout << '\n';
    }
  }
  return 0;
}
