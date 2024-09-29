#include<bits/stdc++.h>
#include "atcoder/dsu"

using namespace std;
using namespace atcoder;

class lowlink {
    int n;
    vector<vector<pair<int, int>>> G;
    vector<int> in, out, low;
    unordered_map<int, int> bridge;
    
    void dfs(int u, int p, int &k) {
        in[u] = low[u] = k++;
        for (auto [v, id]: G[u]) {
            if (in[v] < 0) {
                dfs(v, id, k);
                low[u] = min(low[u], low[v]);
                if (low[v] > in[u]) bridge[id] = v;
            } else if (id != p) {
                low[u] = min(low[u], in[v]);
            }
        }
        out[u] = k;
    }
    
    void init() {
        n = G.size();
        in.assign(n, -1);
        out.assign(n, -1);
        low.assign(n, -1);
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (in[i] < 0) dfs(i, -1, k);
        }
    }

public:
    lowlink(const vector<vector<pair<int, int>>> &G) : G(G) { init(); }
    
    bool query(int a, int s, int t) {
        assert(0 <= s and s < n);
        assert(0 <= t and t < n);
        assert(s != t);
        if (!bridge.count(a)) return false;
        int l = in[bridge[a]], r = out[bridge[a]];
        s = in[s], t = in[t];
        return (l <= s and s < r) xor (l <= t and t < r);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> u(m), v(m), w(m);
    vector<vector<int>> weight(m);
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        --u[i], --v[i], --w[i];
        weight[w[i]].push_back(i);
    }
    int q;
    cin >> q;
    vector<int> a(q), s(q), t(q);
    for (int i = 0; i < q; i++) {
        cin >> a[i] >> s[i] >> t[i];
        --a[i], --s[i], --t[i];
    }
    vector<int> ans(q, -1);
    vector<int> ord(q);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) { return w[a[i]] < w[a[j]]; });
    
    // Process the queries where original d(s[j], t[j]) does not coincides with w[a[j]]
    dsu uf(n);
    int l = 0;
    for (int i = 0; i < m; i++) {
        int r = l;
        while (r < q and w[a[ord[r]]] == i) ++r;
        for (int j = l; j < r; j++) {
            if (uf.same(s[ord[j]], t[ord[j]])) ans[ord[j]] = 0;
        }
        for (int j: weight[i]) {
            uf.merge(u[j], v[j]);
        }
        for (int j = l; j < r; j++) {
            if (!uf.same(s[ord[j]], t[ord[j]])) ans[ord[j]] = 0;
        }
        l = r;
    }
    
    uf = dsu(n);
    int it = 0;
    for (int i = 0; i < m; i++) {
        vector<int> ls; // The set of representative elements of the currenct connected components that are connected to a weight-i edge
        for (int j: weight[i]) {
            ls.push_back(uf.leader(u[j]));
            ls.push_back(uf.leader(v[j]));
        }
        sort(ls.begin(), ls.end());
        ls.erase(unique(ls.begin(), ls.end()), ls.end());
        int sz = ls.size();
        vector<vector<pair<int, int>>> G(sz); // edge = (to, id)
        for (int j: weight[i]) {
            int nu = lower_bound(ls.begin(), ls.end(), uf.leader(u[j])) - ls.begin();
            int nv = lower_bound(ls.begin(), ls.end(), uf.leader(v[j])) - ls.begin();
            if(nu != nv) {
                G[nu].emplace_back(nv, j);
                G[nv].emplace_back(nu, j);
            }
        }
        lowlink lk(G);
        while (it < q and w[a[ord[it]]] == i) {
            int now = ord[it++];
            if (ans[now] != -1) continue;
            int ns = lower_bound(ls.begin(), ls.end(), uf.leader(s[now])) - ls.begin();
            int nt = lower_bound(ls.begin(), ls.end(), uf.leader(t[now])) - ls.begin();
            assert(ns != nt);
            assert(ns < sz and nt < sz);
            assert(ls[ns] == uf.leader(s[now]) and ls[nt] == uf.leader(t[now]));
            // Does ns-nt path always contain a[now] on G?
            ans[now] = lk.query(a[now], ns, nt);
        }
        for (int j: weight[i]) {
            uf.merge(u[j], v[j]);
        }
    }
    
    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
}
