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
  auto f = [&](int x, int y) {
    if (x == y or x == '?' or y == '?') {
      return true;
    }
    return false;
  };
  while (TESTCASE--) {
    string s, t; cin >> s >> t;
    int n = s.size();
    int m = t.size();
    vector<int> pre(m + 1), suf(m + 1);
    pre[0] = suf[0] = 1;
    for (int i = 0; i < min(m, n); ++i) {
      if (!pre[i]) {
        break;
      }
      if (pre[i] and f(s[i], t[i])) {
        pre[i + 1] = 1;
      }
    }
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    for (int i = 0; i < min(m, n); ++i) {
      if (!suf[i]) {
        break;
      }
      if (suf[i] and f(s[i], t[i])) {
        suf[i + 1] = 1;
      }
    }   
    bool ok = true;
    for (int i = 0; i <= m; ++i) {
      if (!pre[i] or !suf[m - i]) {
        cout << "No\n";
      } else {
        cout << "Yes\n";
      }
    }
  }
  return 0;
}
