#ifndef CP
#define CP
#include<bits/stdc++.h>
using namespace std;
#endif

#ifdef LOCAL
#include"lib/debug.h"
#else
#define debug(...) 
#endif

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  vector<int> a{10, 0, 10, 0};
  for (int i = 0; i < 10; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < 10; ++j) {
      if (s[j] == '#') {
        a[0] = min(a[0], i);
        a[1] = max(a[1], i);
        a[2] = min(a[2], j);
        a[3] = max(a[3], j);
      }
    }
  }
  cout << a[0] + 1 << ' ' << a[1] + 1 << '\n';
  cout << a[2] + 1 << ' ' << a[3] + 1 << '\n';
  return 0;
}
