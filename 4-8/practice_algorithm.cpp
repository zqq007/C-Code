#include <iostream>
#include <vector>

class Solution
{
public:
    bool isHappy(int n)
    {
        int slow = n;
        int fast = n;
        do
        {
            slow = calculateHappyNum(slow);
            fast = calculateHappyNum(fast);
            fast = calculateHappyNum(fast);
        } while (slow != fast);

        return slow == 1;
    }

    int calculateHappyNum(int num)
    {
        int sum = 0;
        while (num > 0)
        {
            int val = num % 10;
            sum += val * val;
            num /= 10;
        }
        return sum;
    }
};

class Solution
{
public:
    int maxArea(std::vector<int> &height)
    {
        int left = 0;
        int right = height.size() - 1;
        int max = 0;
        while (left < right)
        {
            int h = std::min(height[left], height[right]);
            int w = right - left;
            int v = h * w;
            max = max > v ? max : v;
            if (height[left] < height[right])
                left++;
            else
                right--;
        }
        return max;
    }
};