#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) 417
#endif
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f64 = double_t;

#include <atcoder/all>

using i128 = __int128_t;

i64 power(i64 a, i64 r, i64 mod) {
  i64 res = 1;
  for (; r; r >>= 1, a = (i128)a * a % mod) {
    if (r & 1) { res = (i128)res * a % mod; }
  }
  return res;
}
bool miller_rabin(i64 n) {
  static constexpr array<int, 9> p = {2, 3, 5, 7, 11, 13, 17, 19, 23};
  if (n == 1) { return false; }
  if (n == 2) { return true; }
  if (not(n % 2)) { return false; }
  int r = countr_zero(u64(n - 1));
  i64 d = (n - 1) >> r;
  for (int pi : p) {
    if (pi < n) {
      i64 x = power(pi, d, n);
      if (x == 1 or x == n - 1) { continue; };
      for (int j = 1; j < r; j += 1) {
        x = (i128)x * x % n;
        if (x == n - 1) { break; }
      }
      if (x != n - 1) { return false; }
    }
  }
  return true;
};
vector<i64> pollard_rho(i64 n) {
  static mt19937_64 mt;
  uniform_int_distribution uid(i64(0), n);
  if (n == 1) { return {}; }
  vector<i64> res;
  function<void(i64)> rho = [&](i64 n) {
    if (miller_rabin(n)) { return res.push_back(n); }
    i64 d = n;
    while (d == n) {
      d = 1;
      for (i64 k = 1, y = 0, x = 0, s = 1, c = uid(mt); d == 1;
           k <<= 1, y = x, s = 1) {
        for (int i = 1; i <= k; i += 1) {
          x = ((i128)x * x + c) % n;
          s = (i128)s * abs(x - y) % n;
          if (not(i % 127) or i == k) {
            d = gcd(s, n);
            if (d != 1) { break; }
          }
        }
      }
    }
    rho(d);
    rho(n / d);
  };
  rho(n);
  return res;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n;
  i64 p;
  cin >> n >> p;
  vector<i64> a(n);
  for (i64& ai : a) { cin >> ai; }
  auto fp = pollard_rho(p - 1);
  map<i64, i64> mp;
  for (i64 ai : a) {
    i64 r = p - 1;
    for (auto pi : fp) {
      if (power(ai, r / pi, p) == 1) { r /= pi; }
    }
    mp[r] += 1;
  }
  i64 ans = 0;
  for (auto [x0, y0] : mp) {
    for (auto [x1, y1] : mp) {
      if (x1 % x0 == 0) { ans += y0 * y1; }
    }
  }
  cout << ans;
}
