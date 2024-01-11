#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class Solution
{
public:
    bool isInterleave(std::string s1, std::string s2, std::string s3)
    {
        int m = s1.size();
        int n = s2.size();
        if ((m + n) != s3.size())
            return false;

        s1 = ' ' + s1;
        s2 = ' ' + s2;
        s3 = ' ' + s3;

        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1));
        dp[0][0] = true;
        for (int i = 1; i <= m; ++i)
            if (s1[i] != s3[i])
                break;
            else
                dp[i][0] = true;
        for (int i = 1; i <= n; ++i)
            if (s2[i] != s3[i])
                break;
            else
                dp[0][i] = true;

        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                dp[i][j] = (s1[i] == s3[i + j] && dp[i - 1][j]) || (s2[j] == s3[i + j] && dp[i][j - 1]);
            }
        }

        return dp[m][n];
    }
};

int main()
{
    std::string s1 = " aabcc";
    std::string s2 = " dbbca";
    std::string s3 = " aadbbcbcac";

    if ((s1.size() + s2.size()) != (s3.size() + 2))
        std::cout << "!= " << std::endl;
    return 0;
}

class Solution
{
public:
    int minimumDeleteSum(std::string s1, std::string s2)
    {
        int m = s1.size();
        int n = s2.size();

        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + s1[i - 1]);
            }
        }

        int sum = cal_sum(s1) + cal_sum(s2);
        return sum - 2 * dp[m][n];
    }

    int cal_sum(std::string s)
    {
        int sum = 0;
        for (auto &c : s)
        {
            sum += c;
        }
        return sum;
    }
};