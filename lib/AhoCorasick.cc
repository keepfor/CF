#include <bits/stdc++.h>

using i64 = long long;

struct AhoCorasick {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len;
        int link;
        std::array<int, ALPHABET> next;
        Node() : link{}, next{} {}
    };
    
    std::vector<Node> t;
    
    AhoCorasick() {
        init();
    }
    
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }
    
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    
    int add(const std::vector<int> &a) {
        int p = 1;
        for (auto x : a) {
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        return p;
    }
    
    int add(const std::string &a, char offset = 'a') {
        std::vector<int> b(a.size());
        for (int i = 0; i < a.size(); i++) {
            b[i] = a[i] - offset;
        }
        return add(b);
    }
    
    void work() {
        std::queue<int> q;
        q.push(1);
        
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            
            for (int i = 0; i < ALPHABET; i++) {
                if (t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].link].next[i];
                } else {
                    t[t[x].next[i]].link = t[t[x].link].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }
    
    int next(int p, int x) {
        return t[p].next[x];
    }
    
    int next(int p, char c, char offset = 'a') {
        return next(p, c - 'a');
    }
    
    int link(int p) {
        return t[p].link;
    }
    
    int len(int p) {
        return t[p].len;
    }
    
    int size() {
        return t.size();
    }
};
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n = 0) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }
    
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    
    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int kth(T k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::string t;
    std::cin >> t;
    
    AhoCorasick ac1, ac2;
    std::vector<std::string> s(n);
    std::vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
        pos[i] = ac1.add(s[i]);
        ac2.add(std::string(s[i].rbegin(), s[i].rend()));
    }
    ac1.work();
    ac2.work();
    
    std::vector<i64> ans(m);
    int L = t.size();
    std::vector<i64> f(L + 1);
    
    std::vector<int> sum(ac1.size());
    std::vector<std::vector<int>> adj1(ac1.size()), adj2(ac2.size());
    for (int i = 2; i < ac1.size(); i++) {
        adj1[ac1.link(i)].push_back(i);
    }
    for (int i = 2; i < ac2.size(); i++) {
        adj2[ac2.link(i)].push_back(i);
    }
    for (auto x : pos) {
        sum[x] += 1;
    }
    
    std::vector<int> in1(ac1.size()), out1(ac1.size());
    std::vector<int> in2(ac2.size()), out2(ac2.size());
    int log = std::__lg(ac2.size());
    std::vector par(log + 1, std::vector<int>(ac2.size()));
    int cur = 0;
    std::function<void(int)> dfs1 = [&](int x) {
        in1[x] = cur++;
        for (auto y : adj1[x]) {
            sum[y] += sum[x];
            dfs1(y);
        }
        out1[x] = cur;
    };
    dfs1(1);
    
    cur = 0;
    std::function<void(int)> dfs2 = [&](int x) {
        par[0][x] = ac2.link(x);
        for (int k = 0; k < log; k++) {
            if (!par[k][x]) {
                break;
            }
            par[k + 1][x] = par[k][par[k][x]];
        }
        in2[x] = cur++;
        for (auto y : adj2[x]) {
            dfs2(y);
        }
        out2[x] = cur;
    };
    dfs2(1);
    
    std::vector<int> pre(L + 1), suf(L + 1);
    pre[0] = 1;
    for (int i = 0, p = 1; i < L; i++) {
        p = ac1.next(p, t[i]);
        f[i + 1] = f[i] + sum[p];
        pre[i + 1] = p;
    }
    suf[L] = 1;
    for (int i = L - 1, p = 1; i >= 0; i--) {
        p = ac2.next(p, t[i]);
        suf[i] = p;
    }
    std::vector<std::array<int, 4>> events;
    for (auto s : s) {
        int L = s.size();
        std::vector<int> suf(L + 1);
        suf[L] = 1;
        for (int i = L - 1; i >= 0; i--) {
            suf[i] = ac2.next(suf[i + 1], s[i]);
        }
        for (int i = 0, p = 1; i < L - 1; i++) {
            p = ac1.next(p, s[i]);
            int q = suf[i + 1];
            events.push_back({in1[p], 0, in2[q], 1});
            events.push_back({in1[p], 0, out2[q], -1});
            events.push_back({out1[p], 0, in2[q], -1});
            events.push_back({out1[p], 0, out2[q], 1});
        }
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        
        ans[i] = f[r] - f[l];
        int p = pre[l], q = suf[l];
        for (int k = log; k >= 0; k--) {
            if (ac2.len(par[k][q]) > r - l) {
                q = par[k][q];
            }
        }
        if (ac2.len(q) > r - l) {
            q = par[0][q];
        }
        events.push_back({in1[p], 1, in2[q], i});
    }
    
    std::sort(events.begin(), events.end());
    
    Fenwick<int> fen(cur);
    for (auto [_, t, y, k] : events) {
        if (t == 0) {
            fen.add(y, k);
        } else {
            ans[k] -= fen.sum(y + 1);
        }
    }
    for (int i = 0; i < m; i++) {
        std::cout << ans[i] << " \n"[i == m - 1];
    }
    
    return 0;
}#include <bits/stdc++.h>

using i64 = long long;

struct AhoCorasick {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len;
        int link;
        std::array<int, ALPHABET> next;
        Node() : link{}, next{} {}
    };
    
    std::vector<Node> t;
    
    AhoCorasick() {
        init();
    }
    
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }
    
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    
    int add(const std::vector<int> &a) {
        int p = 1;
        for (auto x : a) {
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        return p;
    }
    
    int add(const std::string &a, char offset = 'a') {
        std::vector<int> b(a.size());
        for (int i = 0; i < a.size(); i++) {
            b[i] = a[i] - offset;
        }
        return add(b);
    }
    
    void work() {
        std::queue<int> q;
        q.push(1);
        
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            
            for (int i = 0; i < ALPHABET; i++) {
                if (t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].link].next[i];
                } else {
                    t[t[x].next[i]].link = t[t[x].link].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }
    
    int next(int p, int x) {
        return t[p].next[x];
    }
    
    int next(int p, char c, char offset = 'a') {
        return next(p, c - 'a');
    }
    
    int link(int p) {
        return t[p].link;
    }
    
    int len(int p) {
        return t[p].len;
    }
    
    int size() {
        return t.size();
    }
};
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n = 0) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }
    
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    
    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int kth(T k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::string t;
    std::cin >> t;
    
    AhoCorasick ac1, ac2;
    std::vector<std::string> s(n);
    std::vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
        pos[i] = ac1.add(s[i]);
        ac2.add(std::string(s[i].rbegin(), s[i].rend()));
    }
    ac1.work();
    ac2.work();
    
    std::vector<i64> ans(m);
    int L = t.size();
    std::vector<i64> f(L + 1);
    
    std::vector<int> sum(ac1.size());
    std::vector<std::vector<int>> adj1(ac1.size()), adj2(ac2.size());
    for (int i = 2; i < ac1.size(); i++) {
        adj1[ac1.link(i)].push_back(i);
    }
    for (int i = 2; i < ac2.size(); i++) {
        adj2[ac2.link(i)].push_back(i);
    }
    for (auto x : pos) {
        sum[x] += 1;
    }
    
    std::vector<int> in1(ac1.size()), out1(ac1.size());
    std::vector<int> in2(ac2.size()), out2(ac2.size());
    int log = std::__lg(ac2.size());
    std::vector par(log + 1, std::vector<int>(ac2.size()));
    int cur = 0;
    std::function<void(int)> dfs1 = [&](int x) {
        in1[x] = cur++;
        for (auto y : adj1[x]) {
            sum[y] += sum[x];
            dfs1(y);
        }
        out1[x] = cur;
    };
    dfs1(1);
    
    cur = 0;
    std::function<void(int)> dfs2 = [&](int x) {
        par[0][x] = ac2.link(x);
        for (int k = 0; k < log; k++) {
            if (!par[k][x]) {
                break;
            }
            par[k + 1][x] = par[k][par[k][x]];
        }
        in2[x] = cur++;
        for (auto y : adj2[x]) {
            dfs2(y);
        }
        out2[x] = cur;
    };
    dfs2(1);
    
    std::vector<int> pre(L + 1), suf(L + 1);
    pre[0] = 1;
    for (int i = 0, p = 1; i < L; i++) {
        p = ac1.next(p, t[i]);
        f[i + 1] = f[i] + sum[p];
        pre[i + 1] = p;
    }
    suf[L] = 1;
    for (int i = L - 1, p = 1; i >= 0; i--) {
        p = ac2.next(p, t[i]);
        suf[i] = p;
    }
    std::vector<std::array<int, 4>> events;
    for (auto s : s) {
        int L = s.size();
        std::vector<int> suf(L + 1);
        suf[L] = 1;
        for (int i = L - 1; i >= 0; i--) {
            suf[i] = ac2.next(suf[i + 1], s[i]);
        }
        for (int i = 0, p = 1; i < L - 1; i++) {
            p = ac1.next(p, s[i]);
            int q = suf[i + 1];
            events.push_back({in1[p], 0, in2[q], 1});
            events.push_back({in1[p], 0, out2[q], -1});
            events.push_back({out1[p], 0, in2[q], -1});
            events.push_back({out1[p], 0, out2[q], 1});
        }
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        
        ans[i] = f[r] - f[l];
        int p = pre[l], q = suf[l];
        for (int k = log; k >= 0; k--) {
            if (ac2.len(par[k][q]) > r - l) {
                q = par[k][q];
            }
        }
        if (ac2.len(q) > r - l) {
            q = par[0][q];
        }
        events.push_back({in1[p], 1, in2[q], i});
    }
    
    std::sort(events.begin(), events.end());
    
    Fenwick<int> fen(cur);
    for (auto [_, t, y, k] : events) {
        if (t == 0) {
            fen.add(y, k);
        } else {
            ans[k] -= fen.sum(y + 1);
        }
    }
    for (int i = 0; i < m; i++) {
        std::cout << ans[i] << " \n"[i == m - 1];
    }
    
    return 0;
}