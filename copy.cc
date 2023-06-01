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

  auto solve = [&]() {
    map<string, map<string, string>> a;
    cout << a["string"][""] << '\n';
  };

  int TC = 1;

  for (int i = 1; i <= TC; ++i) {
    cout << "Case #" << i << ": ";
    solve();
  }
  
  return 0;
}
