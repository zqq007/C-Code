#include <iostream>
#include <vector>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL)
    {
    }
};

class Solution
{
public:
    bool HasSubtree(TreeNode *pRoot1, TreeNode *pRoot2)
    {
        if (pRoot1 == nullptr || pRoot2 == nullptr)
            return false;

        bool res = false;
        if (pRoot1->val == pRoot2->val)
        {
            res = isSame(pRoot1, pRoot2);
        }

        if (!res)
        {
            res = HasSubtree(pRoot1->left, pRoot2);
        }

        if (!res)
        {
            res = HasSubtree(pRoot1->right, pRoot2);
        }

        return res;
    }

    bool isSame(TreeNode *pRoot1, TreeNode *pRoot2)
    {
        if (pRoot2 == nullptr)
            return true;
        if (pRoot1 == nullptr)
            return false;

        if (pRoot1->val != pRoot2->val)
            return false;

        return isSame(pRoot1->left, pRoot2->left) && isSame(pRoot1->right, pRoot2->right);
    }
};

class Solution
{
public:
    TreeNode *mirrorTree(TreeNode *root)
    {
        if (root == nullptr)
            return root;
        swapTreeNode(&root->left, &root->right);
        mirrorTree(root->left);
        mirrorTree(root->right);
        return root;
    }

    void swapTreeNode(TreeNode **left, TreeNode **right)
    {
        TreeNode *tmp = *left;
        *left = *right;
        *right = tmp;
    }
};