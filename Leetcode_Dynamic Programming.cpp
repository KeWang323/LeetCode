/*

10. Regular Expression Matching (Hard)

Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true

*/
class Solution {
public:
	bool isMatch(string s, string p) {
		int m = s.size(), n = p.size();
		vector<vector<bool>> t(m + 1, vector<bool>(n + 1, false));
		t[0][0] = true;
		for (int j = 1; j <= n; j++) {
			t[0][j] = j > 1 && p[j - 1] == '*' && t[0][j - 2] == true;
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (p[j - 1] == '*') {
					t[i][j] = t[i][j - 2] || (s[i - 1] == p[j - 2] || p[j - 2] == '.') && t[i - 1][j];
				}
				else {
					t[i][j] = t[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
				}
			}
		}
		return t.back().back();
	}
};
/*

32. Longest Valid Parentheses (Hard)

Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

*/
class Solution {
public:
	int longestValidParentheses(string s) {
		vector<bool> t(s.size(), false);
		stack<int> sta;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(') {
				sta.push(i);
			}
			else if (s[i] == ')' && !sta.empty()) {
				t[i] = true;
				t[sta.top()] = true;
				sta.pop();
			}
		}
		int glo = 0, cur = 0;
		for (int i = 0; i < s.size(); i++) {
			if (t[i] == true) {
				cur++;
			}
			else {
				cur = 0;
			}
			glo = max(glo, cur);
		}
		return glo;
	}
};
/*

44. Wildcard Matching (Hard)

Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false

*/
class Solution {
public:
	bool isMatch(string s, string p) {
		int m = s.size(), n = p.size();
		vector<vector<bool>> t(m + 1, vector<bool>(n + 1, false));
		t[0][0] = true;
		for (int j = 1; j <= n; j++) {
			t[0][j] = p[j - 1] == '*' && t[0][j - 1];
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (p[j - 1] != '*') {
					t[i][j] = t[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '?');
				}
				else {
					t[i][j] = t[i][j - 1] || t[i - 1][j];
				}
			}
		}
		return t[m][n];
	}
};
/*

53. Maximum Subarray (Medium)

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

click to show more practice.

More practice:
If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.

*/
class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int res = nums[0], cur = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			if (cur > 0) {
				cur += nums[i];
			}
			else {
				cur = nums[i];
			}
			res = max(res, cur);
		}
		return res;
	}
};
/*

62. Unique Paths (Medium)

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

*/
class Solution {
public:
	int uniquePaths(int m, int n) {
		vector<int> t(n, 1);
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				t[j] += t[j - 1];
			}
		}
		return t.back();
	}
};
/*

63. Unique Paths II (Medium)

Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.

Note: m and n will be at most 100.

*/
class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		vector<int> t(obstacleGrid[0].size(), 0);
		t[0] = 1;
		for (int i = 0; i < obstacleGrid.size(); i++) {
			for (int j = 0; j < obstacleGrid[0].size(); j++) {
				if (obstacleGrid[i][j] == 1) {
					t[j] = 0;
				}
				else if (j > 0) {
					t[j] += t[j - 1];
				}
			}
		}
		return t.back();
	}
};
/*

64. Minimum Path Sum (Medium)

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

*/
class Solution {
public:
	int minPathSum(vector<vector<int>>& grid) {
		if (grid.empty()) {
			return 0;
		}
		vector<int> t(grid[0].size(), INT_MAX);
		t[0] = 0;
		for (int i = 0; i < grid.size(); i++) {
			t[0] += grid[i][0];
			for (int j = 1; j < grid[0].size(); j++) {
				t[j] = min(t[j], t[j - 1]) + grid[i][j];
			}
		}
		return t.back();
	}
};
/*

70. Climbing Stairs (Easy)

You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

*/
class Solution {
public:
	int climbStairs(int n) {
		if (n == 1) {
			return 1;
		}
		int prepre = 1, pre = 2;
		while (n-- > 2) {
			int temp = prepre;
			prepre = pre;
			pre += temp;
		}
		return pre;
	}
};
/*

72. Edit Distance (Hard)

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character

*/
class Solution {
public:
	int minDistance(string word1, string word2) {
		vector<vector<int>> t(word1.size() + 1, vector<int>(word2.size() + 1, 0));
		for (int i = 0; i < t.size(); i++) {
			for (int j = 0; j < t[0].size(); j++) {
				if (i == 0) {
					t[0][j] = j;
				}
				else if (j == 0) {
					t[i][0] = i;
				}
				else if (word1[i - 1] == word2[j - 1]) {
					t[i][j] = t[i - 1][j - 1];
				}
				else {
					t[i][j] = min(t[i - 1][j], min(t[i][j - 1], t[i - 1][j - 1])) + 1;
				}
			}
		}
		return t.back().back();
	}
};
/*

85. Maximal Rectangle (Hard)

Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 6.

*/
class Solution {
public:
	int maximalRectangle(vector<vector<char>>& matrix) {
		if (matrix.empty()) {
			return 0;
		}
		int maxRec = 0;
		vector<int> height(matrix[0].size());
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				height[j] = matrix[i][j] == '0' ? 0 : height[j] + 1;
			}
			maxRec = max(maxRec, largestRectangleArea(height));
		}
		return maxRec;
	}
private:
	int largestRectangleArea(const vector<int>& heights) {
		stack<int> s;
		int maxSize = 0;
		for (int i = 0; i <= heights.size(); i++) {
			int cur = i == heights.size() ? 0 : heights[i];
			while (!s.empty() && heights[s.top()] >= cur) {
				int height = heights[s.top()];
				s.pop();
				int left = s.empty() ? 0 : s.top() + 1;
				maxSize = max(maxSize, (i - left) * height);
			}
			s.push(i);
		}
		return maxSize;
	}
};
/*

87. Scramble String (Hard)

Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

	great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
		   / \
		  a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

	rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
		   / \
		  a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

	rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
	   / \
	  t   a
We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.

*/
class Solution {
public:
	bool isScramble(string s1, string s2) {
		if (s1 == s2) {
			return true;
		}
		int t[26] = { 0 };
		for (int i = 0; i < s1.size(); i++) {
			t[s1[i] - 'a']++;
			t[s2[i] - 'a']--;
		}
		for (int i = 0; i < s2.size(); i++) {
			if (t[s2[i] - 'a'] < 0) {
				return false;
			}
		}
		for (int i = 1; i < s1.size(); i++) {
			if (isScramble(s1.substr(0, i), s2.substr(0, i)) && isScramble(s1.substr(i), s2.substr(i))) {
				return true;
			}
			if (isScramble(s1.substr(0, i), s2.substr(s1.size() - i)) && isScramble(s1.substr(i), s2.substr(0, s1.size() - i))) {
				return true;
			}
		}
		return false;
	}
};
/*

91. Decode Ways (Medium)

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

*/
class Solution {
public:
	int numDecodings(string s) {
		if (s.empty() || s[0] == '0') {
			return 0;
		}
		int t1 = 1, t2 = 1;
		for (int i = 2; i <= s.size(); i++) {
			int temp = (int)(s[i - 1] != '0') * t2 + (int)(s[i - 2] == '1' || s[i - 2] == '2' && s[i - 1] < '7') * t1;
			t1 = t2;
			t2 = temp;
		}
		return t2;
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

97. Interleaving String (Hard)

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.

*/
class Solution {
public:
	bool isInterleave(string s1, string s2, string s3) {
		if (s1.size() + s2.size() != s3.size()) {
			return false;
		}
		bool t[s1.size() + 1][s2.size() + 1] = { false };
		for (int i = 0; i <= s1.size(); i++) {
			for (int j = 0; j <= s2.size(); j++) {
				if (i == 0 && j == 0) {
					t[0][0] = true;
				}
				else if (i == 0) {
					t[0][j] = t[0][j - 1] && s2[j - 1] == s3[j - 1];
				}
				else if (j == 0) {
					t[i][0] = t[i - 1][0] && s1[i - 1] == s3[i - 1];
				}
				else {
					t[i][j] = t[i - 1][j] && s1[i - 1] == s3[i + j - 1] || t[i][j - 1] && s2[j - 1] == s3[i + j - 1];
				}
			}
		}
		return t[s1.size()][s2.size()];
	}
};
class Solution {
public:
	bool isInterleave(string s1, string s2, string s3) {
		if (s1.size() + s2.size() != s3.size()) {
			return false;
		}
		bool t[s2.size() + 1] = { false };
		for (int i = 0; i <= s1.size(); i++) {
			for (int j = 0; j <= s2.size(); j++) {
				if (i == 0 && j == 0) {
					t[0] = true;
				}
				else if (i == 0) {
					t[j] = t[j - 1] && s2[j - 1] == s3[j - 1];
				}
				else if (j == 0) {
					t[0] = t[0] && s1[i - 1] == s3[i - 1];
				}
				else {
					t[j] = t[j] && s1[i - 1] == s3[i + j - 1] || t[j - 1] && s2[j - 1] == s3[i + j - 1];
				}
			}
		}
		return t[s2.size()];
	}
};
/*

115. Distinct Subsequences (Hard)

Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.

*/
class Solution {
public:
	int numDistinct(string s, string t) {
		if (t.size() > s.size()) {
			return 0;
		}
		vector<vector<int>> ta(t.size() + 1, vector<int>(s.size() + 1, 0));
		for (int j = 0; j <= s.size(); j++) {
			ta[0][j] = 1;
		}
		for (int i = 1; i <= t.size(); i++) {
			for (int j = 1; j <= s.size(); j++) {
				if (t[i - 1] == s[j - 1]) {
					ta[i][j] = ta[i - 1][j - 1] + ta[i][j - 1];
				}
				else {
					ta[i][j] = ta[i][j - 1];
				}
			}
		}
		return ta.back().back();
	}
};
/*

120. Triangle (Medium)

Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
	 [2],
	[3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.

*/
class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		for (int i = triangle.size() - 2; i >= 0; i--) {
			for (int j = 0; j < triangle[i].size(); j++) {
				triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
			}
		}
		return triangle[0][0];
	}
};
/*

121. Best Time to Buy and Sell Stock (Easy)

Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Example 1:
Input: [7, 1, 5, 3, 6, 4]
Output: 5

max. difference = 6-1 = 5 (not 7-1 = 6, as selling price needs to be larger than buying price)
Example 2:
Input: [7, 6, 4, 3, 1]
Output: 0

In this case, no transaction is done, i.e. max profit = 0.

*/
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		if (prices.empty()) {
			return 0;
		}
		int res = 0, min = prices[0];
		for (int i = 1; i < prices.size(); i++) {
			if (prices[i] >= min) {
				res = max(res, prices[i] - min);
			}
			else {
				min = prices[i];
			}
		}
		return res;
	}
};
/*

123. Best Time to Buy and Sell Stock III (Hard)

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

*/
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		if (prices.size() < 2) {
			return 0;
		}
		vector<int> t(prices.size(), 0);
		int buy = prices[0], sell = prices.back(), res = 0;
		for (int i = 1; i < t.size(); i++) {
			t[i] = max(t[i - 1], prices[i] - buy);
			buy = min(buy, prices[i]);
		}
		for (int i = t.size() - 2; i >= 0; i--) {
			res = max(res, sell - prices[i] + t[i]);
			sell = max(sell, prices[i]);
		}
		return res;
	}
};
/*

132. Palindrome Partitioning II (Hard)

Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.

*/
class Solution {
public:
	int minCut(string s) {
		int _size = s.size();
		vector<vector<bool>> t(_size, vector<bool>(_size, false));
		vector<int> t2(_size + 1);
		for (int i = 0; i <= _size; i++) {
			t2[i] = i - 1;
		}
		for (int j = 1; j < _size; j++) {
			for (int i = j; i >= 0; i--) {
				if (s[i] == s[j] && (j - i < 3 || t[i + 1][j - 1])) {
					t[i][j] = true;
					t2[j + 1] = min(t2[j + 1], 1 + t2[i]);
				}
			}
		}
		return t2.back();
	}
};
/*

139. Word Break (Medium)

Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

*/
class Solution {
public:
	bool wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> set;
		for (string str : wordDict) {
			set.insert(str);
		}
		vector<bool> t(s.size(), false);
		t[0] = set.find(s.substr(0, 1)) != set.end();
		for (int i = 1; i < s.size(); i++) {
			t[i] = set.find(s.substr(0, i + 1)) != set.end();
			if (t[i] == true) {
				continue;
			}
			for (int j = 0; j < i; j++) {
				if (t[j] == true && set.find(s.substr(j + 1, i - j)) != set.end()) {
					t[i] = true;
					break;
				}
			}
		}
		return t.back();
	}
};
/*

140. Word Break II (Hard)

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. You may assume the dictionary does not contain duplicate words.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

*/
class Solution {
public:
	vector<string> wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> set;
		for (string str : wordDict) {
			set.insert(str);
		}
		return wordBreak(s, set);
	}
private:
	unordered_map<string, vector<string>> mapping;
	vector<string> wordBreak(string s, unordered_set<string>& set) {
		if (mapping.find(s) != mapping.end()) {
			return mapping[s];
		}
		vector<string> result;
		if (set.find(s) != set.end()) {
			result.push_back(s);
		}
		for (int i = 1; i < s.size(); i++) {
			string word = s.substr(i);
			if (set.find(word) != set.end()) {
				string rem = s.substr(0, i);
				vector<string> prev = combine(wordBreak(rem, set), word);
				result.insert(result.end(), prev.begin(), prev.end());
			}
		}
		mapping[s] = result;
		return result;
	}
	vector<string> combine(vector<string> prev, string word) {
		for (int i = 0; i < prev.size(); i++) {
			prev[i] += " " + word;
		}
		return prev;
	}
};
/*

152. Maximum Product Subarray (Medium)

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.

*/
class Solution {
public:
	int maxProduct(vector<int>& nums) {
		if (nums.empty()) {
			return 0;
		}
		int cur_max = nums[0], cur_min = nums[0], glo_max = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			int pre_max = cur_max, pre_min = cur_min;
			cur_max = max(nums[i], max(pre_max * nums[i], pre_min * nums[i]));
			cur_min = min(nums[i], min(pre_max * nums[i], pre_min * nums[i]));
			glo_max = max(glo_max, cur_max);
		}
		return glo_max;
	}
};
/*

174. Dungeon Game (Hard)

The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.


Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

*/
class Solution {
public:
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		vector<int> t(dungeon[0].size(), 0);
		for (int i = dungeon.size() - 1; i >= 0; i--) {
			for (int j = dungeon[0].size() - 1; j >= 0; j--) {
				if (i == dungeon.size() - 1 && j == dungeon[0].size() - 1) {
					t[j] = update(dungeon[i][j], 1);
				}
				else if (i == dungeon.size() - 1) {
					t[j] = update(dungeon[i][j], t[j + 1]);
				}
				else if (j == dungeon[0].size() - 1) {
					t[j] = update(dungeon[i][j], t[j]);
				}
				else {
					t[j] = min(update(dungeon[i][j], t[j + 1]), update(dungeon[i][j], t[j]));
				}
			}
		}
		return t[0];
	}
private:
	int update(int cur, int pre) {
		if (cur < 0) {
			return -cur + pre;
		}
		else if (cur >= pre) {
			return 1;
		}
		else {
			return pre - cur;
		}
		return 0;
	}
};
/*

188. Best Time to Buy and Sell Stock IV (Hard)

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

*/
class Solution {
public:
	int maxProfit(int k, vector<int>& prices) {
		if (prices.size() < 2) {
			return 0;
		}
		int res = 0;
		if (k >= prices.size() / 2) {
			for (int i = 1; i < prices.size(); i++) {
				if (prices[i] > prices[i - 1]) {
					res += prices[i] - prices[i - 1];
				}
			}
		}
		else {
			vector<int> cur(k + 1), glo(k + 1);
			for (int i = 0; i < prices.size() - 1; i++) {
				int increase = prices[i + 1] - prices[i];
				for (int j = k; j >= 1; j--) {
					cur[j] = max(glo[j - 1] + max(increase, 0), cur[j] + increase);
					glo[j] = max(glo[j], cur[j]);
				}
			}
			res = glo.back();
		}
		return res;
	}
};
/*

198. House Robber (Easy)

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

*/
class Solution {
public:
	int rob(vector<int>& nums) {
		if (nums.empty()) {
			return 0;
		}
		int pre = 0, res = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			int temp = res;
			res = max(res, nums[i] + pre);
			pre = temp;
		}
		return res;
	}
};
/*

213. House Robber II (Medium)

Note: This is an extension of House Robber.

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

*/
class Solution {
public:
	int rob(vector<int>& nums) {
		if (nums.size() < 2) {
			return nums.size() == 1 ? nums[0] : 0;
		}
		return max(rob(nums, 0, nums.size() - 2), rob(nums, 1, nums.size() - 1));
	}
private:
	int rob(vector<int>& nums, int l, int r) {
		int pre = 0, cur = nums[l];
		for (int i = l + 1; i <= r; i++) {
			int temp = max(pre + nums[i], cur);
			pre = cur;
			cur = temp;
		}
		return cur;
	}
};
/*

221. Maximal Square (Medium)

Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.

*/
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		if (matrix.empty()) {
			return 0;
		}
		int res = 0;
		vector<vector<int>> t(matrix.size(), vector<int>(matrix[0].size(), 0));
		for (int i = 0; i < t.size(); i++) {
			for (int j = 0; j < t[0].size(); j++) {
				if (i == 0 || j == 0) {
					t[i][j] = matrix[i][j] - '0';
				}
				else if (matrix[i][j] == '1') {
					t[i][j] = min(t[i - 1][j - 1], min(t[i - 1][j], t[i][j - 1])) + 1;
				}
				res = max(res, t[i][j]);
			}
		}
		return res * res;
	}
};
/*

256. Paint House (Medium)

There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

*/
class Solution {
public:
	int minCost(vector<vector<int>>& costs) {
		if (costs.size() == 0 || costs[0].size() == 0) {
			return 0;
		}
		for (int i = 1; i < costs.size(); i++) {
			for (int j = 0; j < 3; j++) {
				if (j == 0) {
					costs[i][0] += min(costs[i - 1][1], costs[i - 1][2]);
				}
				else if (j == 1) {
					costs[i][1] += min(costs[i - 1][0], costs[i - 1][2]);
				}
				else {
					costs[i][2] += min(costs[i - 1][0], costs[i - 1][1]);
				}
			}
		}
		return min(costs.back()[0], min(costs.back()[1], costs.back()[2]));
	}
};
/*

264. Ugly Number II (Medium)

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number, and n does not exceed 1690.

Hint:

The naive approach is to call isUgly for every number until you reach the nth one. Most numbers are not ugly. Try to focus your effort on generating only the ugly ones.
An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly number.
The key is how to maintain the order of the ugly numbers. Try a similar approach of merging from three sorted lists: L1, L2, and L3.
Assume you have Uk, the kth ugly number. Then Uk+1 must be Min(L1 * 2, L2 * 3, L3 * 5).

*/
class Solution {
public:
	int nthUglyNumber(int n) {
		if (n < 0) {
			return 0;
		}
		vector<int> table(1, 1);
		int i2 = 0, i3 = 0, i5 = 0;
		for (int k = 1; k < n; k++) {
			int tmp = min(table[i2] * 2, min(table[i3] * 3, table[i5] * 5));
			if (tmp % 2 == 0) {
				i2++;
			}
			if (tmp % 3 == 0) {
				i3++;
			}
			if (tmp % 5 == 0) {
				i5++;
			}
			table.push_back(tmp);
		}
		return table[n - 1];
	}
};
/*

276. Paint Fence (Easy)

There is a fence with n posts, each post can be painted with one of the k colors.

You have to paint all the posts such that no more than two adjacent fence posts have the same color.

Return the total number of ways you can paint the fence.

Note:
n and k are non-negative integers.

*/
class Solution {
public:
	int numWays(int n, int k) {
		if (n == 0 || k == 0) {
			return 0;
		}
		pair<int, int> p1 = make_pair(0, k), p2;
		for (int i = 2; i <= n; i++) {
			if (i & 1) {
				p1.first = p2.second;
				p1.second = (p2.first + p2.second) * (k - 1);
			}
			else {
				p2.first = p1.second;
				p2.second = (p1.first + p1.second) * (k - 1);
			}
		}
		return n & 1 ? p1.first + p1.second : p2.first + p2.second;
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

300. Longest Increasing Subsequence (Medium)

Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?

*/
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		int res = 0;
		int table[nums.size()];
		for (int i = 0; i < nums.size(); i++) {
			table[i] = 1;
			for (int j = 0; j < i; j++)
				if (nums[j] < nums[i]) table[i] = max(table[i], table[j] + 1);
			res = max(res, table[i]);
		}
		return res;
	}
};
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty()) {
			return 0;
		}
		vector<int> tail = { nums[0] };
		for (auto n : nums) {
			if (n <= tail[0]) {
				tail[0] = n;
			}
			else if (n > tail.back()) {
				tail.push_back(n);
			}
			else {
				int left = 0, right = tail.size() - 1;
				int res = left;
				while (left <= right) {
					int mid = left + (right - left) / 2;
					if (tail[mid] >= n) {
						res = mid;
						right = mid - 1;
					}
					else {
						left = mid + 1;
					}
				}
				tail[res] = n;
			}
		}
		return tail.size();
	}
};
/*

303. Range Sum Query - Immutable (Easy)

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3

Note:
You may assume that the array does not change.
There are many calls to sumRange function.

*/
class NumArray {
public:
	vector<int> t;
	NumArray(vector<int> &nums) {
		t = nums;
		for (int i = 1; i < nums.size(); i++) {
			t[i] += t[i - 1];
		}
	}

	int sumRange(int i, int j) {
		if (i == 0) {
			return t[j];
		}
		else {
			return t[j] - t[i - 1];
		}
	}
};
// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);
/*

304. Range Sum Query 2D - Immutable (Medium)

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.

*/
class NumMatrix {
public:
	vector<vector<int>> table;
	NumMatrix(vector<vector<int>> &matrix) {
		int row = matrix.size(), col = row > 0 ? matrix[0].size() : 0;
		table = vector<vector<int>>(row + 1, vector<int>(col + 1, 0));
		for (int i = 1; i <= row; i++) {
			for (int j = 1; j <= col; j++) {
				table[i][j] = matrix[i - 1][j - 1] + table[i - 1][j] + table[i][j - 1] - table[i - 1][j - 1];
			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		return table[row2 + 1][col2 + 1] - table[row2 + 1][col1] - table[row1][col2 + 1] + table[row1][col1];
	}
};


// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.sumRegion(1, 2, 3, 4);
/*

309. Best Time to Buy and Sell Stock with Cooldown (Medium)

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like
(ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]

*/
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int _size = prices.size();
		if (_size < 2) return 0;
		vector<int> table(_size, 0);
		int temp = -prices[0];
		for (int i = 1; i < _size; i++) {
			table[i] = max(table[i], max(table[i - 1], prices[i] + temp));
			if (i > 1) temp = max(temp, table[i - 2] - prices[i]);
			else temp = max(temp, -prices[i]);
		}
		return table.back();
	}
};
/*

322. Coin Change (Medium)

You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.

*/
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> t(amount + 1, amount + 1);
		t[0] = 0;
		for (int i = 1; i <= amount; i++) {
			for (int j = 0; j < coins.size(); j++) {
				if (i >= coins[j]) {
					t[i] = min(t[i], t[i - coins[j]] + 1);
				}
			}
		}
		return t.back() == amount + 1 ? -1 : t.back();
	}
};
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		sort(coins.begin(), coins.end());
		return coinChange(coins, amount, coins.size() - 1, 0, *(new int(INT_MAX)));
	}
	int coinChange(const vector<int>& coins, int amount, int index, int cur, int &cand) {
		if (amount == 0) {
			return cand = cur;
		}
		if (index < 0) {
			return -1;
		}
		int flag = 0, n = amount / coins[index];
		if (n + cur >= cand) {
			return -1;
		}
		for (int i = n; i >= 0; i--) {
			if (coinChange(coins, amount - i*coins[index], index - 1, cur + i, cand) != -1) {
				flag = 1;
			}
		}
		if (flag) {
			return cand;
		}
		return -1;
	}
};
/*

338. Counting Bits (Medium)

Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.

Example:
For num = 5 you should return [0,1,1,2,1,2].

Follow up:

It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like __builtin_popcount in c++ or in any other language.
Hint:

You should make use of what you have produced already.
Divide the numbers in ranges like [2-3], [4-7], [8-15] and so on. And try to generate new range from previous.
Or does the odd/even status of the number help you in calculating the number of 1s?

*/
class Solution {
public:
	vector<int> countBits(int num) {
		vector<int> t(num + 1);
		for (int i = 1; i <= num; i++) {
			t[i] = 1 + t[i & (i - 1)];
		}
		return t;
	}
};
/*

343. Integer Break (Medium)

Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.

For example, given n = 2, return 1 (2 = 1 + 1); given n = 10, return 36 (10 = 3 + 3 + 4).

Note: You may assume that n is not less than 2 and not larger than 58.

Hint:

There is a simple O(n) solution to this problem.
You may check the breaking results of n ranging from 7 to 10 to discover the regularities.

*/
class Solution {
public:
	int integerBreak(int n) {
		if (n < 3) {
			return 1;
		}
		vector<int> t(n + 1, 1);
		for (int i = 3; i <= n; i++) {
			for (int j = 1; j < i; j++) {
				t[i] = max(t[i], max(t[j], j) * (i - j));
			}
		}
		return t.back();
	}
};
/*

357. Count Numbers with Unique Digits (Medium)

Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10n.

Example:
Given n = 2, return 91. (The answer should be the total numbers in the range of 0 ≤ x < 100, excluding [11,22,33,44,55,66,77,88,99])

Hint:

A direct way is to use the backtracking approach.
Backtracking should contains three states which are (the current number, number of steps to get that number and a bitmask which represent which number is marked as visited so far in the current number). Start with state (0,0,0) and count all valid number till we reach number of steps equals to 10n.
This problem can also be solved using a dynamic programming approach and some knowledge of combinatorics.
Let f(k) = count of numbers with unique digits with length equals k.
f(1) = 10, ..., f(k) = 9 * 9 * 8 * ... (9 - k + 2) [The first factor is 9 because a number cannot start with 0].

*/
class Solution {
public:
	int countNumbersWithUniqueDigits(int n) {
		if (n == 0) {
			return 1;
		}
		else if (n > 10) {
			return 0;
		}
		int res = 10, pre = 9;
		for (int i = 1; i < n; i++) {
			pre *= (10 - i);
			res += pre;
		}
		return res;
	}
};
/*

361. Bomb Enemy (Medium)

Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
Note that you can only put the bomb at an empty cell.

Example:
For the given grid

0 E 0 0
E 0 W E
0 E 0 0

return 3. (Placing a bomb at (1,1) kills 3 enemies)

*/
class Solution {
public:
	int maxKilledEnemies(vector<vector<char>>& grid) {
		if (grid.size() == 0 || grid[0].size() == 0) {
			return 0;
		}
		int col = grid[0].size(), row = grid.size();
		vector<vector<int>> vrl(row, vector<int>(col)), vbu(row, vector<int>(col));
		for (int j = col - 1; j >= 0; j--) {
			for (int i = row - 1; i >= 0; i--) {
				if (grid[i][j] != 'W') {
					int e = grid[i][j] == 'E';
					vrl[i][j] = j == col - 1 ? e : e + vrl[i][j + 1];
					vbu[i][j] = i == row - 1 ? e : e + vbu[i + 1][j];
				}
			}
		}
		vector<int> vlr(row), vub(col);
		int res = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (grid[i][j] == '0') {
					res = max(vlr[i] + vrl[i][j] + vub[j] + vbu[i][j], res);
				}
				else {
					vub[j] = grid[i][j] == 'W' ? 0 : vub[j] + 1;
					vlr[i] = grid[i][j] == 'W' ? 0 : vlr[i] + 1;
				}
			}
		}
		return res;
	}
};
/*

368. Largest Divisible Subset (Medium)

Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0.

If there are multiple solutions, return any subset is fine.

Example 1:

nums: [1,2,3]

Result: [1,2] (of course, [1,3] will also be ok)
Example 2:

nums: [1,2,4,8]

Result: [1,2,4,8]

*/
class Solution {
public:
	vector<int> largestDivisibleSubset(vector<int>& nums) {
		int _size = nums.size();
		if (!_size) return nums;
		sort(nums.begin(), nums.end());
		vector<pair<int, int>> table(1, make_pair(1, -1));
		int globalMax = 1, index = 0;
		for (int i = 1; i < _size; i++) {
			int tempmax = 1, pre_index = -1;
			for (int j = i - 1; j >= 0; j--) {
				if (nums[i] % nums[j] == 0 && table[j].first >= tempmax) {
					tempmax = table[j].first + 1;
					pre_index = j;
				}
			}
			table.emplace_back(tempmax, pre_index);
			if (tempmax > globalMax) {
				globalMax = tempmax;
				index = i;
			}
		}
		vector<int> res;
		for (int i = 0; i < globalMax; i++, index = table[index].second)
			res.insert(res.begin(), nums[index]);
		return res;
	}
};
/*

375. Guess Number Higher or Lower II (Medium)

We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I'll tell you whether the number I picked is higher or lower.

However, when you guess a particular number x, and you guess wrong, you pay $x. You win the game when you guess the number I picked.

Example:

n = 10, I pick 8.

First round:  You guess 5, I tell you that it's higher. You pay $5.
Second round: You guess 7, I tell you that it's higher. You pay $7.
Third round:  You guess 9, I tell you that it's lower. You pay $9.

Game over. 8 is the number I picked.

You end up paying $5 + $7 + $9 = $21.
Given a particular n ≥ 1, find out how much money you need to have to guarantee a win.

Hint:

The best strategy to play the game is to minimize the maximum loss you could possibly face. Another strategy is to minimize the expected loss. Here, we are interested in the first scenario.
Take a small example (n = 3). What do you end up paying in the worst case?
Check out this article if you're still stuck.
The purely recursive implementation of minimax would be worthless for even a small n. You MUST use dynamic programming.
As a follow-up, how would you modify your code to solve the problem of minimizing the expected loss, instead of the worst-case loss?

*/
class Solution {
public:
	int getMoneyAmount(int n) {
		vector<vector<int>> dp(n + 1, vector<int>(n + 3));
		for (int i = 1; i <= n; i++) {
			dp[i][i] = 0;
			dp[i][i + 1] = i;
			dp[i][i + 2] = i + 1;
		}
		for (int nn = 3; nn <= n; nn++) {
			for (int m = 1; m <= n - nn; m++) {
				int mini = 0x7fffffff;
				for (int i = m + 2; i < m + nn; i++) {
					int l = dp[m][i - 1];
					int r = dp[i + 1][m + nn];
					mini = min(mini, max(l, r) + i);
				}
				dp[m][m + nn] = mini;
			}
		}
		return dp[1][n];
	}
};
/*

376. Wiggle Subsequence (Medium)

A sequence of numbers is called a wiggle sequence if the differences between successive
numbers strictly alternate between positive and negative. The first difference (if one
exists) may be either positive or negative. A sequence with fewer than two elements is
trivially a wiggle sequence.

For example, [1,7,4,9,2,5] is a wiggle sequence because the differences (6,-3,5,-7,3)
are alternately positive and negative. In contrast, [1,4,7,2,5] and [1,7,4,5,5] are not
wiggle sequences, the first because its first two differences are positive and the second
because its last difference is zero.

Given a sequence of integers, return the length of the longest subsequence that is a
wiggle sequence. A subsequence is obtained by deleting some number of elements (eventually,
 also zero) from the original sequence, leaving the remaining elements in their original order.

Examples:
Input: [1,7,4,9,2,5]
Output: 6
The entire sequence is a wiggle sequence.

Input: [1,17,5,10,13,15,10,5,16,8]
Output: 7
There are several subsequences that achieve this length. One is [1,17,10,13,10,16,8].

Input: [1,2,3,4,5,6,7,8,9]
Output: 2
Follow up:
Can you do it in O(n) time?
*/
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		int _size = nums.size(), p = 1, n = 1;
		for (int i = 1; i < _size; i++) {
			if (nums[i] > nums[i - 1]) p = n + 1;
			else if (nums[i] < nums[i - 1]) n = p + 1;
		}
		return _size == 0 ? 0 : max(p, n);
	}
};
/*

377. Combination Sum IV (Medium)

Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.

Example:

nums = [1, 2, 3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.
Follow up:
What if negative numbers are allowed in the given array?
How does it change the problem?
What limitation we need to add to the question to allow negative numbers?

*/
class Solution {
public:
	int combinationSum4(vector<int>& nums, int target) {
		int t[target + 1] = { 0 };
		t[0] = 1;
		for (int i = 1; i <= target; i++) {
			for (int num : nums) {
				if (i >= num) {
					t[i] += t[i - num];
				}
			}
		}
		return t[target];
	}
};
/*

392. Is Subsequence (Medium)

Given a string s and a string t, check if s is subsequence of t.

You may assume that there is only lower case English letters in both s and t. t is potentially
a very long (length ~= 500,000) string, and s is a short string (<=100).

A subsequence of a string is a new string which is formed from the original string by deleting
some (can be none) of the characters without disturbing the relative positions of the remaining
characters. (ie, "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
s = "abc", t = "ahbgdc"

Return true.

Example 2:
s = "axc", t = "ahbgdc"

Return false.

Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one
by one to see if T has its subsequence. In this scenario, how would you change your code?

*/
class Solution {
public:
	bool isSubsequence(string s, string t) {
		int i = 0;
		for (int j = 0; j < t.size(); j++) {
			if (s[i] == t[j]) {
				i++;
			}
		}
		return i == s.size();
	}
};
/*

413. Arithmetic Slices (Medium)

A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequence:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.

1, 1, 2, 5, 7

A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.

A slice (P, Q) of array A is called arithmetic if the sequence:
A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.

The function should return the number of arithmetic slices in the array A.


Example:

A = [1, 2, 3, 4]

return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.

*/
class Solution {
public:
	int numberOfArithmeticSlices(vector<int>& A) {
		int cur = 0, sum = 0;
		for (int i = 2; i < A.size(); i++) {
			if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
				cur++;
				sum += cur;
			}
			else {
				cur = 0;
			}
		}
		return sum;
	}
};
/*

416. Partition Equal Subset Sum (Medium)

Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Note:
Each of the array element will not exceed 100.
The array size will not exceed 200.
Example 1:

Input: [1, 5, 11, 5]

Output: true

Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:

Input: [1, 2, 3, 5]

Output: false

Explanation: The array cannot be partitioned into equal sum subsets.

*/
class Solution {
public:
	bool canPartition(vector<int>& nums) {
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum & 1) {
			return false;
		}
		sum >>= 1;
		bool t[sum + 1] = { false };
		t[0] = true;
		for (int i = 0; i < nums.size(); i++) {
			for (int j = sum; j >= nums[i]; j--) {
				if (t[j] == true) {
					break;
				}
				t[j] |= t[j - nums[i]];
			}
		}
		return t[sum];
	}
};
/*

474. Ones and Zeroes (Medium)

In the computer world, use restricted resource you have to generate maximum benefit is what we always want to pursue.

For now, suppose you are a dominator of m 0s and n 1s respectively. On the other hand, there is an array with strings consisting of only 0s and 1s.

Now your task is to find the maximum number of strings that you can form with given m 0s and n 1s. Each 0 and 1 can be used at most once.

Note:
The given numbers of 0s and 1s will both not exceed 100
The size of given string array won't exceed 600.
Example 1:
Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
Output: 4

Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are “10,”0001”,”1”,”0”
Example 2:
Input: Array = {"10", "0", "1"}, m = 1, n = 1
Output: 2

Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".

*/
class Solution {
public:
	int findMaxForm(vector<string>& strs, int m, int n) {
		vector<vector<int>> t(m + 1, vector<int>(n + 1, 0));
		for (string& s : strs) {
			int nz = 0, no = 0;
			for (char& cha : s) {
				if (cha == '0') {
					nz++;
				}
				else {
					no++;
				}
			}
			for (int i = m; i >= nz; i--) {
				for (int j = n; j >= no; j--) {
					t[i][j] = max(t[i][j], t[i - nz][j - no] + 1);
				}
			}
		}
		return t.back().back();
	}
};
/*

486. Predict the Winner (Medium)

Given an array of scores that are non-negative integers. Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on. Each time a player picks a number, that number will not be available for the next player. This continues until all the scores have been chosen. The player with the maximum score wins.

Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.

Example 1:
Input: [1, 5, 2]
Output: False
Explanation: Initially, player 1 can choose between 1 and 2.
If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2).
So, final score of player 1 is 1 + 2 = 3, and player 2 is 5.
Hence, player 1 will never be the winner and you need to return False.
Example 2:
Input: [1, 5, 233, 7]
Output: True
Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
Note:
1 <= length of the array <= 20.
Any scores in the given array are non-negative integers and will not exceed 10,000,000.
If the scores of both players are equal, then player 1 is still the winner.

*/
class Solution {
public:
	bool PredictTheWinner(vector<int>& nums) {
		if (nums.size() & 1 == 0) {
			return true;
		}
		vector<vector<int>> t(nums.size(), vector<int>(nums.size(), -1));
		int myBest = PredictTheWinner(nums, t, 0, nums.size() - 1);
		return 2 * myBest >= accumulate(nums.begin(), nums.end(), 0);
	}
private:
	int PredictTheWinner(const vector<int>& nums, vector<vector<int>>& t, int i, int j) {
		if (i > j) {
			return 0;
		}
		else if (t[i][j] != -1) {
			return t[i][j];
		}
		int pick_i = nums[i] + min(PredictTheWinner(nums, t, i + 1, j - 1), PredictTheWinner(nums, t, i + 2, j));
		int pick_j = nums[j] + min(PredictTheWinner(nums, t, i + 1, j - 1), PredictTheWinner(nums, t, i, j - 2));
		t[i][j] = max(pick_i, pick_j);
		return t[i][j];
	}
};
/*

516. Longest Palindromic Subsequence (Medium)

Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000.

Example 1:
Input:

"bbbab"
Output:
4
One possible longest palindromic subsequence is "bbbb".
Example 2:
Input:

"cbbd"
Output:
2
One possible longest palindromic subsequence is "bb".

*/
class Solution {
public:
	int longestPalindromeSubseq(string s) {
		vector<vector<int>> t(s.size(), vector<int>(s.size(), 0));
		for (int i = s.size() - 1; i >= 0; i--) {
			t[i][i] = 1;
			for (int j = i + 1; j < s.size(); j++) {
				if (s[i] == s[j]) {
					t[i][j] = t[i + 1][j - 1] + 2;
				}
				else {
					t[i][j] = max(t[i + 1][j], t[i][j - 1]);
				}
			}
		}
		return t[0].back();
	}
};