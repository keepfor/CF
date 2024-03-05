#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

using ll = long long;

void SolveOne() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    if (i & 1) {
      a[i] *= -1;
    }
  }
  set<ll> vis;
  ll sum = 0;
  vis.insert(0);
  for (auto& i : a) {
    sum += (ll)i;
    if (vis.count(sum)) {
      cout << "YES\n";
      return;
    }
    vis.insert(sum);
  }
  cout << "NO\n";
}

void SolveAll() {
  auto t{1};
  cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

signed main() {
  SetIO();
  SolveAll();
  return 0;
}
