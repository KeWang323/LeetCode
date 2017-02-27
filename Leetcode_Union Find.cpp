/*

128. Longest Consecutive Sequence (Hard)

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

*/
class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		int res = 0;
		unordered_map<int, int> mapping;
		for (int num : nums) {
			if (mapping.find(num) == mapping.end()) {
				int left = mapping.count(num - 1) ? mapping[num - 1] : 0;
				int right = mapping.count(num + 1) ? mapping[num + 1] : 0;
				mapping[num] = left + right + 1;
				res = max(res, mapping[num]);
				mapping[num - left] = mapping[num];
				mapping[num + right] = mapping[num];
			}
		}
		return res;
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

261. Graph Valid Tree (medium)

Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

For example:

Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.

Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.

Hint:

Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], what should your return? Is this case a valid tree?
According to the definition of tree on Wikipedia: ¡°a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.¡±
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