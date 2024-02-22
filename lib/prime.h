#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

#include <bits/stdc++.h>

using namespace std;

template <class T>
struct Prime {
  vector<bool> p;
  Prime(T z) {
    p.assign(z, true);
    p[0] = p[1] = false;
    for (T i = 2; i < z; ++i) {
      if (!p[i]) {
        continue;
      }
      for (T j = i + i; j < z; j += i) {
        p[j] = false;
      }
    }
  }
  bool operator[](T x) { return p[x]; }
};

const int z = 1e6 + 1;
Prime<int> p(z);

class Solution {
 public:
  int mostFrequentPrime(vector<vector<int>>& v) {
    map<int, int> cnt;
    const int n = v.size();
    const int m = v[0].size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        int now = v[i][j];
        for (int x = -1; x <= 1; ++x) {
          for (int y = -1; y <= 1; ++y) {
            int t = now;
            if (x or y) {
              int xx = i;
              int yy = j;
              while (1) {
                xx += x;
                yy += y;
                if (xx < 0 or yy < 0 or xx >= n or yy >= m) {
                  break;
                }
                t = t * 10 + v[xx][yy];
                if (t <= 10 or !p[t]) {
                  continue;
                }
                ++cnt[t];
              }
            } else {
              if (t <= 10 or !p[t]) {
                continue;
              }
              ++cnt[t];
            }
          }
        }
      }
    }
    int ans = -1;
    int mx = 0;
    for (auto& [i, j] : cnt) {
      if (j >= mx) {
        ans = i;
        mx = j;
      }
    }
    return ans;
  }
};

void SolveOne() {
  Solution s;
  // vector<vector<int>> v{{1, 1}, {9, 9}, {1, 1}};
  vector<vector<int>> v{{9, 7, 8}, {4, 6, 5}, {2, 8, 6}};
  debug(s.mostFrequentPrime(v));
};

void SolveAll() {
  auto t{1};
  // cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

signed main() {
  SetIO();
  SolveAll();
  return 0;
}
