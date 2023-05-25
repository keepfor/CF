#include<bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include"lib/debug.h"
#else 
#define debug(...) 
#endif

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> s(n);
  for (auto& i : s) {
    cin >> i;
  }
           k 
   kk
   int
   int  
   int  
   ifdef

  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int p;
    cin >> p;
    g[i].push_back(p);
  }
  vector<int> pre(n), post(n);
  dfs(0, -1);
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
