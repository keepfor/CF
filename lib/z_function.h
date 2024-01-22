#include <bits/stdc++.h>

using namespace std;

template <typename T>
vector<int> z_function(int n, const T &s) {
  vector<int> z(n, n);
  int l = 0, r = 0;
  for (int i = 1; i < n; i++) {
    z[i] = (i > r ? 0 : min(r - i + 1, z[i - l]));
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

template <typename T>
vector<int> z_function(const T &s) {
  return z_function((int)s.size(), s);
}

int z[N + 10];

void get_z(string & s) {
    int n = (int)s.length();
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return;
}

void SolveOne() {
  using ll = long long;
  const ll mod = 1e9 + 7;

  auto g = [&](string s) -> vector<int> {
    const int n = s.size();
    vector<int> z(n);
    int l = 0;
    int r = 0;
    for (int i = 1; i < n; ++i) {
      if (i <= r) {
        z[i] = min(z[i - l], r - i + 1);
      }
      while (i < n and z[i] + i < n and s[z[i]] == s[z[i] + i]) {
        ++z[i];
      }
      if (i + z[i] - 1 > r) {
        l = i;
        r = i + z[i] - 1;
      }
    }
    return z;
  };

  int n, m;
  string s;
  cin >> n >> m >> s;
  vector<int> y(m);
  for (auto& i : y) {
    cin >> i;
    --i;
  }
  const int p = s.size();
  int now = p;
  vector<int> z = g(s);
  ll ans = 1;
  for (int i = 0, j = 0; i < n; ++i) {
    if (j < m and i == y[j]) {
      if (now >= p) {
        now = 0;
      } else {
        if (z[now] < p - now) {
          cout << 0 << '\n';
          return;
        } else {
          now = 0;
        }
      }
      ++j;
    }
    if (now >= p) {
      ans = ans * 26 % mod;
    }
    ++now;
  }
  cout << ans << '\n';
};