#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include"lib/debug.h"
#else
#define debug(...) 
#endif
[i][i][j][j][l][i][j][k][i][k][j][j][k][j][j]
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int TESTCASES = 1;
  cin >> TESTCASES;
  while (TESTCASES--) {
    long long k;
    cin >> k;
    vector<int> d;
    while (k) {
      d.push_back(k % 9);
      k /= 9;
    }
    reverse(d.begin(), d.end());
    for (auto& i : d) {
      if (i >= 4) ++i;
      cout << i;
    }
    cout << '\n';
  }
  return 0;
}
