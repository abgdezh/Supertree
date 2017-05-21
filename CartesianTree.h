#include <cstdlib>
#include <utility>
#include <string>

using std::pair;

#ifndef INC_2017_03_20_SUPERTREE_CARTESIANTREE_H
#define INC_2017_03_20_SUPERTREE_CARTESIANTREE_H


class CartesianTree {
    CartesianTree *left;
    CartesianTree *right;
    long data, priority;
    long sum;
    size_t elementsNumber;
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

    static pair<CartesianTree *, CartesianTree *> split(CartesianTree *t, size_t num);

    static CartesianTree *merge(CartesianTree *l, CartesianTree *r);

    long getSum() const;

    long getMin() const;

    long getMax() const;

    size_t getUpperOrLowerBound(size_t posBeg, long number, bool suffixIsDecreasing);

    size_t getElementsNumber() const;

    void add(long delta);

    void assign(long value);

    void reverse();

    size_t getBeginningOfMaxOrderedSuffix(bool decreasingOrder);

    static std::string
    toString(CartesianTree *node, bool reversed = false, long assignment = INT32_MAX, long addition = 0);
};


#endif //INC_2017_03_20_SUPERTREE_CARTESIANTREE_H
