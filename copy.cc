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
  while (TESTCASE--) {
    int n, q; cin >> n >> q;
    vector<int> ca(n), co(n); 
    int cai = 0, nc = 0;
    while (q--) {
      int t; cin >> t;
      if (t == 1) {
        ca[cai] = 1;
        ++cai;
      } else if (t == 2) {
        int x; cin >> x;
        --x; 
        co[x] = 1;
      } else {
        while (nc < n and co[nc]) ++nc;
        cout << nc + 1 << '\n';
      }  
    }
  }
  return 0;
}
