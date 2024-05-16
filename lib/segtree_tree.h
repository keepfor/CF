#include <bits/stdc++.h>
using namespace std;
const long long MOD = 998244353;
namespace product
{
struct segment_tree{
  int N;
  vector<long long> ST;
  segment_tree(int n){
    N = 1;
    while (N < n){
      N *= 2;
    }
    ST = vector<long long>(N * 2 - 1, 1);
    for (int i = 0; i < n; i++){
      ST[N - 1 + i] = 0;
    }
    for (int i = N - 2; i >= 0; i--){
      ST[i] = ST[i * 2 + 1] * ST[i * 2 + 2] % MOD;
    }
  }
  long long operator [](int k){
    return ST[N - 1 + k];
  }
  void update(int i, long long x){
    i += N - 1;
    ST[i] = x;
    while (i > 0){
      i = (i - 1) / 2;
      ST[i] = ST[i * 2 + 1] * ST[i * 2 + 2] % MOD;
    }
  }
  long long all(){
    return ST[0];
  }
};  
} // namespace name

