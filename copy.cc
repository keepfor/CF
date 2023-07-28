#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "lib/debug.h"
#else
#define debug(...) 0
#endif

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    int n;
    long long m, s, d;
    cin >> n >> m >> s >> d;
    std::vector<long long> b(n);
    for (auto& i : b) {
      cin >> i;
    }
    sort(b.begin(), b.end());
    int bb = 0;
    int x = 0;
    bool ru = 1;
    vector<long long> jump, run;
    const long long inf = 1e18;
    b.push_back(inf);
    while (true) {
      if (ru) {
        if (b[bb] > m) {
          run.push_back(m - x);
          int z = min(jump.size(), run.size());
          for (int i = 0; i < z; ++i) {
            cout << "RUN " << run[i] << '\n';
            cout <<  "JUMP " << jump[i] << '\n';
          }
          if (run.size() > z and run.back() > 0) {
            cout << "RUN " << run.back() << '\n';
          }
          return;
        }  
        int xx = b[bb] - 1;
        if (xx - x < s) {
          cout << "IMPOSSIBLE\n";
          return;
        }
        run.push_back(xx - x);
        x = xx;
        ru ^= 1;
      } else {
        int nbb = bb + 1;
        while (b[nbb] - 1 - (b[nbb - 1] + 1) < s) ++nbb;
        if (b[nbb - 1] + 1 - x > d) {
          cout << "IMPOSSIBLE\n";
          return; 
        }
        jump.push_back(b[nbb - 1] + 1 - x);
        bb = nbb;
        ru ^= 1;
        x = b[nbb - 1] + 1;
      } 
    }
  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
