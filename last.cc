#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

class Solver {
 public:
  inline void Main() const {
    SetIO();
    Run();
  }

 private:
  inline void SetIO() const { 
    cin.tie(0)->sync_with_stdio(0); 
  }
  void Solve() const;
  void Run() const;
};

using ll = long long;

template<typename T>
class RangeSum2D {
 public:
  int n;
  int m;
  vector<vector<T>> sum;
  vector<vector<T>> a;
  RangeSum2D(vector<vector<T>> a_) : a(a_) {
    n = a.size();
    m = a[0].size();
    sum.resize(n + 1, vector<T>(m + 1));
  }

  void B(T x) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (!i and !j) {
          sum[i][j] = int(a[i - 1][j - 1] == x);
        } else if (!i) {
          sum[i][j] = int(a[i - 1][j - 1] == x) + sum[i][j - 1];
        } else if (!j) {
          sum[i][j] = int(a[i - 1][j - 1] == x) + sum[i - 1][j];
        } else {
          sum[i][j] = int(a[i - 1][j - 1] == x) + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
      }
    }    
  }

  T Q(int x, int y, int nx, int ny) {
    return sum[nx + 1][ny + 1] - sum[nx + 1][y] - sum[x][1 + ny] + sum[x][y];
  }
};

void Solver::Solve() const {
  int h, w, k;
  cin >> h >> w >> k;
  vector<vector<int>> a(h, vector<int>(w));
  for (int i = 0; i < h; ++i) {
    string t;
    cin >> t;
    for (int j = 0; j < w; ++j) {
      if (t[j] == 'o') a[i][j] = 1;
      if (t[j] == 'x') a[i][j] = 2;
    }
  }
  RangeSum2D<int> o(a);
  RangeSum2D<int> x(a);
  o.B(1);
  x.B(2);
  // vector<vector<int>> o(h + 1, vector<int>(w + 1));
  // vector<vector<int>> x(h + 1, vector<int>(w + 1));
  // for (int i = 1; i <= h; ++i) {
  //   for (int j = 1; j <= w; ++j) {
  //     if (!i and !j) {
  //       o[i][j] = int(s[i - 1][j - 1] == 'o');
  //     } else if (!i) {
  //       o[i][j] = int(s[i - 1][j - 1] == 'o') + o[i][j - 1];
  //     } else if (!j) {
  //       o[i][j] = int(s[i - 1][j - 1] == 'o') + o[i - 1][j];
  //     } else {
  //       o[i][j] = int(s[i - 1][j - 1] == 'o') + o[i - 1][j] + o[i][j - 1] - o[i - 1][j - 1];
  //     }
  //   }
  // }
  // for (int i = 1; i <= h; ++i) {
  //   for (int j = 1; j <= w; ++j) {
  //     if (!i and !j) {
  //       x[i][j] = int(s[i - 1][j - 1] == 'x');
  //     } else if (!i) {
  //       x[i][j] = int(s[i - 1][j - 1] == 'x') + x[i][j - 1];
  //     } else if (!j) {
  //       x[i][j] = int(s[i - 1][j - 1] == 'x') + x[i - 1][j];
  //     } else {
  //       x[i][j] = int(s[i - 1][j - 1] == 'x') + x[i - 1][j] + x[i][j - 1] - x[i - 1][j - 1];
  //     }
  //   }
  // }
  // auto Q = [](vector<vector<int>>& sum, int px, int y, int nx, int ny) -> int {
  //   return sum[nx + 1][ny + 1] - sum[nx + 1][y] - sum[px][1 + ny] + sum[px][y];
  // };
  const int inf = 1e9;
  int ans = inf;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (i >= k - 1) {
        if (!x.Q(i - (k - 1), j, i, j)) {
          ans = min(ans, k - o.Q(i - (k - 1), j, i, j));
        }
      }
      if (j >= k - 1) {
        if (!x.Q(i, j - (k - 1), i, j)) {
          ans = min(ans, k - o.Q(i, j - (k - 1), i, j));
        }
      }
    }
  }
  if (ans >= inf) {
    ans = -1;
  }
  cout << ans << '\n';
}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
