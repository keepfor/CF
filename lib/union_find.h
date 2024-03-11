class UnionFind {
  int _n;
  int _size;
  std::vector<int> par_size;

 public:
  UnionFind() : _n(0), _size(0) {}
  UnionFind(int n) : _n(n), _size(n), par_size(n, -1) {}

  int unite(int a, int b) {
    assert(0 <= a && a < _n);
    assert(0 <= b && b < _n);
    a = root(a), b = root(b);
    if (a == b) return a;
    _size--;
    if (-par_size[a] < -par_size[b]) {
      par_size[b] += par_size[a];
      return par_size[a] = b;
    } else {
      par_size[a] += par_size[b];
      return par_size[b] = a;
    }
  }

  int root(int a) {
    assert(0 <= a && a < _n);
    if (par_size[a] < 0) return a;
    return par_size[a] = root(par_size[a]);
  }

  bool same(int a, int b) {
    assert(0 <= a && a < _n);
    assert(0 <= b && b < _n);
    return root(a) == root(b);
  }

  int size(int a) {
    assert(0 <= a && a < _n);
    return -par_size[root(a)];
  }

  int size() { return _size; }

  std::vector<std::vector<int>> groups() {
    std::vector<int> leader_buf(_n), group_size(_n);
    for (int i = 0; i < _n; i++) {
      leader_buf[i] = root(i);
      group_size[leader_buf[i]]++;
    }
    std::vector<std::vector<int>> result(_n);
    for (int i = 0; i < _n; i++) {
      result[i].reserve(group_size[i]);
    }
    for (int i = 0; i < _n; i++) {
      result[leader_buf[i]].push_back(i);
    }
    result.erase(
        std::remove_if(result.begin(), result.end(),
                       [&](const std::vector<int>& v) { return v.empty(); }),
        result.end());
    return result;
  }
};
