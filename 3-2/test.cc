#include <iostream>
#include <vector>

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param n int整型
     * @return int整型
     */
    int Fibonacci(int n)
    {
        // write code here
        std::vector<int> dp(n);

        /*初始化*/
        dp[0] = dp[1] = 1;
        for (int i = 2; i < n; ++i)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n - 1];
    }
};

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param number int整型
     * @return int整型
     */
    int jumpFloor(int number)
    {
        // write code here
        std::vector<int> dp(number);
        dp[0] = 1;
        dp[1] = 2;
        for (int i = 2; i < number; ++i)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[number - 1];
    }
};

class Solution
{
public:
    int rectCover(int number)
    {
        if (number < 2)
            return number;
        std::vector<int> dp(number + 1);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= number; ++i)
        {
            dp[i] = dp[i - 2] + dp[i - 1];
        }
        return dp[number];
    }
};

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param n int整型
     * @return int整型
     */
    int NumberOf1(int n)
    {
        // write code here
        int cnt = 0;
        for (int i = 0; i < 32; ++i)
        {
            if ((n >> i & 1) == 1)
                cnt++;
        }
        return cnt;
    }
};