template <typename T>
vector<int> pi(T s) {
  vector<int> p(s.size());
  for (int i = 1, j = 0; i < s.size(); i++) {
    while (j and s[j] != s[i]) j = p[j - 1];
    if (s[j] == s[i]) j++;
    p[i] = j;
  }
  return p;
}

template <typename T>
vector<int> matching(T& s, T& t) {
  vector<int> p = pi(s), match;
  for (int i = 0, j = 0; i < t.size(); i++) {
    while (j and s[j] != t[i]) j = p[j - 1];
    if (s[j] == t[i]) j++;
    if (j == s.size()) match.push_back(i - j + 1), j = p[j - 1];
  }
  return match;
}

class Solution {
 public:
  vector<int> beautifulIndices(string s, string a, string b, int k) {
    auto pa = matching(a, s);
    auto pb = matching(b, s);

    vector<int> ans;
    for (int i : pa) {
      auto it = lower_bound(pb.begin(), pb.end(), i);
      if (it != pb.end() && *it - i <= k)
        ans.push_back(i);
      else if (it != pb.begin() && i - *prev(it) <= k)
        ans.push_back(i);
    }

    return ans;
  }
};