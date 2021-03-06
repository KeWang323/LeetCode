/*

1. Two Sum (Easy)

Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

UPDATE (2016/2/13):
The return format had been changed to zero-based indices. Please read the above updated description carefully.

*/
class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> mapping;
		for (int i = 0; i < nums.size(); i++) {
			int gap = target - nums[i];
			if (mapping.find(gap) != mapping.end()) {
				return{ i, mapping[gap] };
			}
			mapping[nums[i]] = i;
		}
		return{};
	}
};
/*

3. Longest Substring Without Repeating Characters (Medium)

Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

*/
class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		char t[256] = { 0 };
		int i = 0, j = 0, res = 0;
		while (j < s.size()) {
			t[s[j++]]++;
			while (t[s[j - 1]] > 1) {
				t[s[i++]]--;
			}
			res = max(res, j - i);
		}
		return res;
	}
};
/*

18. 4Sum (Medium)

Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note: The solution set must not contain duplicate quadruplets.

For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

*/
class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		if (nums.size() < 4) {
			return{};
		}
		vector<vector<int>> res;
		int _size = nums.size();
		sort(nums.begin(), nums.end());
		for (int i = 0; i < _size - 3; i++) {
			if (i > 0 && nums[i] == nums[i - 1] || nums[i] + nums[_size - 3] + nums[_size - 2] + nums[_size - 1] < target) {
				continue;
			}
			if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) {
				break;
			}
			for (int j = i + 1; j < _size - 2; j++) {
				if (j > i + 1 && nums[j] == nums[j - 1] || nums[i] + nums[j] + nums[_size - 2] + nums[_size - 1] < target) {
					continue;
				}
				if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) {
					break;
				}
				int k = j + 1, l = _size - 1;
				while (k < l) {
					int _sum = nums[i] + nums[j] + nums[k] + nums[l];
					if (_sum == target) {
						res.push_back({ nums[i], nums[j], nums[k], nums[l] });
						k++;
						l--;
						while (nums[k] == nums[k - 1] && k < l) {
							k++;
						}
						while (nums[l] == nums[l + 1] && k < l) {
							l--;
						}
					}
					else if (_sum > target) {
						l--;
					}
					else {
						k++;
					}
				}
			}
		}
		return res;
	}
};
/*

30. Substring with Concatenation of All Words (Hard)

You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).

*/
class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		if (words.empty()) {
			return{};
		}
		unordered_map<string, int> mapping;
		for (string word : words) {
			mapping[word]++;
		}
		vector<int> res;
		int wsize = words[0].size();
		for (int i = 0; i < wsize; i++) {
			int wcnt = 0, slow = i, fast = i;
			unordered_map<string, int> mapping2;
			while (fast + wsize <= s.size()) {
				string str = s.substr(fast, wsize);
				if (mapping.find(str) == mapping.end()) {
					mapping2.clear();
					wcnt = 0;
					slow = fast + wsize;
				}
				else {
					wcnt++;
					mapping2[str]++;
					while (mapping2[str] > mapping[str]) {
						mapping2[s.substr(slow, wsize)]--;
						wcnt--;
						slow += wsize;
					}
				}
				if (wcnt == words.size()) {
					res.push_back(slow);
				}
				fast += wsize;
			}
		}
		return res;
	}
};
/*

36. Valid Sudoku (Easy)

Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.

*/
class Solution {
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		int mapping1[9][9] = { 0 }, mapping2[9][9] = { 0 }, mapping3[9][9] = { 0 };
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (board[i][j] != '.') {
					int num = board[i][j] - '0' - 1, k = i / 3 * 3 + j / 3;
					if (mapping1[i][num] || mapping2[j][num] || mapping3[k][num]) {
						return false;
					}
					mapping1[i][num] = 1;
					mapping2[j][num] = 1;
					mapping3[k][num] = 1;
				}
			}
		}
		return true;
	}
};
/*

37. Sudoku Solver (Hard)

Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.

*/
class Solution {
public:
	void solveSudoku(vector<vector<char>>& board) {
		solve(board, 0, 0);
	}
private:
	bool solve(vector<vector<char>>& board, int row, int col) {
		for (int i = row; i < 9; i++, col = 0) {
			for (int j = col; j < 9; j++) {
				if (board[i][j] == '.') {
					for (char d = '1'; d <= '9'; d++) {
						if (isValid(board, i, j, d)) {
							board[i][j] = d;
							if (solve(board, i, j + 1)) {
								return true;
							}
							board[i][j] = '.';
						}
					}
					return false;
				}
			}
		}
		return true;
	}
	bool isValid(vector<vector<char>>& board, int i, int j, char d) {
		for (int k = 0; k < 9; k++) {
			if (board[k][j] == d || board[i][k] == d) {
				return false;
			}
		}
		for (int row = (i / 3) * 3; row < (i / 3 + 1) * 3; row++) {
			for (int col = (j / 3) * 3; col < (j / 3 + 1) * 3; col++) {
				if (board[row][col] == d) {
					return false;
				}
			}
		}
		return true;
	}
};
/*

49. Group Anagrams (Medium)

Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

[
["ate", "eat","tea"],
["nat","tan"],
["bat"]
]
Note: All inputs will be in lower-case.

*/
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107 };
		vector<vector<string>> res;
		unordered_map<long, int> mapping;
		for (int i = 0; i < strs.size(); i++) {
			long temp = 1;
			for (int j = 0; j < strs[i].size(); j++) {
				temp *= primes[strs[i][j] - 'a'];
			}
			if (mapping.find(temp) == mapping.end()) {
				mapping[temp] = res.size();
				res.push_back({ strs[i] });
			}
			else {
				res[mapping[temp]].push_back(strs[i]);
			}
		}
		return res;
	}
};
/*

76. Minimum Window Substring (Hard)

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.

*/
class Solution {
public:
	string minWindow(string s, string t) {
		vector<int> mapping(256, 0);
		for (char cha : t) {
			mapping[cha]++;
		}
		int slow = 0, fast = 0, cnt = t.size(), len = s.size() + 1, i;
		while (fast < s.size()) {
			if (--mapping[s[fast++]] >= 0 && --cnt == 0) {
				while (mapping[s[slow]]++ < 0) {
					slow++;
				}
				if (len > fast - slow) {
					i = slow;
					len = fast - slow;
				}
				cnt = 1;
				slow++;
			}
		}
		return len == s.size() + 1 ? "" : s.substr(i, len);
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
class Solution {
public:
	vector<int> inorderTraversal(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		stack<TreeNode*> sta;
		vector<int> res;
		while (root != NULL || !sta.empty()) {
			if (root != NULL) {
				sta.push(root);
				root = root->left;
			}
			else {
				root = sta.top();
				sta.pop();
				res.push_back(root->val);
				root = root->right;
			}
		}
		return res;
	}
};
/*

136. Single Number (Medium)

Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

*/
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		for (int i = 1; i < nums.size(); i++) {
			nums[0] ^= nums[i];
		}
		return nums[0];
	}
};
/*

138. Copy List with Random Pointer (Hard)

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

*/
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
	RandomListNode *copyRandomList(RandomListNode *head) {
		if (head == NULL) {
			return NULL;
		}
		RandomListNode *newhead = new RandomListNode(head->label), *cur = newhead;
		unordered_map<RandomListNode*, RandomListNode*> mapping = { {head, newhead} };
		while (head != NULL) {
			if (head->next != NULL) {
				if (mapping.find(head->next) == mapping.end()) {
					mapping[head->next] = new RandomListNode(head->next->label);;
				}
				cur->next = mapping[head->next];
			}
			if (head->random != NULL) {
				if (mapping.find(head->random) == mapping.end()) {
					mapping[head->random] = new RandomListNode(head->random->label);
				}
				cur->random = mapping[head->random];
			}
			head = head->next;
			cur = cur->next;
		}
		return newhead;
	}
};
/*

149. Max Points on a Line (Hard)

Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

*/
/**
* Definition for a point.
* struct Point {
*     int x;
*     int y;
*     Point() : x(0), y(0) {}
*     Point(int a, int b) : x(a), y(b) {}
* };
*/
class Solution {
public:
	int maxPoints(vector<Point>& points) {
		if (points.size() < 3) {
			return points.size();
		}
		unordered_map<int, unordered_map<int, int>> mapping;
		int res = 0;
		for (int i = 0; i < points.size(); i++) {
			mapping.clear();
			int p0_num = 1, k_max = 0;
			for (int j = i + 1; j < points.size(); j++) {
				int x = points[i].x - points[j].x, y = points[i].y - points[j].y;
				if (x == 0 && y == 0) {
					p0_num++;
					continue;
				}
				int gcd = generateGCD(x, y);
				if (gcd != 0) {
					x /= gcd;
					y /= gcd;
				}
				mapping[x][y]++;
				k_max = max(k_max, mapping[x][y]);
			}
			res = max(res, k_max + p0_num);
		}
		return res;
	}
private:
	int generateGCD(int a, int b) {
		if (b == 0) {
			return a;
		}
		return generateGCD(b, a%b);
	}
};
/*

159. Longest Substring with At Most Two Distinct Characters (Hard)

Given a string, find the length of the longest substring T that contains at most 2 distinct characters.

For example, Given s = “eceba”,

T is "ece" which its length is 3.

*/
class Solution {
public:
	int lengthOfLongestSubstringTwoDistinct(string s) {
		if (s.size() < 3) {
			return s.size();
		}
		int t[256] = { 0 };
		int sl = 0, f = 0, res = 0, cnt = 0;
		while (f < s.size()) {
			if (++t[s[f++]] == 1) {
				cnt++;
			}
			while (cnt > 2) {
				if (--t[s[sl++]] == 0) {
					cnt--;
				}
			}
			res = max(f - sl, res);
		}
		return res;
	}
};
/*

166. Fraction to Recurring Decimal (Medium)

Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".
Hint:

No scary math, just apply elementary math knowledge. Still remember how to perform a long division?
Try a long division on 4/9, the repeating part is obvious. Now try 4/333. Do you see a pattern?
Be wary of edge cases! List out as many test cases as you can think of and test your code thoroughly.

*/
class Solution {
public:
	string fractionToDecimal(int numerator, int denominator) {
		if (numerator == 0) {
			return "0";
		}
		string res;
		if (numerator < 0 ^ denominator < 0) {
			res += "-";
		}
		long na = labs((long)numerator), da = labs((long)denominator);
		res += to_string(na / da);
		if ((na %= da) == 0) {
			return res;
		}
		res += ".";
		unordered_map<int, int> mapping;
		int i = res.size() - 1;
		while (na != 0) {
			if (mapping.find(na) != mapping.end()) {
				res.insert(mapping[na], "(");
				res += ")";
				return res;
			}
			mapping[na] = ++i;
			na *= 10;
			res += to_string(na / da);
			na %= da;
		}
		return res;
	}
};
/*

170. Two Sum III - Data structure design (Easy)

Design and implement a TwoSum class. It should support the following operations: add and find.

add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,
add(1); add(3); add(5);
find(4) -> true
find(7) -> false

*/
class TwoSum {
public:
	/** Initialize your data structure here. */
	unordered_map<int, int> mapping;
	TwoSum() {
		mapping.clear();
	}

	/** Add the number to an internal data structure.. */
	void add(int number) {
		mapping[number]++;
	}

	/** Find if there exists any pair of numbers which sum is equal to the value. */
	bool find(int value) {
		for (auto i = mapping.begin(); i != mapping.end(); i++) {
			if (mapping.find(value - i->first) != mapping.end() && (i->first != value - i->first || mapping[i->first] > 1)) {
				return true;
			}
		}
		return false;
	}
};
/**
* Your TwoSum object will be instantiated and called as such:
* TwoSum obj = new TwoSum();
* obj.add(number);
* bool param_2 = obj.find(value);
*/
/*

187. Repeated DNA Sequences (Medium)

All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].

*/
class Solution {
public:
	vector<string> findRepeatedDnaSequences(string s) {
		unordered_set<int> se;
		vector<string> res;
		for (int t = 0, i = 0; i < s.size(); i++) {
			t = t << 3 & 0x3FFFFFFF | s[i] & 7;
			if (se.find(t) != se.end()) {
				res.push_back(s.substr(i - 9, 10));
			}
			else {
				se.insert(t);
			}
		}
		return res;
	}
};
/*

202. Happy Number (Easy)

Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number

1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1

*/
class Solution {
public:
	bool isHappy(int n) {
		unordered_set<int> s;
		int sum = calculate(n);
		while (s.find(sum) == s.end()) {
			if (sum == 1) {
				return true;
			}
			s.insert(sum);
			sum = calculate(sum);
		}
		return false;
	}
private:
	int calculate(int n) {
		int res = 0;
		while (n > 0) {
			res += pow(n % 10, 2);
			n /= 10;
		}
		return res;
	}
};
/*

204. Count Primes (Easy)

Description:

Count the number of prime numbers less than a non-negative number, n.

*/
class Solution {
public:
	int countPrimes(int n) {
		if (n < 2) {
			return 0;
		}
		vector<bool> t(n, false);
		int cnt = 0;
		for (int i = 2; i < n; i++) {
			if (t[i] == false) {
				cnt++;
				for (int j = 1; i * j < n; j++) {
					t[i * j] = true;
				}
			}
		}
		return cnt;
	}
};
/*

205. Isomorphic Strings (Easy)

Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.

*/
class Solution {
public:
	bool isIsomorphic(string s, string t) {
		char t1[256] = { 0 }, t2[256] = { 0 };
		for (int i = 0; i < s.size(); i++) {
			if (t1[s[i]] != t2[t[i]]) {
				return false;
			}
			t1[s[i]] = i + 1;
			t2[t[i]] = i + 1;
		}
		return true;
	}
};
/*

217. Contains Duplicate (Easy)

Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

*/
class Solution {
public:
	bool containsDuplicate(vector<int>& nums) {
		unordered_set<int> s;
		for (int i : nums) {
			if (s.find(i) != s.end()) {
				return true;
			}
			s.insert(i);
		}
		return false;
	}
};
/*

219. Contains Duplicate II (Easy)

Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k.

*/
class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		if (nums.size() < 2 || k < 1) {
			return false;
		}
		unordered_map<int, int> mapping;
		for (int i = 0; i < nums.size(); i++) {
			if (mapping.count(nums[i]) && i - mapping[nums[i]] <= k) {
				return true;
			}
			mapping[nums[i]] = i;
		}
		return false;
	}
};
/*

242. Valid Anagram (Easy)

Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?

*/
class Solution {
public:
	bool isAnagram(string s, string t) {
		if (s.size() != t.size()) {
			return false;
		}
		int a[256] = { 0 };
		for (char cha : s) {
			a[cha]++;
		}
		for (char cha : t) {
			if (a[cha] == 0) {
				return false;
			}
			a[cha]--;
		}
		return true;
	}
};
/*

244. Shortest Word Distance II (Medium)

his is a follow up of Shortest Word Distance. The only difference is now you are given the list of words and your method will be called repeatedly many times with different parameters. How would you optimize it?

Design a class which receives a list of words in the constructor, and implements a method that takes two words word1 and word2 and return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.

Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.

*/
class WordDistance {
public:
	WordDistance(vector<string> words) {
		for (int i = 0; i < words.size(); i++) {
			mapping[words[i]].push_back(i);
		}
	}

	int shortest(string word1, string word2) {
		int i = 0, j = 0, res = INT_MAX;
		while (i < mapping[word1].size() && j < mapping[word2].size()) {
			res = min(res, abs(mapping[word1][i] - mapping[word2][j]));
			mapping[word1][i] < mapping[word2][j] ? i++ : j++;
		}
		return res;
	}
private:
	unordered_map<string, vector<int>> mapping;
};
/**
* Your WordDistance object will be instantiated and called as such:
* WordDistance obj = new WordDistance(words);
* int param_1 = obj.shortest(word1,word2);
*/
/*

246. Strobogrammatic Number (Easy)

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.

For example, the numbers "69", "88", and "818" are all strobogrammatic.

*/
class Solution {
public:
	bool isStrobogrammatic(string num) {
		if (num.empty()) {
			return false;
		}
		unordered_map<char, char> mapping = { { '0', '0' },{ '1', '1' },{ '6', '9' },{ '8', '8' },{ '9', '6' } };
		int i = 0, j = num.size() - 1;
		while (i <= j) {
			if (mapping[num[i++]] != num[j--]) {
				return false;
			}
		}
		return true;
	}
};
/*

249. Group Shifted Strings (Medium)

Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

"abc" -> "bcd" -> ... -> "xyz"
Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
A solution is:

[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]

*/
class Solution {
public:
	vector<vector<string>> groupStrings(vector<string>& strings) {
		vector<vector<string>> res;
		unordered_map<string, vector<string>> mapping;
		for (string str : strings) {
			int offset = str[0] - 'a';
			string key = "";
			for (int i = 0; i < str.size(); i++) {
				char c = str[i] - offset;
				if (c < 'a') {
					c += 26;
				}
				key += c;
			}
			mapping[key].push_back(str);
		}
		for (auto i = mapping.begin(); i != mapping.end(); i++) {
			res.push_back(i->second);
		}
		return res;
	}
};
/*

266. Palindrome Permutation (Easy)

Given a string, determine if a permutation of the string could form a palindrome.

For example,
"code" -> False, "aab" -> True, "carerac" -> True.

Hint:

Consider the palindromes of odd vs even length. What difference do you notice?
Count the frequency of each character.
If each character occurs even number of times, then it must be a palindrome. How about character which occurs odd number of times?

*/
class Solution {
public:
	bool canPermutePalindrome(string s) {
		unordered_map<char, int> mapping;
		for (char cha : s) {
			mapping[cha]++;
		}
		bool odd = false;
		for (auto i = mapping.begin(); i != mapping.end(); i++) {
			if (i->second % 2) {
				if (odd) {
					return false;
				}
				odd = true;
			}
		}
		return true;
	}
};
/*

274. H-Index (Medium)

Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.

Note: If there are several possible values for h, the maximum one is taken as the h-index.

Hint:

An easy approach is to sort the array first.
What are the possible values of h-index?
A faster approach is to use extra space.

*/
class Solution {
public:
	int hIndex(vector<int>& citations) {
		if (citations.empty()) {
			return 0;
		}
		int t[citations.size() + 1] = { 0 };
		for (int num : citations) {
			if (num > citations.size()) {
				t[citations.size()]++;
			}
			else {
				t[num]++;
			}
		}
		int sum = 0;
		for (int i = citations.size(); i >= 0; i--) {
			sum += t[i];
			if (sum >= i) {
				return i;
			}
		}
		return 0;
	}
};
class Solution {
public:
	int hIndex(vector<int>& citations) {
		if (citations.empty()) {
			return 0;
		}
		sort(citations.begin(), citations.end());
		for (int i = 0; i < citations.size(); i++) {
			if (citations[i] >= citations.size() - i) {
				return citations.size() - i;
			}
		}
		return 0;
	}
};
/*

288. Unique Word Abbreviation (Medium)

An abbreviation of a word follows the form <first letter><number><last letter>. Below are some examples of word abbreviations:

a) it                      --> it    (no abbreviation)

	 1
b) d|o|g                   --> d1g

			  1    1  1
	 1---5----0----5--8
c) i|nternationalizatio|n  --> i18n

			  1
	 1---5----0
d) l|ocalizatio|n          --> l10n
Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary. A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.

Example:
Given dictionary = [ "deer", "door", "cake", "card" ]

isUnique("dear") ->
false

isUnique("cart") ->
true

isUnique("cane") ->
false

isUnique("make") ->
true

*/
class ValidWordAbbr {
public:
	ValidWordAbbr(vector<string> dictionary) {
		for (string& str : dictionary) {
			string abbr = str[0] + to_string(str.size()) + str.back();
			mapping[abbr].insert(str);
		}
	}

	bool isUnique(string word) {
		string abbr = word[0] + to_string(word.size()) + word.back();
		return mapping[abbr].count(word) == mapping[abbr].size();
	}
private:
	unordered_map<string, unordered_set<string>> mapping;
};
/**
* Your ValidWordAbbr object will be instantiated and called as such:
* ValidWordAbbr obj = new ValidWordAbbr(dictionary);
* bool param_1 = obj.isUnique(word);
*/
/*

290. Word Pattern (Easy)

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Examples:
pattern = "abba", str = "dog cat cat dog" should return true.
pattern = "abba", str = "dog cat cat fish" should return false.
pattern = "aaaa", str = "dog cat cat dog" should return false.
pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.

*/
class Solution {
public:
	bool wordPattern(string pattern, string str) {
		unordered_map<char, int> mappingchar;
		unordered_map<string, int> mappingstr;
		string strs;
		int index = 0;
		istringstream in(str);
		while (in >> strs) {
			if (index < pattern.length()) {
				if (mappingchar[pattern[index]] != mappingstr[strs]) {
					return false;
				}
				mappingchar[pattern[index]] = mappingstr[strs] = index + 1;
			}
			index++;
		}
		return index == pattern.length();
	}
};
/*

299. Bulls and Cows (Easy)

You are playing the following Bulls and Cows game with your friend: You write down a number and ask your friend to guess what the number is. Each time your friend makes a guess, you provide a hint that indicates how many digits in said guess match your secret number exactly in both digit and position (called "bulls") and how many digits match the secret number but locate in the wrong position (called "cows"). Your friend will use successive guesses and hints to eventually derive the secret number.

For example:

Secret number:  "1807"
Friend's guess: "7810"
Hint: 1 bull and 3 cows. (The bull is 8, the cows are 0, 1 and 7.)

Write a function to return a hint according to the secret number and friend's guess, use A to indicate the bulls and B to indicate the cows. In the above example, your function should return "1A3B".

Please note that both secret number and friend's guess may contain duplicate digits, for example:

Secret number:  "1123"
Friend's guess: "0111"

In this case, the 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow, and your function should return "1A1B".

You may assume that the secret number and your friend's guess only contain digits, and their lengths are always equal.

*/
class Solution {
public:
	string getHint(string secret, string guess) {
		vector<int> mapping(10, 0);
		int bulls = 0, cows = 0;
		for (int i = 0; i < guess.length(); i++) {
			if (guess[i] == secret[i]) {
				bulls++;
			}
			else {
				mapping[secret[i] - '0']++;
			}
		}
		for (int i = 0; i < guess.length(); i++) {
			if (guess[i] != secret[i] && mapping[guess[i] - '0']) {
				cows++;
				mapping[guess[i] - '0']--;
			}
		}
		char result[10];
		sprintf(result, "%dA%dB", bulls, cows);
		return result;
	}
};
/*

311. Sparse Matrix Multiplication (Medium)

Given two sparse matrices A and B, return the result of AB.

You may assume that A's column number is equal to B's row number.

Example:

A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]

B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]


	 |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
				  | 0 0 1 |

*/
class Solution {
public:
	vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
		int m = A.size(), n = A[0].size();
		vector<vector<int>> res(m, vector<int>(B[0].size(), 0));
		for (int i = 0; i < m; i++) {
			for (int k = 0; k < n; k++) {
				if (A[i][k] != 0) {
					for (int j = 0; j < B[0].size(); j++) {
						res[i][j] += A[i][k] * B[k][j];
					}
				}
			}
		}
		return res;
	}
};
/*

314. Binary Tree Vertical Order Traversal (Medium)

Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

Examples:

Given binary tree [3,9,20,null,null,15,7],
   3
  /\
 /  \
 9  20
	/\
   /  \
  15   7
return its vertical order traversal as:
[
  [9],
  [3,15],
  [20],
  [7]
]
Given binary tree [3,9,8,4,0,1,7],
	 3
	/\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
return its vertical order traversal as:
[
  [4],
  [9],
  [3,0,1],
  [8],
  [7]
]
Given binary tree [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left child is 5),
	 3
	/\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
	/\
   /  \
   5   2
return its vertical order traversal as:
[
  [4],
  [9,5],
  [3,0,1],
  [8,2],
  [7]
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
	vector<vector<int>> verticalOrder(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<vector<int>> res;
		map<int, vector<int>> mapping;
		queue<pair<TreeNode*, int>> q;
		q.push({ root,0 });
		while (!q.empty()) {
			mapping[q.front().second].push_back(q.front().first->val);
			if (q.front().first->left) {
				q.push({ q.front().first->left,q.front().second - 1 });
			}
			if (q.front().first->right) {
				q.push({ q.front().first->right,q.front().second + 1 });
			}
			q.pop();
		}
		for (auto i = mapping.begin(); i != mapping.end(); i++) {
			res.push_back(i->second);
		}
		return res;
	}
};
/*

325. Maximum Size Subarray Sum Equals k (Medium)

Given an array nums and a target value k, find the maximum length of a subarray that sums to k. If there isn't one, return 0 instead.

Note:
The sum of the entire nums array is guaranteed to fit within the 32-bit signed integer range.

Example 1:
Given nums = [1, -1, 5, -2, 3], k = 3,
return 4. (because the subarray [1, -1, 5, -2] sums to 3 and is the longest)

Example 2:
Given nums = [-2, -1, 2, 1], k = 1,
return 2. (because the subarray [-1, 2] sums to 1 and is the longest)

*/
class Solution {
public:
	int maxSubArrayLen(vector<int>& nums, int k) {
		if (nums.empty()) {
			return 0;
		}
		int sum = 0, len = 0;
		unordered_map<int, int> mapping;
		mapping[0] = -1;
		for (int i = 0; i < nums.size(); i++) {
			sum += nums[i];
			if (mapping.find(sum - k) != mapping.end()) {
				len = max(len, i - mapping[sum - k]);
			}
			if (mapping.find(sum) == mapping.end()) {
				mapping[sum] = i;
			}
		}
		return len;
	}
};
/*

340. Longest Substring with At Most K Distinct Characters (Hard)

Given a string, find the length of the longest substring T that contains at most k distinct characters.

For example, Given s = “eceba” and k = 2,

T is "ece" which its length is 3.

*/
class Solution {
public:
	int lengthOfLongestSubstringKDistinct(string s, int k) {
		int  len = 0, i = 0, j = 0, num = 0;
		vector<int> t(256, 0);
		while (j < s.size()) {
			if (t[s[j++]]++ == 0) {
				num++;
			}
			while (num > k) {
				if (--t[s[i++]] == 0) {
					num--;
				}
			}
			if (num <= k && j - i > len) {
				len = j - i;
			}
		}
		return len;
	}
};
/*

347. Top K Frequent Elements (Medium)

Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size

*/
class Comp {
public:
	bool operator()(pair<int, int> p1, pair<int, int> p2) {
		return p1.second > p2.second;
	}
};
class Solution {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> mapping;
		for (int num : nums) {
			mapping[num]++;
		}
		priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> pq;
		for (auto i = mapping.begin(); i != mapping.end(); i++) {
			pq.push(make_pair(i->first, i->second));
			if (pq.size() > k) {
				pq.pop();
			}
		}
		vector<int> res(k, 0);
		for (int i = k - 1; i >= 0; i--) {
			res[i] = pq.top().first;
			pq.pop();
		}
		return res;
	}
};
/*

349. Intersection of Two Arrays (Easy)

Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].

Note:
Each element in the result must be unique.
The result can be in any order.

*/
class Solution {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		if (nums1.empty() || nums2.empty()) {
			return{};
		}
		vector<int> result;
		unordered_map<int, bool> mapping;
		for (auto i : nums1) {
			mapping[i] = true;
		}
		for (auto i : nums2) {
			if (mapping[i] == true) {
				result.push_back(i);
				mapping.erase(i);
			}
		}
		return result;
	}
};
/*

350. Intersection of Two Arrays II (Easy)

Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].

Note:
Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.
Follow up:
What if the given array is already sorted? How would you optimize your algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm is better?
What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?

*/
class Solution {
public:
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		if (nums1.empty() || nums2.empty()) {
			return{};
		}
		vector<int> res;
		unordered_map<int, int> mapping;
		for (int num : nums1) {
			mapping[num]++;
		}
		for (int num : nums2) {
			if (mapping[num] > 0) {
				mapping[num]--;
				res.push_back(num);
			}
		}
		return res;
	}
};
/*

355. Design Twitter (Medium)

Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:

postTweet(userId, tweetId): Compose a new tweet.
getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
follow(followerId, followeeId): Follower follows a followee.
unfollow(followerId, followeeId): Follower unfollows a followee.
Example:

Twitter twitter = new Twitter();

// User 1 posts a new tweet (id = 5).
twitter.postTweet(1, 5);

// User 1's news feed should return a list with 1 tweet id -> [5].
twitter.getNewsFeed(1);

// User 1 follows user 2.
twitter.follow(1, 2);

// User 2 posts a new tweet (id = 6).
twitter.postTweet(2, 6);

// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.getNewsFeed(1);

// User 1 unfollows user 2.
twitter.unfollow(1, 2);

// User 1's news feed should return a list with 1 tweet id -> [5],
// since user 1 is no longer following user 2.
twitter.getNewsFeed(1);

*/
class Twitter {
	struct Tweet
	{
		int time;
		int id;
		Tweet(int time, int id) : time(time), id(id) {}

	};
	unordered_map<int, vector<Tweet>> tweets;
	unordered_map<int, set<int>> following;
	int time;
public:
	/** Initialize your data structure here. */
	Twitter() : time(0) {}

	/** Compose a new tweet. */
	void postTweet(int userId, int tweetId) {
		tweets[userId].emplace_back(time++, tweetId);
	}

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
	vector<int> getNewsFeed(int userId) {
		vector<pair<Tweet*, Tweet*>> h;
		for (auto& u : following[userId]) {
			auto& t = tweets[u];
			if (t.size()) h.emplace_back(t.data(), t.data() + t.size() - 1);
		}
		auto& t = tweets[userId];
		if (t.size()) h.emplace_back(t.data(), t.data() + t.size() - 1);
		auto f = [](const pair<Tweet*, Tweet*>& x, const pair<Tweet*, Tweet*>& y) {
			return x.second->time < y.second->time;
		};
		make_heap(h.begin(), h.end(), f);

		const int n = 10;
		vector<int> o;
		o.reserve(n);
		for (int i = 0; i < n && !h.empty(); i++) {
			pop_heap(h.begin(), h.end(), f);
			auto& hb = h.back();
			o.push_back(hb.second->id);
			if (hb.first == hb.second--) h.pop_back();
			else push_heap(h.begin(), h.end(), f);
		}
		return o;
	}

	/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
	void follow(int followerId, int followeeId) {
		if (followerId != followeeId) following[followerId].insert(followeeId);
	}

	/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
	void unfollow(int followerId, int followeeId) {
		if (followerId != followeeId) following[followerId].erase(followeeId);
	}
};
/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * vector<int> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */
 /*

 356. Line Reflection (Medium)

 Given n points on a 2D plane, find if there is such a line parallel to y-axis that reflect the given points.

 Example 1:
 Given points = [[1,1],[-1,1]], return true.

 Example 2:
 Given points = [[1,1],[-1,-1]], return false.

 Follow up:
 Could you do better than O(n2)?

 Hint:

 Find the smallest and largest x-value for all points.
 If there is a line then it should be at y = (minX + maxX) / 2.
 For each point, make sure that it has a reflected point in the opposite side.

 */
class Solution {
public:
	bool isReflected(vector<pair<int, int>>& points) {
		int r = INT_MIN, l = INT_MAX;
		unordered_set<string> s;
		for (pair<int, int>& p : points) {
			r = max(r, p.first);
			l = min(l, p.first);
			s.insert(to_string(p.first) + "a" + to_string(p.second));
		}
		int sum = l + r;
		for (pair<int, int>& p : points) {
			string str = to_string(sum - p.first) + "a" + to_string(p.second);
			if (s.find(str) == s.end()) {
				return false;
			}
		}
		return true;
	}
};
/*

380. Insert Delete GetRandom O(1) (Medium)

Design a data structure that supports all following operations in average O(1) time.

insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
Example:

// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();

// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);

// Returns false as 2 does not exist in the set.
randomSet.remove(2);

// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);

// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();

// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);

// 2 was already in the set, so return false.
randomSet.insert(2);

// Since 2 is the only number in the set, getRandom always return 2.
randomSet.getRandom();

*/
class RandomizedSet {
public:
	/** Initialize your data structure here. */
	RandomizedSet() {

	}

	/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
	bool insert(int val) {
		if (mapping.find(val) == mapping.end()) {
			mapping[val] = t.size();
			t.push_back(val);
			return true;
		}
		return false;
	}

	/** Removes a value from the set. Returns true if the set contained the specified element. */
	bool remove(int val) {
		if (mapping.find(val) != mapping.end()) {
			mapping[t.back()] = mapping[val];
			t[mapping[val]] = t.back();
			t.pop_back();
			mapping.erase(val);
			return true;
		}
		return false;
	}

	/** Get a random element from the set. */
	int getRandom() {
		return t[rand() % t.size()];
	}
private:
	unordered_map<int, int> mapping;
	vector<int> t;
};
/**
* Your RandomizedSet object will be instantiated and called as such:
* RandomizedSet obj = new RandomizedSet();
* bool param_1 = obj.insert(val);
* bool param_2 = obj.remove(val);
* int param_3 = obj.getRandom();
*/
/*

389. Find the Difference (Easy)

Given two strings s and t which consist of only lowercase letters.

String t is generated by random shuffling string s and then add one more letter at a random position.

Find the letter that was added in t.

Example:

Input:
s = "abcd"
t = "abcde"

Output:
e

Explanation:
'e' is the letter that was added.

*/
class Solution {
public:
	char findTheDifference(string s, string t) {
		char result = 0;
		for (char c : s) {
			result ^= c;
		}
		for (char c : t) {
			result ^= c;
		}
		return result;
	}
};
/*

409. Longest Palindrome (Easy)

Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.

*/
class Solution {
public:
	int longestPalindrome(string s) {
		int t[256] = { 0 }, res = 0;
		bool flag = false;
		for (char& cha : s) {
			t[cha]++;
		}
		for (int num : t) {
			res += num / 2 * 2;
			flag |= num & 1;
		}
		return res + flag;
	}
};
/*

438. Find All Anagrams in a String (Easy)

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

*/
class Solution {
public:
	vector<int> findAnagrams(string s, string p) {
		if (s.size() < p.size()) {
			return{};
		}
		vector<int> res;
		int mapping[26] = { 0 };
		for (char cha : p) {
			mapping[cha - 'a']++;
		}
		int cnt = p.size(), i = 0, j = 0;
		while (j < s.size()) {
			if (--mapping[s[j++] - 'a'] >= 0) {
				cnt--;
			}
			if (cnt == 0) {
				res.push_back(i);
			}
			if (j - i == p.size() && mapping[s[i++] - 'a']++ >= 0) {
				cnt++;
			}
		}
		return res;
	}
};
/*

447. Number of Boomerangs (Easy)

Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).

Find the number of boomerangs. You may assume that n will be at most 500 and coordinates of points are all in the range [-10000, 10000] (inclusive).

Example:
Input:
[[0,0],[1,0],[2,0]]

Output:
2

Explanation:
The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]

*/
class Solution {
public:
	int numberOfBoomerangs(vector<pair<int, int>>& points) {
		int res = 0;
		unordered_map<int, int> mapping;
		for (int i = 0; i < points.size(); i++) {
			for (int j = 0; j < points.size(); j++) {
				if (i == j) {
					continue;
				}
				int d = getDistance(points[i], points[j]);
				mapping[d]++;
			}
			for (auto i = mapping.begin(); i != mapping.end(); i++) {
				res += i->second * (i->second - 1);
			}
			mapping.clear();
		}
		return res;
	}
private:
	int getDistance(pair<int, int> p1, pair<int, int> p2) {
		int dx = p1.first - p2.first, dy = p1.second - p2.second;
		return dx*dx + dy*dy;
	}
};
/*

451. Sort Characters By Frequency (Medium)

Given a string, sort it in decreasing order based on the frequency of characters.

Example 1:

Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
Example 2:

Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.
Example 3:

Input:
"Aabb"

Output:
"bbAa"

Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.

*/
class Solution {
public:
	string frequencySort(string s) {
		string res;
		int t[256] = { 0 };
		vector<string> bucket(s.size() + 1);
		for (char cha : s) {
			t[cha]++;
		}
		for (int i = 0; i < 256; i++) {
			if (t[i] > 0) {
				bucket[t[i]].append(t[i], (char)i);
			}
		}
		for (int i = bucket.size() - 1; i >= 0; i--) {
			if (!bucket[i].empty()) {
				res += bucket[i];
			}
		}
		return res;
	}
};
/*

463. Island Perimeter (Easy)

You are given a map in form of a two-dimensional integer grid where 1 represents land and 0 represents water. Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells). The island doesn't have "lakes" (water inside that isn't connected to the water around the island). One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.

Example:

[[0,1,0,0],
[1,1,1,0],
[0,1,0,0],
[1,1,0,0]]

Answer: 16
Explanation: The perimeter is the 16 yellow stripes in the image below:

*/
class Solution {
public:
	int islandPerimeter(vector<vector<int>>& grid) {
		int lands = 0, neibor = 0;
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[0].size(); j++) {
				if (grid[i][j] == 1) {
					lands++;
					if (i < grid.size() - 1 && grid[i + 1][j] == 1) {
						neibor++;
					}
					if (j < grid[0].size() - 1 && grid[i][j + 1] == 1) {
						neibor++;
					}
				}
			}
		}
		return lands * 4 - neibor * 2;
	}
};
/*

359. Logger Rate Limiter (Easy)

Design a logger system that receive stream of messages along with its timestamps, each message should be printed if and only if it is not printed in the last 10 seconds.

Given a message and a timestamp (in seconds granularity), return true if the message should be printed in the given timestamp, otherwise returns false.

It is possible that several messages arrive roughly at the same time.

Example:

Logger logger = new Logger();

// logging string "foo" at timestamp 1
logger.shouldPrintMessage(1, "foo"); returns true;

// logging string "bar" at timestamp 2
logger.shouldPrintMessage(2,"bar"); returns true;

// logging string "foo" at timestamp 3
logger.shouldPrintMessage(3,"foo"); returns false;

// logging string "bar" at timestamp 8
logger.shouldPrintMessage(8,"bar"); returns false;

// logging string "foo" at timestamp 10
logger.shouldPrintMessage(10,"foo"); returns false;

// logging string "foo" at timestamp 11
logger.shouldPrintMessage(11,"foo"); returns true;

*/
class Logger {
public:
	/** Initialize your data structure here. */
	Logger() {

	}

	/** Returns true if the message should be printed in the given timestamp, otherwise returns false.
	If this method returns false, the message will not be printed.
	The timestamp is in seconds granularity. */
	bool shouldPrintMessage(int timestamp, string message) {
		if (timestamp < mapping[message]) {
			return false;
		}
		mapping[message] = timestamp + 10;
		return true;
	}
private:
	unordered_map<string, int> mapping;
};
/**
* Your Logger object will be instantiated and called as such:
* Logger obj = new Logger();
* bool param_1 = obj.shouldPrintMessage(timestamp,message);
*/
/*

500. Keyboard Row (Easy)

Given a List of words, return the words that can be typed using letters of alphabet on only one row's of American keyboard like the image below.

American keyboard

Example 1:
Input: ["Hello", "Alaska", "Dad", "Peace"]
Output: ["Alaska", "Dad"]
Note:
You may use one character in the keyboard more than once.
You may assume the input string will only contain letters of alphabet.

*/
class Solution {
public:
	vector<string> findWords(vector<string>& words) {
		vector<string> keyboard = { "qwertyuiop", "asdfghjkl", "zxcvbnm" };
		vector<string> res;
		for (string word : words) {
			int num;
			for (int i = 0; i < 3; i++) {
				if (keyboard[i].find(tolower(word[0])) != string::npos) {
					num = i;
					break;
				}
			}
			for (int i = 1; i <= word.size(); i++) {
				if (i == word.size()) {
					res.push_back(word);
				}
				else if (num == 0) {
					if (keyboard[1].find(tolower(word[i])) != string::npos || keyboard[2].find(tolower(word[i])) != string::npos) {
						break;
					}
				}
				else if (num == 1) {
					if (keyboard[0].find(tolower(word[i])) != string::npos || keyboard[2].find(tolower(word[i])) != string::npos) {
						break;
					}
				}
				else {
					if (keyboard[0].find(tolower(word[i])) != string::npos || keyboard[1].find(tolower(word[i])) != string::npos) {
						break;
					}
				}
			}
		}
		return res;
	}
};
/*

508. Most Frequent Subtree Sum (Medium)

Given the root of a tree, you are asked to find the most frequent subtree sum. The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.

Examples 1
Input:

  5
 /  \
2   -3
return [2, -3, 4], since all the values happen only once, return all of them in any order.
Examples 2
Input:

  5
 /  \
2   -5
return [2], since 2 happens twice, however -5 only occur once.
Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.

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
	vector<int> findFrequentTreeSum(TreeNode* root) {
		unordered_map<int, int> mapping;
		int maxCount = 0;
		findFrequentTreeSum(root, mapping, maxCount);
		vector<int> res;
		for (const auto& i : mapping) {
			if (i.second == maxCount) {
				res.push_back(i.first);
			}
		}
		return res;
	}
private:
	int findFrequentTreeSum(TreeNode *root, unordered_map<int, int> &mapping, int& maxCount) {
		if (root == NULL) {
			return 0;
		}
		int sum = root->val;
		sum += findFrequentTreeSum(root->left, mapping, maxCount) + findFrequentTreeSum(root->right, mapping, maxCount);
		mapping[sum]++;
		maxCount = max(maxCount, mapping[sum]);
		return sum;
	}
};