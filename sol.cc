#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

class Solver {
 public:
  inline void Main() const {
    SetIO();
    Run();
  }

 private:
  inline void SetIO() const {
    cin.tie(0)->sync_with_stdio(0);
  }
  void Solve() const;
  void Run() const;
};

using ll = long long;

void Solver::Solve() const {

}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
class Solution {
public:
    int vis[100005];
    int medianOfUniquenessArray(vector<int>& nums) {
        long long tot=nums.size();
        tot=(tot+1)*tot/2;
        long long need=(tot-1)/2;
      //  printf("%lld\n",need);
        int Max=nums.size()+1,Min=0;
        for(auto it:nums)vis[it]=0;
        while(Max>Min+1){
            int mid=(Max+Min)/2;
            int l=0,cnt=0;
            long long sum=0;
            for(int i = 0;i<nums.size();i++){
                if(!vis[nums[i]])cnt++;
                vis[nums[i]]++;
                while(cnt>=mid){
                    vis[nums[l]]--;
                    if(vis[nums[l]]==0)cnt--;
                    l++;
                }
                sum+=i-l+1;
            }
               for(auto it:nums)vis[it]=0;
          //  printf("%d %d\n",mid,sum);
            if(sum<=need)Min=mid;
            else Max=mid;
        }
        return Min;
    }
};