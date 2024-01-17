#include <iostream>
#include <vector>
using namespace std;

// version1
class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    {
        int sum = 0;
        for (auto &i : nums)
            sum += i;

        int res = (target + sum) / 2;
        if (res < 0 || (sum + target) % 2)
            return 0;
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(res + 1));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j <= res; ++j)
            {
                // if(nums[i - 1] == j)
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i - 1])
                    dp[i][j] += dp[i - 1][j - nums[i - 1]];
            }
        }

        return dp[n][res];
    }
};

// version2 空间优化
class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    {
        int sum = 0;
        for (auto &i : nums)
            sum += i;

        int res = (target + sum) / 2;
        if (res < 0 || (sum + target) % 2)
            return 0;
        int n = nums.size();
        vector<int> dp(res + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = res; j >= nums[i - 1]; --j)
            {
                dp[j] += dp[j - nums[i - 1]];
            }
        }

        return dp[res];
    }
};

class Solution
{
public:
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size();
        int sum = 0;
        for (auto &i : stones)
            sum += i;

        int aim = sum / 2;
        vector<vector<int>> dp(n + 1, vector<int>(aim + 1));
        // dp[0][0];
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j <= aim; ++j)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= stones[i - 1])
                {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
                }
            }
        }

        return sum - 2 * dp[n][aim];
    }
};

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        int sum = 0;
        for(auto &i : stones) sum += i;

        int aim = sum / 2;
        vector<int> dp(aim + 1);
        // dp[0][0];
        for(int i = 1; i <= n; ++i)
        {
            for(int j = aim; j >= stones[i - 1]; --j)
            {
                dp[j] = max(dp[j],dp[j - stones[i - 1]] + stones[i - 1]);
            }
        }

        return sum - 2 * dp[aim];
    }
};