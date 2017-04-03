#include <iostream>
#include "Tree.h"

using std::cin;
using std::cout;

int main() {
    Tree tree;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        tree.insert(val, i);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << tree.getSum(l, r) << '\n';
        } else if (type == 2) {
            int x, pos;
            cin >> x >> pos;
            tree.insert(x, pos);
        } else if (type == 3) {
            int pos;
            cin >> pos;
            tree.remove(pos);
        } else if (type == 4) {
            int x, l, r;
            cin >> x >> l >> r;
            tree.assign(l, r, x);
        } else if (type == 5) {
            int x, l, r;
            cin >> x >> l >> r;
            tree.add(l, r, x);
        } else if (type == 6) {
            int l, r;
            cin >> l >> r;
            tree.nextPermutation(l, r);
        } else if (type == 7) {
            int l, r;
            cin >> l >> r;
            tree.prevPermutation(l, r);
        }
    }
    for (int i = 0; i < tree.size(); ++i)
        cout << tree.get(i) << ' ';
}