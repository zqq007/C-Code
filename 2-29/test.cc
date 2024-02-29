#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param numbers int整型vector
     * @return int整型
     */
    int MoreThanHalfNum_Solution(std::vector<int> &numbers)
    {
        // write code here
        std::unordered_map<int, int> map_;
        for (int i = 0; i < numbers.size(); ++i)
        {
            map_[numbers[i]]++;
            if (map_[numbers[i]] > numbers.size() / 2)
                return numbers[i];
        }
        return 0;
    }
};

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param numbers int整型vector
     * @return int整型
     */
    int MoreThanHalfNum_Solution(std::vector<int> &numbers)
    {
        // write code here
        if (numbers.size() == 0)
            return 0;

        int num = numbers[0];
        int cnt = 1;
        for (int i = 1; i < numbers.size(); ++i)
        {
            if (cnt == 0)
            {
                num = numbers[i];
                cnt = 1;
            }
            if (num == numbers[i])
                cnt++;
            else
                cnt--;
        }

        int n = 0;
        for (auto &i : numbers)
        {
            if (i == num)
                n++;
        }

        return n > numbers.size() / 2 ? num : 0;
    }
};

struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL)
    {
    }
};

class Solution
{
public:
    std::vector<int> printListFromTailToHead(ListNode *head)
    {
        std::stack<int> st;
        ListNode *cur = head;
        while (cur != nullptr)
        {
            st.push(cur->val);
            cur = cur->next;
        }

        std::vector<int> v;
        while (!st.empty())
        {
            v.push_back(st.top());
            st.pop();
        }
        return v;
    }
};

class Solution
{
public:
    std::vector<int> printListFromTailToHead(ListNode *head)
    {
        std::vector<int> v;
        func(head, &v);
        return v;
    }

    void func(ListNode *head, std::vector<int> *v)
    {
        if (head == nullptr)
            return;
        func(head->next, v);
        v->push_back(head->val);
    }
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param preOrder int整型vector
     * @param vinOrder int整型vector
     * @return TreeNode类
     */
    TreeNode *reConstructBinaryTree(std::vector<int> &preOrder, std::vector<int> &vinOrder)
    {
        // write code here
        if (preOrder.empty() | vinOrder.empty() ||
            preOrder.size() != vinOrder.size())
            return nullptr;
        return reConstructBinaryTreeHelper(preOrder, 0, preOrder.size() - 1, vinOrder,
                                           0, vinOrder.size() - 1);
    }

    TreeNode *reConstructBinaryTreeHelper(std::vector<int> &pre, int pre_start,
                                          int pre_end, std::vector<int> &vin, int vin_start, int vin_end)
    {
        if (pre_start > pre_end || vin_start > vin_end)
            return nullptr;

        TreeNode *root = new TreeNode(pre[pre_start]);
        for (int i = vin_start; i <= vin_end; ++i)
        {
            if (pre[pre_start] == vin[i])
            {
                root->left = reConstructBinaryTreeHelper(pre, pre_start + 1,
                                                         pre_start + i - vin_start, vin, vin_start, i - 1);
                root->right = reConstructBinaryTreeHelper(pre, pre_start + i - vin_start + 1,
                                                          pre_end, vin, i + 1, vin_end);
                break;
            }
        }
        return root;
    }
};