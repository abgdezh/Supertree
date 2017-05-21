#include "Tree.h"

using std::pair;
using std::make_pair;

Tree::Tree() : root(0) {}

size_t Tree::size() {
    return root ? root->getElementsNumber() : 0;
}

void Tree::separate(Separation &separation, size_t left, size_t right) {
    pair<CartesianTree *, CartesianTree *> beforeLthAndAfterLth = CartesianTree::split(root, left);
    pair<CartesianTree *, CartesianTree *> fromLthToRthAndAfterRth = CartesianTree::split(beforeLthAndAfterLth.second,
                                                                                          right + 1 - left);
    separation.beforeLth = beforeLthAndAfterLth.first;
    separation.fromLthToRth = fromLthToRthAndAfterRth.first;
    separation.afterRth = fromLthToRthAndAfterRth.second;
}

void Tree::join(Separation &separation) {
    root = CartesianTree::merge(separation.beforeLth,
                                CartesianTree::merge(separation.fromLthToRth, separation.afterRth));
}

long Tree::get(size_t pos) {
    return getSum(pos, pos);
}

long Tree::getSum(size_t left, size_t right) {
    return Separation(*this, left, right).fromLthToRth->getSum();
}

void Tree::insert(long elem, size_t position) {
    Separation separation(*this, position, position - 1);
    separation.fromLthToRth = new CartesianTree(elem);
}

void Tree::remove(size_t position) {
    Separation separation(*this, position, position);
    delete separation.fromLthToRth;
    separation.fromLthToRth = nullptr;
}

void Tree::add(size_t left, size_t right, long addition) {
    Separation(*this, left, right).fromLthToRth->add(addition);
}

void Tree::assign(size_t left, size_t right, long assignment) {
    Separation(*this, left, right).fromLthToRth->assign(assignment);
}

void Tree::assign(size_t pos, long assignment) {
    assign(pos, pos, assignment);
}

void Tree::reverse(size_t left, size_t right) {
    Separation(*this, left, right).fromLthToRth->reverse();
}

void Tree::swap(size_t pos1, size_t pos2) {
    long tmp = get(pos1);
    assign(pos1, get(pos2));
    assign(pos2, tmp);
}

long Tree::getMax(size_t left, size_t right) {
    return Separation(*this, left, right).fromLthToRth->getMax();
}

long Tree::getMin(size_t left, size_t right) {
    return Separation(*this, left, right).fromLthToRth->getMin();
}

Tree::Tree(CartesianTree *root) : root(root) {}

void Tree::doGeneralizedNextPrevPermutation(bool next) {
    size_t beginningOfMaxOrderSuffix = root->getBeginningOfMaxOrderedSuffix(next);
    if (beginningOfMaxOrderSuffix > 0) {
        size_t posOfBound = root->getUpperOrLowerBound(beginningOfMaxOrderSuffix,
                                                       get(beginningOfMaxOrderSuffix - 1) + (next ? 1 : -1), next);
        swap(posOfBound, beginningOfMaxOrderSuffix - 1);
    }
    reverse(beginningOfMaxOrderSuffix, root->getElementsNumber() - 1);
}

void Tree::nextPermutation(size_t left, size_t right) {
    Separation separation(*this, left, right);
    Tree segment(separation.fromLthToRth);
    segment.doGeneralizedNextPrevPermutation(true);
}

void Tree::prevPermutation(size_t left, size_t right) {
    Separation separation(*this, left, right);
    Tree segment(separation.fromLthToRth);
    segment.doGeneralizedNextPrevPermutation(false);
}

Tree::Separation::Separation(Tree &tree, size_t left, size_t right) : tree(tree) {
    tree.separate(*this, left, right);
}

Tree::Separation::~Separation() {
    tree.join(*this);
}

