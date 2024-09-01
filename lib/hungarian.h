/**
 *    author:  tourist
 *    created: 08.04.2024 10:55:02
 **/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

template <typename T>
class hungarian {
 public:
  int n;
  int m;
  vector<vector<T>> a;
  vector<T> u;
  vector<T> v;
  vector<int> pa;
  vector<int> pb;
  vector<int> way;
  vector<T> minv;
  vector<bool> used;
  T inf;

  hungarian(int _n, int _m) : n(_n), m(_m) {
    assert(n <= m);
    a = vector<vector<T>>(n, vector<T>(m));
    u = vector<T>(n + 1);
    v = vector<T>(m + 1);
    pa = vector<int>(n + 1, -1);
    pb = vector<int>(m + 1, -1);
    way = vector<int>(m, -1);
    minv = vector<T>(m);
    used = vector<bool>(m + 1);
    inf = numeric_limits<T>::max();
  }

  inline void add_row(int i) {
    fill(minv.begin(), minv.end(), inf);
    fill(used.begin(), used.end(), false);
    pb[m] = i;
    pa[i] = m;
    int j0 = m;
    do {
      used[j0] = true;
      int i0 = pb[j0];
      T delta = inf;
      int j1 = -1;
      for (int j = 0; j < m; j++) {
        if (!used[j]) {
          T cur = a[i0][j] - u[i0] - v[j];
          if (cur < minv[j]) {
            minv[j] = cur;
            way[j] = j0;
          }
          if (minv[j] < delta) {
            delta = minv[j];
            j1 = j;
          }
        }
      }
      for (int j = 0; j <= m; j++) {
        if (used[j]) {
          u[pb[j]] += delta;
          v[j] -= delta;
        } else {
          minv[j] -= delta;
        }
      }
      j0 = j1;
    } while (pb[j0] != -1);
    do {
      int j1 = way[j0];
      pb[j0] = pb[j1];
      pa[pb[j0]] = j0;
      j0 = j1;
    } while (j0 != m);
  }

  inline T current_score() { return -v[m]; }

  inline T solve() {
    for (int i = 0; i < n; i++) {
      add_row(i);
    }
    return current_score();
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
      cin >> s[i];
    }
    vector<int> x(k), y(k), p(k);
    for (int i = 0; i < k; i++) {
      cin >> x[i] >> y[i] >> p[i];
      --x[i];
      --y[i];
    }
    const int MAX = 20;
    hungarian<int64_t> h(MAX, k + MAX);
    int64_t p3 = 1;
    for (int r = 1; r <= MAX; r++) {
      p3 *= 3;
      for (int i = 0; i < k; i++) {
        int64_t v = p3;
        for (int dx = -r; dx <= r; dx++) {
          for (int dy = -r; dy <= r; dy++) {
            if (dx * dx + dy * dy <= r * r) {
              int nx = x[i] + dx;
              int ny = y[i] + dy;
              if (nx >= 0 && ny >= 0 && nx < n && ny < m) {
                if (s[nx][ny] == '#') {
                  v -= p[i];
                }
              }
            }
          }
        }
        h.a[r - 1][i] = v;
      }
    }
    cout << -h.solve() << '\n';
  }
  return 0;
}
