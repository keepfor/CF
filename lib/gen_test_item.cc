#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif

using namespace std;

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s;
  while (getline(cin, s)) {
    auto it = s.find("Name");
    if (it != string::npos) {
      string t = s;
      int i = 0;
      while (i < (int)t.size() and t[i] == ' ') {
        ++i;
      }
      t = t.substr(i);
      t.pop_back();
      cout << t << '\n';
      cout << "Log:\n";
    }
  }
  return 0;
}
