/*

94. Binary Tree Inorder Traversal (Medium)

Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree [1,null,2,3],
   1
	\
	 2
	/
   3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

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
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		inorderTraversal(root, res);
		return res;
	}
private:
	void inorderTraversal(TreeNode* root, vector<int>& res) {
		if (root) {
			inorderTraversal(root->left, res);
			res.push_back(root->val);
			inorderTraversal(root->right, res);
		}
	}
};
/*

95. Unique Binary Search Trees II (Medium)

Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

 1         3     3      2      1
  \       /     /      / \      \
   3     2     1      1   3      2
  /     /       \                 \
 2     1         2                 3

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
private:
	vector<vector<vector<TreeNode*>>> table;
	vector<TreeNode*> generate(int l, int r) {
		if (l > r) return{ NULL };
		if (table[l][r].empty()) {
			for (int mid = l; mid <= r; mid++) {
				vector<TreeNode*> left = generate(l, mid - 1), right = generate(mid + 1, r);
				for (auto a : left) {
					for (auto b : right) {
						TreeNode* cur = new TreeNode(mid);
						cur->left = a;
						cur->right = b;
						table[l][r].push_back(cur);
					}
				}
			}
		}
		return table[l][r];
	}
public:
	vector<TreeNode*> generateTrees(int n) {
		if (n < 1) return{};
		table = vector<vector<vector<TreeNode*>>>(n + 1, vector<vector<TreeNode*>>(n + 1, vector<TreeNode*>()));
		return generate(1, n);
	}
};
/*

96. Unique Binary Search Trees (Medium)

Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

  1         3     3      2      1
   \       /     /      / \      \
	3     2     1      1   3      2
   /     /       \                 \
  2     1         2                 3

*/
class Solution {
public:
	int numTrees(int n) {
		vector<int> t(n + 1, 0);
		t[0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				t[i] += t[j - 1] * t[i - j];
			}
		}
		return t[n];
	}
};
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
		}
		else if (!validate(root->left, prev)) {
			return false;
		}
		else if (prev != NULL && prev->val >= root->val) {
			return false;
		}
		prev = root;
		return validate(root->right, prev);
	}
};
/*

99. Recover Binary Search Tree (Hard)

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

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
	void recoverTree(TreeNode* root) {
		TreeNode* first = NULL, *second = NULL, *pre = new TreeNode(INT_MIN);
		inOrder(root, first, second, pre);
		swap(first->val, second->val);
		return;
	}
private:
	void inOrder(TreeNode* root, TreeNode*& first, TreeNode*& second, TreeNode*& pre) {
		if (root == NULL) {
			return;
		}
		inOrder(root->left, first, second, pre);
		if (pre->val >= root->val) {
			if (first == NULL) {
				first = pre;
			}
			if (first != NULL) {
				second = root;
			}
		}
		pre = root;
		inOrder(root->right, first, second, pre);
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
		if (p == NULL && q == NULL) {
			return true;
		}
		else if (p == NULL || q == NULL || p->val != q->val) {
			return false;
		}
		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
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
		if (root == NULL) {
			return true;
		}
		return isSymmetric(root->left, root->right);
	}
private:
	bool isSymmetric(TreeNode* r1, TreeNode* r2) {
		if (r1 == NULL && r2 == NULL) {
			return true;
		}
		else if (r1 == NULL || r2 == NULL || r1->val != r2->val) {
			return false;
		}
		return isSymmetric(r1->left, r2->right) && isSymmetric(r1->right, r2->left);
	}
};
/*

102. Binary Tree Level Order Traversal (Easy)

Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
	3
   / \
  9  20
	/  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
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
	vector<vector<int>> levelOrder(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		queue<TreeNode*> q;
		q.push(root);
		vector<vector<int>> res;
		while (!q.empty()) {
			int _size = q.size();
			vector<int> res_sub;
			for (int i = 0; i < _size; i++) {
				res_sub.push_back(q.front()->val);
				if (q.front()->left != NULL) {
					q.push(q.front()->left);
				}
				if (q.front()->right != NULL) {
					q.push(q.front()->right);
				}
				q.pop();
			}
			res.push_back(res_sub);
		}
		return res;
	}
};
/*

103. Binary Tree Zigzag Level Order Traversal (Medium)

Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
	3
   / \
  9  20
	/  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
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
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (!root) return res;
		queue<TreeNode*> q;
		q.push(root);
		int level = 0;
		while (!q.empty()) {
			vector<int> lev;
			int _size = q.size();
			for (int i = 0; i < _size; i++) {
				TreeNode *temp = q.front();
				q.pop();
				lev.push_back(temp->val);
				if (temp->left) q.push(temp->left);
				if (temp->right) q.push(temp->right);
			}
			if (level % 2) reverse(lev.begin(), lev.end());
			res.push_back(lev);
			level++;
		}
		return res;
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
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}
		int l = maxDepth(root->left), r = maxDepth(root->right);
		return max(l, r) + 1;
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
		return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
	}
private:
	TreeNode* buildTree(const vector<int>& preorder, int pl, int pr, const vector<int>& inorder, int il, int ir) {
		if (pl > pr) {
			return NULL;
		}
		TreeNode *root = new TreeNode(preorder[pl]);
		int index = ir;
		while (inorder[index] != preorder[pl]) {
			index--;
		}
		root->left = buildTree(preorder, pl + 1, pl + index - il, inorder, il, index - 1);
		root->right = buildTree(preorder, pl + index - il + 1, pr, inorder, index + 1, ir);
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
		root->left = BT(inorder, il, i - 1, postorder, pl, pl - il + i - 1);
		root->right = BT(inorder, i + 1, ir, postorder, pl - il + i, pr - 1);
		return root;
	}
};
/*

107. Binary Tree Level Order Traversal II (Easy)

Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
	3
   / \
  9  20
	/  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
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
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		vector<vector<int>> res;
		if (!root) return res;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			vector<int> lev;
			int _size = q.size();
			for (int i = 0; i < _size; i++) {
				TreeNode *temp = q.front();
				q.pop();
				lev.push_back(temp->val);
				if (temp->left) q.push(temp->left);
				if (temp->right) q.push(temp->right);
			}
			res.push_back(lev);
		}
		reverse(res.begin(), res.end());
		return res;
	}
};
/*

108. Convert Sorted Array to Binary Search Tree (Medium)

Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

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
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		return sortedArrayToBST(nums, 0, nums.size() - 1);
	}
private:
	TreeNode* sortedArrayToBST(const vector<int>& nums, int l, int r) {
		if (l > r) {
			return NULL;
		}
		int mid = l + (r - l) / 2;
		TreeNode* root = new TreeNode(nums[mid]);
		root->left = sortedArrayToBST(nums, l, mid - 1);
		root->right = sortedArrayToBST(nums, mid + 1, r);
		return root;
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
		return isbalanced(root) != -1;
	}
private:
	int isbalanced(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}
		int l = isbalanced(root->left), r = isbalanced(root->right);
		if (l == -1 || r == -1 || abs(l - r) > 1) {
			return -1;
		}
		return max(l, r) + 1;
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
		if (root == NULL) {
			return 0;
		}
		else if (root->left == NULL && root->right == NULL) {
			return 1;
		}
		int l = minDepth(root->left), r = minDepth(root->right);
		l = l == 0 ? INT_MAX : l;
		r = r == 0 ? INT_MAX : r;
		return min(l, r) + 1;
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
		}
		else if (root->left == NULL && root->right == NULL && sum == root->val) {
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
		}
		else if (root->left == NULL && root->right == NULL && sum == root->val) {
			res_sub.push_back(root->val);
			res.push_back(res_sub);
			res_sub.pop_back();
			return;
		}
		res_sub.push_back(root->val);
		if (root->left != NULL) {
			pathSum(root->left, res, res_sub, sum - root->val);
		}
		if (root->right != NULL) {
			pathSum(root->right, res, res_sub, sum - root->val);
		}
		res_sub.pop_back();

	}
};
/*

114. Flatten Binary Tree to Linked List (Medium)

Given a binary tree, flatten it to a linked list in-place.

For example,
Given

		 1
		/ \
	   2   5
	  / \   \
	 3   4   6
The flattened tree should look like:
   1
	\
	 2
	  \
	   3
		\
		 4
		  \
		   5
			\
			 6

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
	void flatten(TreeNode* root) {
		while (root != NULL) {
			if (root->left != NULL && root->right != NULL) {
				TreeNode *temp = root->left;
				while (temp->right != NULL) {
					temp = temp->right;
				}
				temp->right = root->right;
			}
			if (root->left != NULL) {
				root->right = root->left;
			}
			root->left = NULL;
			root = root->right;
		}
	}
};
/*

116. Populating Next Right Pointers in Each Node (Medium)

Given a binary tree

	struct TreeLinkNode {
	  TreeLinkNode *left;
	  TreeLinkNode *right;
	  TreeLinkNode *next;
	}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
For example,
Given the following perfect binary tree,
		 1
	   /  \
	  2    3
	 / \  / \
	4  5  6  7
After calling your function, the tree should look like:
		 1 -> NULL
	   /  \
	  2 -> 3 -> NULL
	 / \  / \
	4->5->6->7 -> NULL

*/
/**
* Definition for binary tree with next pointer.
* struct TreeLinkNode {
*  int val;
*  TreeLinkNode *left, *right, *next;
*  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
* };
*/
class Solution {
public:
	void connect(TreeLinkNode *root) {
		if (root == NULL) {
			return;
		}
		while (root->left != NULL) {
			TreeLinkNode *p = root;
			while (p != NULL) {
				p->left->next = p->right;
				if (p->next != NULL) {
					p->right->next = p->next->left;
				}
				p = p->next;
			}
			root = root->left;
		}
	}
};
/*

117. Populating Next Right Pointers in Each Node II (Hard)

Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,
1
/  \
2    3
/ \    \
4   5    7
After calling your function, the tree should look like:
1 -> NULL
/  \
2 -> 3 -> NULL
/ \    \
4-> 5 -> 7 -> NULL

*/
/**
* Definition for binary tree with next pointer.
* struct TreeLinkNode {
*  int val;
*  TreeLinkNode *left, *right, *next;
*  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
* };
*/
class Solution {
public:
	void connect(TreeLinkNode *root) {
		if (root == NULL) {
			return;
		}
		queue<TreeLinkNode*> q;
		q.push(root);
		while (!q.empty()) {
			int _size = q.size();
			for (int i = 0; i < _size; i++) {
				TreeLinkNode* node = q.front();
				q.pop();
				if (i < _size - 1) {
					node->next = q.front();
				}
				else {
					node->next = NULL;
				}
				if (node->left != NULL) {
					q.push(node->left);
				}
				if (node->right != NULL) {
					q.push(node->right);
				}
			}
		}
	}
};
/*

124. Binary Tree Maximum Path Sum (Hard)

Given a binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

For example:
Given the below binary tree,

	   1
	  / \
	 2   3
Return 6.

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
	int maxPathSum(TreeNode* root) {
		int res = INT_MIN;
		maxPathSum(root, res);
		return res;
	}
private:
	int maxPathSum(TreeNode* root, int& res) {
		if (root == NULL) {
			return 0;
		}
		int l = maxPathSum(root->left, res), r = maxPathSum(root->right, res);
		l = l > 0 ? l : 0;
		r = r > 0 ? r : 0;
		res = max(res, l + r + root->val);
		return max(l, r) + root->val;
	}
};
/*

129. Sum Root to Leaf Numbers (Medium)

Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

  1
 / \
2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.

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
	int sumNumbers(TreeNode* root) {
		vector<int> nums;
		int num = 0;
		sumNumber(root, nums, num);
		num = 0;
		for (int i : nums) {
			num += i;
		}
		return num;
	}
private:
	void sumNumber(TreeNode* root, vector<int>& nums, int& num) {
		if (root == NULL) {
			nums.push_back(0);
			return;
		}
		num = 10 * num + root->val;
		if (root->left == NULL && root->right == NULL) {
			nums.push_back(num);
			num /= 10;
			return;
		}
		if (root->left != NULL) {
			sumNumber(root->left, nums, num);
		}
		if (root->right != NULL) {
			sumNumber(root->right, nums, num);
		}
		num /= 10;
	}
};
/*

144. Binary Tree Preorder Traversal (Medium)

Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
	\
	 2
	/
   3
return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?

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
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> res;
		traversal(root, res);
		return res;
	}
	void traversal(TreeNode* root, vector<int>& res) {
		if (root) {
			res.push_back(root->val);
			traversal(root->left, res);
			traversal(root->right, res);
		}
	}
};
class Solution {
public:
	vector<int> preorderTraversal(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<int> res;
		stack<TreeNode*> sta;
		sta.push(root);
		while (!sta.empty()) {
			TreeNode *node = sta.top();
			sta.pop();
			res.push_back(node->val);
			if (node->right != NULL) {
				sta.push(node->right);
			}
			if (node->left != NULL) {
				sta.push(node->left);
			}
		}
		return res;
	}
};
/*

145. Binary Tree Postorder Traversal (Hard)

Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
	\
	 2
	/
   3
return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?

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
	vector<int> postorderTraversal(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<int> res;
		stack<TreeNode*> s;
		TreeNode *pre = NULL;
		s.push(root);
		while (!s.empty()) {
			TreeNode *cur = s.top();
			if (pre == NULL || pre->left == cur || pre->right == cur) {
				if (cur->left != NULL) {
					s.push(cur->left);
				}
				else if (cur->right != NULL) {
					s.push(cur->right);
				}
				else {
					res.push_back(cur->val);
					s.pop();
				}
			}
			else if (pre == cur->left) {
				if (cur->right != NULL) {
					s.push(cur->right);
				}
				else {
					res.push_back(cur->val);
					s.pop();
				}
			}
			else {
				res.push_back(cur->val);
				s.pop();
			}
			pre = cur;
		}
		return res;
	}
};
/*

156. Binary Tree Upside Down (Medium)

Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node) or empty, flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. Return the new root.

For example:
Given a binary tree {1,2,3,4,5},
1
/ \
2   3
/ \
4   5
return the root of the binary tree [4,5,2,#,#,3,1].
4
/ \
5   2
/ \
3   1

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
	TreeNode* upsideDownBinaryTree(TreeNode* root) {
		if (root == NULL || root->left == NULL) {
			return root;
		}
		TreeNode *node = upsideDownBinaryTree(root->left);
		root->left->left = root->right;
		root->left->right = root;
		root->left = NULL;
		root->right = NULL;
		return node;
	}
};
/*

173. Binary Search Tree Iterator (Medium)

Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.

*/
/**
* Definition for binary tree
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class BSTIterator {
private:
	void postorder(TreeNode* root, stack<int>& s) {
		if (root != NULL) {
			postorder(root->right, s);
			s.push(root->val);
			postorder(root->left, s);
		}
	}
public:
	stack<int> s;
	BSTIterator(TreeNode *root) {
		postorder(root, s);
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !s.empty();
	}

	/** @return the next smallest number */
	int next() {
		int temp = s.top();
		s.pop();
		return temp;
	}
};
/**
* Your BSTIterator will be called like this:
* BSTIterator i = BSTIterator(root);
* while (i.hasNext()) cout << i.next();
*/
/*

199. Binary Tree Right Side View (Medium)

Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
You should return [1, 3, 4].

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
	vector<int> rightSideView(TreeNode *root) {
		vector<int> res;
		recursion(root, 1, res);
		return res;
	}
private:
	void recursion(TreeNode *root, int level, vector<int> &res) {
		if (root == NULL) {
			return;
		}
		if (res.size() < level) {
			res.push_back(root->val);
		}
		recursion(root->right, level + 1, res);
		recursion(root->left, level + 1, res);
	}
};
/*

222. Count Complete Tree Nodes (Medium)

Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled,
and all nodes in the last level are as far left as possible. It can have between 1 and
2h nodes inclusive at the last level h.

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
	int countNodes(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}
		int lh = 0, rh = 0;
		TreeNode *l = root, *r = root;
		while (l != NULL) {
			lh++;
			l = l->left;
		}
		while (r != NULL) {
			rh++;
			r = r->right;
		}
		if (lh == rh) {
			return (1 << lh) - 1;
		}
		return 1 + countNodes(root->left) + countNodes(root->right);
	}
};
class Solution {
public:
	int countNodes(TreeNode* root) {
		if (!root) return 0;
		int h = 0, sum = 0;
		TreeNode *t = root, *t0 = NULL;
		while (t) {
			t = t->left;
			h++;
		}
		t = root;
		int level = h - 2;
		while (level > -1) {
			t0 = t->left;
			for (int i = 0; i < level; i++)
				t0 = t0->right;
			if (t0) {
				sum += 1 << level;
				t = t->right;
			}
			else t = t->left;
			level--;
		}
		if (t) sum++;
		return sum + ((1 << (h - 1)) - 1);
	}
};
/*

226. Invert Binary Tree (Easy)

Invert a binary tree.

4
/   \
2     7
/ \   / \
1   3 6   9
to
4
/   \
7     2
/ \   / \
9   6 3   1

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
	TreeNode* invertTree(TreeNode* root) {
		if (root == NULL) {
			return root;
		}
		swap(root->left, root->right);
		invertTree(root->left);
		invertTree(root->right);
		return root;
	}
};
/*

230. Kth Smallest Element in a BST (Medium)

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Hint:

Try to utilize the property of a BST.
What if you could modify the BST node's structure?
The optimal runtime complexity is O(height of BST).

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
	int kthSmallest(TreeNode* root, int k) {
		vector<int> res;
		traversal(root, res);
		return res[k - 1];
	}
	void traversal(TreeNode* root, vector<int>& res) {
		if (root) {
			traversal(root->left, res);
			res.push_back(root->val);
			traversal(root->right, res);
		}
	}
};
class Solution {
public:
	int kthSmallest(TreeNode* root, int k) {
		stack<TreeNode*> s;
		int cnt = 0, res = root->val;
		while (true) {
			TreeNode* temp = root;
			while (temp) {
				s.push(temp);
				temp = temp->left;
			}
			if (s.empty() || cnt == k) return res;
			cnt++;
			root = s.top();
			s.pop();
			res = root->val;
			root = root->right;
		}
		return res;
	}
};
/*

235. Lowest Common Ancestor of a Binary Search Tree (Easy)

Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

		_______6______
	   /              \
	___2__          ___8__
   /      \        /      \
   0      _4       7       9
		 /  \
		 3   5
For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

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
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == NULL || root == p || root == q) {
			return root;
		}
		TreeNode *l = lowestCommonAncestor(root->left, p, q), *r = lowestCommonAncestor(root->right, p, q);
		if (l != NULL && r != NULL) {
			return root;
		}
		return l != NULL ? l : r;
	}
};
/*

236. Lowest Common Ancestor of a Binary Tree (Medium)

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

		_______3______
	   /              \
	___5__          ___1__
   /      \        /      \
   6      _2       0       8
		 /  \
		 7   4
For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

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
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == NULL || root == p || root == q) {
			return root;
		}
		TreeNode *l = lowestCommonAncestor(root->left, p, q), *r = lowestCommonAncestor(root->right, p, q);
		if (l != NULL && r != NULL) {
			return root;
		}
		return l != NULL ? l : r;
	}
};
/*

250. Count Univalue Subtrees (Medium)

Given a binary tree, count the number of uni-value subtrees.

A Uni-value subtree means all nodes of the subtree have the same value.

For example:
Given binary tree,
			  5
			 / \
			1   5
		   / \   \
		  5   5   5
return 4.

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
	int countUnivalSubtrees(TreeNode* root) {
		int res = 0;
		countUnivalSubtrees(root, res);
		return res;
	}
private:
	bool countUnivalSubtrees(TreeNode* root, int& res) {
		if (root == NULL) {
			return true;
		}
		else if (root->left == NULL && root->right == NULL) {
			res++;
			return true;
		}
		bool l = countUnivalSubtrees(root->left, res), r = countUnivalSubtrees(root->right, res);
		if (l && r && (root->left == NULL || root->val == root->left->val) && (root->right == NULL || root->val == root->right->val)) {
			res++;
			return true;
		}
		return false;
	}
};
/*

255. Verify Preorder Sequence in Binary Search Tree (Medium)

Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.

You may assume each number in the sequence is unique.

Follow up:
Could you do it using only constant space complexity?

*/
class Solution {
public:
	bool verifyPreorder(vector<int>& preorder) {
		int i = 0;
		verifyPreorder(preorder, i, INT_MIN, INT_MAX);
		return i >= preorder.size() ? true : false;
	}
private:
	void verifyPreorder(vector<int>& nums, int& i, int low, int high) {
		if (i >= nums.size() || nums[i] > high || nums[i] < low) return;
		int cur = nums[i++];
		verifyPreorder(nums, i, low, cur);
		verifyPreorder(nums, i, cur, high);
		return;
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
		else if (!(root->left) && !(root->right))
			res.push_back(to_string(root->val));
		string head = to_string(root->val) + "->";
		for (auto item : binaryTreePaths(root->left))
			res.push_back(head + item);
		for (auto item : binaryTreePaths(root->right))
			res.push_back(head + item);
		return res;
	}
};
/*

270. Closest Binary Search Tree Value

Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.

Note:
Given target value is a floating point.
You are guaranteed to have only one unique value in the BST that is closest to the target.

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
	int closestValue(TreeNode* root, double target) {
		int res = root->val;
		while (root != NULL) {
			if (abs(root->val - target) < abs(res - target)) {
				res = root->val;
			}
			if (root->val < target) {
				root = root->right;
			}
			else {
				root = root->left;
			}
		}
		return res;
	}
};
/*

272. Closest Binary Search Tree Value II (Hard)

Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:
Given target value is a floating point.
You may assume k is always valid, that is: k ≤ total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

Hint:

Consider implement these two helper functions:
getPredecessor(N), which returns the next smaller node to N.
getSuccessor(N), which returns the next larger node to N.
Try to assume that each node has a parent pointer, it makes the problem much easier.
Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
You would need two stacks to track the path in finding predecessor and successor node separately.

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
	vector<int> closestKValues(TreeNode* root, double target, int k) {
		stack<TreeNode*> suc, pre;
		vector<int> res;
		iniPreSta(root, target, pre);
		iniSucSta(root, target, suc);
		if (!suc.empty() && !pre.empty() && suc.top()->val == pre.top()->val) {
			getNextPredecessor(pre);
		}
		while (k-- > 0) {
			if (suc.empty()) {
				res.push_back(getNextPredecessor(pre));
			}
			else if (pre.empty()) {
				res.push_back(getNextSuccessor(suc));
			}
			else {
				if (abs((double)pre.top()->val - target) < abs((double)suc.top()->val - target)) {
					res.push_back(getNextPredecessor(pre));
				}
				else {
					res.push_back(getNextSuccessor(suc));
				}
			}
		}
		return res;
	}
private:
	void iniPreSta(TreeNode* root, double target, stack<TreeNode*>& pre) {
		while (root != NULL) {
			if (root->val < target) {
				pre.push(root);
				root = root->right;
			}
			else if (root->val > target) {
				root = root->left;
			}
			else {
				pre.push(root);
				break;
			}
		}
	}
	void iniSucSta(TreeNode* root, double target, stack<TreeNode*>& suc) {
		while (root != NULL) {
			if (root->val > target) {
				suc.push(root);
				root = root->left;
			}
			else if (root->val < target) {
				root = root->right;
			}
			else {
				suc.push(root);
				break;
			}
		}
	}
	int getNextSuccessor(stack<TreeNode*>& suc) {
		TreeNode* cur = suc.top();
		suc.pop();
		int res = cur->val;
		cur = cur->right;
		while (cur != NULL) {
			suc.push(cur);
			cur = cur->left;
		}
		return res;
	}
	int getNextPredecessor(stack<TreeNode*>& pre) {
		TreeNode* cur = pre.top();
		pre.pop();
		int res = cur->val;
		cur = cur->left;
		while (cur != NULL) {
			pre.push(cur);
			cur = cur->right;
		}
		return res;
	}
};
/*

285. Inorder Successor in BST (Medium)

Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null.

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
	TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
		stack<TreeNode*> s;
		iniSucSta(root, p, s);
		if (!s.empty() && s.top() == p) {
			getNextSuccessor(s);
		}
		return getNextSuccessor(s);
	}
private:
	void iniSucSta(TreeNode* root, TreeNode* p, stack<TreeNode*>& s) {
		while (root != NULL) {
			if (root->val > p->val) {
				s.push(root);
				root = root->left;
			}
			else if (root->val < p->val) {
				root = root->right;
			}
			else {
				s.push(root);
				break;
			}
		}
	}
	TreeNode* getNextSuccessor(stack<TreeNode*>& s) {
		if (s.empty()) {
			return NULL;
		}
		TreeNode* cur = s.top();
		s.pop();
		TreeNode* temp = cur;
		cur = cur->right;
		while (cur != NULL) {
			s.push(cur);
			cur = cur->left;
		}
		return temp;
	}
};
/*

297. Serialize and Deserialize Binary Tree (Hard)

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

1
/ \
2   3
/ \
4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

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
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream out;
		serialize(root, out);
		return out.str();
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream in(data);
		return deserialize(in);
	}
private:
	void serialize(TreeNode* root, ostringstream& out) {
		if (root) {
			out << root->val << ' ';
			serialize(root->left, out);
			serialize(root->right, out);
		}
		else {
			out << "# ";
		}
	}
	TreeNode* deserialize(istringstream& in) {
		string val;
		in >> val;
		if (val == "#")
			return nullptr;
		TreeNode* root = new TreeNode(stoi(val));
		root->left = deserialize(in);
		root->right = deserialize(in);
		return root;
	}
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
/*

298. Binary Tree Longest Consecutive Sequence (Medium)

Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).

For example,
1
\
3
/ \
2   4
\
5
Longest consecutive sequence path is 3-4-5, so return 3.
2
\
3
/
2
/
1
Longest consecutive sequence path is 2-3,not3-2-1, so return 2.

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
	int longestConsecutive(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}
		int res = 0;
		longestConsecutive(root, res, 0, root->val);
		return res;
	}
private:
	void longestConsecutive(TreeNode* root, int& res, int cur, int tar) {
		if (root == NULL) {
			return;
		}
		if (root->val == tar) {
			cur++;
		}
		else {
			cur = 1;
		}
		res = max(res, cur);
		longestConsecutive(root->left, res, cur, root->val + 1);
		longestConsecutive(root->right, res, cur, root->val + 1);
	}
};
/*

333. Largest BST Subtree (Medium)

Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.

Note:
A subtree must include all of its descendants.
Here's an example:
10
/ \
5  15
/ \   \
1   8   7
The Largest BST Subtree in this case is the highlighted one.
The return value is the subtree's size, which is 3.
Hint:

You can recursively use algorithm similar to 98. Validate Binary Search Tree at each node of the tree, which will result in O(nlogn) time complexity.

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
	int largestBSTSubtree(TreeNode* root) {
		int res = 0;
		largestBSTSubtree(root, res);
		return res;
	}
private:
	vector<int> largestBSTSubtree(TreeNode* root, int& res) {
		if (root == NULL) {
			return{ 0,0,0 };
		}
		else if (root->left == NULL && root->right == NULL) {
			res = max(res, 1);
			return{ 1, root->val, root->val };
		}
		vector<int> l = largestBSTSubtree(root->left, res), r = largestBSTSubtree(root->right, res);
		if (l[0] != -1 && r[0] != -1) {
			if ((l[0] == 0 || root->val > l[2]) && (r[0] == 0 || root->val < r[1])) {
				res = max(res, l[0] + r[0] + 1);
				int small = l[1] == 0 ? root->val : l[1], large = r[2] == 0 ? root->val : r[2];
				return{ l[0] + r[0] + 1, small, large };
			}
		}
		return{ -1,0,0 };
	}
};
/*

337. House Robber III (Medium)

The thief has found himself a new place for his thievery again. There is only one entrance to this area, called the "root." Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that "all houses in this place forms a binary tree". It will automatically contact the police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:
	 3
	/ \
   2   3
	\   \
	 3   1
Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:
	 3
	/ \
   4   5
  / \   \
 1   3   1
Maximum amount of money the thief can rob = 4 + 5 = 9.

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
	int rob(TreeNode* root) {
		int l = 0, r = 0;
		return rob(root, l, r);
	}
private:
	int rob(TreeNode* root, int& l, int& r) {
		if (root == NULL) {
			return 0;
		}
		int ll = 0, lr = 0, rl = 0, rr = 0;
		l = rob(root->left, ll, lr);
		r = rob(root->right, rl, rr);
		return max(root->val + ll + lr + rl + rr, l + r);
	}
};
/*

366. Find Leaves of Binary Tree (Medium)

Given a binary tree, collect a tree's nodes as if you were doing this: Collect and remove all leaves, repeat until the tree is empty.

Example:
Given binary tree
1
/ \
2   3
/ \
4   5
Returns [4, 5, 3], [2], [1].

Explanation:
1. Removing the leaves [4, 5, 3] would result in this tree:

1
/
2
2. Now removing the leaf [2] would result in this tree:

1
3. Now removing the leaf [1] would result in the empty tree:

[]
Returns [4, 5, 3], [2], [1].

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
	vector<vector<int>> findLeaves(TreeNode* root) {
		vector<vector<int>> res;
		findLeaves(root, res);
		return res;
	}

	int findLeaves(TreeNode* root, vector<vector<int>>& res) {
		if (root == NULL) {
			return 0;
		}
		int value = root->val, height = max(findLeaves(root->left, res), findLeaves(root->right, res)) + 1;
		if (height > res.size()) {
			vector<int> res_sub;
			res_sub.push_back(value);
			res.push_back(res_sub);
		}
		else {
			res[height - 1].push_back(value);
		}
		return height;
	}
};
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
	vector<vector<int>> findLeaves(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<vector<int>> res;
		while (root->right != NULL || root->left != NULL) {
			vector<int> res_sub = helper(root);
			res.push_back(res_sub);
		}
		res.push_back({ root->val });
		return res;
	}
private:
	vector<int> helper(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<int> res_sub, l, r;
		if (root->left != NULL && root->left->left == NULL && root->left->right == NULL) {
			res_sub.push_back(root->left->val);
			root->left = NULL;
		}
		else {
			l = helper(root->left);
		}
		if (root->right != NULL && root->right->left == NULL && root->right->right == NULL) {
			res_sub.push_back(root->right->val);
			root->right = NULL;
		}
		else {
			r = helper(root->right);
		}
		for (int i : l) {
			res_sub.push_back(i);
		}
		for (int i : r) {
			res_sub.push_back(i);
		}
		return res_sub;
	}
};
/*

404. Sum of Left Leaves (Easy)

Find the sum of all left leaves in a given binary tree.

Example:

3
/ \
9  20
/  \
15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.

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
	int sumOfLeftLeaves(TreeNode* root) {
		int res = 0;
		sumOfLeftLeaves(root, NULL, res);
		return res;
	}
private:
	void sumOfLeftLeaves(TreeNode* root, TreeNode* pre, int& res) {
		if (root == NULL) {
			return;
		}
		else if (pre == NULL) {
			sumOfLeftLeaves(root->left, root, res);
			sumOfLeftLeaves(root->right, root, res);
		}
		else if (root->left == NULL && root->right == NULL && pre->left == root) {
			res += root->val;
			return;
		}
		else {
			sumOfLeftLeaves(root->left, root, res);
			sumOfLeftLeaves(root->right, root, res);
		}

	}
};
/*

437. Path Sum III (Easy)

You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

10
/  \
5   -3
/ \    \
3   2   11
/ \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11

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
	int pathSum(TreeNode* root, int sum) {
		unordered_map<int, int> mapping;
		mapping[0] = 1;
		return pathSum(root, 0, sum, mapping);
	}
private:
	int pathSum(TreeNode* root, int sum, const int& target, unordered_map<int, int>& mapping) {
		if (root == NULL) {
			return 0;
		}
		sum += root->val;
		int res = mapping.find(sum - target) != mapping.end() ? mapping[sum - target] : 0;
		mapping[sum]++;
		res += pathSum(root->left, sum, target, mapping) + pathSum(root->right, sum, target, mapping);
		mapping[sum]--;
		return res;
	}
};
/*

449. Serialize and Deserialize BST (Medium)

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary search tree can be serialized to a string and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

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
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream out;
		serialize(root, out);
		return out.str();
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream in(data);
		return deserialize(in);
	}
private:
	void serialize(TreeNode* root, ostringstream& out) {
		if (root) {
			out << root->val << ' ';
			serialize(root->left, out);
			serialize(root->right, out);
		}
		else {
			out << "# ";
		}
	}
	TreeNode* deserialize(istringstream& in) {
		string val;
		in >> val;
		if (val == "#")
			return nullptr;
		TreeNode* root = new TreeNode(stoi(val));
		root->left = deserialize(in);
		root->right = deserialize(in);
		return root;
	}
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
/*

450. Delete Node in a BST (Medium)

Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.
Note: Time complexity should be O(height of tree).

Example:

root = [5,3,6,2,4,null,7]
key = 3

5
/ \
3   6
/ \   \
2   4   7

Given key to delete is 3. So we find the node with value 3 and delete it.

One valid answer is [5,4,6,2,null,null,7], shown in the following BST.

5
/ \
4   6
/     \
2       7

Another valid answer is [5,2,6,null,4,null,7].

5
/ \
2   6
\   \
4   7

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
	TreeNode* deleteNode(TreeNode* root, int key) {
		if (root == NULL) {
			return root;
		}
		else if (root->val > key) {
			root->left = deleteNode(root->left, key);
		}
		else if (root->val < key) {
			root->right = deleteNode(root->right, key);
		}
		else {
			if (root->right == NULL || root->left == NULL) {
				return root->left == NULL ? root->right : root->left;
			}
			else {
				root->val = findSmallest(root->right);
				root->right = deleteNode(root->right, root->val);
			}
		}
		return root;
	}
private:
	int findSmallest(TreeNode* root) {
		while (root->left != NULL) {
			root = root->left;
		}
		return root->val;
	}
};