#include<bits/stdc++.h>

#ifdef LOCAL
#include"debug.h"
#else 
#define debug(...) 0
#endif

using namespace std;

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    string s;
    cin >> s;
    if ((int) s.size() == 1) {
      cout << "NO\n";
      continue;
    }
    bool no = false;
    for (int i = 0; i < (int) s.size(); ++i) {
      if (i and s[i] == s[i - 1] and s[i] == 'B') {
        no = true;
        break;
      }
    }
    cout << (no ? "NO" : "YES") << '\n';
  }
  return 0;
}
