#include <bits/stdc++.h>

using i64 = long long;

template<class Info,
    class Merge = std::plus<Info>>
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
    void pull(int p) {
        info[p] = merge(info[2 * p], info[2 * p + 1]);
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
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
};

constexpr int inf = 1E9;

struct Info {
    std::array<int, 2> sid;
    int mid;
    std::array<int, 2> l;
    std::array<int, 2> r;
    std::array<int, 3> ans;
    
    Info() : sid{-inf, -1}, mid{-inf}, l{-inf, -1}, r{-inf, -1}, ans{-inf, -1, -1} {}
    Info(int x, int a, int id) : sid{x + a, id}, mid{-2 * x}, l{-x + a, id}, r{-x + a, id}, ans{0, id, id} {}
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.sid = std::max(a.sid, b.sid);
    c.mid = std::max(a.mid, b.mid);
    c.l = std::max({a.l, b.l, std::array{a.sid[0] + b.mid, a.sid[1]}});
    c.r = std::max({a.r, b.r, std::array{b.sid[0] + a.mid, b.sid[1]}});
    c.ans = std::max({a.ans, b.ans, std::array{a.l[0] + b.sid[0], a.l[1], b.sid[1]}, std::array{a.sid[0] + b.r[0], a.sid[1], b.r[1]}});
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
