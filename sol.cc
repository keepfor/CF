#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef double db;
typedef unsigned long long ull;

template<typename T>inline void read(T&num){
    int f=1,ch=getchar();num=0;
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){num=num*10+(ch^48);ch=getchar();}
    num=num*f;
}
template<typename T>void print(T x){
    if(x<0){putchar('-');x=-x;}
    if(x>9)print(x/10);
    putchar(x%10+48);
}

const int MAXN=5e5+15;
int a[MAXN],q,tot,x,now,fa[MAXN];
map<int,int>pos;
char opt[10];

inline void create(int x){
    tot++;a[tot]=x;fa[tot]=now;now=tot;
}
inline void del(){
    now=fa[now];
}

int main(){
    read(q);
    for(int times=1;times<=q;times++){
        scanf("%s",opt+1);
        if(opt[1]=='A'){
            read(x);
            create(x);
        }
        else if(opt[1]=='S'){
            read(x);
            pos[x]=now;
        }
        else if(opt[1]=='L'){
            read(x);
            now=pos[x];
        }
        else if(opt[1]=='D'){
            if(now)now=fa[now];
        }
        if(!now)print(-1);
        else print(a[now]);
        putchar(' ');
    }puts("");
    
    return 0;
}
