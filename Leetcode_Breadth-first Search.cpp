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

261. Graph Valid Tree (medium)

Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

For example:

Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.

Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.

Hint:

Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], what should your return? Is this case a valid tree?
According to the definition of tree on Wikipedia: ��a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.��
Note: you can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

*/
class Solution {
public:
	bool validTree(int n, vector<pair<int, int>>& edges) {
		vector<int> t(n);
		for (int i = 0; i < n; i++) {
			t[i] = i;
		}
		for (pair<int, int> p : edges) {
			int node1 = find(t, p.first), node2 = find(t, p.second);
			if (node1 == node2) {
				return false;
			}
			t[node1] = node2;
		}
		return edges.size() == n - 1;
	}
private:
	int find(vector<int> t, int id) {
		while (t[id] != id) {
			t[id] = t[t[id]];
			id = t[id];
		}
		return id;
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
		rightSideView(root, 1, res);
		return res;
	}
private:
	void rightSideView(TreeNode *root, int level, vector<int> &res) {
		if (root == NULL) {
			return;
		}
		if (res.size() < level) {
			res.push_back(root->val);
		}
		rightSideView(root->right, level + 1, res);
		rightSideView(root->left, level + 1, res);
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
/*

286. Walls and Gates (Medium)

You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

For example, given the 2D grid:
INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
After running your function, the 2D grid should be:
  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4

*/
class Solution {
public:
	void wallsAndGates(vector<vector<int>>& rooms) {
		if (rooms.empty()) {
			return;
		}
		for (int i = 0; i < rooms.size(); i++) {
			for (int j = 0; j < rooms[0].size(); j++) {
				if (rooms[i][j] == 0) {
					bfs(rooms, i, j);
				}
			}
		}
		return;
	}
private:
	vector<int> dir = { 0,1, 0, -1, 0 };
	void bfs(vector<vector<int>>& rooms, int i, int j) {
		queue<pair<int, int>> q;
		q.push({ i, j });
		while (!q.empty()) {
			int x = q.front().first, y = q.front().second;
			int step = rooms[x][y] + 1;
			q.pop();
			for (int k = 0; k < 4; k++) {
				int xx = x + dir[k], yy = y + dir[k + 1];
				if (xx >= 0 && xx < rooms.size() && yy >= 0 && yy < rooms[0].size() && rooms[xx][yy] > step) {
					rooms[xx][yy] = step;
					q.push({ xx, yy });
				}
			}
		}
	}
};
/*

323. Number of Connected Components in an Undirected Graph (Medium)

Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to find the number of connected components in an undirected graph.

Example 1:
	 0          3
	 |          |
	 1 --- 2    4
Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.

Example 2:
	 0           4
	 |           |
	 1 --- 2 --- 3
Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.

Note:
You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

*/
class Solution {
public:
	int countComponents(int n, vector<pair<int, int>>& edges) {
		vector<int> t(n);
		for (int i = 0; i < n; i++) {
			t[i] = i;
		}
		for (pair<int, int> p : edges) {
			int root1 = find(t, p.first), root2 = find(t, p.second);
			if (root1 != root2) {
				t[root1] = root2;
				n--;
			}
		}
		return n;
	}
private:
	int find(vector<int> t, int id) {
		while (t[id] != id) {
			t[id] = t[t[id]];
			id = t[id];
		}
		return id;
	}
};
/*

407. Trapping Rain Water II (Hard)

Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.

Note:
Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.

Example:

Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

Return 4.

*/
class Cell {
public:
	int row, col, height;
	Cell(int r, int c, int h) : row(r), col(c), height(h) {}
};
class Comp {
public:
	bool operator()(Cell* c1, Cell* c2) {
		return c1->height > c2->height;
	}
};
class Solution {
public:
	int trapRainWater(vector<vector<int>>& heightMap) {
		if (heightMap.empty()) {
			return 0;
		}
		int m = heightMap.size(), n = heightMap[0].size();
		priority_queue<Cell*, vector<Cell*>, Comp> pq;
		vector<vector<bool>> t(heightMap.size(), vector<bool>(heightMap[0].size(), false));
		for (int i = 0; i < m; i++) {
			t[i][0] = true;
			t[i][n - 1] = true;
			pq.push(new Cell(i, 0, heightMap[i][0]));
			pq.push(new Cell(i, n - 1, heightMap[i][n - 1]));
		}
		for (int i = 1; i < n - 1; i++) {
			t[0][i] = true;
			t[m - 1][i] = true;
			pq.push(new Cell(0, i, heightMap[0][i]));
			pq.push(new Cell(m - 1, i, heightMap[m - 1][i]));
		}
		int res = 0;
		vector<pair<int, int>> nei = { make_pair(-1, 0), make_pair(1, 0), make_pair(0, -1), make_pair(0, 1) };
		while (!pq.empty()) {
			Cell *c = pq.top();
			pq.pop();
			for (pair<int, int> p : nei) {
				int row = c->row + p.first, col = c->col + p.second;
				if (row >= 0 && row < m && col >= 0 && col < n && t[row][col] == false) {
					t[row][col] = true;
					res += max(0, c->height - heightMap[row][col]);
					pq.push(new Cell(row, col, max(c->height, heightMap[row][col])));
				}
			}
		}
		return res;
	}
};
/*

417. Pacific Atlantic Water Flow (Medium)

Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

Note:
The order of returned grid coordinates does not matter.
Both m and n are less than 150.
Example:

Given the following 5x5 matrix:

  Pacific ~   ~   ~   ~   ~
	   ~  1   2   2   3  (5) *
	   ~  3   2   3  (4) (4) *
	   ~  2   4  (5)  3   1  *
	   ~ (6) (7)  1   4   5  *
	   ~ (5)  1   1   2   4  *
		  *   *   *   *   * Atlantic

Return:

[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).

*/
class Solution {
public:
	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
		if (matrix.empty()) {
			return{};
		}
		vector<pair<int, int>> res;
		int m = matrix.size(), n = matrix[0].size();
		vector<vector<bool>> tp(m, vector<bool>(n, false)), ta(m, vector<bool>(n, false));
		queue<pair<int, int>> P, A;
		for (int i = 0; i < m; i++) {
			P.push({ i,0 });
			tp[i][0] = true;
			A.push({ i, n - 1 });
			ta[i].back() = true;
		}
		for (int j = 0; j < n; j++) {
			P.push({ 0, j });
			tp[0][j] = true;
			A.push({ m - 1, j });
			ta[m - 1][j] = true;
		}
		bfs(matrix, P, tp, m, n);
		bfs(matrix, A, ta, m, n);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (tp[i][j] && ta[i][j]) {
					res.push_back({ i,j });
				}
			}
		}
		return res;
	}
private:
	vector<int> dir = { 0, 1, 0, -1, 0 };
	void bfs(const vector<vector<int>>& matrix, queue<pair<int, int>>& q, vector<vector<bool>>& t, const int& m, const int& n) {
		while (!q.empty()) {
			pair<int, int> cell = q.front();
			q.pop();
			for (int i = 0; i < dir.size() - 1; i++) {
				int x = cell.first + dir[i], y = cell.second + dir[i + 1];
				if (x < 0 || x >= m || y < 0 || y >= n || t[x][y] || matrix[x][y] < matrix[cell.first][cell.second]) {
					continue;
				}
				t[x][y] = true;
				q.push({ x, y });
			}
		}
	}
};
/*

490. The Maze (Medium)

There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the ball's start position, the destination and the maze, determine whether the ball could stop at the destination.

The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.

Example 1

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (4, 4)

Output: true
Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.

Example 2

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (3, 2)

Output: false
Explanation: There is no way for the ball to stop at the destination.

Note:
There is only one ball and one destination in the maze.
Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.

*/
class Solution {
public:
	bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
		queue<pair<int, int>> q;
		int m = maze.size(), n = maze[0].size();
		vector<vector<bool>> visited(m, vector<bool>(n, false));
		q.push({ start[0], start[1] });
		visited[start[0]][start[1]] = true;
		while (!q.empty()) {
			pair<int, int> p = q.front();
			q.pop();
			for (int k = 0; k < 4; k++) {
				int i = p.first, j = p.second;
				while (i + dir[k] >= 0 && i + dir[k] < m && j + dir[k + 1] >= 0 && j + dir[k + 1] < n && maze[i + dir[k]][j + dir[k + 1]] != 1) {
					i += dir[k];
					j += dir[k + 1];
				}
				if (visited[i][j] == false) {
					if (i == destination[0] && j == destination[1]) {
						return true;
					}
					visited[i][j] = true;
					q.push({ i, j });
				}
			}
		}
		return false;
	}
private:
	vector<int> dir = { 0, 1, 0, -1, 0 };
};
/*

505. The Maze II (Medium)

There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the ball's start position, the destination and the maze, find the shortest distance for the ball to stop at the destination. The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included). If the ball cannot stop at the destination, return -1.

The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.

Example 1

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (4, 4)

Output: 12
Explanation: One shortest way is : left -> down -> left -> down -> right -> down -> right.
			 The total distance is 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12.

Example 2

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (3, 2)

Output: -1
Explanation: There is no way for the ball to stop at the destination.

Note:
There is only one ball and one destination in the maze.
Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.

*/
class Solution {
public:
	int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
		queue<pair<int, int>> q;
		int m = maze.size(), n = maze[0].size();
		vector<vector<int>> visited(m, vector<int>(n, INT_MAX));
		q.push({ start[0], start[1] });
		visited[start[0]][start[1]] = 0;
		while (!q.empty()) {
			pair<int, int> p = q.front();
			q.pop();
			for (int k = 0; k < 4; k++) {
				int i = p.first, j = p.second;
				while (i + dir[k] >= 0 && i + dir[k] < m && j + dir[k + 1] >= 0 && j + dir[k + 1] < n && maze[i + dir[k]][j + dir[k + 1]] != 1) {
					i += dir[k];
					j += dir[k + 1];
				}
				int step = max(abs(i - p.first), abs(j - p.second));
				if (visited[p.first][p.second] + step < visited[i][j]) {
					visited[i][j] = visited[p.first][p.second] + step;
					q.push({ i, j });
				}
			}
		}
		return visited[destination[0]][destination[1]] == INT_MAX ? -1 : visited[destination[0]][destination[1]];
	}
private:
	vector<int> dir = { 0, 1, 0, -1, 0 };
};
/*

499. The Maze III (Hard)

There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up (u), down (d), left (l) or right (r), but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction. There is also a hole in this maze. The ball will drop into the hole if it rolls on to the hole.

Given the ball position, the hole position and the maze, find out how the ball could drop into the hole by moving the shortest distance. The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the hole (included). Output the moving directions by using 'u', 'd', 'l' and 'r'. Since there could be several different shortest ways, you should output the lexicographically smallest way. If the ball cannot reach the hole, output "impossible".

The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The ball and the hole coordinates are represented by row and column indexes.

Example 1

Input 1: a maze represented by a 2D array

0 0 0 0 0
1 1 0 0 1
0 0 0 0 0
0 1 0 0 1
0 1 0 0 0

Input 2: ball coordinate (rowBall, colBall) = (4, 3)
Input 3: hole coordinate (rowHole, colHole) = (0, 1)

Output: "lul"
Explanation: There are two shortest ways for the ball to drop into the hole.
The first way is left -> up -> left, represented by "lul".
The second way is up -> left, represented by 'ul'.
Both ways have shortest distance 6, but the first way is lexicographically smaller because 'l' < 'u'. So the output is "lul".

Example 2

Input 1: a maze represented by a 2D array

0 0 0 0 0
1 1 0 0 1
0 0 0 0 0
0 1 0 0 1
0 1 0 0 0

Input 2: ball coordinate (rowBall, colBall) = (4, 3)
Input 3: hole coordinate (rowHole, colHole) = (3, 0)
Output: "impossible"
Explanation: The ball cannot reach the hole.

Note:
There is only one ball and one hole in the maze.
Both the ball and hole exist on an empty space, and they will not be at the same position initially.
The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
The maze contains at least 2 empty spaces, and the width and the height of the maze won't exceed 30.

*/
class Solution {
public:
	string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
		queue<pair<int, int>> q;
		int m = maze.size(), n = maze[0].size();
		vector<vector<pair<int, string>>> visited(m, vector<pair<int, string>>(n, make_pair(INT_MAX, "impossible")));
		q.push({ ball[0], ball[1] });
		visited[ball[0]][ball[1]] = { 0,"" };
		while (!q.empty()) {
			pair<int, int> p = q.front();
			q.pop();
			for (int k = 0; k < 4; k++) {
				int i = p.first, j = p.second;
				string res = visited[i][j].second;
				res += s[k];
				int step = 0;
				while (i + dir[k].first >= 0 && i + dir[k].first < m && j + dir[k].second >= 0 && j + dir[k].second < n && maze[i + dir[k].first][j + dir[k].second] != 1) {
					i += dir[k].first;
					j += dir[k].second;
					step++;
					if (i == hole[0] && j == hole[1]) {
						if (visited[p.first][p.second].first + step < visited[i][j].first) {
							visited[i][j].first = visited[p.first][p.second].first + step;
							visited[i][j].second = res;
						}
						else if (visited[p.first][p.second].first + step == visited[i][j].first) {
							visited[i][j].second = res < visited[i][j].second ? res : visited[i][j].second;
						}
					}
				}
				if (visited[p.first][p.second].first + step < visited[i][j].first) {
					visited[i][j].first = visited[p.first][p.second].first + step;
					visited[i][j].second = res;
					q.push({ i, j });
				}
				else if (visited[p.first][p.second].first + step == visited[i][j].first && res < visited[i][j].second) {
					visited[i][j].second = res;
					q.push({ i, j });
				}
			}
		}
		return visited[hole[0]][hole[1]].second;
	}
private:
	vector<pair<int, int>> dir = { { 0, 1 },{ 1,0 },{ 0,-1 },{ -1, 0 } };
	vector<string> s = { "r", "d", "l", "u" };
};
/*

513. Find Bottom Left Tree Value (Medium)

Given a binary tree, find the leftmost value in the last row of the tree.

Example 1:
Input:

	2
   / \
  1   3

Output:
1
Example 2:
Input:

		1
	   / \
	  2   3
	 /   / \
	4   5   6
	   /
	  7

Output:
7
Note: You may assume the tree (i.e., the given root node) is not NULL.

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
	int findBottomLeftValue(TreeNode* root) {
		int res, maxlevel = 0;
		findBottomLeftValue(root, res, 1, maxlevel);
		return res;
	}
private:
	void findBottomLeftValue(TreeNode* root, int& res, int cur, int& maxlevel) {
		if (root == NULL) {
			return;
		}
		findBottomLeftValue(root->left, res, cur + 1, maxlevel);
		if (cur > maxlevel) {
			res = root->val;
			maxlevel = cur;
		}
		findBottomLeftValue(root->right, res, cur + 1, maxlevel);
	}
};
/*

515. Find Largest Value in Each Tree Row (Medium)

You need to find the largest value in each row of a binary tree.

Example:
Input:

		  1
		 / \
		3   2
	   / \   \
	  5   3   9

Output: [1, 3, 9]

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
	vector<int> largestValues(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<int> res;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			int _size = q.size();
			int temp;
			for (int i = 0; i < _size; i++) {
				temp = i == 0 ? q.front()->val : max(temp, q.front()->val);
				if (q.front()->left != NULL) {
					q.push(q.front()->left);
				}
				if (q.front()->right != NULL) {
					q.push(q.front()->right);
				}
				q.pop();
			}
			res.push_back(temp);
		}
		return res;
	}
};