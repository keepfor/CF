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
  vector<bool> getResults(vector<vector<int>>& q) {
    set<int> p{0};
    for (auto& i : q) {
      if (i[0] != 1) {
        continue;
      }
      p.insert(i[1]);
    }
    int pre = -1;
    const int mxn = 5e4;
    fenwick<int> f(mxn + 1);
    for (auto& i : p) {
      if (pre != -1) {
        f.ModifyMax(i, i - pre);
      }
      pre = i;
    }
    const int m = q.size();
    vector<bool> ans;
    for (int i = m - 1; i >= 0; --i) {
      auto it = p.lower_bound(q[i][1]);
      if (q[i][0] == 1) {
        if (it != p.end()) {
          f.ModifyMax(*next(it), *next(it) - *prev(it));
        }
        p.erase(it);
      } else {
        const int z = q[i][2];
        ans.push_back((q[i][1] - *prev(it) >= z) or (f.GetMax(q[i][1]) >= z));
      }
    }
    reverse(ans.begin(), ans.end());
    return ans;
  }
};
