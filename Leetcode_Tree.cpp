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
		return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
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
		return check(root->left, root->right);
	}
	bool check(TreeNode* L, TreeNode* R) {
		if (!L || !R) {
			if (L || R) return false;
			return true;
		}
		return L->val == R->val && check(L->left, R->right) && check(L->right, R->left);
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
				if (temp->left) q.push(temp->left);
				if (temp->right) q.push(temp->right);
			}
		}
		return res;
	}
};
class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (!root) return 0;
		else if (!(root->left) && !(root->right)) return 1;
		int depth_L = maxDepth(root->left);
		int depth_R = maxDepth(root->right);
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
		root->left = BT(preorder, pl + 1, pl + i - il, inorder, il, i - 1);
		root->right = BT(preorder, pl + i - il + 1, pr, inorder, i + 1, ir);
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
	TreeNode* sortedArrayToBST(vector<int>& nums, int l, int r) {
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
		if (!root) return true;
		else if (abs(depth(root->left) - depth(root->right)) > 1) return false;
		else return isBalanced(root->left) && isBalanced(root->right);
	}
	int depth(TreeNode* root) {
		if (!root) return 0;
		else if (!(root->left) && !(root->right)) return 1;
		int depth_L = depth(root->left);
		int depth_R = depth(root->right);
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
		else if (!root->left && !root->right) return 1;
		else {
			int depth_L, depth_R;
			if (root->left) depth_L = minDepth(root->left);
			else depth_L = INT_MAX;
			if (root->right) depth_R = minDepth(root->right);
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
	int maxPathSum(TreeNode* root, int& max) {
		if (root == NULL) {
			return 0;
		}
		int l = maxPathSum(root->left, max), r = maxPathSum(root->right, max);
		l = l < 0 ? 0 : l;
		r = r < 0 ? 0 : r;
		max = max > l + r + root->val ? max : l + r + root->val;
		return l > r ? l + root->val : r + root->val;
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
	stack<int> s;
	void traversal(TreeNode* root, stack<int>& s) {
		if (root) {
			traversal(root->right, s);
			s.push(root->val);
			traversal(root->left, s);
		}
	}
public:
	BSTIterator(TreeNode *root) {
		traversal(root, s);
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !s.empty();
	}

	/** @return the next smallest number */
	int next() {
		int num = s.top();
		s.pop();
		return num;
	}
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
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
		if (!root || !(root->left) && !(root->right))
			return root;
		else {
			swap(root->left, root->right);
			invertTree(root->left);
			invertTree(root->right);
		}
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
		if (min(p->val, q->val) < root->val && max(p->val, q->val) > root->val)
			return root;
		else if (root->val < min(p->val, q->val))
			return lowestCommonAncestor(root->right, p, q);
		else if (root->val > max(p->val, q->val))
			return lowestCommonAncestor(root->left, p, q);
		else
			return root;
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
		else if (l != NULL) {
			return l;
		}
		else if (r != NULL) {
			return r;
		}
		return NULL;
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