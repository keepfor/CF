#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include"lib/debug.h"
#else
#define debug(...) 
#endif

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int TESTCASES = 1;
  cin >> TESTCASES;
  while (TESTCASES--) {
    string s; cin >> s;
    int a = -1;
    int n = (int) s.size();
    for (int i = 1; i < n - 1; ++i) {
      if (s[i] == 'a') {
        a = i;
        break;
      }
    }
    if (a == -1) {
      cout << s.front() << ' ' << s.substr(1, n - 2) << ' ' << s.back();
    } else {
      cout << s.substr(0, a) << ' ' << 'a' << ' ' << s.substr(a + 1);
    }
    cout << '\n';
  }
  return 0;
}
