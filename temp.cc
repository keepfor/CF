#include <bits/stdc++.h>                                                                                                            

#include "debug.h"

using namespace std;                                                                                                                
                                                                                                                                    
// https://www.brand.site.co.il/riddles/201401a.html                                                                                
//                                                                                                                                  
vector<string> strategies[4];                                                                                                       
                                                                                                                                    
int interact(string s) {                                                                                                            
  cout << s << endl;                                                                                                                
  int n;                                                                                                                            
  cin >> n;                                                                                                                         
  return n;                                                                                                                         
}                                                                                                                                   
                                                                                                                                    
int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  strategies[0] = {"1"};
  for (int i = 1; i < 4; i++) {
    for (string& s: strategies[i-1]) {
      strategies[i].push_back(s+s);
    }
    for (string&s: strategies[i-1]) {
      strategies[i].push_back(string(1<<(i-1), '0')+s);
      for (string& t: strategies[i-1]) {
        strategies[i].push_back(t+t);
      }
    }
  }
  for (int i = 0; i < 4; ++i) {
    debug(strategies[i]);
  }
  strategies[3].insert(strategies[3].begin(), "00000000");
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    for (string& s: strategies[3]) {
      if (!interact(s)) break;
    }
  }
}

