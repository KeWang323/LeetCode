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
			return fake->left;
		}
		else if (head->next == NULL) {
			fake->val = head->val;
			return fake;
		}
		ListNode *fast = head, *slow = head, *slow_prev = NULL;
		while (fast->next != NULL && fast->next->next != NULL) {
			slow_prev = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		fake->val = slow->val;
		if (slow_prev != NULL) {
			slow_prev->next = NULL;
			fake->left = sortedListToBST(head);
		}
		fake->right = sortedListToBST(slow->next);
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
	void flatten(TreeNode *root) {
		while (root) {
			if (root->left && root->right) {
				TreeNode* t = root->left;
				while (t->right) {
					t = t->right;
				}
				t->right = root->right;
			}
			if (root->left) {
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

133. Clone Graph (Medium)

Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

1
/ \
/   \
0 --- 2
/ \
\_/

*/
/**
* Definition for undirected graph.
* struct UndirectedGraphNode {
*     int label;
*     vector<UndirectedGraphNode *> neighbors;
*     UndirectedGraphNode(int x) : label(x) {};
* };
*/
class Solution {
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (node == NULL) {
			return NULL;
		}
		unordered_map<int, UndirectedGraphNode*> mapping;
		UndirectedGraphNode *newhead = new UndirectedGraphNode(node->label);
		mapping[node->label] = newhead;
		queue<UndirectedGraphNode*> q;
		q.push(node);
		while (!q.empty()) {
			UndirectedGraphNode *node1 = q.front();
			q.pop();
			for (UndirectedGraphNode* nei : node1->neighbors) {
				if (mapping.find(nei->label) == mapping.end()) {
					mapping[nei->label] = new UndirectedGraphNode(nei->label);
					q.push(nei);
				}
				mapping[node1->label]->neighbors.push_back(mapping[nei->label]);
			}
		}
		return newhead;
	}
};
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
class Solution {
public:
	vector<int> rightSideView(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<int> res;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			int _size = q.size();
			for (int i = 0; i < _size; i++) {
				TreeNode* node = q.front();
				q.pop();
				if (node->left != NULL) {
					q.push(node->left);
				}
				if (node->right != NULL) {
					q.push(node->right);
				}
				if (i == _size - 1) {
					res.push_back(node->val);
				}
			}
		}
		return res;
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