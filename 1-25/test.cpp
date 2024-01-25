#include <iostream>
#include <vector>

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param target int整型
     * @param array int整型vector<vector<>>
     * @return bool布尔型
     */
    bool Find(int target, std::vector<std::vector<int>> &array)
    {
        // write code here
        int m = 0;
        int n = array[0].size() - 1;
        while (m < array.size() && n >= 0)
        {
            if (target < array[m][n])
                n--;
            else if (target > array[m][n])
                m++;
            else
                return true;
        }
        return false;
    }
};

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param nums int整型vector
     * @return int整型
     */
    int minNumberInRotateArray(std::vector<int> &nums)
    {
        // write code here
        int left = 0, right = nums.size() - 1;
        int mid = 0;
        while (nums[left] >= nums[right])
        {
            mid = (left + right) / 2;
            if (left + 1 == right)
            {
                mid = right;
                break;
            }
            if (nums[left] == nums[right] && nums[mid] == nums[left])
            {
                int res = nums[left];
                for (int i = left + 1; i < right; ++i)
                {
                    res = std::min(res, nums[i]);
                }
                return res;
            }
            if (nums[mid] >= nums[left])
                left = mid;
            else
                right = mid;
        }
        return nums[mid];
    }
};

class Solution
{
public:
    void reOrderArray(std::vector<int> &array)
    {
        int k = 0, i = 0;
        while (i < array.size())
        {
            if (array[i] & 1)
            {
                int n = array[i];
                int j = i;
                while (j > k)
                {
                    array[j] = array[j - 1];
                    j--;
                }
                array[k++] = n;
            }
            i++;
        }
    }
};