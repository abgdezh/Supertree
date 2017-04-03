#include <cstdlib>
#include <utility>
#include <string>

using std::pair;

#ifndef INC_2017_03_20_SUPERTREE_CARTESIANTREE_H
#define INC_2017_03_20_SUPERTREE_CARTESIANTREE_H


class CartesianTree {
    CartesianTree *left;
    CartesianTree *right;
    int data, priority;
    long long sum;
    int elementsNumber;
    int minimum, maximum;

    bool isReversed;
    bool isAssigned;

    int addition;
    int assignment;

    enum Order {
        NO_ORDER, INCREASING, DECREASING, STABLE
    } order;
    int firstElement, lastElement;

    static bool isCompatibleWithOrder(CartesianTree *tree, Order order);

    void recalculate();

    void push();

public:
    CartesianTree(int x);

    static pair<CartesianTree *, CartesianTree *> split(CartesianTree *t, int num);

    static CartesianTree *merge(CartesianTree *l, CartesianTree *r);

    long long getSum() const;

    int getMin() const;

    int getMax() const;

    int getUpperOrLowerBound(int posBeg, int number, bool suffixIsDecreasing);

    int getElementsNumber() const;

    void add(int delta);

    void assign(int value);

    void reverse();

    int getBeginningOfMaxOrderedSuffix(bool decreasingOrder);

    static std::string toString(CartesianTree *node, bool reversed = false, int assignment = INT32_MAX, int addition = 0);
};


#endif //INC_2017_03_20_SUPERTREE_CARTESIANTREE_H
