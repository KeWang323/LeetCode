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

17. Letter Combinations of a Phone Number (Medium)

Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.

*/
class Solution {
public:
	vector<string> letterCombinations(string digits) {
		if (digits.empty()) {
			return{};
		}
		vector<string> t = { "", "","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" }, res;
		string res_sub;
		letterCombinations(res, res_sub, 0, digits, t);
		return res;
	}
private:
	void letterCombinations(vector<string>& res, string& res_sub, int index, const string& digits, const vector<string>& t) {
		if (index == digits.size()) {
			res.push_back(res_sub);
			return;
		}
		for (int i = 0; i < t[digits[index] - '0'].size(); i++) {
			res_sub += t[digits[index] - '0'][i];
			letterCombinations(res, res_sub, index + 1, digits, t);
			res_sub.pop_back();
		}
	}
};
/*

22. Generate Parentheses (Medium)

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
"((()))",
"(()())",
"(())()",
"()(())",
"()()()"
]

*/
class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> res;
		string res_sub;
		generateParenthesis(res, res_sub, 0, 0, n);
		return res;
	}
private:
	void generateParenthesis(vector<string>& res, string& res_sub, int l, int r, const int& n) {
		if (l == n && r == n) {
			res.push_back(res_sub);
			return;
		}
		if (l < n) {
			res_sub += "(";
			generateParenthesis(res, res_sub, l + 1, r, n);
			res_sub.pop_back();
		}
		if (r < l) {
			res_sub += ")";
			generateParenthesis(res, res_sub, l, r + 1, n);
			res_sub.pop_back();
		}
	}
};
/*

39. Combination Sum (Medium)

Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [2, 3, 6, 7] and target 7,
A solution set is:
[
  [7],
  [2, 2, 3]
]

*/
class Solution {
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		if (candidates.empty()) {
			return{};
		}
		vector<vector<int>> res;
		vector<int> res_sub;
		combinationSum(res, res_sub, candidates, target, 0);
		return res;
	}
private:
	void    combinationSum(vector<vector<int>>& res, vector<int>&res_sub, const vector<int>& candidates, int target, int index) {
		if (target == 0) {
			res.push_back(res_sub);
			return;
		}
		for (int i = index; i < candidates.size(); i++) {
			if (candidates[i] <= target) {
				res_sub.push_back(candidates[i]);
				combinationSum(res, res_sub, candidates, target - candidates[i], i);
				res_sub.pop_back();
			}
		}
	}
};
/*

40. Combination Sum II (Medium)

Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8,
A solution set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

*/
class Solution {
public:
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		vector<vector<int>> res;
		vector<int> res_sub;
		sort(candidates.begin(), candidates.end());
		combinationSum2(res, res_sub, candidates, target, 0);
		return res;
	}
private:
	void combinationSum2(vector<vector<int>>& res, vector<int>& res_sub, const vector<int>& candidates, int target, int index) {
		if (target == 0) {
			res.push_back(res_sub);
			return;
		}
		for (int i = index; i < candidates.size() && candidates[i] <= target; i++) {
			res_sub.push_back(candidates[i]);
			combinationSum2(res, res_sub, candidates, target - candidates[i], i + 1);
			while (i < candidates.size() - 1 && candidates[i] == candidates[i + 1]) {
				i++;
			}
			res_sub.pop_back();
		}
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

46. Permutations (Medium)

Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

*/
class Solution {
public:
	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> res;
		permute(nums, res, 0);
		return res;
	}
private:
	void permute(vector<int>& nums, vector<vector<int>>& res, int index) {
		if (index == nums.size()) {
			res.push_back(nums);
			return;
		}
		for (int i = index; i < nums.size(); i++) {
			swap(nums[index], nums[i]);
			permute(nums, res, index + 1);
			swap(nums[index], nums[i]);
		}
	}
};
/*

47. Permutations II (Medium)

Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]

*/
class Solution {
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		if (nums.empty()) {
			return{};
		}
		vector<vector<int>> res;
		permuteUnique(res, nums, 0);
		return res;
	}
private:
	void permuteUnique(vector<vector<int>>& res, vector<int>& nums, int index) {
		if (index == nums.size()) {
			res.push_back(nums);
			return;
		}
		unordered_set<int> s;
		for (int i = index; i < nums.size(); i++) {
			if (s.find(nums[i]) == s.end()) {
				s.insert(nums[i]);
				swap(nums[i], nums[index]);
				permuteUnique(res, nums, index + 1);
				swap(nums[i], nums[index]);
			}
		}
	}
};
/*

51. N-Queens (Hard)

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]

*/
class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> res;
		vector<string> res_sub(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				res_sub[i].push_back('.');
			}
		}
		unordered_map<int, bool> v;
		unordered_map<int, bool> u;
		unordered_map<int, bool> d;
		solve(res, res_sub, 0, v, u, d);
		return res;
	}
private:
	void solve(vector<vector<string>>& res, vector<string>& res_sub, int col, unordered_map<int, bool>& v, unordered_map<int, bool>& u, unordered_map<int, bool>& d) {
		if (res_sub.size() == col) {
			res.push_back(res_sub);
			return;
		}
		for (int i = 0; i < res_sub.size(); i++) {
			if (valid(col, v, u, d, i)) {
				res_sub[i][col] = 'Q';
				solve(res, res_sub, col + 1, v, u, d);
				res_sub[i][col] = '.';
				back(col, v, u, d, i);
			}
		}
	}
	bool valid(int col, unordered_map<int, bool>& v, unordered_map<int, bool>& u, unordered_map<int, bool>& d, int row) {
		if (v[row] == false && u[row - col] == false && d[row + col] == false) {
			v[row] = true;
			u[row - col] = true;
			d[row + col] = true;
			return true;
		}
		return false;
	}
	void back(int col, unordered_map<int, bool>& v, unordered_map<int, bool>& u, unordered_map<int, bool>& d, int row) {
		v[row] = false;
		u[row - col] = false;
		d[row + col] = false;
	}
};
/*

52. N-Queens II (Hard)

Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.

*/
class Solution {
public:
	int totalNQueens(int n) {
		int res;
		vector<int> res_sub;
		unordered_map<int, bool> v;
		unordered_map<int, bool> u;
		unordered_map<int, bool> d;
		solve(res, res_sub, n, v, u, d);
		return res;
	}
private:
	void solve(int& res, vector<int>& res_sub, int size, unordered_map<int, bool>& v, unordered_map<int, bool>& u, unordered_map<int, bool>& d) {
		if (res_sub.size() == size) {
			res++;
			return;
		}
		for (int i = 0; i < size; i++) {
			if (valid(res_sub.size(), v, u, d, i)) {
				res_sub.push_back(i);
				solve(res, res_sub, size, v, u, d);
				res_sub.pop_back();
				back(res_sub.size(), v, u, d, i);
			}
		}
	}
	bool valid(int col, unordered_map<int, bool>& v, unordered_map<int, bool>& u, unordered_map<int, bool>& d, int row) {
		if (v[row] == false && u[row - col] == false && d[row + col] == false) {
			v[row] = true;
			u[row - col] = true;
			d[row + col] = true;
			return true;
		}
		return false;
	}
	void back(int col, unordered_map<int, bool>& v, unordered_map<int, bool>& u, unordered_map<int, bool>& d, int row) {
		v[row] = false;
		u[row - col] = false;
		d[row + col] = false;
	}
};
/*

60. Permutation Sequence (Medium)

The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.

*/
class Solution {
public:
	string getPermutation(int n, int k) {
		int f = 1;
		string s(n, '0');
		for (int i = 1; i <= n; i++) {
			f *= i;
			s[i - 1] = i + '0';
		}
		k--;
		for (int i = 0; i < n; i++) {
			f /= n - i;
			int j = i + k / f;
			char c = s[j];
			for (; j > i;j--) {
				s[j] = s[j - 1];
			}
			s[i] = c;
			k %= f;
		}
		return s;
	}
};
/*

77. Combinations (Medium)

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

*/
class Solution {
public:
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> res;
		vector<int> res_sub;
		combine(res, res_sub, n, k, 1);
		return res;
	}
private:
	void combine(vector<vector<int>>& res, vector<int>& res_sub, const int& n, const int& k, int index) {
		if (res_sub.size() == k) {
			res.push_back(res_sub);
			return;
		}
		if (index > n) {
			return;
		}
		res_sub.push_back(index);
		combine(res, res_sub, n, k, index + 1);
		res_sub.pop_back();
		combine(res, res_sub, n, k, index + 1);
	}
};
/*

78. Subsets (Medium)

Given a set of distinct integers, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

*/
class Solution {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		if (nums.empty()) {
			return{};
		}
		vector<vector<int>> res;
		vector<int> res_sub;
		subsets(res, res_sub, nums, 0);
		return res;
	}
private:
	void subsets(vector<vector<int>>& res, vector<int>& res_sub, const vector<int>& nums, int index) {
		if (index == nums.size()) {
			res.push_back(res_sub);
			return;
		}
		res_sub.push_back(nums[index]);
		subsets(res, res_sub, nums, index + 1);
		res_sub.pop_back();
		subsets(res, res_sub, nums, index + 1);
	}
};
/*

79. Word Search (Medium)

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.

*/
class Solution {
public:
	bool exist(vector<vector<char>>& board, string word) {
		row = board.size();
		col = board[0].size();
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (search(board, word.c_str(), i, j)) return true;
			}
		}
		return false;
	}
private:
	int row, col;
	bool search(vector<vector<char>>& board, const char* w, int i, int j) {
		if (i < 0 || i >= row || j < 0 || j >= col || board[i][j] == '\0' || board[i][j] != *w) return false;
		else if (*(w + 1) == '\0') return true;
		else {
			char t = board[i][j];
			board[i][j] = '\0';
			if (search(board, w + 1, i + 1, j) || search(board, w + 1, i - 1, j) || search(board, w + 1, i, j - 1) || search(board, w + 1, i, j + 1)) return true;
			board[i][j] = t;
		}
		return false;
	}
};
/*

89. Gray Code (Medium)

The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2
Note:
For a given n, a gray code sequence is not uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.

For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.

*/
class Solution {
public:
	vector<int> grayCode(int n) {
		vector<int> res;
		for (int i = 0; i < 1 << n; i++) {
			res.push_back(i ^ i >> 1);
		}
		return res;
	}
};
/*

90. Subsets II (Medium)

Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

*/
class Solution {
public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<vector<int>> res;
		vector<int> res_sub;
		res.push_back(res_sub);
		subsetsWithDup(nums, res, res_sub, 0);
		return res;
	}
private:
	void subsetsWithDup(const vector<int>& nums, vector<vector<int>>& res, vector<int>& res_sub, int index) {
		if (index == nums.size()) {
			return;
		}
		for (int i = index; i < nums.size(); i++) {
			if (i > index && nums[i] == nums[i - 1]) {
				continue;
			}
			res_sub.push_back(nums[i]);
			res.push_back(res_sub);
			subsetsWithDup(nums, res, res_sub, i + 1);
			res_sub.pop_back();
		}
	}
};
/*

93. Restore IP Addresses (Medium)

Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)

*/
class Solution {
public:
	vector<string> restoreIpAddresses(string s) {
		if (s.size() < 4 || s.size() > 12) {
			return{};
		}
		vector<string> res;
		restoreIpAddresses(s, res, "", 0, 0);
		return res;
	}
private:
	void restoreIpAddresses(const string& s, vector<string>& res, string res_sub, int index, int n) {
		if (index == s.size() && n == 4) {
			res_sub.pop_back();
			res.push_back(res_sub);
			return;
		}
		if (s.size() - index > 3 * (4 - n)) {
			return;
		}
		for (int i = 0; i < 3 && i + index < s.size(); i++) {
			if (i == 0) {
				restoreIpAddresses(s, res, res_sub + s.substr(index, 1) + ".", index + 1, n + 1);
			}
			if (i == 1 && s[index] != '0') {
				restoreIpAddresses(s, res, res_sub + s.substr(index, 2) + ".", index + 2, n + 1);
			}
			if (i == 2 && stoi(s.substr(index, 3)) > 99 && stoi(s.substr(index, 3)) < 256) {
				restoreIpAddresses(s, res, res_sub + s.substr(index, 3) + ".", index + 3, n + 1);
			}
		}
	}
};
/*

131. Palindrome Partitioning (Medium)

Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
  ["aa","b"],
  ["a","a","b"]
]

*/
class Solution {
public:
	vector<vector<string>> partition(string s) {
		int _size = s.size();
		vector<vector<bool>> t(_size, vector<bool>(_size, false));
		for (int j = 0; j < _size;j++) {
			for (int i = 0; i < _size;i++) {
				if (i + j < _size) {
					if (j == 0) {
						t[i][i + j] = true;
					}
					else if (j < 3) {
						t[i][i + j] = (s[i] == s[i + j]);
					}
					else {
						t[i][i + j] = (s[i] == s[i + j]) && (t[i + 1][i + j - 1]);
					}
				}
			}
		}
		vector<vector<string>> res;
		vector<string> res_sub;
		partition(res, res_sub, t, 0, s);
		return res;
	}
private:
	void partition(vector<vector<string>>& res, vector<string>& res_sub, const vector<vector<bool>>& t, int index, const string& s) {
		if (index == t[0].size()) {
			res.push_back(res_sub);
			return;
		}
		for (int i = index; i < t[0].size(); i++) {
			if (t[index][i]) {
				res_sub.push_back(s.substr(index, i - index + 1));
				partition(res, res_sub, t, i + 1, s);
				res_sub.pop_back();
			}
		}
	}
};
/*

216. Combination Sum III (Medium)

Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]

Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]

*/
class Solution {
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		vector<vector<int>> res;
		vector<int> res_sub;
		combinationSum3(k, n, 1, res, res_sub);
		return res;
	}
private:
	void combinationSum3(int k, int n, int start, vector<vector<int>>& res, vector<int>& res_sub) {
		if (n == 0 && res_sub.size() == k) {
			res.push_back(res_sub);
			return;
		}
		for (int i = start; i < 10 && i <= n && res_sub.size() < k; i++) {
			res_sub.push_back(i);
			combinationSum3(k, n - i, i + 1, res, res_sub);
			res_sub.pop_back();
		}
	}
};
/*

267. Palindrome Permutation I (Medium)

Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.

For example:

Given s = "aabb", return ["abba", "baab"].

Given s = "abc", return [].

Hint:

If a palindromic permutation exists, we just need to generate the first half of the string.
To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.

*/
class Solution {
public:
	vector<string> generatePalindromes(string s) {
		unordered_map<char, int> mapping;
		for (char cha : s) {
			mapping[cha]++;
		}
		string str;
		string c = "";
		bool odd = false;
		for (auto i = mapping.begin(); i != mapping.end(); i++) {
			if (i->second % 2) {
				if (odd) {
					return{};
				}
				c.push_back(i->first);
				odd = true;
			}
			int temp = i->second / 2;
			while (temp > 0) {
				str += i->first;
				temp--;
			}
		}
		vector<string> res;
		helper(res, str, 0);
		for (int i = 0; i < res.size(); i++) {
			string temp = res[i];
			reverse(temp.begin(), temp.end());
			res[i] += c + temp;
		}
		return res;
	}
private:
	void helper(vector<string>& res, string& str, int index) {
		if (index == str.size()) {
			res.push_back(str);
			return;
		}
		set<char> s;
		for (int i = index; i < str.size(); i++) {
			if (i == index || s.find(str[i]) == s.end()) {
				s.insert(str[i]);
				swap(str[i], str[index]);
				helper(res, str, index + 1);
				swap(str[i], str[index]);
			}
		}
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

401. Binary Watch (Easy)

A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).

Each LED represents a zero or one, with the least significant bit on the right.

For example, the above binary watch reads "3:25".

Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.

Example:

Input: n = 1
Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
Note:
The order of output does not matter.
The hour must not contain a leading zero, for example "01:00" is not valid, it should be "1:00".
The minute must be consist of two digits and may contain a leading zero, for example "10:2" is not valid, it should be "10:02".

*/
class Solution {
public:
	vector<int> t = { 1,2,4,8,1,2,4,8,16,32 };
	vector<string> readBinaryWatch(int num) {
		vector<string> res;
		readBinaryWatch(res, 0, 0, 0, num);
		return res;
	}
private:
	void readBinaryWatch(vector<string>& res, int h, int m, int index, int num) {
		if (num == 0) {
			res.push_back(to_string(h) + (m < 10 ? ":0" : ":") + to_string(m));
		}
		for (int i = index; i < 10; i++) {
			if (i < 4 && h + t[i] < 12) {
				h += t[i];
				readBinaryWatch(res, h, m, i + 1, num - 1);
				h -= t[i];
			}
			else if (i >= 4 && m + t[i] < 60) {
				m += t[i];
				readBinaryWatch(res, h, m, i + 1, num - 1);
				m -= t[i];
			}
		}
	}
};