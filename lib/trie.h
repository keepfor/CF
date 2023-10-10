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

class Trie {
public:
    vector<vector<int>> v;
    vector<int> nw;
    vector<int> end;

    void nd() {
        v.emplace_back(vector<int>(26, -1));
        end.push_back(0);
    }

    Trie() {
        nd();
    }
    
    void insert(string w) {
        int cur = 0;
        for (auto& i : w) {
            int x = i - 'a';
            if (v[cur][x] == -1) {
                v[cur][x] = v.size();
            }
            cur = v[cur][x];
            if (cur == v.size()) {
                nd();
            }
        }
        end[cur] = 1;
    }
    
    bool search(string w) {
        int cur = 0;
        for (auto& i : w) {
            int x = i - 'a';
            if (v[cur][x] == -1) {
                return false;
            }
            cur = v[cur][x];
        }
        return end[cur];
    }
    
    bool startsWith(string w) {
        int cur = 0;
        for (auto& i : w) {
            int x = i - 'a';
            if (v[cur][x] == -1) {
                return false;
            }
            cur = v[cur][x];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
