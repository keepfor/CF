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
    int h, w, x, y;
    cin >> h >> w >> x >> y;
    int n;
    cin >> n;
    vector<pair<int, int>> v1, v2;
    for (int i = 0; i < n; ++i) {
      int r, c;
      cin >> r >> c;
      v1.emplace_back(r, c);
      v2.emplace_back(c, r);
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    int q;
    cin >> q;
    while (q--) {
      char d;
      int l;
      cin >> d >> l;
      if (d == 'R') {
        int z = w;
        auto it = upper_bound(v1.begin(), v1.end(), make_pair(x, y));
        if (it != v1.end()) {
          auto t = *it;
          if (t.first == x) {
            z = t.second - 1;
          }
        }
        y = min(z, y + l);
      } else if (d == 'L') {
        int z = 1;
        auto it = lower_bound(v1.begin(), v1.end(), make_pair(x, y));
        if (it != v1.begin()) {
          auto t = *prev(it);
          if (t.first == x) {
            z = t.second + 1;
          }
        } 
        y = max(z, y - l);
      } else if (d == 'U') {
        int z = 1;
        auto it = lower_bound(v2.begin(), v2.end(), make_pair(y, x));
        if (it != v2.begin()) {
          auto t = *prev(it);
          if (t.first == y) {
            z = t.second + 1;
          }
        }
        x = max(z, x - l);
      } else {
        int z = h;
        auto it = upper_bound(v2.begin(), v2.end(), make_pair(y, x));
        if (it != v2.end()) {
          auto t = *it;
          if (t.first == y) {
            z = t.second - 1;
          }
        }
        x = min(z, x + l);
      }
      cout << x << ' ' << y << '\n';
    } 
  }
  return 0;
}
