#include<bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include"lib/debug.h"
#else 
#define debug(...) 
#endif

#define int long long

void solve() {
  int v, m;
  cin >> v >> m;
  vector<int> p(v), d(v);
  set<pair<int, int>> pin, din;
  for (int i = 0; i < v; ++i) {
    cin >> p[i];
    pin.emplace(p[i], i);
  }
  for (int i = 0; i < v; ++i) {
    cin >> d[i];
  }
  int cur = 0;
  while (m--) {
    int x;
    cin >> x;
    int nx = x + cur;
    int l = min(cur, nx);
    int r = max(cur, nx);
    int ans = 0;
    auto it = din.lower_bound({l, -1});
    while (din.size()) {
      if (it == din.end()) {
        break;
      }
      if (it->first > r) {
        break;
      }
      ++ans;
      it = din.erase(it);
    }
    it = pin.lower_bound({l, -1}); 
    while (pin.size()) {
      if (it == pin.end()) {
        break;
      }
      int pp = it->first;
      if (pp > r) {
        break;
      }
      int idx = it->second;
      if (d[idx] >= l and d[idx] <= r and abs(cur - d[idx]) > abs(cur - p[idx])) {
        ++ans;
      } else {
        din.emplace(d[idx], idx);
      }
      it = pin.erase(it);
    }
    cout << ans << ' ';
    cur = nx;
  }
  cout << '\n';
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int TC = 1;
  cin >> TC;

  for (int i = 1; i <= TC; ++i) {
    cout << "Case #" << i << ": ";
    solve();
  }
  
  return 0;
}
