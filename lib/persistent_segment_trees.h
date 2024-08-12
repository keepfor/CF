#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Node {
	ll val;
	Node *l, *r;

	Node(ll x) : val(x), l(nullptr), r(nullptr) {}
	Node(Node *ll, Node *rr) {
		l = ll, r = rr;
		val = 0;
		if (l) val += l->val;
		if (r) val += r->val;
	}
	Node(Node *cp) : val(cp->val), l(cp->l), r(cp->r) {}
};

int n, cnt = 1;
ll a[200001];
Node *roots[200001];

Node *build(int l = 1, int r = n) {
	if (l == r) return new Node(a[l]);
	int mid = (l + r) / 2;
	return new Node(build(l, mid), build(mid + 1, r));
}

Node *update(Node *node, int val, int pos, int l = 1, int r = n) {
	if (l == r) return new Node(val);
	int mid = (l + r) / 2;
	if (pos > mid)
		return new Node(node->l, update(node->r, val, pos, mid + 1, r));
	else return new Node(update(node->l, val, pos, l, mid), node->r);
}

ll query(Node *node, int a, int b, int l = 1, int r = n) {
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return node->val;
	int mid = (l + r) / 2;
	return query(node->l, a, b, l, mid) + query(node->r, a, b, mid + 1, r);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	roots[cnt++] = build();

	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int k, i, x;
			cin >> k >> i >> x;
			roots[k] = update(roots[k], x, i);
		} else if (t == 2) {
			int k, l, r;
			cin >> k >> l >> r;
			cout << query(roots[k], l, r) << '\n';
		} else {
			int k;
			cin >> k;
			roots[cnt++] = new Node(roots[k]);
		}
	}
	return 0;
}