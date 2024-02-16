#include <iostream>
#include <vector>
#include <string>
#include <cstring>

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

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (nums[mid] < nums[right])
            {
                right = mid;
            }
            else if (nums[mid] > nums[right])
            {
                left = mid + 1;
            }
            else
            {
                right--;
            }
        }

        return nums[left];
    }
};

//Use containers
class Solution
{
public:
    void replaceSpace(char *str, int length)
    {
        size_t cnt = 0;

        // char res[length + cnt];
        std::string res;

        size_t cur = length - 1;
        for (int i = 0; i < length; ++i)
        {
            if (str[i] == ' ')
                res += "%20";
            else
                res.push_back(str[i]);
        }

        strcpy(str, res.c_str());
    }
};

// Non containers
class Solution
{
public:
    void replaceSpace(char *str, int length)
    {
        size_t cnt = 0;
        for (int i = 0; i < length; ++i)
        {
            if (str[i] == ' ')
                cnt++;
        }

        char *old_ = str + length;
        char *new_ = str + length + 2 * cnt;

        while (old_ >= str)
        {
            if (*old_ == ' ')
            {
                (*new_) = '0';
                new_--;
                (*new_) = '2';
                new_--;
                (*new_) = '%';
                // new_--;
            }
            else
            {
                *new_ = *old_;
            }
            new_--;
            old_--;
        }
    }
};

// int main()
// {
//     std::vector<int> nums{3, 4, 5, 1, 2};
//     std::cout << Solution().minNumberInRotateArray(nums) << std::endl;
//     return 0;
// }