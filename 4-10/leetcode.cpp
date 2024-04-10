#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int> &price, int target)
    {
        int left = 0;
        int right = price.size() - 1;

        int first = price[0];
        int last = price[right];

        while (left < right)
        {
            first = price[left];
            int val = target - first;
            while (price[right] > val)
                right--;
            if (price[right] == val)
            {
                last = price[right];
                break;
            }
            else
                left++;
        }

        std::vector<int> res;
        res.push_back(first);
        res.push_back(last);
        return res;
    }
};