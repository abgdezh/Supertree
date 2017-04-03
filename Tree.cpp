#include "Tree.h"

using std::pair;
using std::make_pair;

Tree::Tree() : root(0) {}

int Tree::size() {
    return root ? root->getElementsNumber() : 0;
}

void Tree::separate(int left, int right) {
    pair<CartesianTree *, CartesianTree *> beforeLthAndAfterLth = CartesianTree::split(root, left);
    pair<CartesianTree *, CartesianTree *> fromLthToRthAndAfterRth = CartesianTree::split(beforeLthAndAfterLth.second,
                                                                                          right - left + 1);
    separation.beforeLth = beforeLthAndAfterLth.first;
    separation.fromLthToRth = fromLthToRthAndAfterRth.first;
    separation.afterRth = fromLthToRthAndAfterRth.second;
}

void Tree::join() {
    root = CartesianTree::merge(separation.beforeLth,
                                CartesianTree::merge(separation.fromLthToRth, separation.afterRth));
}

int Tree::get(int pos) {
    return static_cast<int>(getSum(pos, pos));
}

long long Tree::getSum(int left, int right) {
    separate(left, right);
    long long res = separation.fromLthToRth->getSum();
    join();
    return res;
}

void Tree::insert(int elem, int position) {
    separate(position, position - 1);
    separation.fromLthToRth = new CartesianTree(elem);
    join();
}

void Tree::remove(int position) {
    separate(position, position);
    if (separation.fromLthToRth)
        delete separation.fromLthToRth;
    separation.fromLthToRth = nullptr;
    join();
}

void Tree::add(int left, int right, int addition) {
    separate(left, right);
    separation.fromLthToRth->add(addition);
    join();
}

void Tree::assign(int left, int right, int assignment) {
    separate(left, right);
    separation.fromLthToRth->assign(assignment);
    join();
}

void Tree::assign(int pos, int assignment) {
    assign(pos, pos, assignment);
}

void Tree::reverse(int left, int right) {
    separate(left, right);
    separation.fromLthToRth->reverse();
    join();
}

void Tree::swap(int pos1, int pos2) {
    int tmp = get(pos1);
    assign(pos1, get(pos2));
    assign(pos2, tmp);
}

int Tree::getMax(int left, int right) {
    separate(left, right);
    int ret = separation.fromLthToRth->getMax();
    join();
    return ret;
}

int Tree::getMin(int left, int right) {
    separate(left, right);
    int ret = separation.fromLthToRth->getMin();
    join();
    return ret;
}

Tree::Tree(CartesianTree *root) : root(root) {}

void Tree::doGeneralizedNextPrevPermutation(bool next) {
    int beginningOfMaxOrderSuffix = root->getBeginningOfMaxOrderedSuffix(next);
    if (beginningOfMaxOrderSuffix > 0) {
        int posOfBound = root->getUpperOrLowerBound(beginningOfMaxOrderSuffix,
                                                    get(beginningOfMaxOrderSuffix - 1) + (next ? 1 : -1), next);
        swap(posOfBound, beginningOfMaxOrderSuffix - 1);
    }
    reverse(beginningOfMaxOrderSuffix, root->getElementsNumber() - 1);
}

void Tree::nextPermutation(int left, int right) {
    separate(left, right);
    Tree segment(separation.fromLthToRth);
    segment.doGeneralizedNextPrevPermutation(true);
    join();
}

void Tree::prevPermutation(int left, int right) {
    separate(left, right);
    Tree segment(separation.fromLthToRth);
    segment.doGeneralizedNextPrevPermutation(false);
    join();
}
