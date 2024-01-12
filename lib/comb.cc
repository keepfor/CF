#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "lib/debug.h"
#else
#define debug(...) 0
#endif

namespace comb_one_loop {
const int mod = 1e9 + 7, mx = 2e3 + 10;
int fac[mx], inv[mx], invfac[mx];
class Solution {
public:
    int mul(int a, int b) {
        return (1ll * a * b) % mod;
    }
    void init() {
        fac[0] = fac[1] = invfac[0] = invfac[1] = inv[1] = 1;
        for (int i = 2; i < mx; ++i) {
            fac[i] = mul(fac[i - 1], i);
            inv[i] = mul(inv[mod % i], mod - mod / i);
            invfac[i] = mul(invfac[i - 1], inv[i]);
            //cout << fac[i] << ',' << invfac[i] << '\n';
        }
    }
    int cnr(int n, int r) {
        if (r > n) return 0;
        return (((1LL * fac[n] * invfac[n - r]) % mod) * 1LL * invfac[r]) % mod;
    }
    int numberOfSets(int n, int k) {
        init();
        return cnr(n + k - 1, 2 * k);
    }
};
}

class comb {
  long long mod;
  int m;
  vector<long long> fac, inv;

 public:
  void init(const long long _mod=2000000011, const int _m=1000) {
    mod = _mod;
    m = _m + 1;
    fac.resize(m);
    inv.resize(m);
    fac[0] = 1;
    for (int i = 1; i < m; ++i) {
      fac[i] = fac[i - 1] * i % mod;
    }
    auto fp = [&](long long x, long long y) -> long long {
      long long z = 1;
      while (y) {
        if (y & 1) z = z * x % mod;
        x = x * x % mod;
        y >>= 1;
      }
      return z;
    };
    inv[m - 1] = fp(fac[m - 1], mod - 2);
    for (int i = m - 2; i >= 0; --i) {
      inv[i] = inv[i + 1] * (i + 1) % mod;
    }
  }
  long long nk(long long n, long long k) {
    if (k < 0 or k > n) return 0;
    return fac[n] * inv[k] % mod * inv[n - k] % mod;
  }
};

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  const long long mod = 2000000011;
  const int m = 1001;

  comb cb;
  cb.init(mod, m);

  auto solve = [&]() {
    int k;
    cin >> k;
    vector<int> c(k);
    int s = 0;
    for (auto& i : c) {
      cin >> i;
      s += i;
    }
    long long ans = 1;
    reverse(c.begin(), c.end());
    for (auto& i : c) {
      ans = ans * cb.nk(s - 1, i - 1) % mod;
      s -= i;
    }
    cout << ans << '\n';
  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
