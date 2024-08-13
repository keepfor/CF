#include <bits/stdc++.h>

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

// TODO: Dynamic ModInt

template<typename T>
constexpr T power(T a, u64 b) {
    T res {1};
    for (; b != 0; b /= 2, a *= a) {
        if (b % 2 == 1) {
            res *= a;
        }
    }
    return res;
}

template<u32 P>
constexpr u32 mulMod(u32 a, u32 b) {
    return 1ULL * a * b % P;
}

template<u64 P>
constexpr u64 mulMod(u64 a, u64 b) {
    u64 res = a * b - u64(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

template<typename U, U P>
requires std::unsigned_integral<U>
struct ModIntBase {
public:
    constexpr ModIntBase() : x {0} {}
    
    template<typename T>
    requires std::integral<T>
    constexpr ModIntBase(T x_) : x {norm(x_ % T {P})} {}
    
    constexpr static U norm(U x) {
        if ((x >> (8 * sizeof(U) - 1) & 1) == 1) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }
    
    constexpr U val() const {
        return x;
    }
    
    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = norm(P - x);
        return res;
    }
    
    constexpr ModIntBase inv() const {
        return power(*this, P - 2);
    }
    
    constexpr ModIntBase &operator*=(const ModIntBase &rhs) & {
        x = mulMod<P>(x, rhs.val());
        return *this;
    }
    
    constexpr ModIntBase &operator+=(const ModIntBase &rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    
    constexpr ModIntBase &operator-=(const ModIntBase &rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    
    constexpr ModIntBase &operator/=(const ModIntBase &rhs) & {
        return *this *= rhs.inv();
    }
    
    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase &rhs) {
        lhs *= rhs;
        return lhs;
    }
    
    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase &rhs) {
        lhs += rhs;
        return lhs;
    }
    
    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase &rhs) {
        lhs -= rhs;
        return lhs;
    }
    
    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase &rhs) {
        lhs /= rhs;
        return lhs;
    }
    
    friend constexpr std::ostream &operator<<(std::ostream &os, const ModIntBase &a) {
        return os << a.val();
    }
    
    friend constexpr bool operator==(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() == rhs.val();
    }
    
    friend constexpr bool operator!=(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() != rhs.val();
    }
    
    friend constexpr bool operator<(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() < rhs.val();
    }
    
private:
    U x;
};

template<u32 P>
using ModInt = ModIntBase<u32, P>;

template<u64 P>
using ModInt64 = ModIntBase<u64, P>;

constexpr u32 P = 1000000007;
using Z = ModInt<P>;


constexpr int N = 130;
constexpr int M = 30;

Z dp[M + 1][N + 1][N / 2 + 1];
Z sum[M + 1][N + 1];

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    for (int k = 0; k <= (n - 1) / 2; k++) {
        std::cout << dp[m][n][k] << " \n"[k == (n - 1) / 2];
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    dp[0][0][0] = 1;
    sum[0][0] = 1;
    for (int m = 1; m <= M; m++) {
        Z fl[N + 1][N + 1][N + 1];
        Z fr[N + 1][N + 1][N + 1];
        for (int a = 0; a <= N; a++) {
            for (int b = 0; b <= a / 2; b++) {
                fl[a][0][a - 2 * b] += dp[m - 1][a][b];
                fr[a][0][a] += dp[m - 1][a][b];
            }
        }
        for (int n = 0; n <= N; n++) {
            for (int c = 0; c <= n; c++) {
                for (int l = 0; l <= n; l++) {
                    if (fl[n][c][l] == 0) {
                        continue;
                    }
                    int nc = c + (l == 0 ? 0 : (l - 1) % 2 + 1);
                    dp[m][n][(n - nc) / 2] += fl[n][c][l];
                }
                for (int a = 0; n + a < N; a++) {
                    int nn = n + 1 + a;
                    Z p[2], q[2];
                    for (int l = 0; l <= n; l++) {
                        if (fl[n][c][l] != 0) {
                            int nc = c + 1;
                            int nr;
                            if (l <= a) {
                                nr = a - l;
                            } else {
                                nc++;
                                int v = std::min((l - 1) % 2, a);
                                nr = a - v;
                                if ((l - v) % 2 == 0) {
                                    nc++;
                                }
                            }
                            // for (int b = 0; b <= a / 2; b++) {
                            //     fr[nn][nc][nr] += fl[n][c][l] * dp[m - 1][a][b];
                            // }
                            fr[nn][nc][nr] += fl[n][c][l] * sum[m - 1][a];
                        }
                    }
                    for (int r = 0; r <= a; r++) {
                        if (fr[n][c][r] != 0) {
                            int nc = c + 1;
                            for (int b = 0; b <= a / 2; b++) {
                                int nl = a - r;
                                nl -= 2 * std::min(nl / 2, b);
                                fl[nn][nc][nl] += fr[n][c][r] * dp[m - 1][a][b];
                            }
                        }
                    }
                    for (int i = 0; i <= a; i++) {
                        p[i % 2] += fl[n][c][i] - fr[n][c][i];
                    }
                    for (int i = a + 1; i <= n; i++) {
                        q[i % 2] += fl[n][c][i];
                    }
                    for (int t = 0; t <= 1; t++) {
                        if (p[t] != 0) {
                            int u = a;
                            if ((u - t) % 2 != 0) {
                                u--;
                            }
                            assert(u >= 0);
                            int nc = c + 1;
                            int nl = a - u;
                            fl[nn][nc][nl] += p[t] * sum[m - 1][a];
                        }
                        if (q[t] != 0) {
                            int nc = c + 2;
                            int u = a;
                            if (u > 0 && (u - t) % 2 == 0) {
                                u--;
                            }
                            if ((u - t) % 2 == 0) {
                                nc++;
                            }
                            int nl = a - u;
                            fl[nn][nc][nl] += q[t] * sum[m - 1][a];
                        }
                    }
                }
                // for (int l = 0; l <= n; l++) {
                //     for (int r = l; r <= n; r += 2) {
                //         if (f[n][c][l][r] == 0) {
                //             continue;
                //         }
                //         assert((r - l) % 2 == 0);
                //         int nc = c + (l == 0 ? 0 : (l - 1) % 2 + 1);
                //         assert((n - nc) % 2 == 0);
                //         dp[m][n][(n - nc) / 2] += f[n][c][l][r];
                //         for (int a = 0; n + a < N; a++) {
                //             int nn = n + 1 + a;
                //             int nc;
                //             int nl;
                //             int nr;
                //             if (l > a) {
                //                 int u = a;
                //                 if (u > 0 && (l - u) % 2 == 0) {
                //                     u--;    
                //                 }
                //                 nc = c + 1;
                //                 if ((l - u) % 2 == 0) {
                //                     nc++;
                //                 }
                //                 int v = std::min((l - 1) % 2, a);
                //                 assert((u - v) % 2 == 0);
                //                 nl = a - u;
                //                 nr = a - v;
                //             } else if (r <= a) {
                //                 nc = c;
                //                 nr = a - l;
                //                 nl = a - r;
                //             } else {
                //                 int u = a;
                //                 if ((r - u) % 2 != 0) {
                //                     u--;
                //                 }
                //                 nc = c;
                //                 nr = a - l;
                //                 nl = a - u;
                //             }
                //             nc++;
                //             for (int b = 0; b <= a / 2; b++) {
                //                 int nnl = nl - 2 * std::min(nl / 2, b);
                //                 f[nn][nc][nnl][nr] += f[n][c][l][r] * dp[m - 1][a][b];
                //             }
                //         }
                //     }
                // }
            }
        }
        for (int n = 0; n <= N; n++) {
            for (int k = 0; k <= n / 2; k++) {
                sum[m][n] += dp[m][n][k];
            }
        }
    }
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
