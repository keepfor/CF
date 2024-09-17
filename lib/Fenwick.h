template <typename T>
class Fenwick {
 public:
  vector<T> fenw;
  int n;

  Fenwick(int _n) : n(_n) { fenw.resize(n); }

  void modify(int x, T v) {
    while (x < n) {
      fenw[x] += v;
      x |= (x + 1);
    }
  }

  void ModifyMax(int x, T v) {
    while (x < n) {
      fenw[x] = max(fenw[x], v);
      x |= (x + 1);
    }
  }

  T get(int x) {
    T v{};
    while (x >= 0) {
      v += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }

  T GetMax(int x) {
    T v{};
    while (x >= 0) {
      v = max(v, fenw[x]);
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};

class Solution {
public:
    int maxPathLength(vector<vector<int>>& a, int k) {
        const int n = a.size();
        vector<int> y(n);
        for (int i = 0; i < n; ++i) {
          y[i] = a[i][1];
        }
        sort(y.begin(), y.end());
        y.resize(unique(y.begin(), y.end()) - y.begin());
        vector<array<int, 3>> p(n);
        for (int i = 0; i < n; ++i) {
          int py = lower_bound(y.begin(), y.end(), a[i][1]) - y.begin();
          p[i] = {a[i][0], py + 1, i};
        }
        sort(p.begin(), p.end());
        const int m = y.size();
        Fenwick<int> f(m);
        vector<int> pre(n);
        for (int i = 0; i < n;) {
          auto u = p[i];
          vector<array<int, 2>> vis;
          while (i < n && p[i][0] == u[0]) {
            int t = f.GetMax(p[i][1] - 1);
            pre[p[i][2]] = t + 1;
            vis.push_back({p[i][1], t + 1});
            ++i;
          }
          for (auto& i : vis) {
            f.ModifyMax(i[0], i[1]);
          }
        }
        Fenwick<int> sf(m);
        vector<int> suf(n);
        for (int i = n - 1; i >= 0;) {
          auto u = p[i]; 
          vector<array<int, 2>> vis;
          while (i >= 0 && p[i][0] == u[0]) {
            int t = sf.GetMax(m - p[i][1]);
            suf[p[i][2]] = t + 1;
            vis.push_back({m - p[i][1] + 1, t + 1});
            --i;
          }
          for (auto& i : vis) {
            sf.ModifyMax(i[0], i[1]);
          }
        }
        return pre[k] + suf[k] - 1;
    }
};
