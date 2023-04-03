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
  while (TESTCASES--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i : a) cin >> i;
    vector<pair<int, int>> ans;
    while (1) {
      bool ok = 0;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (a[i] > a[j] and (a[i] + a[j] - 1) / a[j] < a[i]) {
            a[i] = (a[i] + a[j] - 1) / a[j];
            ok = 1;
            ans.emplace_back(i, j);
          }
        }
      }
      if (!ok) break;
    }
    int c = count(a.begin(), a.end(), a[0]);
    if (c == a.size()) {
      cout << ans.size() << '\n';
      for (auto& [i, j] : ans) {
        cout << i + 1 << ' ' << j + 1 << '\n';
      }
    } else {
      cout << -1 << '\n';
    }
  }
  return 0;
}
