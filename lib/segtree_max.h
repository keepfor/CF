#include <bits/stdc++.h>

using namespace std;

template<class T> struct seg_tree {
	const T ID = -1;
	T combine(T a, T b) {
		return max(a, b);
	}

	int n;
	vector<T> seg;
	void init(int _n) {
		n = _n;
		seg.assign(4 * n, ID);
	}

	void pull(int u) {
		seg[u] = combine(seg[2 * u], seg[2 * u + 1]);
	}

	void build(vector<T>& a, int u, int l, int r) {
		if (l == r) {
			seg[u] = a[l];
			return;
		}
		int mid = (l + r) / 2;
		build(a, 2 * u, l, mid);
		build(a, 2 * u + 1, mid + 1, r);
		pull(u);
	}

	void build(vector<T>& a) {
		build(a, 1, 0, n - 1);
	}

	void upd(int x, T val, int u, int l, int r) {
		if (l > x || r < x) return;
		if (l == r) {
			seg[u] = val;
			return;
		}
		int mid = (l + r) / 2;
		upd(x, val, 2 * u, l, mid);
		upd(x, val, 2 * u + 1, mid + 1, r);
		pull(u);
	}

	void upd(int x, T val) {
		upd(x, val, 1, 0, n - 1);
	}

	T qry(int x, int y, int u, int l, int r) {
		if (l > y || r < x) return ID;
		if (x <= l && r <= y) return seg[u];
		int mid = (l + r) / 2;
		return combine(qry(x, y, 2 * u, l, mid), qry(x, y, 2 * u + 1, mid + 1, r));
	}

	T qry(int x, int y) {
		return qry(x, y, 1, 0, n - 1);
	}
};
