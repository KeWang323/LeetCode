/*

44. Wildcard Matching (Hard)

Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") ¡ú false
isMatch("aa","aa") ¡ú true
isMatch("aaa","aa") ¡ú false
isMatch("aa", "*") ¡ú true
isMatch("aa", "a*") ¡ú true
isMatch("ab", "?*") ¡ú true
isMatch("aab", "c*a*b") ¡ú false

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

45. Jump Game II (Hard)

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)

Note:
You can assume that you can always reach the last index.

*/
class Solution {
public:
	int jump(vector<int>& nums) {
		int n = nums.size(), start = 0, end = 0, step = 0;
		while (end < n - 1) {
			step++;
			int maxend = end + 1;
			for (int i = start; i <= end; i++) {
				if (i + nums[i] >= n - 1) {
					return step;
				}
				maxend = max(maxend, i + nums[i]);
			}
			start = end + 1;
			end = maxend;
		}
		return step;
	}
};
/*

55. Jump Game (Medium)

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.

*/
class Solution {
public:
	bool canJump(vector<int>& nums) {
		int steps = 0, _size = nums.size();
		for (int i = 0; i < _size; i++) {
			steps = steps > nums[i] ? steps : nums[i];
			if (steps >= _size - 1 - i) {
				return true;
			}
			else if (--steps < 0) {
				return false;
			}
		}
		return false;
	}
};
/*

122. Best Time to Buy and Sell Stock II (Medium)

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

*/
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int res = 0;
		for (int i = 1; i < prices.size(); i++) {
			if (prices[i] - prices[i - 1] > 0) {
				res += prices[i] - prices[i - 1];
			}
		}
		return res;
	}
};
/*

134. Gas Station (Medium)

There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.

*/
class Solution {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int rem = 0, index = 0, sum = INT_MAX;
		for (int i = 0; i < gas.size(); i++) {
			rem += gas[i] - cost[i];
			if (rem < sum) {
				sum = rem;
				index = i + 1;
			}
		}
		return rem < 0 ? -1 : index % gas.size();
	}
};
/*

316. Remove Duplicate Letters (Hard)

Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example:
Given "bcabc"
Return "abc"

Given "cbacdcbc"
Return "acdb"

*/
class Solution {
public:
	string removeDuplicateLetters(string s) {
		int cnt[256] = { 0 };
		bool visited[256] = { false };
		string res = "0";
		for (char cha : s) {
			cnt[cha]++;
		}
		for (char cha : s) {
			cnt[cha]--;
			if (visited[cha] == true) {
				continue;
			}
			while (cha < res.back() && cnt[res.back()] > 0) {
				visited[res.back()] = false;
				res.pop_back();
			}
			res += cha;
			visited[cha] = true;
		}
		return res.substr(1);
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
		int s_i = 0;
		for (int t_i = 0; t_i < t.length() && s_i < s.length(); t_i++)
			if (t[t_i] == s[s_i]) s_i++;
		return s_i == s.length();
	}
};