#include <iostream>
#include "CartesianTree.h"

#ifndef INC_2017_03_20_SUPERTREE_TREE_H
#define INC_2017_03_20_SUPERTREE_TREE_H


class Tree {
    CartesianTree *root;

    Tree(CartesianTree *root);

    struct Separation {
        CartesianTree *beforeLth;
        CartesianTree *fromLthToRth;
        CartesianTree *afterRth;
        Tree &tree;

        Separation(Tree &tree, size_t left, size_t right);

        ~Separation();
    };

    void separate(Separation &separation, size_t left, size_t right);

    void join(Separation &separation);

    void doGeneralizedNextPrevPermutation(bool next);

public:
    Tree();

    long get(size_t pos);

    long getSum(size_t left, size_t right);

    long getMin(size_t left, size_t right);

    long getMax(size_t left, size_t right);

    size_t size();

    void insert(long elem, size_t position);

    void remove(size_t position);

    void add(size_t left, size_t right, long addition);

    void assign(size_t left, size_t right, long assignment);

    void assign(size_t pos, long assignment);

    void reverse(size_t left, size_t right);

    void swap(size_t pos1, size_t pos2);

    void nextPermutation(size_t left, size_t right);

    void prevPermutation(size_t left, size_t right);
};


#endif //INC_2017_03_20_SUPERTREE_TREE_H
