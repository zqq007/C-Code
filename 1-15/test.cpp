#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1001;
int n, V, v[N], w[N];
int dp[N];

int main()
{
    // 读取数据
    cin >> n >> V;
    for (int i = 1; i <= n; ++i)
    {
        cin >> v[i] >> w[i];
    }

    // 问题1
    for (int i = 1; i <= n; ++i)
    {
        for (int j = V; j >= 1; --j) // 从右往左填
        {
            if (j >= v[i])
                dp[j] = max(dp[j], w[i] + dp[j - v[i]]);
        }
    }
    cout << dp[V] << endl;

    // 问题2
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= V; ++i)
        dp[i] = -1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = V; j >= 1; --j)
        {
            if (j >= v[i] && dp[j - v[i]] != -1)
                dp[j] = max(dp[j], w[i] + dp[j - v[i]]);
        }
    }

    cout << (dp[V] == -1 ? 0 : dp[V]);
    return 0;
}

// version1
class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int sum = 0;
        for (auto &i : nums)
            sum += i;
        if (sum % 2 == 1)
            return false;
        sum /= 2;
        vector<vector<int>> dp(nums.size() + 1, vector<int>(sum + 1));
        for (int i = 1; i <= sum; ++i)
            dp[0][i] = -1;

        for (int i = 1; i <= nums.size(); ++i)
        {
            for (int j = 1; j <= sum; ++j)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i - 1] && dp[i - 1][j - nums[i - 1]] != -1)
                    dp[i][j] = max(dp[i][j], nums[i - 1] + dp[i - 1][j - nums[i - 1]]);
            }
        }

        return dp[nums.size()][sum] != -1;
    }
};

// version2:空间优化
class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int sum = 0;
        for (auto &i : nums)
            sum += i;
        if (sum % 2 == 1)
            return false;
        sum /= 2;
        vector<bool> dp(sum + 1);
        dp[0] = true;
        for (int i = 1; i <= nums.size(); ++i)
        {
            for (int j = sum; j >= nums[i - 1]; --j)
            {
                dp[j] = dp[j] || dp[j - nums[i - 1]];
            }
        }

        return dp[sum];
    }
};