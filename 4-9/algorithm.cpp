#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

class Solution
{
public:
    int findCircleNum(std::vector<std::vector<int>> &isConnected)
    {
        unionFindSet ufs(isConnected.size());
        for (int i = 0; i < isConnected.size(); ++i)
        {
            for (int j = 0; j < isConnected[i].size(); ++j)
            {
                if (isConnected[i][j])
                    ufs.unionSet(i, j);
            }
        }
        return ufs.setSize();
    }
};

class Solution
{
public:
    bool equationsPossible(std::vector<std::string> &equations)
    {
        std::vector<int> ufs(26, -1);

        auto findRoot = [&ufs](int x)
        {
            while (ufs[x] >= 0)
                x = ufs[x];
            return x;
        };

        // 第一次遍历，把相同的放在一个集合中
        for (auto &s : equations)
        {
            if (s[1] == '=')
            {
                int root1 = findRoot(s[0] - 'a');
                int root2 = findRoot(s[3] - 'a');
                if (root1 != root2)
                {
                    ufs[root1] += ufs[root2];
                    ufs[root2] = root1;
                }
            }
        }

        // 第二次遍历，如果遇到不相同的，并且这两个数在同一个集合中那就返回false
        for (auto &s : equations)
        {
            if (s[1] == '!')
            {
                int root1 = findRoot(s[0] - 'a');
                int root2 = findRoot(s[3] - 'a');
                if (root1 == root2)
                {
                    return false;
                }
            }
        }
        return true;
    }
};

class Solution
{
public:
    int triangleNumber(std::vector<int> &nums)
    {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        int cnt = 0;

        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                int left = j + 1, right = n - 1, k = j;
                while (left <= right)
                {
                    int mid = (left + right) / 2;
                    if (nums[mid] < nums[i] + nums[j])
                    {
                        k = mid;
                        left = mid + 1;
                    }
                    else
                    {
                        right = mid - 1;
                    }
                }
                cnt += k - j;
            }
        }
        return cnt;
    }
};