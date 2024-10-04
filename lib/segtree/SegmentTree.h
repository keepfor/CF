#include <bits/stdc++.h>

using i64 = long long;

template <class Info, class Merge = std::plus<Info>>
struct SegmentTree {
  const int n;
  const Merge merge;
  std::vector<Info> info;
  SegmentTree(int n) : n(n), merge(Merge()), info(4 << std::__lg(n)) {}
  SegmentTree(std::vector<Info> init) : SegmentTree(init.size()) {
    std::function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        info[p] = init[l];
        return;
      }
      int m = (l + r) / 2;
      build(2 * p, l, m);
      build(2 * p + 1, m, r);
      pull(p);
    };
    build(1, 0, n);
  }
  void pull(int p) { info[p] = merge(info[2 * p], info[2 * p + 1]); }
  void modify(int p, int l, int r, int x, const Info &v) {
    if (r - l == 1) {
      info[p] = v;
      return;
    }
    int m = (l + r) / 2;
    if (x < m) {
      modify(2 * p, l, m, x, v);
    } else {
      modify(2 * p + 1, m, r, x, v);
    }
    pull(p);
  }
  void modify(int p, const Info &v) { modify(1, 0, n, p, v); }
  Info rangeQuery(int p, int l, int r, int x, int y) {
    if (l >= y || r <= x) {
      return Info();
    }
    if (l >= x && r <= y) {
      return info[p];
    }
    int m = (l + r) / 2;
    return merge(rangeQuery(2 * p, l, m, x, y),
                 rangeQuery(2 * p + 1, m, r, x, y));
  }
  Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }
};

constexpr int inf = 1E9;

struct Info {
  std::array<int, 2> sid;
  int mid;
  std::array<int, 2> l;
  std::array<int, 2> r;
  std::array<int, 3> ans;

  Info()
      : sid{-inf, -1}, mid{-inf}, l{-inf, -1}, r{-inf, -1}, ans{-inf, -1, -1} {}
  Info(int x, int a, int id)
      : sid{x + a, id},
        mid{-2 * x},
        l{-x + a, id},
        r{-x + a, id},
        ans{0, id, id} {}
};

Info operator+(const Info &a, const Info &b) {
  Info c;
  c.sid = std::max(a.sid, b.sid);
  c.mid = std::max(a.mid, b.mid);
  c.l = std::max({a.l, b.l, std::array{a.sid[0] + b.mid, a.sid[1]}});
  c.r = std::max({a.r, b.r, std::array{b.sid[0] + a.mid, b.sid[1]}});
  c.ans =
      std::max({a.ans, b.ans, std::array{a.l[0] + b.sid[0], a.l[1], b.sid[1]},
                std::array{a.sid[0] + b.r[0], a.sid[1], b.r[1]}});
  return c;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<std::vector<int>> adj(n);
  for (int i = 1; i < n; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  std::vector<int> euler, teul(n), dep(n);
  const int lg = std::__lg(n);
  std::vector par(n, std::vector<int>(lg + 1, -1));
  int tm = 0;

  auto dfs = [&](auto dfs, int x) -> void {
    for (int i = 0; (2 << i) <= dep[x]; i++) {
      par[x][i + 1] = par[par[x][i]][i];
    }
    euler.push_back(x);
    teul[x] = tm++;
    for (auto y : adj[x]) {
      if (y == par[x][0]) continue;
      par[y][0] = x;
      dep[y] = dep[x] + 1;
      dfs(dfs, y);
      euler.push_back(x);
      tm++;
    }
  };
  dfs(dfs, 0);

  std::vector<Info> ini(2 * n - 1);
  for (int i = 0; i < 2 * n - 1; i++) {
    int x = euler[i];
    if (i == teul[x]) {
      ini[i] = Info(dep[x], a[x], x);
    } else {
      ini[i] = Info(dep[x], 0, x);
    }
  }
  SegmentTree<Info> seg(ini);

  int m;
  std::cin >> m;

  while (m--) {
    int x, y;
    std::cin >> x >> y;
    x--;
    a[x] = y;
    seg.modify(teul[x], Info(dep[x], a[x], x));

    auto [d, u, v] = seg.info[1].ans;

    if (dep[u] + a[u] < dep[v] + a[v]) std::swap(u, v);

    int lim = dep[u] - (d / 2 - a[u]);
    int w = u;
    for (int i = lg; i >= 0; i--) {
      if ((1 << i) <= dep[w] && dep[par[w][i]] >= lim) {
        w = par[w][i];
      }
    }
    int d1 = dep[u] + a[u] - dep[w];
    int ans = std::max(d1, d - d1);
    if (dep[w] > lim) {
      w = par[w][0];
      d1 = dep[u] + a[u] - dep[w];
      ans = std::min(ans, std::max(d1, d - d1));
    }
    std::cout << ans << "\n";
  }

  return 0;
}


namespace segtree_matrix {
  #include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
template<class Info>
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F &&pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

constexpr i64 inf = 1E18;
struct Matrix {
    i64 a[4][4];
    Matrix() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                a[i][j] = (i == j ? 0 : -inf);
            }
        }
    }
};

Matrix operator+(const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            c.a[i][j] = -inf;
            for (int k = 0; k < 4; k++) {
                c.a[i][j] = std::max(c.a[i][j], a.a[i][k] + b.a[k][j]);
            }
        }
    }
    return c;
}
void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> ord(n);
    std::iota(ord.begin(), ord.end(), 0);
    std::sort(ord.begin(), ord.end(),
        [&](int i, int j) {
            return a[i] > a[j];
        });
    
    Matrix init;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            init.a[i][j] = -inf;
        }
    }
    init.a[0][0] = 0;
    init.a[1][0] = 0;
    init.a[2][2] = 0;
    init.a[3][2] = 0;
    SegmentTree<Matrix> seg(std::vector(n, init));
    i64 ans = 0;
    for (auto i : ord) {
        Matrix m = init;
        m.a[0][1] = 1;
        m.a[0][3] = a[i] + 1;
        m.a[2][3] = 1;
        seg.modify(i, m);
        auto res = seg.rangeQuery(0, n);
        ans = std::max({ans, res.a[0][2] + a[i], res.a[0][3] + a[i]});
    }
    
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
}
