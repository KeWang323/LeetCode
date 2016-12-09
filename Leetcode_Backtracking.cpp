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
		for (int i = 1; i <= m; i++) {
			t[i][0] = false;
		}
		for (int j = 1; j <= n; j++) {
			t[0][j] = j > 1 && '*' == p[j - 1] && t[0][j - 2];
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (p[j - 1] != '*') {
					t[i][j] = t[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
				}
				else {
					t[i][j] = t[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && t[i - 1][j];
				}
			}
		}
		return t[m][n];
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
		vector<string> res;
		if (digits.empty()) return res;
		vector<string> letters = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
		string s;
		generate(digits, res, 0, s, letters);
		return res;
	}
	void generate(string digits, vector<string>& res, int start, string s, vector<string>& letters) {
		if (start == digits.length()) {
			res.push_back(s);
			return;
		}
		int num = digits[start] - '0';
		for (int j = 0; j < letters[num].length(); j++) {
			s.push_back(letters[num][j]);
			generate(digits, res, start + 1, s, letters);
			s.pop_back();
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
		string s;
		generate(n, n, res, s);
		return res;
	}
	void generate(int p, int q, vector<string>& res, string s) {
		if (!p) {
			if (q) {
				s.push_back(')');
				generate(0, q - 1, res, s);
			}
			else {
				res.push_back(s);
				return;
			}
		}
		else if (p == q) {
			s.push_back('(');
			generate(p - 1, q, res, s);
		}
		else {
			s.push_back('(');
			generate(p - 1, q, res, s);
			s.pop_back();
			s.push_back(')');
			generate(p, q - 1, res, s);
			s.pop_back();
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
		vector<vector<int>> res;
		vector<int> res_sub;
		sort(candidates.begin(), candidates.end());
		combinationSum(candidates, target, 0, res_sub, res);
		return res;
	}
private:
	void combinationSum(vector<int>& candidates, int target, int start, vector<int>& res_sub, vector<vector<int>>& res) {
		if (target < 0 || start > candidates.size()) {
			return;
		}
		else if (target == 0) {
			res.push_back(res_sub);
			return;
		}
		for (int i = start; i < candidates.size() && candidates[i] <= target; i++) {
			res_sub.push_back(candidates[i]);
			combinationSum(candidates, target - candidates[i], i, res_sub, res);
			res_sub.pop_back();
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
		combinationSum2(candidates, target, 0, res_sub, res);
		return res;
	}
private:
	void combinationSum2(vector<int>& candidates, int target, int start, vector<int>& res_sub, vector<vector<int>>& res) {
		if (target < 0 || start > candidates.size()) {
			return;
		}
		else if (target == 0) {
			res.push_back(res_sub);
			return;
		}
		for (int i = start; i < candidates.size() && candidates[i] <= target; i++) {
			if (i > start && candidates[i] == candidates[i - 1]) continue;
			res_sub.push_back(candidates[i]);
			combinationSum2(candidates, target - candidates[i], i + 1, res_sub, res);
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
		permute(res, nums, 0);
		return res;
	}
private:
	void permute(vector<vector<int>>& res, vector<int>& nums, int index) {
		if (index == nums.size()) {
			res.push_back(nums);
			return;
		}
		for (int i = index; i < nums.size(); i++) {
			swap(nums[i], nums[index]);
			permute(res, nums, index + 1);
			swap(nums[i], nums[index]);
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
				swap(nums[i], nums[index]);
				permuteUnique(res, nums, index + 1);
				swap(nums[i], nums[index]);
				s.insert(nums[i]);
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
		int i = 0;
		vector<int> p(k, 0);
		while (i >= 0) {
			p[i]++;
			if (p[i] > n) --i;
			else if (i == k - 1) res.push_back(p);
			else {
				i++;
				p[i] = p[i - 1];
			}
		}
		return res;
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
		vector<vector<int>> res;
		vector<int> res_sub;
		res.push_back(res_sub);
		generate(nums, 0, res, res_sub);
		return res;
	}
	void generate(vector<int>& nums, int start, vector<vector<int>>& res, vector<int>& res_sub) {
		if (start >= nums.size()) {
			return;
		}
		for (int i = start; i < nums.size(); i++) {
			res_sub.push_back(nums[i]);
			res.push_back(res_sub);
			generate(nums, i + 1, res, res_sub);
			res_sub.pop_back();
		}
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
		vector<vector<int>> res;
		vector<int> res_sub;
		res.push_back(res_sub);
		sort(nums.begin(), nums.end());
		generate(nums, 0, res, res_sub);
		return res;
	}
	void generate(vector<int>& nums, int start, vector<vector<int>>& res, vector<int>& res_sub) {
		if (start >= nums.size()) {
			return;
		}
		for (int i = start; i < nums.size(); i++) {
			if (i - start > 0 && nums[i] == nums[i - 1]) continue;
			res_sub.push_back(nums[i]);
			res.push_back(res_sub);
			generate(nums, i + 1, res, res_sub);
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
		vector<string> res;
		if (s.length() < 4 || s.length() > 12) return res;
		generate(s, 0, 4, res, "");
		return res;
	}
	void generate(string s, int start, int cnt, vector<string>& res, string res_sub) {
		if (start == s.length() && cnt == 0) {
			res_sub.pop_back();
			res.push_back(res_sub);
			return;
		}
		if (s.length() - start > 3 * cnt) return;
		for (int i = 0; i + start < s.length() && i < 3; i++) {
			if (i == 0) generate(s, start + 1, cnt - 1, res, res_sub + s.substr(start, 1) + ".");
			if (i == 1 && s[start] != '0') generate(s, start + 2, cnt - 1, res, res_sub + s.substr(start, 2) + ".");
			if (i == 2 && stoi(s.substr(start, 3)) > 99 && stoi(s.substr(start, 3)) < 256) generate(s, start + 3, cnt - 1, res, res_sub + s.substr(start, 3) + ".");
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
Given n = 2, return 91. (The answer should be the total numbers in the range of 0 ≤ x < 100,
excluding [11,22,33,44,55,66,77,88,99])

Hint:

A direct way is to use the backtracking approach.
Backtracking should contains three states which are (the current number, number of steps to
get that number and a bitmask which represent which number is marked as visited so far in the
current number). Start with state (0,0,0) and count all valid number till we reach number of
steps equals to 10n.

This problem can also be solved using a dynamic programming approach and some knowledge of
combinatorics.
Let f(k) = count of numbers with unique digits with length equals k.
f(1) = 10, ..., f(k) = 9 * 9 * 8 * ... (9 - k + 2) [The first factor is 9 because a number
cannot start with 0].

*/
class Solution {
public:
	int countNumbersWithUniqueDigits(int n) {
		if (n < 1) return 1;
		int pre = 9, sum = 10;
		for (int i = 1; i < n; i++) {
			pre *= (10 - i);
			sum += pre;
		}
		return sum;
	}
};