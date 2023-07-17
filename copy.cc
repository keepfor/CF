#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "lib/debug.h"
#else 
#define debug(...) 0
#endif

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i : a) {
      cin >> i;
    }
    vector<int> f;
    for (auto& i : a) {
      auto it = upper_bound(f.begin(), f.end(), i);
      if (it != f.end()) {
        *it = i;
      } else {
        f.push_back(i);
      }
    }
    cout << f.size() << '\n';
  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
