#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Solution
{
public:
    int numSquares(int n)
    {
        int m = sqrt(n);
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int j = 1; j <= n; ++j)
            dp[0][j] = 0x3f3f3f3f;

        for (int i = 1; i <= m; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                int res = pow(i, 2);
                dp[i][j] = dp[i - 1][j];
                if (j >= res)
                    dp[i][j] = min(dp[i][j], dp[i][j - res] + 1);
            }
        }

        return dp[m][n];
    }
};

class Solution
{
public:
    int numSquares(int n)
    {
        int m = sqrt(n);
        vector<int> dp(n + 1, 0x3f3f3f3f);

        dp[0] = 0;

        for (int i = 1; i <= m; ++i)
        {
            for (int j = i * i; j <= n; ++j)
            {
                int res = pow(i, 2);
                dp[j] = min(dp[j], dp[j - res] + 1);
            }
        }

        return dp[n];
    }
};

class Solution
{
public:
    int findMaxForm(vector<string> &strs, int m, int n)
    {
        int len = strs.size();
        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(m + 1, vector<int>(n + 1)));
        for (int i = 1; i <= len; ++i)
        {
            int a = 0, b = 0;
            for (auto &i : strs[i - 1])
                if (i == '0')
                    a++;
                else
                    b++;
            for (int j = 0; j <= m; ++j)
            {
                for (int k = 0; k <= n; ++k)
                {
                    dp[i][j][k] = dp[i - 1][j][k];
                    if (j >= a && k >= b)
                        dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - a][k - b] + 1);
                }
            }
        }
        return dp[len][m][n];
    }
};

class Solution
{
public:
    int findMaxForm(vector<string> &strs, int m, int n)
    {
        int len = strs.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= len; ++i)
        {
            int a = 0, b = 0;
            for (auto &i : strs[i - 1])
                if (i == '0')
                    a++;
                else
                    b++;
            for (int j = m; j >= a; --j)
            {
                for (int k = n; k >= b; --k)
                {
                    dp[j][k] = max(dp[j][k], dp[j - a][k - b] + 1);
                }
            }
        }
        return dp[m][n];
    }
};

class Solution
{
public:
    int profitableSchemes(int n, int minProfit, vector<int> &group, vector<int> &profit)
    {
        int x = group.size();
        const int mod = 1e9 + 7;
        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1));
        for (int j = 0; j <= n; ++j)
            dp[j][0] = 1;
        for (int i = 1; i <= x; ++i)
        {
            for (int j = n; j >= group[i - 1]; --j)
            {
                for (int k = minProfit; k >= 0; --k)
                {
                    dp[j][k] += dp[j - group[i - 1]][max(0, k - profit[i - 1])];
                    dp[j][k] %= mod;
                }
            }
        }

        // int res = (dp[x][n][minProfit] % ((1e9 + 7)));

        return dp[n][minProfit];
    }
};

class Solution
{
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        int last = m + n - 1;
        while (n)
        {
            if (m == 0 || nums1[m - 1] <= nums2[n - 1])
            {
                nums1[last--] = nums2[--n];
            }
            else
            {
                nums1[last--] = nums1[--m];
            }
        }
    }
};