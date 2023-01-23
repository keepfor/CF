#ifndef CP
#define CP
#include<bits/stdc++.h>
using namespace std;
#endif

#ifdef LOCAL
#include"./lib/debug.h"
#else 
#define debug(...) 0
#endif

#include <unistd.h>

int main(int argc, char * argv[]) {
  cout << "argc is " << argc << '\n';
  cout << "argv is ";
  for (int i = 1; i < argc; ++i) {
    cout << argv[i] << '\n';
  }
  int t = stoi(argv[1]);
  t *= 60;
  while (t--) {
    auto getT = [&]() {
      int tt = t;
      int m = tt / 60;
      tt %= 60;
      cout << m << ":" << tt << '\n';
    };
    getT();
    sleep(1);
  }
  return 0;
}
