#include <bits/stdc++.h>

using i64 = long long;
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
struct HLD {
    int n;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
    int cur;
    
    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 0) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
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
    
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    
    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        
        int d = dep[u] - k;
        
        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }
        
        return seq[in[u] - dep[u] + d];
    }
    
    bool isAncester(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }
    
    int rootedParent(int u, int v) {
        std::swap(u, v);
        if (u == v) {
            return u;
        }
        if (!isAncester(u, v)) {
            return parent[u];
        }
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }
    
    int rootedSize(int u, int v) {
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    }
    
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, M;
    std::cin >> N >> M;
    
    std::vector<int> U(M), V(M), W(M);
    std::vector<std::vector<int>> edge(M + 1);
    for (int i = 0; i < M; i++) {
        std::cin >> U[i] >> V[i] >> W[i];
        U[i]--, V[i]--;
        edge[W[i]].push_back(i);
    }
    
    int Q;
    std::cin >> Q;
    
    std::vector<int> A(Q), S(Q), T(Q);
    std::vector<std::vector<int>> qry(M + 1);
    for (int i = 0; i < Q; i++) {
        std::cin >> A[i] >> S[i] >> T[i];
        S[i]--, T[i]--, A[i]--;
        qry[W[A[i]] - 1].push_back(i);
        qry[W[A[i]]].push_back(i);
    }
    
    std::vector<int> ans(Q, 1);
    
    DSU dsu(N);
    HLD t(N);
    std::vector<bool> vis(M);
    for (int i = 0; i <= M; i++) {
        for (auto j : edge[i]) {
            if (dsu.merge(U[j], V[j])) {
                t.addEdge(U[j], V[j]);
            } else {
                vis[j] = true;
            }
        }
        for (auto j : qry[i]) {
            if (W[A[j]] == i + 1 && dsu.same(S[j], T[j])) {
                ans[j] = 0;
            }
            if (W[A[j]] == i && !dsu.same(S[j], T[j])) {
                ans[j] = 0;
            }
        }
    }
    t.work();
    
    dsu.init(N);
    for (int i = 0; i <= M; i++) {
        for (auto j : edge[i]) {
            if (vis[j]) {
                int u = U[j], v = V[j];
                u = dsu.find(u);
                v = dsu.find(v);
                while (u != v) {
                    if (t.dep[u] < t.dep[v]) {
                        std::swap(u, v);
                    }
                    dsu.merge(t.parent[u], u);
                    u = dsu.find(u);
                }
            }
        }
        for (auto j : qry[i]) {
            if (W[A[j]] == i) {
                if (vis[A[j]]) {
                    ans[j] = 0;
                } else {
                    int u = U[A[j]], v = V[A[j]];
                    if (t.dep[u] < t.dep[v]) {
                        std::swap(u, v);
                    }
                    if (t.isAncester(u, S[j]) == t.isAncester(u, T[j])) {
                        ans[j] = 0;
                    }
                    if (dsu.find(u) != u) {
                        ans[j] = 0;
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < Q; i++) {
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}