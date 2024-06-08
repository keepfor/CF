template<typename T> 
struct SegTreeSingle {
  int n;
  vector<T> v;
  SegTreeSingle(int n_) : n(n_) {
    v.assign(2 * n, T());
  }
  void update(int p, T t) {
    for (v[p += n] = t; p >>= 1;) {
      v[p] = v[p << 1] + v[(p << 1) | 1];
    }
  }
  T get(int l, int r) {
    T ansl{};
    T ansr{};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        ansl = ansl + v[l++];
      }
      if (r & 1) {
        ansr = v[--r] + ansr;
      }
    }
    return ansl + ansr;
  }
};


template<typename T>
struct Node {
  T v[2][2];
  Node() {
    memset(v, 0, sizeof v);
  }
  Node(T x) {
    memset(v, 0, sizeof v);
    v[1][1] = x;
  }
};

template<typename T>
Node<T> operator + (const Node<T> lhs, const Node<T> rhs) {
  Node<T> ans;
  for (int a = 0; a < 2; ++a) {
    for (int b = 0; b < 2; ++b) {
      for (int c = 0; c < 2; ++c) {
        if (b && c) {
          continue;
        }
        for (int d = 0; d < 2; ++d) {
          ans.v[a][d] = max(ans.v[a][d], lhs.v[a][b] + rhs.v[c][d]);
        }
      }
    }
  }
  return ans;
} 

class Solution {
public:
    int maximumSumSubsequence(vector<int>& a, vector<vector<int>>& q) {
        const int n = a.size();
        using ll = long long;
        SegTreeSingle<Node<ll>> t(n);
        for (int i = 0; i < n; ++i) {
          t.update(i, Node<ll>(a[i]));
        }
        const ll mod = 1e9 + 7;
        ll ans = 0;
        for (auto& i : q) {
          int p = i[0];
          int x = i[1];
          t.update(p, Node<ll>(x));
          ll mx = 0;
          Node<ll> nd = t.get(0, n);
          for (int a = 0; a < 2; ++a) {
            for (int b = 0; b < 2; ++b) {
              mx = max(mx, nd.v[a][b]);
            }
          }
          ans = (ans + mx) % mod;
        }
        return ans;
    }
};
