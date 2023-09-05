#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...)
#endif

class LightComb {
  int n;
  long long mod;
  vector<long long> fac;
  vector<long long> inv;

  long long fp(long long x, long long y, const long long mod = 1e9) {
    long long z = 1;
    while (y) {
      if (y & 1) z = z * x % mod;
      x = x * x % mod;
      y >>= 1;
    }
    return z;
  }

 public:
  LightComb(int _n, long long _mod) : n(_n), mod(_mod) {
    fac.resize(n + 1, 1);
    inv.resize(n + 1, 1);

    for (int i = 2; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;

    inv[n] = fp(fac[n], mod - 2, mod);

    for (int i = n - 1; i; --i) {
      inv[i] = inv[i + 1] * (i + 1) % mod;
    }
  }

  long long c(long long x, long long y) {
    if (y > x or y < 0) return 0;
    return fac[x] * inv[y] % mod * inv[x - y] % mod;
  }
};

/*int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    LightComb lc(10, 1e9 + 7);
    debug(lc.c(4, 2));
  };

  {
    int tt = 1;
    while (tt--) solve();
  }
  return 0;
}*/
