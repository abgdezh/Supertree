#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>

using std::cin;
using std::pair;
using std::min;
using std::max;
using std::cout;
using std::swap;
using std::make_pair;

class CartesianTree {
    CartesianTree *left;
    CartesianTree *right;
    long data, priority;
    long sum;
    long elementsNumber;
    long minimum, maximum;

    bool isReversed;
    bool isAssigned;

    long addition;
    long assignment;

    enum Order {
        NO_ORDER, INCREASING, DECREASING, STABLE
    } order;
    long firstElement, lastElement;

    static bool isCompatibleWithOrder(CartesianTree *tree, Order order);

    void recalculate();

    void push();

public:
    CartesianTree(long x);

    static pair<CartesianTree *, CartesianTree *> split(CartesianTree *t, long num);

    static CartesianTree *merge(CartesianTree *l, CartesianTree *r);

    long getSum() const;

    long getMin() const;

    long getMax() const;

    long getUpperOrLowerBound(long posBeg, long number, bool suffixIsDecreasing);

    long getElementsNumber() const;

    void add(long delta);

    void assign(long value);

    void reverse();

    long getBeginningOfMaxOrderedSuffix(bool decreasingOrder);

    static std::string toString(CartesianTree *node, bool reversed = false, long assignment = INT32_MAX, long addition = 0);
};




CartesianTree::CartesianTree(long x) : left(0), right(0), data(x), priority(rand()),
                                      sum(x), elementsNumber(1), minimum(x), maximum(x),
                                      isReversed(false), isAssigned(false), addition(0), assignment(0),
                                      order(STABLE), firstElement(x), lastElement(x) {}

pair<CartesianTree *, CartesianTree *> CartesianTree::split(CartesianTree *t, long num) {
    if (!t)
        return make_pair(nullptr, nullptr);
    t->push();
    long leftNum = t->left ? t->left->elementsNumber : 0;
    if (leftNum < num) {
        pair<CartesianTree *, CartesianTree *> tmp = split(t->right, num - leftNum - 1);
        t->right = tmp.first;
        t->recalculate();
        return make_pair(t, tmp.second);
    } else {
        pair<CartesianTree *, CartesianTree *> tmp = split(t->left, num);
        t->left = tmp.second;
        t->recalculate();
        return make_pair(tmp.first, t);
    }
}

CartesianTree *CartesianTree::merge(CartesianTree *l, CartesianTree *r) {
    if (!l)
        return r;
    if (!r)
        return l;
    CartesianTree *ret = l->priority > r->priority ? l : r;
    if (l->priority > r->priority) {
        l->push();
        l->right = merge(l->right, r);
    } else {
        r->push();
        r->left = merge(l, r->left);
    }
    ret->recalculate();
    return ret;
}

bool CartesianTree::isCompatibleWithOrder(CartesianTree *tree, Order order) {
    if (!tree)
        return true;
    if (order == NO_ORDER)
        return true;
    if (order == STABLE)
        return tree->order == STABLE;
    if (order == INCREASING)
        return tree->order == STABLE || tree->order == INCREASING;
    if (order == DECREASING)
        return tree->order == STABLE || tree->order == DECREASING;
}

void CartesianTree::recalculate() {
    elementsNumber = 1 + (left ? left->elementsNumber : 0) + (right ? right->elementsNumber : 0);
    sum = data + (left ? left->sum : 0) + (right ? right->sum : 0);
    minimum = maximum = data;
    if (left) {
        minimum = min(minimum, left->minimum);
        maximum = max(maximum, left->maximum);
    }
    if (right) {
        minimum = min(minimum, right->minimum);
        maximum = max(maximum, right->maximum);
    }
    if (isCompatibleWithOrder(left, STABLE) && (!left || left->data == data) &&
        isCompatibleWithOrder(right, STABLE) && (!right || right->data == data))
        order = STABLE;
    else if (isCompatibleWithOrder(left, INCREASING) && (!left || left->lastElement <= data) &&
             isCompatibleWithOrder(right, INCREASING) && (!right || right->firstElement >= data))
        order = INCREASING;
    else if (isCompatibleWithOrder(left, DECREASING) && (!left || left->lastElement >= data) &&
             isCompatibleWithOrder(right, DECREASING) && (!right || right->firstElement <= data))
        order = DECREASING;
    else
        order = NO_ORDER;

    lastElement = right ? right->lastElement : data;
    firstElement = left ? left->firstElement : data;
}

void CartesianTree::push() {
    if (isReversed) {
        isReversed = !isReversed;
        if (left)
            left->reverse();
        if (right)
            right->reverse();
    }

    if (isAssigned) {
        isAssigned = false;
        if (left)
            left->assign(assignment);
        if (right)
            right->assign(assignment);
    }

    if (addition) {
        if (left)
            left->add(addition);
        if (right)
            right->add(addition);
        addition = 0;
    }
    recalculate();
}

void CartesianTree::add(long delta) {
    addition += delta;
    data += delta;
    sum += 1L * elementsNumber * delta;
    minimum += delta;
    maximum += delta;
    firstElement += delta;
    lastElement += delta;
}

void CartesianTree::assign(long value) {
    assignment = data = maximum = minimum = firstElement = lastElement = value;
    isAssigned = true;
    addition = 0;
    sum = 1L * elementsNumber * value;
    order = STABLE;
}

void CartesianTree::reverse() {
    isReversed = !isReversed;
    if (order == INCREASING)
        order = DECREASING;
    else if (order == DECREASING)
        order = INCREASING;
    swap(firstElement, lastElement);
    swap(left, right);
}

long CartesianTree::getSum() const {
    return sum;
}

long CartesianTree::getMin() const {
    return minimum;
}

long CartesianTree::getMax() const {
    return maximum;
}

long CartesianTree::getElementsNumber() const {
    return elementsNumber;
}

long CartesianTree::getBeginningOfMaxOrderedSuffix(bool decreasingOrder) {
    push();
    Order rightOrder = decreasingOrder ? DECREASING : INCREASING;
    long leftNum = left ? left->elementsNumber : 0;
    if (isCompatibleWithOrder(right, rightOrder)) {
        if (!right || (decreasingOrder ? (right->firstElement <= data) : (right->firstElement >= data))) {
            if (left && (decreasingOrder ? (left->lastElement >= data) : (left->lastElement <= data))) {
                return left->getBeginningOfMaxOrderedSuffix(decreasingOrder);
            }
            return leftNum;
        }
        return leftNum + 1;
    } else
        return leftNum + 1 + right->getBeginningOfMaxOrderedSuffix(decreasingOrder);

}

long CartesianTree::getUpperOrLowerBound(long posBeg, long number, bool suffixIsDecreasing) {
    push();
    long posRoot = left ? left->elementsNumber : 0;
    if (right && (suffixIsDecreasing ? (right->maximum >= number) : (right->minimum <= number)))
        return right->getUpperOrLowerBound(max(posBeg - posRoot - 1, 0L), number, suffixIsDecreasing) + posRoot + 1;
    if (suffixIsDecreasing ? (data >= number) : (data <= number))
        return posRoot;
    return left->getUpperOrLowerBound(posBeg, number, suffixIsDecreasing);
}

std::string CartesianTree::toString(CartesianTree *node, bool reversed, long assignment, long addition) {
    std::string res = "";
    if (!node)
        return res;
    reversed ^= node->isReversed;
    res += toString(reversed ? node->right : node->left, reversed, assignment, addition);
    res += std::to_string(node->data) + " ";
    res += toString(reversed ? node->left : node->right, reversed, assignment, addition);
    return res;
}



class Tree {
    CartesianTree *root;

    Tree(CartesianTree *root);

    struct Separation {
        CartesianTree *beforeLth;
        CartesianTree *fromLthToRth;
        CartesianTree *afterRth;
    } separation;

    void separate(long left, long right);

    void join();

    void doGeneralizedNextPrevPermutation(bool next);

public:
    Tree();

    long get(long pos);

    long getSum(long left, long right);

    long getMin(long left, long right);

    long getMax(long left, long right);

    long size();

    void insert(long elem, long position);

    void remove(long position);

    void add(long left, long right, long addition);

    void assign(long left, long right, long assignment);

    void assign(long pos, long assignment);

    void reverse(long left, long right);

    void swap(long pos1, long pos2);

    void nextPermutation(long left, long right);

    void prevPermutation(long left, long right);
};




Tree::Tree() : root(0) {}

long Tree::size() {
    return root ? root->getElementsNumber() : 0;
}

void Tree::separate(long left, long right) {
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

long Tree::get(long pos) {
    return getSum(pos, pos);
}

long Tree::getSum(long left, long right) {
    separate(left, right);
    long res = separation.fromLthToRth->getSum();
    join();
    return res;
}

void Tree::insert(long elem, long position) {
    separate(position, position - 1);
    separation.fromLthToRth = new CartesianTree(elem);
    join();
}

void Tree::remove(long position) {
    separate(position, position);
    if (separation.fromLthToRth)
        delete separation.fromLthToRth;
    separation.fromLthToRth = nullptr;
    join();
}

void Tree::add(long left, long right, long addition) {
    separate(left, right);
    separation.fromLthToRth->add(addition);
    join();
}

void Tree::assign(long left, long right, long assignment) {
    separate(left, right);
    separation.fromLthToRth->assign(assignment);
    join();
}

void Tree::assign(long pos, long assignment) {
    assign(pos, pos, assignment);
}

void Tree::reverse(long left, long right) {
    separate(left, right);
    separation.fromLthToRth->reverse();
    join();
}

void Tree::swap(long pos1, long pos2) {
    long tmp = get(pos1);
    assign(pos1, get(pos2));
    assign(pos2, tmp);
}

long Tree::getMax(long left, long right) {
    separate(left, right);
    long ret = separation.fromLthToRth->getMax();
    join();
    return ret;
}

long Tree::getMin(long left, long right) {
    separate(left, right);
    long ret = separation.fromLthToRth->getMin();
    join();
    return ret;
}

Tree::Tree(CartesianTree *root) : root(root) {}

void Tree::doGeneralizedNextPrevPermutation(bool next) {
    long beginningOfMaxOrderSuffix = root->getBeginningOfMaxOrderedSuffix(next);
    if (beginningOfMaxOrderSuffix > 0) {
        long posOfBound = root->getUpperOrLowerBound(beginningOfMaxOrderSuffix,
                                                    get(beginningOfMaxOrderSuffix - 1) + (next ? 1 : -1), next);
        swap(posOfBound, beginningOfMaxOrderSuffix - 1);
    }
    reverse(beginningOfMaxOrderSuffix, root->getElementsNumber() - 1);
}

void Tree::nextPermutation(long left, long right) {
    separate(left, right);
    Tree segment(separation.fromLthToRth);
    segment.doGeneralizedNextPrevPermutation(true);
    join();
}

void Tree::prevPermutation(long left, long right) {
    separate(left, right);
    Tree segment(separation.fromLthToRth);
    segment.doGeneralizedNextPrevPermutation(false);
    join();
}


int main() {
    Tree tree;
    long n;
    cin >> n;
    for (long i = 0; i < n; ++i) {
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
            long l, r;
            cin >> l >> r;
            cout << tree.getSum(l, r) << '\n';
        } else if (type == 2) {
            long x, pos;
            cin >> x >> pos;
            tree.insert(x, pos);
        } else if (type == 3) {
            long pos;
            cin >> pos;
            tree.remove(pos);
        } else if (type == 4) {
            long x, l, r;
            cin >> x >> l >> r;
            tree.assign(l, r, x);
        } else if (type == 5) {
            long x, l, r;
            cin >> x >> l >> r;
            tree.add(l, r, x);
        } else if (type == 6) {
            long l, r;
            cin >> l >> r;
            tree.nextPermutation(l, r);
        } else if (type == 7) {
            long l, r;
            cin >> l >> r;
            tree.prevPermutation(l, r);
        }
    }
    for (long i = 0; i < tree.size(); ++i)
        cout << tree.get(i) << ' ';
}
