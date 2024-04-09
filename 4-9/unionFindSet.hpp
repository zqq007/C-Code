#pragma once

#include <iostream>
#include <vector>

class unionFindSet
{
public:
    unionFindSet(size_t sz) : _ufs(sz, -1) {}

    void unionSet(int x1, int x2)
    {
        int root1 = findRoot(x1);
        int root2 = findRoot(x2);

        // 如果两个相等，说明在同一个集合中
        if (root1 == root2)
            return;

        _ufs[root1] += _ufs[root2];
        _ufs[root2] = root1;
    }

    int findRoot(int x)
    {
        int root = x;
        while (_ufs[root] >= 0)
            root = _ufs[root];
        return root;
    }

    bool inSet(int x1, int x2)
    {
        return findRoot(x1) == findRoot(x2);
    }

    size_t setSize()
    {
        size_t size = 0;
        for (const auto &x : _ufs)
        {
            if (x < 0)
                size++;
        }
        return size;
    }

private:
    std::vector<int> _ufs;
};