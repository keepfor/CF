#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

void SolveOne() {
  // TODO
  int n;
  cin >> n;
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first;
    a[i].second = i;
  }
  if (!a[0].first) {
    cout << -1 << '\n';
    return;
  }
  sort(a.begin() + 1, a.end(), greater<pair<int, int>>());
  int j = 1;
  vector<pair<int, int>> ans;
  for (int i = 0; i < n; ++i) {
    while (j < n and a[i].first) {
      ans.emplace_back(a[i].second, a[j].second);
      ++j;
      --a[i].first;
    }
    if (j == n) {
      break;
    }
  }
  if (j != n) {
    cout << -1 << '\n';
    return;
  }
  const int m = ans.size();
  cout << m << '\n';
  for (int i = 0; i < m; ++i) {
    cout << ans[i].first + 1 << ' ' << 1 + ans[i].second << '\n';
  }
};

void Solve() {
  int t = 1;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

int32_t main() {
  SetIO();
  Solve();
  return 0;
}
