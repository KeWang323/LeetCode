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