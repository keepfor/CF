#ifndef CP
#define CP
#include<bits/stdc++.h>
using namespace std;
#endif

template<class T>
class EasySegTree{
  int n;  
  vector<T> t;

public:
  EasySegTree(int n): n(n) {
    t.resize(2 * n);
  }

  void build() {  
    for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
  }

  void modify(int p, int value) {  
    for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
  }

  void modify(int p, int value, function<const int&(const T&, const T&)> f) {  
    for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = f(t[p], t[p^1]);
  }

  void modify(int p, int value, string s) {  
    if (s == "max") {
      return modify(p, value, Max);
    }
    assert(0);
  }

  T query(int l, int r) {  
    // sum on interval [l, r)
    T res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l&1) res += t[l++];
      if (r&1) res += t[--r];
    }
    return res;
  }

  T query(int l, int r, string s) {  
    if (s == "max") {
      return query(l, r, this->Max);
    }
    assert(0);
  }

  T query(int l, int r, function<const T&(const T&, const T&)> f) {  
    // sum on interval [l, r)
    T res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        res = f(res, t[l++]);
      }
      if (r & 1) {
        res = f(res, t[--r]);
      }
    }
    return res;
  }

  function<const T&(const T&, const T&)> Max = [&](const int& x, const int& y) -> const int& {
    return x >= y ? x : y;
  };
};
