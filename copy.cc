#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

using ll = long long;

void Solve() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (auto& i : a) {
    cin >> i;
  }
  vector<int> x(n);
  for (auto& i : x) {
    cin >> i;
    i = abs(i);
  }
  vector<int> ord(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(),
       [&](int i, int j) -> bool { return x[i] < x[j]; });
  ll sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += 1ll * a[ord[i]];
    if (sum > 1ll * k * x[ord[i]]) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
}

void Main() {
  auto t{1};
  cin >> t;
  while (t--) {
    Solve();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

signed main() {
  SetIO();
  Main();
  return 0;
}
