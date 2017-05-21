#include <iostream>
#include "Tree.h"

using std::cin;
using std::cout;

int main() {
    Tree tree;
    long n;
    cin >> n;
    for (size_t i = 0; i < n; ++i) {
        long val;
        cin >> val;
        tree.insert(val, i);
    }
    long q;
    cin >> q;
    for (long i = 0; i < q; ++i) {
        long type;
        cin >> type;
        if (type == 1) {
            size_t l, r;
            cin >> l >> r;
            cout << tree.getSum(l, r) << '\n';
        } else if (type == 2) {
            long x;
            size_t pos;
            cin >> x >> pos;
            tree.insert(x, pos);
        } else if (type == 3) {
            size_t pos;
            cin >> pos;
            tree.remove(pos);
        } else if (type == 4) {
            long x;
            size_t l, r;
            cin >> x >> l >> r;
            tree.assign(l, r, x);
        } else if (type == 5) {
            long x;
            size_t l, r;
            cin >> x >> l >> r;
            tree.add(l, r, x);
        } else if (type == 6) {
            size_t l, r;
            cin >> l >> r;
            tree.nextPermutation(l, r);
        } else if (type == 7) {
            size_t l, r;
            cin >> l >> r;
            tree.prevPermutation(l, r);
        }
    }
    for (size_t i = 0; i < tree.size(); ++i)
        cout << tree.get(i) << ' ';
}
