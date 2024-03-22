class DSU {
 public:
  vector<int> p;
  int n;

  DSU(int n_) : n(n_) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x]))); }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      return true;
    }
    return false;
  }
};

struct DSU {
  std::vector<int> f, siz, mn, mx;
  DSU(int n) : f(n), siz(n, 1) {
    std::iota(f.begin(), f.end(), 0), mn = mx = f;
  }
  int leader(int x) {
    while (x != f[x]) x = f[x] = f[f[x]];
    return x;
  }
  bool same(int x, int y) { return leader(x) == leader(y); }
  bool merge(int x, int y) {
    x = leader(x);
    y = leader(y);
    if (x == y) return false;
    siz[x] += siz[y];
    mn[x] = std::min(mn[x], mn[y]);
    mx[x] = std::max(mx[x], mx[y]);
    f[y] = x;
    return true;
  }
  int size(int x) { return siz[leader(x)]; }
  int min(int x) { return mn[leader(x)]; }
  int max(int x) { return mx[leader(x)]; }
};
