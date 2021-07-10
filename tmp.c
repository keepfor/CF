
const int MAXN = 100005;

struct SuffixAutomaton {
	map<int,int> ch[MAXN << 1];
    int last, tot, nxt[MAXN << 1], len[MAXN << 1];
    SuffixAutomaton() {
        last = tot = 1;
    }
    inline void extend(int c) {
        int u = ++tot, v = last; 
        len[u] = len[v] + 1;
        for(; v && !ch[v][c]; v = nxt[v]) ch[v][c] = u;
        if(!v) {
            nxt[u] = 1;
        } else if(len[ch[v][c]] == len[v] + 1) {
            nxt[u] = ch[v][c];
        } else {
            int n = ++tot, o = ch[v][c]; len[n] = len[v] + 1;
            ch[n]= ch[o];
            nxt[n] = nxt[o]; nxt[o] = nxt[u] = n;
            for(; v && ch[v][c] == o; v = nxt[v]) ch[v][c] = n;
        }
        last = u;
    } 
} sam;

int a[MAXN << 1], c[MAXN << 1], mx[MAXN << 1], ans[MAXN << 1];

class Solution {
public:
    int longestCommonSubpath(int n, vector<vector<int>>& paths) {
	    memset(ans, 0x3f, sizeof(ans));
	    memset(a, 0, sizeof(a));
	    memset(c, 0, sizeof(a));
	    memset(mx, 0, sizeof(a));
	    for(int i=0;i<MAXN<<1;i++)sam.ch[i].clear();
	    sam.last = sam.tot = 1;
	    memset(sam.nxt, 0, sizeof(a));
	    memset(sam.len, 0, sizeof(a));
	    for(int i = 0; i<paths[0].size(); i++) {
	        sam.extend(paths[0][i]);
	    }
	    for(int i = 1; i <= sam.tot; i++) c[sam.len[i]]++;
	    for(int i = 1; i <= sam.tot; i++) c[i] += c[i - 1];
	    for(int i = 1; i <= sam.tot; i++) a[c[sam.len[i]]--] = i;
	    for(int j = 1;j<paths.size();j++){
	        int len = 0, p = 1, c; 
	        for(int i = 0; i<paths[j].size(); i++) {
	            c = paths[j][i];
	            while(p && !sam.ch[p][c]) {
	                p = sam.nxt[p]; len = sam.len[p];
	            }
	            if(p) {
	                len++; p = sam.ch[p][c]; mx[p] = std::max(mx[p], len);
	            } else {
	                p = 1; len = 0;
	            }
	        }
	        for(int i = sam.tot; i; i--) {
	            int p = a[i];
	            mx[sam.nxt[p]] = std::max(mx[sam.nxt[p]], std::min(mx[p], sam.len[sam.nxt[p]]));
	            ans[p] = std::min(ans[p], mx[p]); mx[p] = 0;
	        }
	    }
	    int res = 0;
	    for(int i = 1; i <= sam.tot; i++) {
	        res = std::max(res, ans[i]);
	    }
	    return res;
    }
};