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
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i : a)
      cin >> i;

    vector<tuple<int, int, int>> ans;
    for (int i = 0; i < n; ++i) {
      int mn = min_element(a.begin() + i, a.end()) - a.begin();
      if (mn == i) continue;
      ans.emplace_back(i + 1, n, mn - i);
      rotate(a.begin() + i, a.begin() + mn, a.end());
    }
    cout << ans.size() << '\n';
    for (auto& [x, y, z] : ans) {
      cout << x << ' ' << y << ' ' << z << '\n';
    }
    cout << '\n';
  };

  {
    int tt = 1;
    cin >> tt;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
