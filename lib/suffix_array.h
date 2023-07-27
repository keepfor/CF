#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif

using namespace std;

struct SuffixArray {
  int n;
  string S;
  vector<int> sa, lcp, rev;
  SuffixArray() {}
  SuffixArray(string& S) : S(S) { init(); }
  void init() {
    n = S.length();
    S.push_back('$');
    build_sa();
    build_lcp();
  }
  void build_sa() {
    sa.assign(n + 1, 0);
    iota(sa.begin(), sa.end(), 0);
    sort(sa.begin(), sa.end(), [&](int a, int b) {
      if (S[a] == S[b]) return a > b;
      return S[a] < S[b];
    });
    vector<int> c(n + 1, 0), r(n + 1), cnt(n + 1), s(n + 1);
    for (int i = 0; i <= n; i++) r[i] = S[i];
    for (int len = 1; len <= n; len *= 2) {
      for (int i = 0; i <= n; i++) {
        c[sa[i]] = i > 0 && r[sa[i - 1]] == r[sa[i]] && sa[i - 1] + len <= n &&
                           r[sa[i - 1] + len / 2] == r[sa[i] + len / 2]
                       ? c[sa[i - 1]]
                       : i;
      }
      iota(cnt.begin(), cnt.end(), 0);
      copy(sa.begin(), sa.end(), r.begin());
      for (int i = 0; i <= n; i++) {
        int s1 = r[i] - len;
        if (s1 >= 0) sa[cnt[c[s1]]++] = s1;
      }
      c.swap(r);
    }
  }

  bool lt_substr(string& T, int si = 0, int ti = 0) {
    int sn = S.size(), tn = T.size();
    while (si < sn && ti < tn) {
      if (S[si] < T[ti]) return 1;
      if (S[si] > T[ti]) return 0;
      si++;
      ti++;
    }
    return si >= sn && ti < tn;
  }

  int lower_bound(string& T) {
    int low = 0, high = n + 1;
    while (low + 1 < high) {
      int mid = (low + high) / 2;
      if (lt_substr(T, sa[mid], 0))
        low = mid;
      else
        high = mid;
    }
    return high;
  }

  int upper_bound(string& T) {
    T.back()++;
    int res = lower_bound(T);
    T.back()--;
    return res;
  }

  // O(|T|*log|S|)
  int count(string& T) { return upper_bound(T) - lower_bound(T); }

  void build_lcp() {
    lcp.assign(n, 0);
    rev.assign(n + 1, 0);
    for (int i = 0; i <= n; i++) rev[sa[i]] = i;
    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < n; i++) {
      int j = sa[rev[i] - 1];
      if (h > 0) h--;
      for (; j + h < n && i + h < n; h++) {
        if (S[j + h] != S[i + h]) break;
      }
      lcp[rev[i] - 1] = h;
    }
  }

  int getlcp(int p, string& T, int d) {
    int i = 0;
    int len = min((int)T.length() - d, (int)S.length() - p - d);
    while (i < len && S[p + d + i] == T[d + i]) i++;
    return i;
  }

  struct RMQ {
    vector<vector<int> > dat;
    vector<int> ht;

    void init(int n) {
      int h = 1;
      while ((1 << h) < n) h++;
      dat.assign(h, vector<int>(n));
      ht.assign(n + 1, 0);
      for (int j = 2; j <= n; j++) ht[j] = ht[j >> 1] + 1;
    }

    void build(int n, vector<int>& v) {
      int h = 1;
      while ((1 << h) < n) h++;
      for (int j = 0; j < n; j++) dat[0][j] = v[j];
      for (int i = 1, p = 1; i < h; i++, p <<= 1)
        for (int j = 0; j < n; j++)
          dat[i][j] = min(dat[i - 1][j], dat[i - 1][min(j + p, n - 1)]);
    };

    int query(int a, int b) {
      if (a > b) swap(a, b);
      int l = b - a;
      return min(dat[ht[l]][a], dat[ht[l]][b - (1 << ht[l])]);
    }
  };
};
string test(string& s) {
  int n = s.size();
  SuffixArray sa(s);
  int len = 0;
  int start = 0;
  for (int i = 0; i < n; ++i) {
    int t = sa.lcp[i];
    if (t > len) {
      len = t;
      start = sa.sa[i];
    }
  }
  if (!len) {
    return "";
  }
  return s.substr(start, len);
}
/*
 * Example
 *
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s = "banana";
  cout << test(s) << '\n';
  return 0;
}
*/

namespace {
using namespace std;

namespace atcoder {

namespace internal {

std::vector<int> sa_naive(const std::vector<int>& s) {
  int n = int(s.size());
  std::vector<int> sa(n);
  std::iota(sa.begin(), sa.end(), 0);
  std::sort(sa.begin(), sa.end(), [&](int l, int r) {
    if (l == r) return false;
    while (l < n && r < n) {
      if (s[l] != s[r]) return s[l] < s[r];
      l++;
      r++;
    }
    return l == n;
  });
  return sa;
}

std::vector<int> sa_doubling(const std::vector<int>& s) {
  int n = int(s.size());
  std::vector<int> sa(n), rnk = s, tmp(n);
  std::iota(sa.begin(), sa.end(), 0);
  for (int k = 1; k < n; k *= 2) {
    auto cmp = [&](int x, int y) {
      if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
      int rx = x + k < n ? rnk[x + k] : -1;
      int ry = y + k < n ? rnk[y + k] : -1;
      return rx < ry;
    };
    std::sort(sa.begin(), sa.end(), cmp);
    tmp[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
      tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
    }
    std::swap(tmp, rnk);
  }
  return sa;
}

template <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40>
std::vector<int> sa_is(const std::vector<int>& s, int upper) {
  int n = int(s.size());
  if (n == 0) return {};
  if (n == 1) return {0};
  if (n == 2) {
    if (s[0] < s[1]) {
      return {0, 1};
    } else {
      return {1, 0};
    }
  }
  if (n < THRESHOLD_NAIVE) {
    return sa_naive(s);
  }
  if (n < THRESHOLD_DOUBLING) {
    return sa_doubling(s);
  }

  std::vector<int> sa(n);
  std::vector<bool> ls(n);
  for (int i = n - 2; i >= 0; i--) {
    ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
  }
  std::vector<int> sum_l(upper + 1), sum_s(upper + 1);
  for (int i = 0; i < n; i++) {
    if (!ls[i]) {
      sum_s[s[i]]++;
    } else {
      sum_l[s[i] + 1]++;
    }
  }
  for (int i = 0; i <= upper; i++) {
    sum_s[i] += sum_l[i];
    if (i < upper) sum_l[i + 1] += sum_s[i];
  }

  auto induce = [&](const std::vector<int>& lms) {
    std::fill(sa.begin(), sa.end(), -1);
    std::vector<int> buf(upper + 1);
    std::copy(sum_s.begin(), sum_s.end(), buf.begin());
    for (auto d : lms) {
      if (d == n) continue;
      sa[buf[s[d]]++] = d;
    }
    std::copy(sum_l.begin(), sum_l.end(), buf.begin());
    sa[buf[s[n - 1]]++] = n - 1;
    for (int i = 0; i < n; i++) {
      int v = sa[i];
      if (v >= 1 && !ls[v - 1]) {
        sa[buf[s[v - 1]]++] = v - 1;
      }
    }
    std::copy(sum_l.begin(), sum_l.end(), buf.begin());
    for (int i = n - 1; i >= 0; i--) {
      int v = sa[i];
      if (v >= 1 && ls[v - 1]) {
        sa[--buf[s[v - 1] + 1]] = v - 1;
      }
    }
  };

  std::vector<int> lms_map(n + 1, -1);
  int m = 0;
  for (int i = 1; i < n; i++) {
    if (!ls[i - 1] && ls[i]) {
      lms_map[i] = m++;
    }
  }
  std::vector<int> lms;
  lms.reserve(m);
  for (int i = 1; i < n; i++) {
    if (!ls[i - 1] && ls[i]) {
      lms.push_back(i);
    }
  }

  induce(lms);

  if (m) {
    std::vector<int> sorted_lms;
    sorted_lms.reserve(m);
    for (int v : sa) {
      if (lms_map[v] != -1) sorted_lms.push_back(v);
    }
    std::vector<int> rec_s(m);
    int rec_upper = 0;
    rec_s[lms_map[sorted_lms[0]]] = 0;
    for (int i = 1; i < m; i++) {
      int l = sorted_lms[i - 1], r = sorted_lms[i];
      int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
      int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
      bool same = true;
      if (end_l - l != end_r - r) {
        same = false;
      } else {
        while (l < end_l) {
          if (s[l] != s[r]) {
            break;
          }
          l++;
          r++;
        }
        if (l == n || s[l] != s[r]) same = false;
      }
      if (!same) rec_upper++;
      rec_s[lms_map[sorted_lms[i]]] = rec_upper;
    }

    auto rec_sa = sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

    for (int i = 0; i < m; i++) {
      sorted_lms[i] = lms[rec_sa[i]];
    }
    induce(sorted_lms);
  }
  return sa;
}

}  // namespace internal

std::vector<int> suffix_array(const std::vector<int>& s, int upper) {
  assert(0 <= upper);
  for (int d : s) {
    assert(0 <= d && d <= upper);
  }
  auto sa = internal::sa_is(s, upper);
  return sa;
}

template <class T>
std::vector<int> suffix_array(const std::vector<T>& s) {
  int n = int(s.size());
  std::vector<int> idx(n);
  iota(idx.begin(), idx.end(), 0);
  sort(idx.begin(), idx.end(), [&](int l, int r) { return s[l] < s[r]; });
  std::vector<int> s2(n);
  int now = 0;
  for (int i = 0; i < n; i++) {
    if (i && s[idx[i - 1]] != s[idx[i]]) now++;
    s2[idx[i]] = now;
  }
  return internal::sa_is(s2, now);
}

std::vector<int> suffix_array(const std::string& s) {
  int n = int(s.size());
  std::vector<int> s2(n);
  for (int i = 0; i < n; i++) {
    s2[i] = s[i];
  }
  return internal::sa_is(s2, 255);
}

template <class T>
std::vector<int> lcp_array(const std::vector<T>& s,
                           const std::vector<int>& sa) {
  int n = int(s.size());
  assert(n >= 1);
  std::vector<int> rnk(n);
  for (int i = 0; i < n; i++) {
    rnk[sa[i]] = i;
  }
  std::vector<int> lcp(n - 1);
  int h = 0;
  for (int i = 0; i < n; i++) {
    if (h > 0) h--;
    if (rnk[i] == 0) continue;
    int j = sa[rnk[i] - 1];
    for (; j + h < n && i + h < n; h++) {
      if (s[j + h] != s[i + h]) break;
    }
    lcp[rnk[i] - 1] = h;
  }
  return lcp;
}

std::vector<int> lcp_array(const std::string& s, const std::vector<int>& sa) {
  int n = int(s.size());
  std::vector<int> s2(n);
  for (int i = 0; i < n; i++) {
    s2[i] = s[i];
  }
  return lcp_array(s2, sa);
}

template <class T>
std::vector<int> z_algorithm(const std::vector<T>& s) {
  int n = int(s.size());
  if (n == 0) return {};
  std::vector<int> z(n);
  z[0] = 0;
  for (int i = 1, j = 0; i < n; i++) {
    int& k = z[i];
    k = (j + z[j] <= i) ? 0 : std::min(j + z[j] - i, z[i - j]);
    while (i + k < n && s[k] == s[i + k]) k++;
    if (j + z[j] < i + z[i]) j = i;
  }
  z[0] = n;
  return z;
}

std::vector<int> z_algorithm(const std::string& s) {
  int n = int(s.size());
  std::vector<int> s2(n);
  for (int i = 0; i < n; i++) {
    s2[i] = s[i];
  }
  return z_algorithm(s2);
}

}  // namespace atcoder

using namespace atcoder;
