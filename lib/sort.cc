#include<bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include"debug.h"
#endif
#include"time.h"
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int> a;
    int x;
    while (cin >> x) {
        a.push_back(x);
    }
    int n = a.size();
    function<void(int, int)> quick = [&](int left, int right) {
        if (left >= right) {
            return;
        }
        int add = rand() % (right - left + 1);
        swap(a[left], a[left + add]);
        auto partition = [&]() {
            int val = a[right];
            int now = left;
            for (int i = left; i < right; ++i) {
                if (a[i] <= val) {
                    swap(a[i], a[now]);
                    ++now;
                }
            }
            swap(a[right], a[now]);
            return now;
        };
        int pivot = partition();
        quick(left, pivot - 1);
        quick(pivot + 1, right);
    };
    function<void(int, int)> merge = [&](int left, int right) {
        if (left >= right) {
            return;
        }
        int mid = (left + right) >> 1;
        merge(left, mid);
        merge(mid + 1, right);
        auto sort = [&]() {
            int sz = right - left + 1;
            vector<int> tmp(sz);
            int k = 0;
            int one = left;
            int two = mid + 1;
            while (one <= mid && two <= right) {
                tmp[k++] = a[one] < a[two] ? a[one++] : a[two++];
            }
            while (one <= mid) {
                tmp[k++] = a[one++];
            }
            while (two <= right) {
                tmp[k++] = a[two++];
            }
            k = 0;
            for (int i = left; i <= right; ++i) {
                a[i] = tmp[k++];
            }
        };
        sort();
    };
    auto heap = [&]() {
        function<void(int, int)> _max = [&](int left, int right) -> void {
            if (left >= right) {
                return;
            }
            while (left < right) {
                int child_left = left * 2 + 1;
                int child_right = left * 2 + 2;
                int max_child = -1;
                if (child_left <= right && child_right <= right) {
                    max_child = a[child_left] > a[child_right] ? child_left : child_right;
                } else if (child_left <= right) {
                    max_child = child_left;
                } else {
                    return;
                }
                if (a[left] >= a[max_child]) {
                    return;
                }
                swap(a[left], a[max_child]);
                left = max_child;
            }
        };
        for (int i = n / 2; i >= 0; --i) {
            _max(i, n - 1);
        }
        for (int i = n - 1; i >= 0; --i) {
            swap(a[i], a[0]);
            _max(0, i - 1);
        }
    };
    Time T;
    T.start();
    heap();
    T.get();
    bool ans = is_sorted(a.begin(), a.end());
    cout << (ans ? "YES" : "NO") << '\n';
    return 0;

