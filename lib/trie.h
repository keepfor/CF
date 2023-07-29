#include <bits/stdc++.h>
using namespace std;

class Trie {
 public:
  vector<vector<int>> t;
  int sz = 0;
  unordered_set<int> end;
  Trie() {
    // do intialization if necessary
    t.emplace_back(vector<int>(26, -1));
    vector<int> end;
  }

  /*
   * @param word: a word
   * @return: nothing
   */
  void insert(string& word) {
    // write your code here
    int now = 0;
    for (auto& i : word) {
      int x = i - 'a';
      if (t[now][x] == -1) {
        t.emplace_back(vector<int>(26, -1));
        t[now][x] = ++sz;
      }
      now = t[now][x];
    }
    end.insert(now);
  }

  /*
   * @param word: A string
   * @return: if the word is in the trie.
   */
  bool search(string& word) {
    // write your code here
    int now = 0;
    for (auto& i : word) {
      int x = i - 'a';
      if (t[now][x] == -1) {
        return false;
      }
      now = t[now][x];
    }
    return end.count(now);
  }

  /*
   * @param prefix: A string
   * @return: if there is any word in the trie that starts with the given
   * prefix.
   */
  bool startsWith(string& prefix) {
    // write your code here
    int now = 0;
    for (auto& i : prefix) {
      int x = i - 'a';
      if (t[now][x] == -1) {
        return false;
      }
      now = t[now][x];
    }
    return true;
  }
};
