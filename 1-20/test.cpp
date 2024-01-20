#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1));
        for (int j = 1; j <= amount; ++j)
            dp[0][j] = 1e4 + 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j <= amount; ++j)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= coins[i - 1])
                    dp[i][j] = min(dp[i][j], dp[i][j - coins[i - 1]] + 1);
            }
        }

        return dp[n][amount] <= 1e4 ? dp[n][amount] : -1;
    }
};

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<int> dp(amount + 1);
        for (int j = 1; j <= amount; ++j)
            dp[j] = 1e4 + 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = coins[i - 1]; j <= amount; ++j)
            {
                dp[j] = min(dp[j], dp[j - coins[i - 1]] + 1);
            }
        }

        return dp[amount] <= 1e4 ? dp[amount] : -1;
    }
};

class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j <= amount; ++j)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= coins[i - 1])
                    dp[i][j] += dp[i][j - coins[i - 1]];
            }
        }

        return dp[n][amount];
    }
};

class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        int n = coins.size();
        vector<int> dp(amount + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = coins[i - 1]; j <= amount; ++j)
            {
                dp[j] += dp[j - coins[i - 1]];
            }
        }

        return dp[amount];
    }
};