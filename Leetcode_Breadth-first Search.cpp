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
		if (root == NULL) {
			return{};
		}
		vector<vector<int>> res;
		deque<TreeNode*> dq;
		dq.push_back(root);
		bool odd = true;
		while (!dq.empty()) {
			int _size = dq.size();
			vector<int> res_sub;
			if (odd == true) {
				for (int i = 0; i < _size; i++) {
					res_sub.push_back(dq.front()->val);
					if (dq.front()->left != NULL) {
						dq.push_back(dq.front()->left);
					}
					if (dq.front()->right != NULL) {
						dq.push_back(dq.front()->right);
					}
					dq.pop_front();
				}
			}
			else {
				for (int i = 0; i < _size; i++) {
					res_sub.push_back(dq.back()->val);
					if (dq.back()->right != NULL) {
						dq.push_front(dq.back()->right);
					}
					if (dq.back()->left != NULL) {
						dq.push_front(dq.back()->left);
					}
					dq.pop_back();
				}
			}
			odd = !odd;
			res.push_back(res_sub);
		}
		return res;
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
		if (root == NULL) {
			return{};
		}
		vector<vector<int>> res;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			vector<int> lev;
			int _size = q.size();
			for (int i = 0; i < _size; i++) {
				lev.push_back(q.front()->val);
				if (q.front()->left != NULL) {
					q.push(q.front()->left);
				}
				if (q.front()->right != NULL) {
					q.push(q.front()->right);
				}
				q.pop();
			}
			res.push_back(lev);
		}
		reverse(res.begin(), res.end());
		return res;
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

279. Perfect Squares (Medium)

Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.

*/
class Solution {
public:
	int numSquares(int n) {
		vector<int> t(n + 1, INT_MAX);
		t[0] = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j * j <= i; j++) {
				t[i] = min(t[i], t[i - j * j] + 1);
			}
		}
		return t.back();
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
		UndirectedGraphNode* newhead = new UndirectedGraphNode(node->label);
		mapping[node->label] = newhead;
		queue<UndirectedGraphNode*> q;
		q.push(node);
		while (!q.empty()) {
			for (UndirectedGraphNode *nei : q.front()->neighbors) {
				if (mapping.find(nei->label) == mapping.end()) {
					mapping[nei->label] = new UndirectedGraphNode(nei->label);
					q.push(nei);
				}
				mapping[q.front()->label]->neighbors.push_back(mapping[nei->label]);
			}
			q.pop();
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

200. Number of Islands (Medium)

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000
Answer: 1

Example 2:

11000
11000
00100
00011
Answer: 3

*/
class Solution {
public:
	int numIslands(vector<vector<char>>& grid) {
		if (grid.empty()) {
			return 0;
		}
		int res = 0;
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[0].size(); j++) {
				if (grid[i][j] == '1') {
					res++;
					BFS(grid, i, j);
				}
			}
		}
		return res;
	}
private:
	void BFS(vector<vector<char>>& grid, int i, int j) {
		queue<pair<int, int>> q;
		grid[i][j] = '0';
		q.push(make_pair(i, j));
		while (!q.empty()) {
			i = q.front().first;
			j = q.front().second;
			q.pop();
			if (i > 0 && grid[i - 1][j] == '1') {
				grid[i - 1][j] = '0';
				q.push(make_pair(i - 1, j));
			}
			if (i < grid.size() - 1 && grid[i + 1][j] == '1') {
				grid[i + 1][j] = '0';
				q.push(make_pair(i + 1, j));
			}
			if (j > 0 && grid[i][j - 1] == '1') {
				grid[i][j - 1] = '0';
				q.push(make_pair(i, j - 1));
			}
			if (j < grid[0].size() - 1 && grid[i][j + 1] == '1') {
				grid[i][j + 1] = '0';
				q.push(make_pair(i, j + 1));
			}
		}
	}
};