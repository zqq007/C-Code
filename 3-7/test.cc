#include <iostream>
#include <vector>
#include <stack>

typedef struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(int n) : val(n), next(nullptr) {}
} ListNode;

// class Solution
// {
// public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      *
//      * @param head ListNode类
//      * @return ListNode类
//      */
//     ListNode *ReverseList(ListNode *head)
//     {
//         // write code here
//         if (head == nullptr)
//             return nullptr;
//         std::stack<ListNode *> st;
//         ListNode *cur = head;
//         int cnt = 0;
//         while (cur)
//         {
//             st.push(cur);
//             cur = cur->next;
//             cnt++;
//         }

//         ListNode *res = nullptr, *p = nullptr;
//         while (cnt--)
//         {
//             if (res == nullptr)
//                 res = p = st.top();
//             else
//             {
//                 p->next = st.top();
//                 p = p->next;
//             }
//             st.pop();
//             if (cnt == 0)
//                 p->next = nullptr;
//         }
//         return res;
//     }
// };

// class Solution
// {
// public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      *
//      * @param head ListNode类
//      * @return ListNode类
//      */
//     ListNode *ReverseList(ListNode *head)
//     {
//         // write code here
//         if (head == nullptr || head->next == nullptr)
//             return head;
//         ListNode *left = head;
//         ListNode *mid = left->next;
//         ListNode *right = mid->next;

//         while (right != nullptr)
//         {
//             mid->next = left;
//             // right->next = mid;//这里right就找不着next了
//             left = mid;
//             mid = right;
//             right = right->next;
//         }
//         mid->next = left;
//         head->next = nullptr;
//         head = mid;
//         return head;
//     }
// };

// class Solution
// {
// public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      *
//      * @param head ListNode类
//      * @return ListNode类
//      */
//     ListNode *ReverseList(ListNode *head)
//     {
//         // write code here
//         if (head == nullptr || head->next == nullptr)
//             return head;
//         ListNode *new_head = nullptr;
//         while (head != nullptr)
//         {
//             ListNode *p = head;
//             head = head->next;
//             p->next = new_head;
//             new_head = p;
//         }
//         return new_head;
//     }
// };

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param pHead1 ListNode类
     * @param pHead2 ListNode类
     * @return ListNode类
     */
    ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
    {
        // write code here
        if (pHead1 == nullptr)
            return pHead2;
        if (pHead2 == nullptr)
            return pHead1;
        ListNode *p1 = pHead1;
        ListNode *p2 = pHead2;
        ListNode *head = nullptr, *cur = nullptr;

        while (p1 != nullptr || p2 != nullptr)
        {
            if ((p1 != nullptr && p2 != nullptr) && p1->val >= p2->val)
            {
                if (head == nullptr)
                    head = cur = p2;
                else
                {
                    cur->next = p2;
                    cur = cur->next;
                };
                p2 = p2->next;
            }
            else if ((p1 != nullptr && p2 != nullptr) && p1->val < p2->val)
            {
                if (head == nullptr)
                    head = cur = p1;
                else
                {
                    cur->next = p1;
                    cur = cur->next;
                };
                p1 = p1->next;
            }
            else
            {
                if (p1 == nullptr)
                    cur->next = p2;
                else
                    cur->next = p1;
                break;
            }
        }
        return head;
    }
};

int main()
{
    ListNode p1(1);
    ListNode p2(2);
    ListNode *head = Solution().Merge(&p1, &p2);

    ListNode *cur = head;
    while (cur)
    {
        std::cout << "val:" << cur->val << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
    return 0;
}