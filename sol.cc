#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    vector<int> x(m), y(m);
    for (int i = 0; i < m; i++) {
        cin >> x[i] >> y[i];
        --x[i], --y[i];
        if (x[i] == y[i] and a[x[i]] < b[x[i]]) swap(a[x[i]], b[x[i]]);
    }
    int ans = 0;
    vector<int> p, q; // p: 選ぶと損　q: 選ぶと得
    vector<int> id(n);
    for (int i = 0; i < n; i++) {
        ans += a[i] * 2;
        int d = abs(a[i] - b[i]);
        if (a[i] >= b[i]) {
            id[i] = p.size();
            p.push_back(d);
        } else {
            id[i] = q.size();
            q.push_back(d);
        }
    }
    int ps = p.size(), qs = q.size();
    vector<ll> ls(ps);
    for (int i = 0; i < m; i++) {
        bool xp = (a[x[i]] >= b[x[i]]);
        bool yp = (a[y[i]] >= b[y[i]]);
        if (xp == yp) {
            if (!xp) {
                ans += q[id[x[i]]] + q[id[y[i]]];
                q[id[x[i]]] = q[id[y[i]]] = 0;
            }
        } else {
            if (!xp) swap(x[i], y[i]);
            ls[id[x[i]]] |= 1LL << id[y[i]];
        }
    }
    if (ps <= qs) {
        int mx = 0;
        for (int bit = 0; bit < (1 << ps); bit++) {
            int now = 0;
            ll cq = 0;
            for (int i = 0; i < ps; i++) {
                if (bit >> i & 1) {
                    now -= p[i];
                    cq |= ls[i];
                }
            }
            for (int i = 0; i < qs; i++) {
                if (cq >> i & 1) now += q[i];
            }
            mx = max(mx, now);
        }
        ans += mx;
    } else {
        vector dp(ps + 1, vector<int>(1 << qs, -1e9));
        dp[0][0] = 0;
        for (int i = 0; i < ps; i++) {
            for (int j = 0; j < (1 << qs); j++) {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                dp[i + 1][j | ls[i]] = max(dp[i + 1][j | ls[i]], dp[i][j] - p[i]);
            }
        }
        int mx = 0;
        for (int j = 0; j < (1 << qs); j++) {
            int now = dp[ps][j];
            for (int i = 0; i < qs; i++) {
                if (j >> i & 1) now += q[i];
            }
            mx = max(mx, now);
        }
        ans += mx;
    }
    cout << fixed << ans / 2. << endl;
}

