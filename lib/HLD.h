#include <bits/stdc++.h>

using i64 = long long;
struct HLD {
    int n;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
    HLD(int n) : n(n), siz(n), top(n), dep(n), parent(n, -1), in(n), out(n), seq(n), adj(n) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void init(int root = 0) {
        top[root] = root;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    int cur = 0;
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
};

/*
void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    HLD tree(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        tree.addEdge(u, v);
    }
    tree.init();
    
    int q;
    std::cin >> q;
    
    std::vector<int> ans(q);
    std::vector<std::vector<std::array<int, 2>>> qry(2 * n);
    
    auto get = [&](int x, int y) {
        auto &a = tree.adj[y];
        auto it = std::upper_bound(a.begin(), a.end(), x, [&](int i, int j) {
            return tree.in[i] < tree.in[j];
        }) - 1;
        return *it;
    };
    
    for (int i = 0; i < q; i++) {
        int r, v;
        std::cin >> r >> v;
        r--, v--;
        
        if (r == v) {
            qry[n - 1].push_back({0, i});
        } else if (tree.lca(r, v) == v) {
            int y = get(r, v);
            qry[tree.in[y] + n - 1].push_back({tree.out[y], i});
        } else {
            qry[tree.out[v] - 1].push_back({tree.in[v], i});
        }
    }
    
    std::array<int, 30> t{}, p{};
    for (int i = 0; i < 2 * n; i++) {
        int x = a[tree.seq[i % n]], y = i;
        for (int j = 29; j >= 0; j--) {
            if (x >> j & 1) {
                if (t[j]) {
                    if (y > p[j]) {
                        std::swap(x, t[j]);
                        std::swap(y, p[j]);
                    }
                    x ^= t[j];
                } else {
                    t[j] = x;
                    p[j] = y;
                    break;
                }
            }
        }
        
        for (auto [l, j] : qry[i]) {
            int x = 0;
            for (int k = 29; k >= 0; k--) {
                if ((~x >> k & 1) && l <= p[k]) {
                    x ^= t[k];
                }
            }
            ans[j] = x;
        }
    }
    
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }
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
*/
