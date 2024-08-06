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

#include <bits/stdc++.h>

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, Q;
    std::cin >> N >> Q;
    
    std::vector<int> L(Q), R(Q), C(Q);
    for (int i = 0; i < Q; i++) {
        std::cin >> L[i] >> R[i] >> C[i];
        L[i]--;
    }
    
    std::vector<int> p(Q);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(),
        [&](int i, int j) {
            return C[i] < C[j];
        });
    
    DSU dsu(N);
    i64 ans = 0;
    for (auto i : p) {
        ans += C[i];
        for (int x = dsu.find(L[i]); x < R[i] - 1; x = dsu.find(x)) {
            dsu.merge(x + 1, x);
            ans += C[i];
        }
    }
    if (dsu.find(0) != N - 1) {
        std::cout << -1 << "\n";
    } else {
        std::cout << ans << "\n";
    }
    
    return 0;
}
