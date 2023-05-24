#include<bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include"lib/debug.h"
#else 
#define debug(...) 
#endif

void solve() {
  string s;
  cin >> s;
  int n = s.size();
  int c = count(s.begin(), s.end(), s[0]);
  if (c == n) {
    cout << (n + 1) / 2 << '\n';
    return;
  }
  if (s[0] == s[n - 1]) {
    string t;
    int i = 0;
    while (i < n and s[i] == s[n - 1]) {
      ++i;
    }
    int j = i;
    for (int k = j; k < n; ++k) {
      t += s[k];
    }
    for (int k = 0; k < i; ++k) {
      t += s[k];
    }
    swap(s, t);
  }
  map<char, int> dp;
  for (auto j : "RPS") {
    dp[j] = 1;
  }
  dp[s[0]] = 0;
  for (int i = 1; i < n; ++i) {
    map<char, int> ndp;
    for (auto& [k, v] : dp) {
      for (auto j : "RPS") {
        if (k == j) {
          continue;
        }
        int x = v + (s[i] != j);
        if (ndp.count(j)) {
          ndp[j] = min(ndp[j], x);
        } else {
          ndp[j] = x;
        }
      }
    }
    swap(ndp, dp);
  }
  int ans = 1e9;
  for (auto& [i, j] : dp) {
    ans = min(ans, j);
  }
  cout << ans << '\n';
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
