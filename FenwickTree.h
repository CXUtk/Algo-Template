//
// Created by DELL on 2018/11/14.
//

#ifndef OJONLY_FENWICKTREE_H
#define OJONLY_FENWICKTREE_H

#include <cstring>

struct FenwickTree {
    FenwickTree() {}
    inline void increase(int t, int x) {
        for (int i = t; i <= maxx; i += lowbit(i)) _arr[i] += x;
    }
    inline int getSum(int t) {
        int s = 0;
        for (int i = t; i; i -= lowbit(i)) s += _arr[i];
        return s;
    }
    int _arr[MAXN];
    inline int lowbit(int x) { return x & (-x); }
};

#endif  // OJONLY_FENWICKTREE_H