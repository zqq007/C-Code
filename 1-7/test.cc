#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        int n = s.size();
        int m = p.size();

        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1));
        dp[0][0] = true;
        // 下面这条循环不需要，因为vector默认填充的0
        //  for (int i = 1; i < n + 1; ++i)
        //      dp[i][0] = false;
        for (int i = 1; i < m + 1; ++i)
        {
            if (p[i - 1] != '*')
                break;
            dp[0][i] = true;
        }

        for (int i = 1; i < n + 1; ++i)
        {
            for (int j = 1; j < m + 1; ++j)
            {
                if ((p[j - 1] == s[i - 1]) || (p[j - 1] == '?'))
                    dp[i][j] = dp[i - 1][j - 1];
                else if (p[j - 1] == '*')
                {
                    dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
                }
            }
        }

        return dp[n][m];
    }
};

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        int n = s.size();
        int m = p.size();

        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1));
        dp[0][0] = true;
        for (int i = 2; i < m + 1; i += 2)
        {
            if (p[i - 1] == '*')
                dp[0][i] = true;
            else
                break;
        }

        for (int i = 1; i < n + 1; ++i)
        {
            for (int j = 1; j < m + 1; ++j)
            {
                if (p[j - 1] == '*')
                {
                    dp[i][j] = dp[i][j - 2] || (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j];
                }
                else
                    dp[i][j] = (s[i - 1] == p[j - 1] || p[j - 1] == '.') && dp[i - 1][j - 1];
            }
        }

        return dp[n][m];
    }
};