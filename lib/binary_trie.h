#include <bits/stdc++.h>
using namespace std;

const int INF = int(1e9) + 5;
const int BITS = 30;

template<int ALPHABET = 2>
struct binary_trie {
    struct trie_node {
        array<int, ALPHABET> child;
        int min_index = INF;

        trie_node() {
            memset(&child[0], -1, ALPHABET * sizeof(int));
        }

        void update_index(int index) {
            min_index = min(min_index, index);
        }
    };

    static const int ROOT = 0;

    vector<trie_node> nodes = {trie_node()};

    binary_trie(int total_length = -1) {
        if (total_length >= 0)
            nodes.reserve(total_length + 1);
    }

    int get_or_create_child(int node, int c) {
        if (nodes[node].child[c] < 0) {
            nodes[node].child[c] = int(nodes.size());
            nodes.emplace_back();
        }

        return nodes[node].child[c];
    }

    int add(int word, int index) {
        int node = ROOT;

        for (int bit = BITS - 1; bit >= 0; bit--) {
            nodes[node].update_index(index);
            node = get_or_create_child(node, int(word >> bit & 1));
        }

        nodes[node].update_index(index);
        return node;
    }

    int query_max(int target, int max_index) const {
        if (nodes[ROOT].min_index > max_index)
            return 0;

        int node = ROOT, ans = 0;

        for (int bit = BITS - 1; bit >= 0; bit--) {
            int want = (target >> bit & 1) ^ 1;
            int c = nodes[node].child[want];
            int oc = nodes[node].child[want ^ 1];

            if (c >= 0 && nodes[c].min_index <= max_index) {
                ans |= 1 << bit;
                node = c;
            } else {
                node = oc;
            }
        }

        return ans;
    }
};


struct query {
    int start0, end0;
    int start1, end1;
    int max_index;

    bool operator<(const query &other) const {
        return start1 < other.start1;
    }
};
/*
void run_case() {
    int N;
    cin >> N;
    vector<int> A(N);

    for (auto &a : A)
        cin >> a;

    RMQ<int, true> rmq(A);
    vector<query> queries;

    y_combinator([&](auto self, int start, int end) -> void {
        if (end - start <= 1)
            return;

        int max_index = rmq.query_index(start, end);
        int start0 = start, end0 = max_index;
        int start1 = max_index + 1, end1 = end;

        if (end1 - start1 < end0 - start0) {
            swap(start0, start1);
            swap(end0, end1);
        }

        queries.emplace_back();
        queries.back().start0 = start0;
        queries.back().start1 = start1;
        queries.back().end0 = end0;
        queries.back().end1 = end1;
        queries.back().max_index = max_index;

        self(start, max_index);
        self(max_index + 1, end);
    })(0, N);

    sort(queries.rbegin(), queries.rend());
    vector<int> prefix_xor(N + 1, 0);

    for (int i = 0; i < N; i++)
        prefix_xor[i + 1] = prefix_xor[i] ^ A[i];

    binary_trie trie;
    int p = N, best = 0;

    for (query &qry : queries) {
        while (p >= qry.start1) {
            trie.add(prefix_xor[p], p);
            p--;
        }

        for (int i = qry.start0; i <= qry.end0; i++) {
            int target = prefix_xor[i] ^ A[qry.max_index];
            best = max(best, trie.query_max(target, qry.end1));
        }
    }

    cout << best << '\n';
}

int main() {
    ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
    cin.tie(nullptr);
#endif

    int tests;
    cin >> tests;

    while (tests-- > 0)
        run_case();
}
*/
