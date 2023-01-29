#include<bits/stdc++.h>
namespace {
using namespace std;
#define rep(i,n) for(int i = 0; i < (int)(n); i++)
#define rrep(i,n) for(int i = (int)(n) - 1; i >= 0; i--)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
template<class T> bool chmax(T& a, const T& b) { if (a < b) { a = b; return true; } else return false; }
template<class T> bool chmin(T& a, const T& b) { if (b < a) { a = b; return true; } else return false; }
using ll = long long;
using P = pair<int,int>;
using VI = vector<int>;
using VVI = vector<VI>;
using VL = vector<ll>;
using VVL = vector<VL>;

pair<vector<int>, vector<int>> primes_lpf(const int n) {
  vector<int> primes; primes.reserve(n / 10);
  vector<int> lpf(n + 1);
  for (int i = 2; i <= n; i += 2) lpf[i] = 2;
  for (int i = 3; i <= n; i += 6) lpf[i] = 3;
  if (2 <= n) primes.push_back(2);
  if (3 <= n) primes.push_back(3);
  // 5 * x <= n, x <= floor(n / 5)
  const int n5 = n / 5;
  int x = 5;
  char add_next = 2;
  for (; x <= n5; x += add_next, add_next ^= 2 ^ 4) {
    int px = lpf[x];
    if (px == 0) {
      lpf[x] = px = x;
      primes.push_back(x);
    }
    for (int i = 2;; ++i) {
      int q = primes[i];
      int y = q * x;
      if (y > n) break;
      lpf[y] = q;
      if (q == px) break;
    }
  }
  for (; x <= n; x += add_next, add_next ^= 2 ^ 4) {
    if (lpf[x] == 0) {
      lpf[x] = x;
      primes.push_back(x);
    }
  }
  return {move(primes), move(lpf)};
}

constexpr int PSIZE = 1000000;
auto [primes, lpf] = primes_lpf(PSIZE);

vector<pair<int, int>> factorize(int x) {
  int ps[10], cs[10];
  int sz = 0;
  while (x != 1) {
    int p = lpf[x], c = 0;
    do {x /= p; c++;} while (x % p == 0);
    ps[sz] = p; cs[sz] = c; sz++;
  }
  vector<pair<int, int>> fs; fs.reserve(sz);
  for (int i = 0; i < sz; i++) fs.emplace_back(ps[i], cs[i]);
  return fs;
}

vector<int> divisors(int x) {
  int ps[10], cs[10];
  int sz = 0, dcnt = 1;
  while (x != 1) {
    int p = lpf[x], c = 0;
    do {x /= p; c++;} while (x % p == 0);
    ps[sz] = p; cs[sz] = c; sz++;
    dcnt *= c + 1;
  }
  vector<int> res; res.reserve(dcnt);
  res.emplace_back(1);
  for (int i = 0; i < sz; i++) {
    int p = ps[i], ptr = 0;
    for (int t = cs[i] * res.size(); t > 0; t--)
      res.emplace_back(res[ptr++] * p);
  }
  sort(all(res));
  return res;
}

/*
} int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while(tt--) {
    int n, m;
    cin >> n >> m;
    VI a(n);
    rep(i, n) cin >> a[i];
    sort(all(a));
    a.erase(unique(all(a)), a.end());
    n = a.size();
    VI cnt(m + 1);
    int cz = m;
    int r = 0;
    constexpr int INF = 1001001001;
    int ans = INF;
    rep(l, n) {
      while(r < n && cz) {
        for(int d: divisors(a[r])) {
          if (d > m) break;
          cz -= cnt[d]++ == 0;
        }
        r++;
      }
      if (cz) break;
      chmin(ans, a[r - 1] - a[l]);
      for(int d: divisors(a[l])) {
        if (d > m) break;
        cz += --cnt[d] == 0;
      }
    }
    if (ans == INF) ans = -1;
    cout << ans << '\n';
  }
}
*/
