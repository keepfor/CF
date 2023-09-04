#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    int a, b, c;
    cin >> a >> b >> c;
    for (int i = 0; i <= c / a; ++i) {
      if ((c - a * i) % b == 0) {
        cout << "Yes\n";
        return;
      }
    }
    cout << "No\n";
    return;
  };

  {
    int tt = 1;
    while (tt--) solve();
  }
  return 0;
}
