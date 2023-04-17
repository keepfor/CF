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
  while (TESTCASE--) {
    int n;
    cin >> n;
    vector<int> t(2 * n + 2);
    for (int i = 1; i <= n; ++i) {
      int p;
      cin >> p;
      t[2 * i] = t[2 * i + 1] = t[p] + 1;
    }
    for (int i = 1; i < 2 * n + 2; ++i) {
      cout << t[i] << " \n"[i == 2 * n + 1];
    }
  }
  return 0;
}
