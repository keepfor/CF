
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1000;

int qu[N], dd[N], pp[N], qq[N];

int main() {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		cout << "+ " << n << endl;
		int a; cin >> a;
		cout << "+ " << n + 1 << endl;
		cin >> a;
		for (int h = 0, i = 0, j = n - 1; i <= j; i++, j--) {
			qu[h++] = j;
			if (i < j)
				qu[h++] = i;
		}
		int i_ = 0, d_ = 0;
		for (int i = 1; i < n; i++)
			if (i) {
				cout << "? 1 " << i + 1 << endl;
				int d; cin >> d;
				if (d_ < d) {
					i_ = i;
					d_ = d;
				}
			}
		for (int i = 0; i < n; i++)
			if (i != i_) {
				cout << "? " << i_ + 1 << ' ' << i + 1 << endl;
				cin >> dd[i];
			}
		pp[i_] = qu[0];
		for (int i = 0; i < n; i++)
			if (i != i_)
				pp[i] = qu[dd[i]];
		qq[i_] = qu[n - 1];
		for (int i = 0; i < n; i++)
			if (i != i_)
				qq[i] = qu[n - 1 - dd[i]];
		cout << '!';
		for (int i = 0; i < n; i++)
			cout << ' ' << pp[i] + 1;
		for (int i = 0; i < n; i++)
			cout << ' ' << qq[i] + 1;
		cout << endl;
		cin >> a;
	}
	return 0;
}

