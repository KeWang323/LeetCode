/*

98. Validate Binary Search Tree (Medium)

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
Example 1:
    2
   / \
  1   3
Binary tree [2,1,3], return true.
Example 2:
    1
   / \
  2   3
Binary tree [1,2,3], return false.

*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        TreeNode* prev = NULL;
        return validate(root, prev);
    }
private:
    bool validate(TreeNode* root, TreeNode* &prev) {
        if (root == NULL) {
            return true;
        } else if (!validate(root->left, prev)) {
            return false;
        } else if (prev != NULL && prev->val >= root->val) {
            return false;
        }
        prev = root;
        return validate(root->right, prev);
    }
};
/*

100. Same Tree (Easy)

Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value.

*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p || !q) {
            if (p || q) return false;
            return true;
        }
        return p -> val == q -> val && isSameTree(p -> left, q -> left) && isSameTree(p -> right, q -> right);
    }
};
/*

101. Symmetric Tree (Easy)

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

		1
	 / \
	2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
		1
	 / \
	2   2
	 \   \
	 3    3
Note:
Bonus points if you could solve it both recursively and iteratively.

*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return check(root -> left, root -> right);
    }
    bool check(TreeNode* L, TreeNode* R) {
        if (!L || !R) {
            if (L || R) return false;
            return true;
        }
        return L -> val == R -> val && check(L -> left, R -> right) && check(L -> right, R -> left);
    }
};
/*

104. Maximum Depth of Binary Tree (Easy)

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;m
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        int res = 0;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int _size = q.size();
            res++;
            for (int i = 0; i < _size; i++) {
                TreeNode *temp = q.front();
                q.pop();
                if (temp -> left) q.push(temp -> left);
                if (temp -> right) q.push(temp -> right);
            }
        }
        return res;
    }
};
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        else if (!(root -> left) && !(root -> right)) return 1;
        int depth_L = maxDepth(root -> left);
        int depth_R = maxDepth(root -> right);
        return depth_L > depth_R ? depth_L + 1 : depth_R + 1;
    }
};
/*

105. Construct Binary Tree from Preorder and Inorder Traversal (Medium)

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return BT(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
    TreeNode* BT(vector<int>& preorder, int pl, int pr, vector<int>& inorder, int il, int ir) {
        if (il > ir) {
            return NULL;
        }
        int val = preorder[pl];
        TreeNode *root = new TreeNode(val);
        int i = il;
        for (; i < ir; i++) {
            if (val == inorder[i]) {
                break;
            }
        }
        root -> left = BT(preorder, pl + 1, pl + i - il, inorder, il, i - 1);
        root -> right = BT(preorder, pl + i - il + 1, pr, inorder, i + 1, ir);
        return root;
    }
};
/*

106. Construct Binary Tree from Inorder and Postorder Traversal (Medium)

Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return BT(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }
    TreeNode* BT(vector<int>& inorder, int il, int ir, vector<int>& postorder, int pl, int pr) {
        if (il > ir) {
            return NULL;
        }
        int val = postorder[pr];
        TreeNode *root = new TreeNode(val);
        int i = il;
        for (; i < ir; i++) {
            if (val == inorder[i]) {
                break;
            }
        }
        root -> left = BT(inorder, il, i - 1, postorder, pl, pl - il + i - 1);
        root -> right = BT(inorder, i + 1, ir, postorder, pl - il + i, pr - 1);
        return root;
    }
};
/*

109. Convert Sorted List to Binary Search Tree (Medium)

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        TreeNode *fake = new TreeNode(-1);
        if (head == NULL) {
            return fake -> left;
        }else if (head -> next == NULL) {
            fake -> val = head -> val;
            return fake;
        }
        ListNode *fast = head, *slow = head, *slow_prev = NULL;
        while (fast -> next != NULL && fast -> next -> next != NULL) {
            slow_prev = slow;
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        fake -> val = slow -> val;
        if (slow_prev != NULL) {
            slow_prev -> next = NULL;
            fake -> left = sortedListToBST(head);
        }
        fake -> right = sortedListToBST(slow -> next);
        return fake;
    }
};
/*

110. Balanced Binary Tree (Easy)

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if (!root) return true;
        else if (abs(depth(root->left) - depth(root->right)) > 1) return false;
        else return isBalanced(root->left) && isBalanced(root->right);
    }
    int depth(TreeNode* root) {
        if (!root) return 0;
        else if (!(root -> left) && !(root -> right)) return 1;
        int depth_L = depth(root -> left);
        int depth_R = depth(root -> right);
        return depth_L > depth_R ? depth_L + 1 : depth_R + 1;
    }
};
/*

111. Minimum Depth of Binary Tree (Easy)

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        else if (!root -> left && !root -> right) return 1;
        else {
            int depth_L, depth_R;
            if (root -> left) depth_L = minDepth(root -> left);
            else depth_L = INT_MAX;
            if (root -> right) depth_R = minDepth(root -> right);
            else depth_R = INT_MAX;
            return min(depth_L, depth_R) + 1;
        }
    }
};
/*

112. Path Sum (Easy)

Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.

*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (root == NULL) {
            return false;
        } else if (root->left == NULL && root->right == NULL && sum == root->val) {
            return true;
        }
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};
/*

113. Path Sum II (Medium)

Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
return
[
   [5,4,11,2],
   [5,8,4,5]
]

*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<int> res_sub;
        pathSum(root, res, res_sub, sum);
        return res;
    }
private:
    void pathSum(TreeNode* root, vector<vector<int>>& res, vector<int>& res_sub, int sum) {
        if (root == NULL) {
            return;
        } else if (root->left == NULL && root->right == NULL && sum == root->val) {
            res_sub.push_back(root->val);
            res.push_back(res_sub);
            res_sub.pop_back();
            return;
        }
        if (root->left != NULL) {
            res_sub.push_back(root->val);
            pathSum(root->left, res, res_sub, sum - root->val);
            res_sub.pop_back();
        }
        if (root->right != NULL) {
            res_sub.push_back(root->val);
            pathSum(root->right, res, res_sub, sum - root->val);
            res_sub.pop_back();
        }
        
    }
};
/*

257. Binary Tree Paths (Easy)

Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5
All root-to-leaf paths are:

["1->2->5", "1->3"]

*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
  vector<string> binaryTreePaths(TreeNode* root) {
   vector<string> res;
   if (!root)
    return res;
else if (!(root -> left) && !(root -> right))
    res.push_back(to_string(root -> val));
string head = to_string(root->val) + "->";
for(auto item: binaryTreePaths(root->left))
    res.push_back(head + item);
for(auto item: binaryTreePaths(root->right))
    res.push_back(head + item);
return res;
}
};