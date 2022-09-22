#include<bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include"debug.h"
#endif
void f() {
    const int N = 1e9;
    srand(time(0));
    for(int x=0;x<N;x++) {
        cout << 1+ (rand() % N) <<"\n"; 
    }
    return; 
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    f();
    return 0;
}
