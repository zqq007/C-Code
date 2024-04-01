#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

class Solution
{
public:
    void moveZeroes(std::vector<int> &nums)
    {
        int sz = nums.size();
        if (sz == 1)
            return;
        int first = sz - 1;
        int last = sz - 1;
        int cnt_zero = 0;
        while (first >= 0)
        {
            if (nums[first] != 0)
            {
                nums[last] = nums[first];
                last--;
                first--;
            }
            else
            {
                first--;
                cnt_zero++;
            }
        }
        for (int i = 0; i < sz; ++i)
        {
            if (i < sz - cnt_zero)
            {
                nums[i] = nums[i + cnt_zero];
            }
            else
                nums[i] = 0;
        }
    }
};

class Solution
{
public:
    void moveZeroes(std::vector<int> &nums)
    {
        for (int cur = 0, index = -1; cur < nums.size(); ++cur)
        {
            if (nums[cur])
                std::swap(nums[++index], nums[cur]);
        }
    }
};

int main()
{
    // int fd = open("tp", O_RDONLY);
    // if (fd == -1)
    // {
    //     perror("open tp fail");
    //     exit(-1);
    // }
    // std::cout << "open sucess" << std::endl;
    return 0;
}