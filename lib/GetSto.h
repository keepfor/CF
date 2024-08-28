#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

class Solver {
 public:
  void Main() const;

 private:
  void SetIO() const;
  void Run() const;
  void Solve() const;
};

vector<string> ResultList;

int SearhMatch(string input) {
  regex reg("(\\d+)\\)");
  smatch sm;
  int count = 0;
  int cnt = 0;
  while (cnt < 2 && regex_search(input, sm, reg)) {
    ++count;
    cout << sm[1] << '\n';
    ResultList.push_back(sm[1]);
    input = sm.suffix().str();
    ++cnt;
  }
  return 0;
}

vector<string> SplitLine(string sen) {
  stringstream ss(sen);
  string word;
  vector<string> words;
  while (ss >> word) {
    words.push_back(word);
  }
  SearhMatch(words[1]);
  return words;
}

void GetLine() {
  string s;
  int cnt = 0;
  while (getline(cin, s)) {
    SplitLine(s);
    ++cnt;
  }
}

void Solver::Solve() const {
  using ll = long long;
  GetLine();
}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

inline void Solver::SetIO() const { cin.tie(0)->sync_with_stdio(0); }

void Solver::Main() const {
  SetIO();
  Run();
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
/*
6012-0067242	元大高股息(0056)	上市	現股	3,000
114,996	38.32	38.43	38.99	116,970	1.75%	116,829	1,833	1.59%	提交
6012-0067242	復華富時不動產(00712)	上市	現股	2,000
19,846	9.92	9.95	9.97	19,940	0.50%	19,906	60	0.3%	提交
6012-0067242	國泰永續高股息(00878)	上市	現股	1,000
23,098	23.09	23.16	22.93	22,930	-0.69%	22,900	-198	-0.85%	提交
6012-0067242	中信中國高股息(00882)	上市	現股	1,000
10,948	10.94	10.98	11.01	11,010	0.64%	10,991	43	0.39%	提交
6012-0067242	富邦特選高股息30(00900)	上市	現股	1,000
14,888	14.88	14.93	15.1	15,100	1.48%	15,077	189	1.26%	提交
6012-0067242	群益台灣精選高息(00919)	上市	現股	1,000	25,008
25	25.07	24.65	24,650	-1.40%	24,618	-390	-1.55%	提交
6012-0067242	復華台灣科技優息(00929)	上市	現股	4,000
79,132	19.78	19.84	19.59	78,360	-0.96%	78,252	-880	-1.11%	提交
6012-0067242	台泥(1101)	上市	現股	1,000
32,758	32.75	32.91	32.9	32,900	0.46%	32,794	36	0.1%	提交
6012-0067242	亞泥(1102)	上市	現股	1,000
41,609	41.6	41.8	44.9	44,900	7.93%	44,756	3,147	7.56%	提交
6012-0067242	中鋼(2002)	上市	現股	1,000
23,208	23.2	23.32	22.35	22,350	-3.66%	22,275	-933	-4.02%	提交
6012-0067242	聯電(2303)	上市	現股	1,000
51,912	51.9	52.15	55.2	55,200	6.36%	55,022	3,110	5.99%	提交
6012-0067242	仁寶(2324)	上市	現股	1,000
32,108	32.1	32.26	33.25	33,250	3.58%	33,143	1,035	3.22%	提交
6012-0067242	宏碁(2353)	上市	現股	1,000
46,060	46.05	46.27	44.3	44,300	-3.80%	44,158	-1,902	-4.12%	提交
6012-0067242	瑞昱(2379)	上市	現股	1,000	519,124	519	521.44
532	532,000	2.50%	530,277	11,153	2.14%	提交 6012-0067242
中華電(2412)	上市	現股	2,000	237,056	118.5	119.06	124
248,000	4.64%	247,198	10,142	4.27%	提交 6012-0067242	燦坤(2430)
上市	現股	1,000	36,058	36.05	36.22	33.4	33,400	-7.35%	33,292
-2,766	-7.67%	提交 6012-0067242	長榮(2603)	上市	現股	1,000
171,540	171.5	172.31	183	183,000	6.71%	182,408	10,868	6.33%	提交
6012-0067242	榮運(2607)	上市	現股	1,000	30,208	30.2	30.35
31	31,000	2.65%	30,899	691	2.28%	提交 6012-0067242
華航(2610)	上市	現股	2,000	43,116	21.55	21.66	20.85	41,700
-3.25%	41,560	-1,556	-3.6%	提交 6012-0067242	長榮航(2618)	上市
現股	1,000	35,208	35.2	35.37	34.9	34,900	-0.85%	34,788	-420
-1.19%	提交 6012-0067242	彰銀(2801)	上市	現股	1,000
18,558	18.55	18.65	18	18,000	-2.96%	17,938	-620	-3.34%	提交
6012-0067242	統一證(2855)	上市	現股	2,000
56,516	28.25	28.39	26.4	52,800	-6.55%	52,626	-3,890	-6.88%	提交
6012-0067242	玉山金(2884)	上市	現股	1,000
26,308	26.3	26.43	27.85	27,850	5.89%	27,759	1,451	5.51%	提交
6012-0067242	中信金(2891)	上市	現股	1,000
35,558	35.55	35.72	33.1	33,100	-6.89%	32,993	-2,565	-7.21%	提交
6012-0067242	遠百(2903)	上市	現股	1,000
30,808	30.8	30.95	28.5	28,500	-7.47%	28,407	-2,401	-7.79%	提交
6012-0067242	聯詠(3034)	上市	現股	1,000	573,137	573	575.69
541	541,000	-5.58%	539,248	-33,889	-5.91%	提交 6012-0067242
台灣大(3045)	上市	現股	1,000	101,024	101	101.48	111.5
111,500	10.40%	111,140	10,116	10.01%	提交 6012-0067242	洋華(3622)
上市	現股	1,000	56,013	56	56.27	58.2	58,200	3.93%	58,013
2,000	3.57%	提交 6012-0067242	遠傳(4904)	上市	現股	1,000
79,618	79.6	79.98	91.6	91,600	15.08%	91,305	11,687	14.67%	提交
6012-0067242	中租-KY(5871)	上市	現股	1,000	149,035	149	149.7
144.5	144,500	-3.02%	144,033	-5,002	-3.35%	提交 6012-0067242
群益證(6005)	上市	現股	1,000	23,858	23.85	23.97	21.95	21,950
-7.97%	21,877	-1,981	-8.3%	提交 6012-0067242	頎邦(6147)	上櫃
現股	1,000	64,915	64.9	65.21	66.2	66,200	2.00%	65,987
1,072	1.65%	提交 6012-0067242	豐泰(9910)	上市	現股	1,000
143,034	143	143.67	146.5	146,500	2.45%	146,026
*/