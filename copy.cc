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
  cin >> TESTCASE;
  while (TESTCASE--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    set<pair<char, char>> vis;
    for (int i = 0; i + 1 < n; ++i) {
      vis.emplace(s[i], s[i + 1]);
    }
    cout << vis.size() << '\n';
  }
  return 0;
}
