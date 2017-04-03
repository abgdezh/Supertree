#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>

using std::vector;
using std::cout;
using std::cin;

int main() {
    vector<long long> v;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        v.push_back(x);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << std::accumulate(v.begin() + l, v.begin() + r + 1, 0LL) << '\n';
        } else if (type == 2) {
            long long x;
            int pos;
            cin >> x >> pos;
            v.insert(v.begin() + pos, x);
        } else if (type == 3) {
            int pos;
            cin >> pos;
            v.erase(v.begin() + pos);
        } else if (type == 4) {
            long long x;
            int l, r;
            cin >> x >> l >> r;
            for (int i = l; i <= r; ++i)
                v[i] = x;
        } else if (type == 5) {
            long long x;
            int l, r;
            cin >> x >> l >> r;
            for (int i = l; i <= r; ++i)
                v[i] += x;
        } else if (type == 6) {
            int l, r;
            cin >> l >> r;
            std::next_permutation(v.begin() + l, v.begin() + r + 1);
        } else if (type == 7) {
            int l, r;
            cin >> l >> r;
            std::prev_permutation(v.begin() + l, v.begin() + r + 1);
        }
    }
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << ' ';
}