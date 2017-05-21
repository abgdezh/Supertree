#include <utility>
#include <iostream>
#include "CartesianTree.h"

using std::make_pair;
using std::swap;
using std::cout;
using std::min;
using std::max;

CartesianTree::CartesianTree(long x) : left(0), right(0), data(x), priority(rand()),
                                       sum(x), elementsNumber(1), minimum(x), maximum(x),
                                       isReversed(false), isAssigned(false), addition(0), assignment(0),
                                       order(STABLE), firstElement(x), lastElement(x) {}

pair<CartesianTree *, CartesianTree *> CartesianTree::split(CartesianTree *t, size_t num) {
    //std::string tToStr = toString(t);
    if (!t)
        return make_pair<CartesianTree *, CartesianTree *>(nullptr, nullptr);
    t->push();
    size_t leftNum = t->left ? t->left->elementsNumber : 0;
    if (leftNum < num) {
        pair<CartesianTree *, CartesianTree *> tmp = split(t->right, num - leftNum - 1);
        t->right = tmp.first;
        t->recalculate();
        /*cout << "Split: [" << tToStr << "], num=" << num << ", result: [" << toString(t) << "], ["
             << toString(tmp.second) << "]\n";*/
        return make_pair(t, tmp.second);
    } else {
        pair<CartesianTree *, CartesianTree *> tmp = split(t->left, num);
        t->left = tmp.second;
        t->recalculate();
        /*cout << "Split: [" << tToStr << "], num=" << num << ", result: [" << toString(tmp.first) << "], ["
             << toString(t) << "]\n";*/
        return make_pair(tmp.first, t);
    }
}

CartesianTree *CartesianTree::merge(CartesianTree *l, CartesianTree *r) {
    //std::string lToStr = toString(l);
    //std::string rToStr = toString(r);
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
    //cout << "Merge: [" << lToStr << "], [" << rToStr << "], result: [" << toString(ret) << "]\n";
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

size_t CartesianTree::getElementsNumber() const {
    return elementsNumber;
}

size_t CartesianTree::getBeginningOfMaxOrderedSuffix(bool decreasingOrder) {
    push();
    Order rightOrder = decreasingOrder ? DECREASING : INCREASING;
    size_t leftNum = left ? left->elementsNumber : 0;
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

size_t CartesianTree::getUpperOrLowerBound(size_t posBeg, long number, bool suffixIsDecreasing) {
    push();
    size_t posRoot = left ? left->elementsNumber : 0;
    if (right && (suffixIsDecreasing ? (right->maximum >= number) : (right->minimum <= number)))
        return right->getUpperOrLowerBound(posBeg >= posRoot + 1 ? posBeg - posRoot - 1 : 0, number,
                                           suffixIsDecreasing) + posRoot + 1;
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
