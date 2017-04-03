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
    } separation;

    void separate(int left, int right);

    void join();

    void doGeneralizedNextPrevPermutation(bool next);

public:
    Tree();

    int get(int pos);

    long long getSum(int left, int right);

    int getMin(int left, int right);

    int getMax(int left, int right);

    int size();

    void insert(int elem, int position);

    void remove(int position);

    void add(int left, int right, int addition);

    void assign(int left, int right, int assignment);

    void assign(int pos, int assignment);

    void reverse(int left, int right);

    void swap(int pos1, int pos2);

    void nextPermutation(int left, int right);

    void prevPermutation(int left, int right);
};


#endif //INC_2017_03_20_SUPERTREE_TREE_H
