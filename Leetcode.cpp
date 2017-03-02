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

2. Add Two Numbers (Medium)

You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

*/
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode *dummy = new ListNode(-1), *p = dummy;
		int carry = 0;
		while (carry != 0 || l1 != NULL || l2 != NULL) {
			int a = l1 == NULL ? 0 : l1->val, b = l2 == NULL ? 0 : l2->val;
			carry += a + b;
			p->next = new ListNode(carry % 10);
			p = p->next;
			carry /= 10;
			l1 = l1 == NULL ? NULL : l1->next;
			l2 = l2 == NULL ? NULL : l2->next;
		}
		return dummy->next;
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

4. Median of Two Sorted Arrays (Hard)

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5

*/
class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int sum = nums1.size() + nums2.size();
		if (sum & 1) {
			return findMedian(nums1, 0, nums2, 0, sum / 2 + 1);
		}
		else {
			return (findMedian(nums1, 0, nums2, 0, sum / 2) + findMedian(nums1, 0, nums2, 0, sum / 2 + 1)) / 2.0;
		}
		return 0.0;
	}
private:
	double findMedian(const vector<int>& nums1, int ind1, const vector<int>& nums2, int ind2, int k) {
		if (ind1 >= nums1.size() || ind2 >= nums2.size()) {
			return ind1 >= nums1.size() ? nums2[ind2 + k - 1] : nums1[ind1 + k - 1];
		}
		if (k == 1) {
			return min(nums1[ind1], nums2[ind2]);
		}
		int mid1 = ind1 + k / 2 - 1 >= nums1.size() ? INT_MAX : nums1[ind1 + k / 2 - 1];
		int mid2 = ind2 + k / 2 - 1 >= nums2.size() ? INT_MAX : nums2[ind2 + k / 2 - 1];
		if (mid1 < mid2) {
			return findMedian(nums1, ind1 + k / 2, nums2, ind2, k - k / 2);
		}
		else {
			return findMedian(nums1, ind1, nums2, ind2 + k / 2, k - k / 2);
		}
	}
};
/*

5. Longest Palindromic Substring (Medium)

Given a string S, find the longest palindromic substring in S. You may assume that the maximum
length of S is 1000, and there exists one unique longest palindromic substring.

*/
class Solution {
public:
	string longestPalindrome(string s) {
		int len_max = 0, left_max = 0, l, r, i = 0;
		while (i < s.size() && s.size() - i > len_max / 2) {
			l = i;
			r = i;
			while (r < s.size() - 1 && s[r] == s[r + 1]) {
				r++;
			}
			i = r + 1;
			while (l > 0 && r < s.size() - 1 && s[l - 1] == s[r + 1]) {
				l--;
				r++;
			}
			if (r - l + 1 > len_max) {
				left_max = l;
				len_max = r - l + 1;
			}
		}
		return s.substr(left_max, len_max);
	}
};
class Solution {
public:
	string longestPalindrome(string s) {
		string t = "$#";
		for (int i = 0; i < s.size(); ++i) {
			t += s[i];
			t += "#";
		}
		vector<int> p(t.size(), 0);
		int mx = 0, id = 0, resLen = 0, resCenter = 0;
		for (int i = 1; i < t.size(); i++) {
			p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
			while (t[i + p[i]] == t[i - p[i]]) {
				p[i]++;
			}
			if (mx < i + p[i]) {
				mx = i + p[i];
				id = i;
			}
			if (resLen < p[i]) {
				resLen = p[i];
				resCenter = i;
			}
		}
		return s.substr((resCenter - resLen) / 2, resLen - 1);
	}
};
/*

6. ZigZag Conversion (Easy)

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:
s
string convert(string text, int nRows);

convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

*/
class Solution {
public:
	string convert(string s, int numRows) {
		if (numRows == 1) {
			return s;
		}
		string res;
		int delta1 = 2 * numRows - 2;
		for (int i = 0; i < numRows; i++) {
			int delta2 = delta1 - 2 * i, j = i;
			while (j < s.size()) {
				res += s[j];
				if (delta2 == 0 || delta2 == delta1) {
					j += delta1;
				}
				else {
					j += delta2;
					if (j >= s.size()) {
						break;
					}
					res += s[j];
					j += delta1 - delta2;
				}
			}
		}
		return res;
	}
};
/*

7. Reverse Integer (Easy)

Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

click to show spoilers.

Have you thought about this?
Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!

If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.

Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. How should you handle such cases?

For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

Update (2014-11-10):
Test cases had been added to test the overflow behavior.

*/
class Solution {
public:
	int reverse(int x) {
		long num_rev = 0;
		while (x != 0) {
			num_rev = num_rev * 10 + x % 10;
			if (num_rev < INT_MIN || num_rev > INT_MAX) {
				return 0;
			}
			x /= 10;
		}
		return num_rev;
	}
};
/*

8. String to Integer (atoi) (Easy)

Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.

Update (2015-02-10):
The signature of the C++ function had been updated. If you still see your function signature accepts a const char * argument, please click the reload button  to reset your code definition.

spoilers alert... click to show requirements for atoi.

Requirements for atoi:
The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned. If the correct value is out of the range of representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.

*/
class Solution {
public:
	int myAtoi(string str) {
		if (str.empty()) {
			return 0;
		}
		long res = 0;
		int i = 0, sign = 1;
		while (i < str.size() && str[i] == ' ') {
			i++;
		}
		if (str[i] == '+' || str[i] == '-') {
			sign = str[i++] == '+' ? 1 : -1;
		}
		while (i < str.size()) {
			if (isdigit(str[i])) {
				res = res * 10 + str[i] - '0';
				if (res > INT_MAX) {
					return sign == 1 ? INT_MAX : INT_MIN;
				}
				i++;
			}
			else {
				break;
			}
		}
		return (int)res * sign;
	}
};
/*

9. Palindrome Number (Easy)

Determine whether an integer is a palindrome. Do this without extra space.

click to show spoilers.

Some hints:
Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.

*/
class Solution {
public:
	bool isPalindrome(int x) {
		if (x < 0) {
			return false;
		}
		int len = 1;
		while (x / len >= 10) {
			len *= 10;
		}
		while (len > 1) {
			if (x / len != x % 10) {
				return false;
			}
			x = x % len / 10;
			len /= 100;
		}
		return true;
	}
};
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

11. Container With Most Water (Medium)

Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container.

*/
class Solution {
public:
	int maxArea(vector<int>& height) {
		int res = 0, i = 0, j = height.size() - 1;
		while (i < j) {
			int hei = min(height[i], height[j]);
			res = max(res, (j - i) * hei);
			while (height[i] <= hei) {
				i++;
			}
			while (height[j] <= hei) {
				j--;
			}
		}
		return res;
	}
};
/*

12. Integer to Roman (Medium)

Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.

*/
class Solution {
public:
	string intToRoman(int num) {
		string res;
		char* c[4][10] = {
			{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
			{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
			{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
			{"", "M", "MM", "MMM"}
		};
		res += c[3][num / 1000 % 10];
		res += c[2][num / 100 % 10];
		res += c[1][num / 10 % 10];
		res += c[0][num % 10];
		return res;
	}
};
/*

13. Roman to Integer (Easy)

Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

*/
class Solution {
public:
	int romanToInt(string s) {
		int res = ChartoNum(s[0]);
		for (int i = 1; i < s.size(); i++) {
			res += ChartoNum(s[i]);
			if (ChartoNum(s[i]) > ChartoNum(s[i - 1])) {
				res -= 2 * ChartoNum(s[i - 1]);
			}
		}
		return res;
	}
private:
	int ChartoNum(const char& cha) {
		switch (cha) {
		case 'I': return 1;
		case 'V': return 5;
		case 'X': return 10;
		case 'L': return 50;
		case 'C': return 100;
		case 'D': return 500;
		case 'M': return 1000;
		}
		return 0;
	}
};
/*

14. Longest Common Prefix (Easy)

Write a function to find the longest common prefix string amongst an array of strings.

*/
class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		if (strs.empty()) {
			return "";
		}
		int len = strs[0].size();
		for (int i = 1; i < strs.size(); i++) {
			for (int j = 0; j < len; j++) {
				if (strs[i][j] != strs[i - 1][j]) {
					len = min(len, j);
					break;
				}
			}
		}
		return strs[0].substr(0, len);
	}
};
/*

15. 3Sum (Medium)

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]

*/
class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		if (nums.size() < 3) {
			return{};
		}
		vector<vector<int>> res;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size() - 2; i++) {
			if (nums[i] + nums[i + 1] + nums[i + 2] > 0) {
				break;
			}
			else if (i > 0 && nums[i - 1] == nums[i] || nums[i] + nums[nums.size() - 2] + nums[nums.size() - 1] < 0) {
				continue;
			}
			int j = i + 1, k = nums.size() - 1;
			while (j < k) {
				int sum = nums[i] + nums[j] + nums[k];
				if (sum < 0) {
					j++;
				}
				else if (sum > 0) {
					k--;
				}
				else {
					res.push_back({ nums[i], nums[j], nums[k] });
					while (j < k && nums[j] == nums[j + 1]) {
						j++;
					}
					while (j < k && nums[k] == nums[k - 1]) {
						k--;
					}
					j++;
					k--;
				}
			}
		}
		return res;
	}
};
/*

16. 3Sum Closest (Medium)

Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

For example, given array S = {-1 2 1 -4}, and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

*/
class Solution {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		int res = nums[0] + nums[1] + nums[2];
		for (int i = 0; i < nums.size() - 2; i++) {
			int j = i + 1, k = nums.size() - 1;
			while (j < k) {
				int _sum = nums[i] + nums[j] + nums[k];
				if (_sum == target) {
					return target;
				}
				else if (abs(_sum - target) < abs(res - target)) {
					res = _sum;
				}
				if (_sum < target) {
					j++;
				}
				else {
					k--;;
				}
			}
		}
		return res;
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

19. Remove Nth Node From End of List (Easy)

Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.

*/
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		int len = getLength(head);
		ListNode *dummy = new ListNode(-1);
		dummy->next = head;
		ListNode *p = dummy;
		for (int i = 0; i < len - n; i++) {
			p = p->next;
		}
		p->next = p->next->next;
		return dummy->next;
	}
private:
	int getLength(ListNode* head) {
		int res = 0;
		while (head != NULL) {
			res++;
			head = head->next;
		}
		return res;
	}
};
/*

20. Valid Parentheses (Easy)

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

*/
class Solution {
public:
	bool isValid(string s) {
		stack<char> sta;
		for (char cha : s) {
			if (cha == '(' || cha == '{' || cha == '[') {
				sta.push(cha);
			}
			else if (sta.empty() || cha == ')' && sta.top() != '(' || cha == '}' && sta.top() != '{' || cha == ']' && sta.top() != '[') {
				return false;
			}
			else {
				sta.pop();
			}
		}
		return sta.empty();
	}
};
/*

21. Merge Two Sorted Lists (Easy)

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == NULL) {
			return l2;
		}
		else if (l2 == NULL) {
			return l1;
		}
		else if (l1->val < l2->val) {
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		}
		l2->next = mergeTwoLists(l2->next, l1);
		return l2;
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

23. Merge k Sorted Lists (Hard)

Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

*/
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Comp {
public:
	bool operator()(ListNode* node1, ListNode* node2) {
		return node1->val > node2->val;
	}
};
class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		priority_queue<ListNode*, vector<ListNode*>, Comp> pq;
		for (auto node : lists) {
			if (node != NULL) {
				pq.push(node);
			}
		}
		ListNode* dummy = new ListNode(-1), *p = dummy;
		while (!pq.empty()) {
			ListNode* node = pq.top();
			pq.pop();
			p->next = node;
			p = p->next;
			if (node->next != NULL) {
				pq.push(node->next);
			}
		}
		return dummy->next;
	}
};
/*

24. Swap Nodes in Pairs (Easy)

Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *post = head->next;
		head->next = swapPairs(post->next);
		post->next = head;
		return post;
	}
};
/*

25. Reverse Nodes in k-Group (Hard)

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *node = head;
		int index = 1;
		while (index++ < k) {
			node = node->next;
			if (node == NULL) {
				return head;
			}
		}
		ListNode *post = head->next;
		head->next = reverseKGroup(node->next, k);
		index = 1;
		while (index++ < k) {
			ListNode *next = post->next;
			post->next = head;
			head = post;
			post = next;
		}
		return node;
	}
};
/*

26. Remove Duplicates from Sorted Array (Easy)

Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.

*/
class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.empty()) {
			return 0;
		}
		int index = 1;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[index - 1] != nums[i]) {
				nums[index++] = nums[i];
			}
		}
		return index;
	}
};
/*

27. Remove Element (Easy)

Given an array and a value, remove all instances of that value in place and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

Example:
Given input array nums = [3,2,2,3], val = 3

Your function should return length = 2, with the first two elements of nums being 2.

Hint:

Try two pointers.
Did you use the property of "the order of elements can be changed"?
What happens when the elements to remove are rare?

*/
class Solution {
public:
	int removeElement(vector<int>& nums, int val) {
		int index = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] != val) {
				nums[index++] = nums[i];
			}
		}
		return index;
	}
};
/*

28. Implement strStr() (Easy)

Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

*/
class Solution {
public:
	int strStr(string haystack, string needle) {
		int haylen = haystack.length(), neelen = needle.length();
		for (int i = 0, j; i <= haylen - neelen; i++) {
			for (j = 0; j < neelen && haystack[i + j] == needle[j]; j++) {
			}
			if (j == neelen) return i;
		}
		return -1;
	}
};
/*

29. Divide Two Integers (Medium)

Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT.

*/
class Solution {
public:
	int divide(int dividend, int divisor) {
		if (dividend == 0) {
			return 0;
		}
		if (divisor == 0 || dividend == INT_MIN && divisor == -1) {
			return INT_MAX;
		}
		int sign = (dividend > 0 ^ divisor > 0) ? -1 : 1;
		long dd = labs((long)dividend), dr = labs((long)divisor);
		if (dd < dr) {
			return 0;
		}
		int h = 0;
		long t = dr;
		while (t <= dd) {
			t <<= 1;
			h++;
		}
		long ret = 1 << --h;
		dd -= (t >>= 1);
		while (dd >= dr) {
			while (t > dd) {
				t >>= 1;
				h--;
			}
			ret |= 1 << h;
			dd -= t;
		}
		return sign < 0 ? -ret : ret;
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

31. Next Permutation (Medium)

Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

*/
class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		int j = nums.size() - 1, k = nums.size() - 1;
		while (j > 0 && nums[j] <= nums[j - 1]) {
			j--;
		}
		if (j == 0) {
			reverse(nums.begin(), nums.end());
			return;
		}
		while (k > j && nums[k] <= nums[j - 1]) {
			k--;
		}
		swap(nums[j - 1], nums[k]);
		sort(nums.begin() + j, nums.end());
		return;
	}
};
class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		next_permutation(nums.begin(), nums.end());
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

33. Search in Rotated Sorted Array (Hard)

Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

*/
class Solution {
public:
	int search(vector<int>& nums, int target) {
		if (nums.empty()) {
			return -1;
		}
		int l = 0, r = nums.size() - 1;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			if (nums[mid] == target) {
				return mid;
			}
			else if (nums[mid] <= nums[r]) {
				if (nums[mid] < target && target <= nums[r]) {
					l = mid + 1;
				}
				else {
					r = mid - 1;
				}
			}
			else {
				if (nums[l] <= target && target < nums[mid]) {
					r = mid - 1;
				}
				else {
					l = mid + 1;
				}
			}
		}
		return -1;
	}
};
/*

34. Search for a Range (Medium)

Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].

*/
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int l = 0, r = nums.size() - 1;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			if (nums[mid] < target) {
				l = mid + 1;
			}
			else if (nums[mid] > target) {
				r = mid - 1;
			}
			else {
				r = mid;
				l = mid;
				while (l > 0 && nums[l - 1] == target) {
					l--;
				}
				while (r < nums.size() - 1 && nums[r + 1] == target) {
					r++;
				}
				return{ l, r };
			}
		}
		return{ -1, -1 };
	}
};
/*

35. Search Insert Position (Medium)

Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0

*/
class Solution {
public:
	int searchInsert(vector<int>& nums, int target) {
		int l = 0, r = nums.size() - 1;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			if (nums[mid] == target) return mid;
			else if (nums[mid] > target) {
				r = mid - 1;
			}
			else {
				l = mid + 1;
			}
		}
		return l;
	}
};
class Solution {
public:
	int searchInsert(vector<int>& nums, int target) {
		int i = 0;
		while (i < nums.size()) {
			if (nums[i] >= target) {
				return i;
			}
			i++;
		}
		return i;
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
		for (int row = 0; row < 9; row++) {
			if (board[row][j] == d) {
				return false;
			}
		}
		for (int col = 0; col < 9; col++) {
			if (board[i][col] == d) {
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

38. Count and Say (Easy)

The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string.

*/
class Solution {
public:
	string countAndSay(int n) {
		if (n == 1) {
			return "1";
		}
		string pre = countAndSay(n - 1), res;
		int i = 0, j = 0;
		while (j < pre.size()) {
			char cur = pre[j];
			while (j + 1 < pre.size() && pre[j] == pre[j + 1]) {
				j++;
			}
			j++;
			res += to_string(j - i) + cur;
			i = j;
		}
		return res;
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

41. First Missing Positive (Hard)

Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.

*/
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		int n = nums.size();
		for (int i = 0; i < n; i++) {
			while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
				swap(nums[i], nums[nums[i] - 1]);
			}
		}
		for (int i = 0; i < n; i++) {
			if (nums[i] != i + 1) {
				return i + 1;
			}
		}
		return n + 1;
	}
};
/*

42. Trapping Rain Water (Hard)

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.


The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!

*/
class Solution {
public:
	int trap(vector<int>& height) {
		int i = 0, j = height.size() - 1, res = 0, left = 0, right = 0;
		while (i <= j) {
			left = max(left, height[i]);
			right = max(right, height[j]);
			res += left < right ? left - height[i++] : right - height[j--];
		}
		return res;
	}
};
/*

43. Multiply Strings (Medium)

Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2.

Note:

The length of both num1 and num2 is < 110.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.

*/
class Solution {
public:
	string multiply(string num1, string num2) {
		if (num1 == "0" || num2 == "0") {
			return "0";
		}
		int s1 = num1.size() - 1, s2 = num2.size() - 1;
		int i = s1 + s2, j = 0, carry = 0;
		string res;
		while (j <= i || carry > 0) {
			for (int k = 0; k <= j; k++) {
				if (k <= s1 && j - k <= s2) {
					carry += (num1[s1 - k] - '0') * (num2[s2 - (j - k)] - '0');
				}
			}
			res += carry % 10 + '0';
			carry /= 10;
			j++;
		}
		reverse(res.begin(), res.end());
		return res;
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

48. Rotate Image (Medium)

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?

*/
class Solution {
public:
	void rotate(vector<vector<int>>& matrix) {
		int n = matrix.size() - 1;
		for (int i = 0; i < (n + 1) / 2; i++) {
			for (int j = i; j < n - i; j++) {
				swap(matrix[i][j], matrix[j][n - i]);
				swap(matrix[i][j], matrix[n - i][n - j]);
				swap(matrix[i][j], matrix[n - j][i]);
			}
		}
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

50. Pow(x, n) (Medium)

Implement pow(x, n).

*/
class Solution {
public:
	double myPow(double x, int n) {
		if (n == 0) {
			return (double)1;
		}
		if (n < 0) {
			if (n == INT_MIN) {
				return 1 / x * myPow(x, n + 1);
			}
			x = 1 / x;
			n = -n;
		}
		double temp = myPow(x, n / 2);
		return n & 1 ? temp *temp * x : temp *temp;
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

54. Spiral Matrix (Medium)

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]

You should return [1,2,3,6,9,8,7,4,5].

*/
class Solution {
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		if (matrix.empty()) {
			return{};
		}
		vector<int> res;
		spiralOrder(matrix, res, matrix.size(), matrix[0].size(), 0);
		return res;
	}
private:
	void spiralOrder(const vector<vector<int>>& matrix, vector<int>& res, int r, int l, int offset) {
		if (l <= 0 || r <= 0) {
			return;
		}
		for (int i = 0; i < l; i++) {
			res.push_back(matrix[offset][i + offset]);
		}
		if (r - 1 == 0) {
			return;
		}
		for (int i = 1; i < r; i++) {
			res.push_back(matrix[i + offset][offset + l - 1]);
		}
		if (l - 1 == 0) {
			return;
		}
		for (int i = l - 2; i >= 0; i--) {
			res.push_back(matrix[offset + r - 1][i + offset]);
		}
		for (int i = r - 2; i >= 1; i--) {
			res.push_back(matrix[offset + i][offset]);
		}
		spiralOrder(matrix, res, r - 2, l - 2, offset + 1);
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
		int step = 0, _size = nums.size();
		for (int i = 0; i < _size; i++) {
			if (step < nums[i]) {
				step = nums[i];
			}
			if (step >= _size - 1 - i) {
				return true;
			}
			if (--step < 0) {
				return false;
			}
		}
		return true;
	}
};
/*

56. Merge Intervals (Hard)

Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].

*/
/**
* Definition for an interval.
* struct Interval {
*     int start;
*     int end;
*     Interval() : start(0), end(0) {}
*     Interval(int s, int e) : start(s), end(e) {}
* };
*/
class Comp {
public:
	bool operator()(Interval in1, Interval in2) {
		return in1.start < in2.start;
	}
}comp;
class Solution {
public:
	vector<Interval> merge(vector<Interval>& intervals) {
		if (intervals.empty()) {
			return{};
		}
		sort(intervals.begin(), intervals.end(), comp);
		vector<Interval> res = { intervals[0] };
		int i = 0, j = 1;
		while (j < intervals.size()) {
			if (res[i].end >= intervals[j].start) {
				res[i].start = min(res[i].start, intervals[j].start);
				res[i].end = max(res[i].end, intervals[j].end);
				j++;
			}
			else {
				res.push_back(intervals[j++]);
				i++;
			}
		}
		return res;
	}
};
/*

57. Insert Interval (Medium)

Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].

*/
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		vector<Interval> res;
		bool inserted = false;
		for (Interval inter : intervals) {
			if (inserted == true) {
				res.push_back(inter);
			}
			else {
				if (newInterval.end < inter.start) {
					res.push_back(newInterval);
					res.push_back(inter);
					inserted = true;
				}
				else if (inter.end < newInterval.start) {
					res.push_back(inter);
				}
				else {
					newInterval.start = min(inter.start, newInterval.start);
					newInterval.end = max(inter.end, newInterval.end);
				}
			}
		}
		if (inserted == false) {
			res.push_back(newInterval);
		}
		return res;
	}
};
/*

58. Length of Last Word (Easy)

Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example,
Given s = "Hello World",
return 5.

*/
class Solution {
public:
	int lengthOfLastWord(string s) {
		int r = s.size() - 1;
		while (r >= 0 && !isalpha(s[r])) {
			r--;
		}
		int l = r;
		while (l >= 0 && isalpha(s[l])) {
			l--;
		}
		return r - l;
	}
};
/*

59. Spiral Matrix II (Medium)

Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]

*/
class Solution {
public:
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> res(n, vector<int>(n));
		int cnt = 1;
		generateMatrix(res, n, 0, cnt);
		return res;
	}
private:
	void generateMatrix(vector<vector<int>>& res, int size, int offset, int cnt) {
		if (size < 1) {
			return;
		}
		for (int i = 0; i < size; i++) {
			res[offset][i + offset] = cnt++;
		}
		for (int i = 1; i < size; i++) {
			res[i + offset][offset + size - 1] = cnt++;
		}
		for (int i = size - 2; i >= 0; i--) {
			res[offset + size - 1][i + offset] = cnt++;
		}
		for (int i = size - 2; i >= 1; i--) {
			res[i + offset][offset] = cnt++;
		}
		generateMatrix(res, size - 2, offset + 1, cnt);
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

61. Rotate List (Medium)

Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* rotateRight(ListNode* head, int k) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *p = head;
		int len = 1;
		while (p->next != NULL) {
			len++;
			p = p->next;
		}
		k %= len;
		p->next = head;
		for (int i = 0; i < len - k;i++) {
			p = p->next;
		}
		head = p->next;
		p->next = NULL;
		return head;
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

66. Plus One (Easy)

Given a non-negative number represented as an array of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.

*/
class Solution {
public:
	vector<int> plusOne(vector<int>& digits) {
		reverse(digits.begin(), digits.end());
		int digit = 1;
		for (int i = 0; i < digits.size(); i++) {
			digit += digits[i];
			digits[i] = digit % 10;
			digit /= 10;
			if (digit == 0) {
				reverse(digits.begin(), digits.end());
				return digits;
			}
		}
		if (digit > 0) {
			digits.push_back(digit);
		}
		reverse(digits.begin(), digits.end());
		return digits;
	}
};
/*

67. Add Binary (Easy)

Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".

*/
class Solution {
public:
	string addBinary(string a, string b) {
		string s = "";
		int c = 0, i = 0, j = 0;
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		while (i < a.size() || j < b.size() || c == 1) {
			c += i < a.size() ? a[i++] - '0' : 0;
			c += j < b.size() ? b[j++] - '0' : 0;
			s += c % 2 + '0';
			c /= 2;
		}
		reverse(s.begin(), s.end());
		return s;
	}
};
/*

68. Text Justification (Hard)

Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Note: Each word is guaranteed not to exceed L in length.

*/
class Solution {
public:
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		vector<string> res;
		for (int i = 0, k, l; i < words.size(); i += k) {
			for (k = l = 0; i + k < words.size() && l + words[i + k].size() <= maxWidth - k; k++) {
				l += words[i + k].size();
			}
			string temp = words[i];
			for (int j = 0; j < k - 1; j++) {
				if (i + k >= words.size()) {
					temp += " ";
				}
				else {
					temp += string((maxWidth - l) / (k - 1) + (j < (maxWidth - l) % (k - 1)), ' ');
				}
				temp += words[i + j + 1];
			}
			temp += string(maxWidth - temp.size(), ' ');
			res.push_back(temp);
		}
		return res;
	}
};
/*

69. Sqrt(x) (Medium)

Implement int sqrt(int x).

Compute and return the square root of x.

*/
class Solution {
public:
	int mySqrt(int x) {
		if (x < 2) {
			return x;
		}
		int l = 1, r = x;
		while (l < r) {
			int mid = l + (r - l) / 2;
			if (x / mid < mid) {
				r = mid;
			}
			else {
				l = mid + 1;
			}
		}
		return r - 1;
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

71. Simplify Path (Medium)

Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
click to show corner cases.

Corner Cases:

Did you consider the case where path = "/../"?
In this case, you should return "/".

Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
In this case, you should ignore redundant slashes and return "/home/foo".

*/
class Solution {
public:
	string simplifyPath(string path) {
		string res = "", token;
		stringstream ss(path);
		vector<string> pos;
		while (getline(ss, token, '/')) {
			if (token == "." || token == "") {
				continue;
			}
			else if (token == "..") {
				if (!pos.empty()) {
					pos.pop_back();
				}
			}
			else {
				pos.push_back(token);
			}
		}
		if (pos.empty()) {
			return "/";
		}
		for (string str : pos) {
			res += '/' + str;
		}
		return res;
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

73. Set Matrix Zeroes (Medium)

Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

click to show follow up.

Follow up:
Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?

*/
class Solution {
public:
	void setZeroes(vector<vector<int>>& matrix) {
		bool row = false, col = false;
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				if (matrix[i][j] == 0) {
					if (i == 0) {
						row = true;
					}
					if (j == 0) {
						col = true;
					}
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}
		for (int i = 1; i < matrix.size(); i++) {
			for (int j = 1; j < matrix[0].size(); j++) {
				if (matrix[0][j] == 0 || matrix[i][0] == 0) {
					matrix[i][j] = 0;
				}
			}
		}
		if (row) {
			for (int j = 0; j < matrix[0].size(); j++) {
				matrix[0][j] = 0;
			}
		}
		if (col) {
			for (int i = 0; i < matrix.size(); i++) {
				matrix[i][0] = 0;
			}
		}
	}
};
/*

74. Search a 2D Matrix (Medium)

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
Given target = 3, return true.

*/
class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int m = matrix.size(), n = matrix[0].size();
		int l = 0, r = m * n - 1;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			int i = mid / n, j = mid % n;
			if (matrix[i][j] < target) {
				l = mid + 1;
			}
			else if (target < matrix[i][j]) {
				r = mid - 1;
			}
			else {
				return true;
			}
		}
		return false;
	}
};
/*

75. Sort Colors (Medium)

Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

click to show follow up.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?

*/
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int i = 0, k = 0, j = nums.size() - 1;
		while (k <= j) {
			if (nums[k] == 0) {
				swap(nums[i++], nums[k++]);
			}
			else if (nums[k] == 2) {
				swap(nums[j--], nums[k]);
			}
			else {
				k++;
			}
		}
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
		int i = 0, len = s.size() + 1;
		vector<int> mapping(256, -len);
		for (char cha : t) {
			mapping[cha] = mapping[cha] > 0 ? mapping[cha] + 1 : 1;
		}
		int slow = 0, fast = 0, cnt = t.size();
		while (fast < s.size()) {
			if (--mapping[s[fast++]] >= 0 && --cnt == 0) {
				while (mapping[s[slow]] < -len || ++mapping[s[slow]] <= 0) {
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
		int row = board.size(), col = board[0].size();
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (search(board, word, i, j, 0)) {
					return true;
				}
			}
		}
		return false;
	}
private:
	bool search(vector<vector<char>>& board, const string& word, int i, int j, int index) {
		if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] == '\0' || board[i][j] != word[index]) {
			return false;
		}
		else if (index + 1 == word.size()) {
			return true;
		}
		char temp = board[i][j];
		board[i][j] = '\0';
		if (search(board, word, i + 1, j, index + 1) || search(board, word, i - 1, j, index + 1) || search(board, word, i, j + 1, index + 1) || search(board, word, i, j - 1, index + 1)) {
			return true;
		}
		board[i][j] = temp;
		return false;
	}
};
/*

80. Remove Duplicates from Sorted Array II (Medium)

Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.

*/
class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() <= 2) {
			return nums.size();
		}
		int index = 2;
		for (int i = 2; i < nums.size(); i++) {
			if (nums[index - 2] != nums[i]) {
				nums[index++] = nums[i];
			}
		}
		return index;
	}
};
////no duplicates as follows
class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.empty()) {
			return 0;
		}
		int index = 1;
		for (int i = 1; i < nums.size(); i++) {
			if (nums[index - 1] != nums[i]) {
				nums[index++] = nums[i];
			}
		}
		return index;
	}
};
class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.empty()) {
			return 0;
		}
		int index = 0;
		for (int i = 1; i < nums.size(); i++) {
			if (nums[index] != nums[i]) {
				nums[++index] = nums[i];
			}
		}
		return index + 1;
	}
};
/*

81. Search in Rotated Sorted Array II (Medium)

Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Write a function to determine if a given target is in the array.

The array may contain duplicates.

*/
class Solution {
public:
	bool search(vector<int>& nums, int target) {
		int l = 0, r = nums.size() - 1;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			if (nums[mid] == target) {
				return true;
			}
			else if (nums[l] < nums[mid]) {
				if (nums[l] <= target && target < nums[mid]) {
					r = mid - 1;
				}
				else {
					l = mid + 1;
				}
			}
			else if (nums[l] > nums[mid]) {
				if (nums[mid] < target && target <= nums[r]) {
					l = mid + 1;
				}
				else {
					r = mid - 1;
				}
			}
			else {
				l++;
			}
		}
		return false;
	}
};
/*

82. Remove Duplicates from Sorted List II (Medium)

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *dummy = new ListNode(-1), *p = dummy;
		dummy->next = head;
		while (head != NULL) {
			if (head->next != NULL && head->val == head->next->val) {
				int temp = head->val;
				while (head != NULL && head->val == temp) {
					head = head->next;
				}
				p->next = head;
			}
			else {
				p->next = head;
				p = p->next;
				head = head->next;
			}
		}
		return dummy->next;
	}
};
/*

83. Remove Duplicates from Sorted List (Easy)

Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *p = head;
		while (p->next != NULL) {
			if (p->val == p->next->val) {
				p->next = p->next->next;
			}
			else {
				p = p->next;
			}
		}
		return head;
	}
};
/*

84. Largest Rectangle in Histogram (Hard)

Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given heights = [2,1,5,6,2,3],
return 10.

*/
class Solution {
public:
	int largestRectangleArea(vector<int>& heights) {
		stack<int> s;
		int res = 0;
		for (int i = 0; i <= heights.size(); i++) {
			int cur = i == heights.size() ? 0 : heights[i];
			while (!s.empty() && cur <= heights[s.top()]) {
				int height = heights[s.top()];
				s.pop();
				int left = s.empty() ? 0 : s.top() + 1;
				res = max(res, height * (i - left));
			}
			s.push(i);
		}
		return res;
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

86. Partition List (Medium)

Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* partition(ListNode* head, int x) {
		ListNode *sh = new ListNode(-1), *lh = new ListNode(-1);
		ListNode *s = sh, *l = lh;
		while (head != NULL) {
			if (head->val < x) {
				s->next = head;
				s = s->next;
			}
			else {
				l->next = head;
				l = l->next;
			}
			head = head->next;
		}
		l->next = NULL;
		s->next = lh->next;
		return sh->next;
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
88. Merge Sorted Array (Easy)

Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.

*/
class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		for (int i = m - 1, j = n - 1, k = m + n - 1; k >= 0; k--) {
			if (i < 0 || j >= 0 && nums1[i] < nums2[j]) {
				nums1[k] = nums2[j--];
			}
			else {
				nums1[k] = nums1[i--];
			}
		}
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

92. Reverse Linked List II (Medium)

Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list.

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		ListNode *head_new = new ListNode(0);
		head_new->next = head;
		ListNode *p = head_new;
		int i = 1;
		while (i < n) {
			if (i++ < m) {
				p = head;
				head = head->next;
			}
			else {
				ListNode *post = head->next;
				head->next = head->next->next;
				post->next = p->next;
				p->next = post;
			}
		}
		return head_new->next;
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
		TreeNode *prev = NULL;
		return isValidBST(root, prev);
	}
private:
	bool isValidBST(TreeNode* root, TreeNode*& prev) {
		if (root == NULL) {
			return true;
		}
		if (!isValidBST(root->left, prev)) {
			return false;
		}
		if (prev != NULL && prev->val >= root->val) {
			return false;
		}
		prev = root;
		return isValidBST(root->right, prev);
	}
};
/*

99. Recover Binary Search Tree (Hard)

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

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
	void recoverTree(TreeNode* root) {
		TreeNode* first = NULL, *second = NULL, *pre = new TreeNode(INT_MIN);
		inOrder(root, first, second, pre);
		swap(first->val, second->val);
		return;
	}
private:
	void inOrder(TreeNode* root, TreeNode*& first, TreeNode*& second, TreeNode*& pre) {
		if (root == NULL) {
			return;
		}
		inOrder(root->left, first, second, pre);
		if (pre->val >= root->val) {
			if (first == NULL) {
				first = pre;
			}
			if (first != NULL) {
				second = root;
			}
		}
		pre = root;
		inOrder(root->right, first, second, pre);
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
		if (p == NULL && q == NULL) {
			return true;
		}
		else if (p == NULL || q == NULL || p->val != q->val) {
			return false;
		}
		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
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

104. Maximum Depth of Binary Tree (Easy)

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

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
	int maxDepth(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}
		int l = maxDepth(root->left), r = maxDepth(root->right);
		return max(l, r) + 1;
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
		return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
	}
private:
	TreeNode* buildTree(const vector<int>& preorder, int pl, int pr, const vector<int>& inorder, int il, int ir) {
		if (pl > pr) {
			return NULL;
		}
		TreeNode *root = new TreeNode(preorder[pl]);
		int index = ir;
		while (inorder[index] != preorder[pl]) {
			index--;
		}
		root->left = buildTree(preorder, pl + 1, pl + index - il, inorder, il, index - 1);
		root->right = buildTree(preorder, pl + index - il + 1, pr, inorder, index + 1, ir);
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
		TreeNode *root = new TreeNode(postorder[pr]);
		int i = il;
		while (postorder[pr] != inorder[i]) {
			i++;
		}
		root->left = BT(inorder, il, i - 1, postorder, pl, pl + i - il - 1);
		root->right = BT(inorder, i + 1, ir, postorder, pl + i - il, pr - 1);
		return root;
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
	TreeNode* sortedArrayToBST(const vector<int>& nums, int l, int r) {
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
		return isbalanced(root) != -1;
	}
private:
	int isbalanced(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}
		int l = isbalanced(root->left), r = isbalanced(root->right);
		if (l == -1 || r == -1 || abs(l - r) > 1) {
			return -1;
		}
		return max(l, r) + 1;
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
		res_sub.push_back(root->val);
		if (root->left == NULL && root->right == NULL && root->val == sum) {
			res.push_back(res_sub);
			res_sub.pop_back();
			return;
		}
		pathSum(root->left, res, res_sub, sum - root->val);
		pathSum(root->right, res, res_sub, sum - root->val);
		res_sub.pop_back();
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
	void flatten(TreeNode* root) {
		while (root != NULL) {
			if (root->left != NULL && root->right != NULL) {
				TreeNode *temp = root->left;
				while (temp->right != NULL) {
					temp = temp->right;
				}
				temp->right = root->right;
			}
			if (root->left != NULL) {
				root->right = root->left;
			}
			root->left = NULL;
			root = root->right;
		}
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
		while (root->left != NULL) {
			TreeLinkNode *p = root;
			while (p != NULL) {
				p->left->next = p->right;
				if (p->next != NULL) {
					p->right->next = p->next->left;
				}
				p = p->next;
			}
			root = root->left;
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

118. Pascal's Triangle (Easy)

Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
	 [1],
	[1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]

*/
class Solution {
public:
	vector<vector<int>> generate(int numRows) {
		if (numRows < 1) {
			return{};
		}
		vector<vector<int>> res;
		vector<int> unit;
		for (int i = 0; i < numRows; i++) {
			for (int j = unit.size() - 1; j > 0; j--) {
				unit[j] += unit[j - 1];
			}
			unit.push_back(1);
			res.push_back(unit);
		}
		return res;
	}
};
/*

119. Pascal's Triangle II (Easy)

Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

*/
class Solution {
public:
	vector<int> getRow(int rowIndex) {
		vector<int> res = { 1 };
		for (int i = 1; i <= rowIndex; i++) {
			for (int j = res.size() - 1; j > 0; j--) {
				res[j] += res[j - 1];
			}
			res.push_back(1);
		}
		return res;
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
	int maxPathSum(TreeNode* root, int& res) {
		if (root == NULL) {
			return 0;
		}
		int l = maxPathSum(root->left, res), r = maxPathSum(root->right, res);
		l = l > 0 ? l : 0;
		r = r > 0 ? r : 0;
		res = max(res, l + r + root->val);
		return max(l, r) + root->val;
	}
};
/*

125. Valid Palindrome (Easy)

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome.

*/
class Solution {
public:
	bool isPalindrome(string s) {
		int i = 0, j = s.size() - 1;
		while (i < j) {
			while (i < j && !isalnum(s[i])) {
				i++;
			}
			while (i < j && !isalnum(s[j])) {
				j--;
			}
			if (tolower(s[i++]) != tolower(s[j--])) {
				return false;
			}
		}
		return true;
	}
};
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
		int res = 0, num = 0;
		sumNumbers(root, res, num);
		return res;
	}
private:
	void sumNumbers(TreeNode* root, int& res, int& num) {
		if (root == NULL) {
			return;
		}
		num = num * 10 + root->val;
		if (root->left == NULL && root->right == NULL) {
			res += num;
			num /= 10;
			return;
		}
		if (root->left != NULL) {
			sumNumbers(root->left, res, num);
		}
		if (root->right != NULL) {
			sumNumbers(root->right, res, num);
		}
		num /= 10;
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
		for (int j = 0; j < _size; j++) {
			for (int i = 0; i < _size; i++) {
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

135. Candy (Hard)

There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?

*/
class Solution {
public:
	int candy(vector<int>& ratings) {
		if (ratings.size() <= 1) {
			return ratings.size();
		}
		vector<int> num(ratings.size(), 1);
		for (int i = 1; i < ratings.size(); i++) {
			if (ratings[i] > ratings[i - 1])
				num[i] = num[i - 1] + 1;
		}
		for (int i = ratings.size() - 1; i > 0; i--) {
			if (ratings[i - 1] > ratings[i]) {
				num[i - 1] = max(num[i] + 1, num[i - 1]);
			}
		}
		return accumulate(num.begin(), num.end(), 0);
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

137. Single Number II (Medium)

Given an array of integers, every element appears three times except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

*/
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		int one = 0, two = 0, three = 0;
		for (int num : nums) {
			two |= one & num;
			one ^= num;
			three = one & two;
			one &= ~three;
			two &= ~three;
		}
		return one;
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
		unordered_map<RandomListNode*, RandomListNode*> mapping;
		RandomListNode *newhead = new RandomListNode(head->label);
		RandomListNode *cur = newhead;
		mapping[head] = newhead;
		while (head != NULL) {
			if (head->next != NULL) {
				if (mapping.find(head->next) == mapping.end()) {
					RandomListNode *node = new RandomListNode(head->next->label);
					mapping[head->next] = node;
				}
				cur->next = mapping[head->next];
			}
			if (head->random != NULL) {
				if (mapping.find(head->random) == mapping.end()) {
					RandomListNode *node = new RandomListNode(head->random->label);
					mapping[head->random] = node;
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

141. Linked List Cycle (Easy)

Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	bool hasCycle(ListNode *head) {
		if (head == NULL || head->next == NULL) {
			return false;
		}
		ListNode *slow = head, *fast = head;
		while (fast->next != NULL && fast->next->next != NULL) {
			slow = slow->next;
			fast = fast->next->next;
			if (fast == slow) {
				return true;
			}
		}
		return false;
	}
};
/*

142. Linked List Cycle II (Medium)

Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		if (head == NULL || head->next == NULL) {
			return NULL;
		}
		ListNode *s = head, *f = head;
		while (f != NULL && f->next != NULL) {
			s = s->next;
			f = f->next->next;
			if (s == f) {
				break;
			}
		}
		if (s != f) {
			return NULL;
		}
		while (head != s) {
			head = head->next;
			s = s->next;
		}
		return head;
	}
};
/*

143. Reorder List (Medium)

Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.

*/
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	void reorderList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return;
		}
		ListNode *s = head, *f = head;
		while (f->next != NULL && f->next->next != NULL) {
			f = f->next->next;
			s = s->next;
		}
		ListNode *newhead = reverse(s->next);
		s->next = NULL;
		s = head;
		while (newhead != NULL) {
			ListNode *post = newhead->next;
			newhead->next = s->next;
			s->next = newhead;
			s = s->next->next;
			newhead = post;
		}
	}
private:
	ListNode* reverse(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *pre = NULL;
		while (head != NULL) {
			ListNode* post = head->next;
			head->next = pre;
			pre = head;
			head = post;
		}
		return pre;
	}
};
/*

144. Binary Tree Preorder Traversal (Medium)

Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
	\
	 2
	/
   3
return [1,2,3].

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
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> res;
		traversal(root, res);
		return res;
	}
	void traversal(TreeNode* root, vector<int>& res) {
		if (root) {
			res.push_back(root->val);
			traversal(root->left, res);
			traversal(root->right, res);
		}
	}
};
class Solution {
public:
	vector<int> preorderTraversal(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<int> res;
		stack<TreeNode*> sta;
		sta.push(root);
		while (!sta.empty()) {
			TreeNode *node = sta.top();
			sta.pop();
			res.push_back(node->val);
			if (node->right != NULL) {
				sta.push(node->right);
			}
			if (node->left != NULL) {
				sta.push(node->left);
			}
		}
		return res;
	}
};
/*

145. Binary Tree Postorder Traversal (Hard)

Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
	\
	 2
	/
   3
return [3,2,1].

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
	vector<int> postorderTraversal(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<int> res;
		stack<TreeNode*> sta;
		TreeNode *pre = NULL;
		sta.push(root);
		while (!sta.empty()) {
			TreeNode *cur = sta.top();
			if (pre == NULL || pre->left == cur || pre->right == cur) {
				if (cur->left != NULL) {
					sta.push(cur->left);
				}
				else if (cur->right != NULL) {
					sta.push(cur->right);
				}
				else {
					res.push_back(cur->val);
					sta.pop();
				}
			}
			else if (cur->left == pre) {
				if (cur->right != NULL) {
					sta.push(cur->right);
				}
				else {
					res.push_back(cur->val);
					sta.pop();
				}
			}
			else {
				res.push_back(cur->val);
				sta.pop();
			}
			pre = cur;
		}
		return res;
	}
};
/*

146. LRU Cache (Hard)

Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

*/
class KeyValue {
public:
	int key, value;
	KeyValue* next;
	KeyValue(int k, int v) : key(k), value(v), next(NULL) {}
};
class LRUCache {
public:
	unordered_map<int, KeyValue*> mapping;//map key the the previous node
	KeyValue *head, *tail;
	int capacity, size;
	LRUCache(int capacity) : capacity(capacity), size(0) {
		this->head = new KeyValue(0, 0);
		this->tail = head;
		mapping.clear();
	}

	int get(int key) {
		if (mapping.find(key) == mapping.end()) {
			return -1;
		}
		moveToTail(mapping[key]);//move this one to the tail
		return mapping[key]->next->value;
	}

	void set(int key, int value) {
		if (mapping.find(key) != mapping.end()) {
			mapping[key]->next->value = value;
			moveToTail(mapping[key]);
		}
		else {
			KeyValue *node = new KeyValue(key, value);
			tail->next = node;
			mapping[key] = tail;
			tail = node;
			size++;
			if (size > capacity) {
				mapping.erase(head->next->key);
				head->next = head->next->next;
				if (head->next != NULL) {
					mapping[head->next->key] = head;
				}
				size--;
			}
		}
	}
private:
	void moveToTail(KeyValue *pre) {
		if (pre->next == tail) {
			return;
		}
		KeyValue *node = pre->next;
		pre->next = node->next;
		if (node->next != NULL) {
			mapping[node->next->key] = pre;
		}
		tail->next = node;
		node->next = NULL;
		mapping[node->key] = tail;
		tail = node;
	}
};
/*

147. Insertion Sort List (Medium)

Sort a linked list using insertion sort.

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* insertionSortList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode* dummy = new ListNode(-1), *p = dummy;
		while (head != NULL) {
			ListNode *next = head->next;
			while (p->next != NULL && p->next->val < head->val) {
				p = p->next;
			}
			head->next = p->next;
			p->next = head;
			p = dummy;
			head = next;
		}
		return dummy->next;
	}
};
/*

148. Sort List (Medium)

Sort a linked list in O(n log n) time using constant space complexity.

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* sortList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *newhead = split(head);
		return sort_combine(sortList(head), sortList(newhead));
	}
private:
	ListNode* split(ListNode* head) {
		ListNode *s = head, *f = head;
		while (f->next != NULL && f->next->next != NULL) {
			s = s->next;
			f = f->next->next;
		}
		f = s->next;
		s->next = NULL;
		return f;
	}
	ListNode* sort_combine(ListNode* head, ListNode* s) {
		ListNode *head_new = new ListNode(-1), *p = head_new;
		while (head != NULL || s != NULL) {
			if (head == NULL || s != NULL && head->val > s->val) {
				p->next = s;
				s = s->next;
			}
			else {
				p->next = head;
				head = head->next;
			}
			p = p->next;
		}
		return head_new->next;
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
		int res = 0;
		for (int i = 0; i < points.size(); i++) {
			int p0_num = 1, k_max = 0;
			unordered_map<double, int> mapping;
			for (int j = i + 1; j < points.size(); j++) {
				if (points[i].x == points[j].x && points[i].y == points[j].y) {
					p0_num++;
				}
				else {
					double k;
					if (points[i].x == points[j].x) {
						k = INT_MAX;
					}
					else {
						k = double(points[i].y - points[j].y) / double(points[i].x - points[j].x);
					}
					k_max = max(k_max, ++mapping[k]);
				}
			}
			res = max(res, k_max + p0_num);
		}
		return res;
	}
};
/*

150. Evaluate Reverse Polish Notation (Medium)

Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:
["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

*/
class Solution {
public:
	int evalRPN(vector<string>& tokens) {
		stack<int> sta;
		for (string t : tokens) {
			if (t == "+" || t == "-" || t == "*" || t == "/") {
				int b = sta.top();
				sta.pop();
				int a = sta.top();
				sta.pop();
				if (t == "+") {
					sta.push(a + b);
				}
				else if (t == "-") {
					sta.push(a - b);
				}
				else if (t == "*") {
					sta.push(a * b);
				}
				else {
					sta.push(a / b);
				}
			}
			else {
				sta.push(stoi(t));
			}
		}
		return sta.top();
	}
};
/*

151. Reverse Words in a String (Medium)

Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Update (2015-02-12):
For C programmers: Try to solve it in-place in O(1) space.

click to show clarification.

Clarification:
What constitutes a word?
A sequence of non-space characters constitutes a word.

Could the input string contain leading or trailing spaces?
Yes. However, your reversed string should not contain leading or trailing spaces.

How about multiple spaces between two words?
Reduce them to a single space in the reversed string.

*/
class Solution {
public:
	void reverseWords(string &s) {
		istringstream ss(s);
		string temp;
		ss >> temp;
		s = temp;
		while (ss >> temp) {
			s = temp + ' ' + s;
		}
		return;
	}
};
class Solution {
public:
	void reverseWords(string &s) {
		int i = 0, j = 0;
		bool wordfound = false;
		while (j < s.size()) {
			if (s[j] != ' ') {
				if (wordfound) {
					s[i++] = ' ';
				}
				int start = i;
				while (j < s.size() && s[j] != ' ') {
					s[i++] = s[j++];
				}
				wordfound = true;
				reverse(s.begin() + start, s.begin() + i);
			}
			j++;
		}
		s.resize(i);
		reverse(s.begin(), s.end());
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

153. Find Minimum in Rotated Sorted Array (Medium)

Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.

*/
class Solution {
public:
	int findMin(vector<int>& nums) {
		int l = 0, r = nums.size() - 1;
		while (l < r) {
			int mid = l + (r - l) / 2;
			if (nums[mid] > nums[r]) {
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}
		return nums[l];
	}
};
/*

154. Find Minimum in Rotated Sorted Array II (Hard)

Follow up for "Find Minimum in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

The array may contain duplicates.

*/
class Solution {
public:
	int findMin(vector<int>& nums) {
		int l = 0, r = nums.size() - 1;
		while (l < r) {
			int mid = l + (r - l) / 2;
			if (nums[mid] == nums[r]) {
				r--;
			}
			else if (nums[mid] > nums[r]) {
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}
		return nums[l];
	}
};
/*

155. Min Stack (Easy)

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.

Example:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

*/
class MinStack {
public:
	stack<int> s, s_min;
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		s.push(x);
		if (s_min.empty() || x <= s_min.top()) {
			s_min.push(x);
		}
	}

	void pop() {
		if (s.top() == s_min.top()) {
			s_min.pop();
		}
		s.pop();
	}

	int top() {
		return s.top();
	}

	int getMin() {
		return s_min.top();
	}
};
/**
* Your MinStack object will be instantiated and called as such:
* MinStack obj = new MinStack();
* obj.push(x);
* obj.pop();
* int param_3 = obj.top();
* int param_4 = obj.getMin();
*/
/*

156. Binary Tree Upside Down (Medium)

Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node) or empty, flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. Return the new root.

For example:
Given a binary tree {1,2,3,4,5},
1
/ \
2   3
/ \
4   5
return the root of the binary tree [4,5,2,#,#,3,1].
4
/ \
5   2
/ \
3   1

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
	TreeNode* upsideDownBinaryTree(TreeNode* root) {
		if (root == NULL || root->left == NULL) {
			return root;
		}
		TreeNode *node = upsideDownBinaryTree(root->left);
		root->left->left = root->right;
		root->left->right = root;
		root->left = NULL;
		root->right = NULL;
		return node;
	}
};
/*

157. Read N Characters Given Read4 (Easy)

The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function will only be called once for each test case.

*/
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
	/**
	* @param buf Destination buffer
	* @param n   Maximum number of characters to read
	* @return    The number of characters read
	*/
	int read(char *buf, int n) {
		int res = 0;
		while (n > 0) {
			int temp = min(read4(buf + res), n);
			res += temp;
			if (temp < 4) {
				break;
			}
			n -= 4;
		}
		return res;
	}
};
/*

158. Read N Characters Given Read4 II - Call multiple times (Hard)

The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called multiple times.

*/
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
	/**
	* @param buf Destination buffer
	* @param n   Maximum number of characters to read
	* @return    The number of characters read
	*/
	int read(char *buf, int n) {
		int i = 0;
		while (i < n) {
			if (i4 >= n4) {
				i4 = 0;
				n4 = read4(buf4);
				if (n4 == 0) {
					break;
				}
			}
			buf[i++] = buf4[i4++];
		}
		return i;
	}
	char buf4[4];
	int i4 = 0, n4 = 0;
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
		vector<int> t(256, 0);
		int sl = 0, f = 0, res = 0, cnt = 0;
		while (f < s.size()) {
			if (++t[s[f++]] == 1) {
				cnt++;
			}
			while (cnt > 2) {
				--t[s[sl++]];
				if (t[s[sl - 1]] == 0) {
					cnt--;
				}
			}
			res = max(f - sl, res);
		}
		return res;
	}
};
/*

160. Intersection of Two Linked Lists (Easy)

Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:          a1 → a2
				   ↘
					 c1 → c2 → c3
				   ↗
B:     b1 → b2 → b3
begin to intersect at node c1.


Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.

*/
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		if (headA == NULL || headB == NULL) {
			return NULL;
		}
		ListNode *p1 = headA, *p2 = headB;
		while (p1 != NULL && p2 != NULL && p1 != p2) {
			p1 = p1->next;
			p2 = p2->next;
			if (p1 == p2) {
				return p1;
			}
			if (p1 == NULL) {
				p1 = headB;
			}
			if (p2 == NULL) {
				p2 = headA;
			}
		}
		return p1;
	}
};
/*

161. One Edit Distance (Medium)

Given two strings S and T, determine if they are both one edit distance apart.

*/
class Solution {
public:
	bool isOneEditDistance(string s, string t) {
		if (s == t || abs(int(s.size() - t.size())) > 1) {
			return false;
		}
		int i = 0, j = 0;
		bool flag = false;
		while (i < s.size() && j < t.size()) {
			if (s[i] == t[j]) {
				i++;
				j++;
			}
			else {
				if (flag == true) {
					return false;
				}
				if (s.size() >= t.size()) {
					i++;
				}
				if (s.size() <= t.size()) {
					j++;
				}
				flag = true;
			}
		}
		return true;
	}
};
/*

162. Find Peak Element (Medium)

A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

click to show spoilers.

Note:
Your solution should be in logarithmic complexity.

*/
class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		int l = 0, r = nums.size() - 1;
		while (l < r) {
			int mid = l + (r - l) / 2;
			if (nums[mid] < nums[mid + 1]) {
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}
		return l;
	}
};
/*

163. Missing Ranges (Medium)

Given a sorted integer array where the range of elements are in the inclusive range [lower, upper], return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].

*/
class Solution {
public:
	vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
		vector<string> res;
		for (int i = 0; i < nums.size(); i++) {
			if (lower < nums[i]) {
				res.push_back(range(lower, nums[i] - 1));
			}
			lower = nums[i] + 1;
		}
		if (nums.empty() || nums.back() < upper) {
			res.push_back(range(lower, upper));
		}
		return res;
	}
private:
	string range(int lower, int upper) {
		return lower == upper ? to_string(lower) : to_string(lower) + "->" + to_string(upper);
	}
};
/*

164. Maximum Gap (Hard)

Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Try to solve it in linear time/space.

Return 0 if the array contains less than 2 elements.

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.

*/
class Solution {
public:
	int maximumGap(vector<int>& nums) {
		if (nums.empty()) {
			return 0;
		}
		int minnum = nums[0], maxnum = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			minnum = min(minnum, nums[i]);
			maxnum = max(maxnum, nums[i]);
		}
		int gap = (int)ceil((double)(maxnum - minnum) / (nums.size() - 1));
		vector<int> bucketmin(nums.size() - 1, INT_MAX);
		vector<int> bucketmax(nums.size() - 1, INT_MIN);
		for (int num : nums) {
			if (num == minnum || num == maxnum) {
				continue;
			}
			int idx = (num - minnum) / gap;
			bucketmin[idx] = min(num, bucketmin[idx]);
			bucketmax[idx] = max(num, bucketmax[idx]);
		}
		int maxGap = INT_MIN, pre = minnum;
		for (int i = 0; i < nums.size() - 1; i++) {
			if (bucketmin[i] == INT_MAX && bucketmax[i] == INT_MIN) {
				continue;
			}
			maxGap = max(maxGap, bucketmin[i] - pre);
			pre = bucketmax[i];
		}
		maxGap = max(maxGap, maxnum - pre);
		return maxGap;
	}
};
/*

165. Compare Version Numbers (Easy)

Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:

0.1 < 1.1 < 1.2 < 13.37

*/
class Solution {
public:
	int compareVersion(string version1, string version2) {
		vector<int> ver1 = split(version1, '.'), ver2 = split(version2, '.');
		int index = 0;
		for (; index < min(ver1.size(), ver2.size()); index++) {
			if (ver1[index] > ver2[index]) {
				return 1;
			}
			else if (ver1[index] < ver2[index]) {
				return -1;
			}
		}
		if (ver1.size() > ver2.size()) {
			while (index < ver1.size() && ver1[index] == 0) {
				index++;
			}
			if (index < ver1.size()) {
				return 1;
			}
		}
		if (ver1.size() < ver2.size()) {
			while (index < ver2.size() && ver2[index] == 0) {
				index++;
			}
			if (index < ver2.size()) {
				return -1;
			}
		}
		return 0;
	}
private:
	vector<int> split(const string& version, char sign) {
		vector<int> res;
		stringstream str(version);
		string item;
		while (getline(str, item, sign)) {
			res.push_back(atoi(item.c_str()));
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

167. Two Sum II - Input array is sorted (Medium)

Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2

*/
class Solution {
public:
	vector<int> twoSum(vector<int>& numbers, int target) {
		int i = 0, j = numbers.size() - 1;
		while (i < j) {
			if (numbers[i] + numbers[j] > target) {
				j--;
			}
			else if (numbers[i] + numbers[j] < target) {
				i++;
			}
			else {
				return{ i + 1, j + 1 };
			}
		}
		return{};
	}
};
/*

168. Excel Sheet Column Title (Easy)

Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

	1 -> A
	2 -> B
	3 -> C
	...
	26 -> Z
	27 -> AA
	28 -> AB

*/
class Solution {
public:
	string convertToTitle(int n) {
		string res;
		while (n > 0) {
			res += (n - 1) % 26 + 'A';
			n = (n - 1) / 26;
		}
		reverse(res.begin(), res.end());
		return res;
	}
};
/*

169. Majority Element (Easy)

Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

*/
class Solution {
public:
	int majorityElement(vector<int>& nums) {
		int res, cnt = 0;
		for (int num : nums) {
			if (cnt == 0) {
				cnt = 1;
				res = num;
			}
			else {
				cnt = num == res ? cnt + 1 : cnt - 1;
				if (cnt > nums.size() / 2) {
					return res;
				}
			}
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

171. Excel Sheet Column Number (Easy)

Related to question Excel Sheet Column Title

Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28

*/
class Solution {
public:
	int titleToNumber(string s) {
		int res = 0;
		for (char cha : s) {
			res = 26 * res + (cha - 'A' + 1);
		}
		return res;
	}
};
/*

172. Factorial Trailing Zeroes (Easy)

Given an integer n, return the number of trailing zeroes in n!.'/[/'

Note: Your solution should be in logarithmic time complexity.

*/
class Solution {
public:
	int trailingZeroes(int n) {
		int res = 0;
		while (n > 0) {
			n /= 5;
			res += n;
		}
		return res;
	}
};
/*

173. Binary Search Tree Iterator (Medium)

Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.

*/
/**
* Definition for binary tree
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class BSTIterator {
private:
	void postorder(TreeNode* root, stack<int>& s) {
		if (root != NULL) {
			postorder(root->right, s);
			s.push(root->val);
			postorder(root->left, s);
		}
	}
public:
	stack<int> s;
	BSTIterator(TreeNode *root) {
		postorder(root, s);
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !s.empty();
	}

	/** @return the next smallest number */
	int next() {
		int temp = s.top();
		s.pop();
		return temp;
	}
};
/**
* Your BSTIterator will be called like this:
* BSTIterator i = BSTIterator(root);
* while (i.hasNext()) cout << i.next();
*/
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

179. Largest Number (Medium)

Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.

*/
class Comp {
public:
	bool operator()(int i, int j) {
		return to_string(i) + to_string(j) > to_string(j) + to_string(i);
	}
}comp;
class Solution {
public:
	string largestNumber(vector<int>& nums) {
		if (nums.empty()) {
			return "";
		}
		sort(nums.begin(), nums.end(), comp);
		if (nums[0] == 0) {
			return "0";
		}
		string res;
		for (int num : nums) {
			res += to_string(num);
		}
		return res;
	}
};
/*

186. Reverse Words in a String II (Medium)

Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.

The input string does not contain leading or trailing spaces and the words are always separated by a single space.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Could you do it in-place without allocating extra space?

Related problem: Rotate Array

*/
class Solution {
public:
	void reverseWords(string &s) {
		int i = 0, j = 0;
		while (j < s.size()) {
			while (j < s.size() && s[j] != ' ') {
				j++;
			}
			reverse(s.begin() + i, s.begin() + j);
			i = ++j;
		}
		reverse(s.begin(), s.end());
	}
};
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

189. Rotate Array (Easy)

Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.

*/
class Solution {
public:
	void rotate(vector<int>& nums, int k) {
		if (nums.empty()) {
			return;
		}
		k %= nums.size();
		reverse(nums.end() - k, nums.end());
		reverse(nums.begin(), nums.end() - k);
		reverse(nums.begin(), nums.end());
	}
};
/*

190. Reverse Bits (Easy)

Reverse bits of a given 32 bits unsigned integer.

For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).

*/
class Solution {
public:
	uint32_t reverseBits(uint32_t n) {
		uint32_t res = 0;
		int bit = 31;
		while (n > 0) {
			res |= (n & 0x1) << bit;
			n >>= 1;
			bit--;
		}
		return res;
	}
};
/*

191. Number of 1 Bits (Easy)

Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).

For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, so the function should return 3.

*/
class Solution {
public:
	int hammingWeight(uint32_t n) {
		int res = 0;
		while (n != 0) {
			res++;
			n &= (n - 1);
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

201. Bitwise AND of Numbers Range (Medium)

Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.

For example, given the range [5, 7], you should return 4.

*/
class Solution {
public:
	int rangeBitwiseAnd(int m, int n) {
		int bit = 1;
		while (m != n) {
			m >>= 1;
			n >>= 1;
			bit <<= 1;
		}
		return m * bit;
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

203. Remove Linked List Elements (Easy)

Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* removeElements(ListNode* head, int val) {
		ListNode* dummy = new ListNode(-1);
		dummy->next = head;
		ListNode *p = dummy;
		while (p->next != NULL) {
			if (p->next->val == val) {
				p->next = p->next->next;
			}
			else {
				p = p->next;
			}
		}
		return dummy->next;
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

206. Reverse Linked List (Easy)

Reverse a singly linked list.

click to show more hints.

Hint:

A linked list can be reversed either iteratively or recursively. Could you implement both?

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *pre = NULL;
		while (head != NULL) {
			ListNode *post = head->next;
			head->next = pre;
			pre = head;
			head = post;
		}
		return pre;
	}
};
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *newhead = reverseList(head->next);
		head->next->next = head;
		head->next = NULL;
		return newhead;
	}
};
/*

208. Implement Trie (Prefix Tree) (Medium)

Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.

*/
class TrieNode {
public:
	TrieNode *next[26];
	bool isWord;
	TrieNode() :isWord(false), next({ NULL }) {}
};
class Trie {
public:
	/** Initialize your data structure here. */
	Trie() {
		root = new TrieNode();
	}

	/** Inserts a word into the trie. */
	void insert(string word) {
		TrieNode *p = root;
		for (int i = 0; i < word.size(); i++) {
			if (p->next[word[i] - 'a'] == NULL) {
				p->next[word[i] - 'a'] = new TrieNode();
			}
			p = p->next[word[i] - 'a'];
		}
		p->isWord = true;
	}

	/** Returns if the word is in the trie. */
	bool search(string word) {
		TrieNode *p = find(word);
		return p != NULL && p->isWord == true;
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		return find(prefix) != NULL;
	}
private:
	TrieNode *root;
	TrieNode* find(string word) {
		TrieNode *p = root;
		for (int i = 0; i < word.size() && p != NULL; i++) {
			p = p->next[word[i] - 'a'];
		}
		return p;
	}
};
/**
* Your Trie object will be instantiated and called as such:
* Trie obj = new Trie();
* obj.insert(word);
* bool param_2 = obj.search(word);
* bool param_3 = obj.startsWith(prefix);
*/
/*

209. Minimum Size Subarray Sum (Medium)

Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

click to show more practice.

More practice:

If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).

*/
class Solution {
public:
	int minSubArrayLen(int s, vector<int>& nums) {
		int res = nums.size() + 1, sum = 0;
		int i = 0, j = 0;
		while (j < nums.size()) {
			while (j < nums.size() && sum < s) {
				sum += nums[j++];
			}
			while (i < nums.size() && sum >= s) {
				sum -= nums[i++];
			}
			res = min(res, j - i + 1);
		}
		return res == nums.size() + 1 ? 0 : res;
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

214. Shortest Palindrome (Hard)

Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".

*/
class Solution {
public:
	string shortestPalindrome(string s) {
		string rev = s;
		reverse(rev.begin(), rev.end());
		string l = s + "#" + rev;
		vector<int> t(l.size(), 0);
		for (int i = 1; i < l.size(); i++) {
			int j = t[i - 1];
			while (j > 0 && l[i] != l[j]) {
				j = t[j - 1];
			}
			t[i] = (j += l[i] == l[j]);
		}
		return rev.substr(0, s.size() - t.back()) + s;
	}
};
/*

215. Kth Largest Element in an Array (Medium)

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note:
You may assume k is always valid, 1 ≤ k ≤ array's length.

*/
class Comp {
public:
	bool operator()(int num1, int num2) {
		return num1 > num2;
	}
};
class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		priority_queue<int, vector<int>, Comp> pq;
		for (int num : nums) {
			pq.push(num);
			if (pq.size() > k) {
				pq.pop();
			}
		}
		return pq.top();
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

220. Contains Duplicate III (Medium)

Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.

*/
class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		if (k < 1 || t < 0) {
			return false;
		}
		unordered_map<long, long> mapping;
		for (int i = 0; i < nums.size(); i++) {
			long remappedNum = (long)nums[i] - INT_MIN, bucket = remappedNum / ((long)t + 1);
			if (mapping.count(bucket)
				|| mapping.count(bucket - 1) && remappedNum - mapping[bucket - 1] <= t
				|| mapping.count(bucket + 1) && mapping[bucket + 1] - remappedNum <= t) {
				return true;
			}
			if (mapping.size() >= k) {
				long lastBucket = ((long)nums[i - k] - INT_MIN) / ((long)t + 1);
				mapping.erase(lastBucket);
			}
			mapping[bucket] = remappedNum;
		}
		return false;
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

222. Count Complete Tree Nodes (Medium)

Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled,
and all nodes in the last level are as far left as possible. It can have between 1 and
2h nodes inclusive at the last level h.

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
	int countNodes(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}
		int lh = 0, rh = 0;
		TreeNode *l = root, *r = root;
		while (l != NULL) {
			lh++;
			l = l->left;
		}
		while (r != NULL) {
			rh++;
			r = r->right;
		}
		if (lh == rh) {
			return (1 << lh) - 1;
		}
		return 1 + countNodes(root->left) + countNodes(root->right);
	}
};
class Solution {
public:
	int countNodes(TreeNode* root) {
		if (!root) return 0;
		int h = 0, sum = 0;
		TreeNode *t = root, *t0 = NULL;
		while (t) {
			t = t->left;
			h++;
		}
		t = root;
		int level = h - 2;
		while (level > -1) {
			t0 = t->left;
			for (int i = 0; i < level; i++)
				t0 = t0->right;
			if (t0) {
				sum += 1 << level;
				t = t->right;
			}
			else t = t->left;
			level--;
		}
		if (t) sum++;
		return sum + ((1 << (h - 1)) - 1);
	}
};
/*

223. Rectangle Area (Easy)

Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.

Assume that the total area is never beyond the maximum possible value of int.

*/
class Solution {
public:
	int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
		if (C <= E || H <= B || G <= A || D <= F) {
			return (C - A) * (D - B) + (G - E) * (H - F);
		}
		return (C - A) * (D - B) + (G - E) * (H - F) - (min(C, G) - max(A, E)) * (min(D, H) - max(B, F));
	}
};
/*

225. Implement Stack using Queues (Easy)

Implement the following operations of a stack using queues.

push(x) -- Push element x onto stack.

pop() -- Removes the element on top of the stack.

top() -- Get the top element.

empty() -- Return whether the stack is empty.

Notes:

You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.

Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue.

You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).

*/
class Stack {
public:
	queue<int> q1, q2;
	// Push element x onto stack.
	void push(int x) {
		if (q1.empty()) {
			q1.push(x);
			while (!q2.empty()) {
				q1.push(q2.front());
				q2.pop();
			}
		}
		else {
			q2.push(x);
			while (!q1.empty()) {
				q2.push(q1.front());
				q1.pop();
			}
		}
	}

	// Removes the element on top of the stack.
	void pop() {
		if (!q1.empty()) {
			q1.pop();
		}
		if (!q2.empty()) {
			q2.pop();
		}
	}

	// Get the top element.
	int top() {
		if (!q1.empty()) {
			return q1.front();
		}
		if (!q2.empty()) {
			return q2.front();
		}
		return -1;
	}

	// Return whether the stack is empty.
	bool empty() {
		return q1.empty() && q2.empty();
	}
};
/*

226. Invert Binary Tree (Easy)

Invert a binary tree.

	 4
   /   \
  2     7
 / \   / \
1   3 6   9
to
	 4
   /   \
  7     2
 / \   / \
9   6 3   1

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
	TreeNode* invertTree(TreeNode* root) {
		if (root == NULL) {
			return root;
		}
		swap(root->left, root->right);
		invertTree(root->left);
		invertTree(root->right);
		return root;
	}
};
/*

228. Summary Ranges (Medium)

Given a sorted integer array without duplicates, return the summary of its ranges.

For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].

*/
class Solution {
public:
	vector<string> summaryRanges(vector<int>& nums) {
		if (nums.empty()) {
			return{};
		}
		vector<string> res;
		int i = 0;
		while (i < nums.size()) {
			int start = nums[i];
			while (i < nums.size() - 1 && nums[i] + 1 == nums[i + 1]) {
				i++;
			}
			if (start == nums[i]) {
				res.push_back(to_string(start));
			}
			else {
				res.push_back(to_string(start) + "->" + to_string(nums[i]));
			}
			i++;
		}
		return res;
	}
};
/*

229. Majority Element II (Medium)

Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.

Hint:

How many majority elements could it possibly have?
Do you have a better hint? Suggest it!

*/
class Solution {
public:
	vector<int> majorityElement(vector<int>& nums) {
		if (nums.empty()) {
			return{};
		}
		int num1, num2, cnt1 = 0, cnt2 = 0;
		for (int num : nums) {
			if (num1 == num) {
				cnt1++;
			}
			else if (num2 == num) {
				cnt2++;
			}
			else if (cnt1 == 0) {
				num1 = num;
				cnt1++;
			}
			else if (cnt2 == 0) {
				num2 = num;
				cnt2++;
			}
			else {
				cnt1--;
				cnt2--;
			}
		}
		cnt1 = 0;
		cnt2 = 0;
		for (int num : nums) {
			if (num == num1) {
				cnt1++;
			}
			else if (num == num2) {
				cnt2++;
			}
		}
		vector<int> res;
		if (cnt1 > nums.size() / 3) {
			res.push_back(num1);
		}
		if (cnt2 > nums.size() / 3) {
			res.push_back(num2);
		}
		return res;
	}
};
/*

230. Kth Smallest Element in a BST (Medium)

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Hint:

Try to utilize the property of a BST.
What if you could modify the BST node's structure?
The optimal runtime complexity is O(height of BST).

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
	int kthSmallest(TreeNode* root, int k) {
		vector<int> res;
		traversal(root, res);
		return res[k - 1];
	}
	void traversal(TreeNode* root, vector<int>& res) {
		if (root) {
			traversal(root->left, res);
			res.push_back(root->val);
			traversal(root->right, res);
		}
	}
};
class Solution {
public:
	int kthSmallest(TreeNode* root, int k) {
		stack<TreeNode*> s;
		int cnt = 0, res = root->val;
		while (true) {
			TreeNode* temp = root;
			while (temp) {
				s.push(temp);
				temp = temp->left;
			}
			if (s.empty() || cnt == k) return res;
			cnt++;
			root = s.top();
			s.pop();
			res = root->val;
			root = root->right;
		}
		return res;
	}
};
/*

231. Power of Two (Easy)

Given an integer, write a function to determine if it is a power of two.

*/
class Solution {
public:
	bool isPowerOfTwo(int n) {
		return n > 0 && (n & (n - 1)) == 0;
	}
};
/*

232. Implement Queue using Stacks (Easy)

Implement the following operations of a queue using stacks.

push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.

Notes:

You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).

*/
class Queue {
public:
	stack<int> s1, s2;
	// Push element x to the back of queue.
	void push(int x) {
		s1.push(x);
	}

	// Removes the element from in front of queue.
	void pop(void) {
		if (!s2.empty()) {
			s2.pop();
		}
		else if (!s1.empty()) {
			transfer(s1, s2);
			s2.pop();
		}
	}

	// Get the front element.
	int peek(void) {
		if (!s2.empty()) {
			return s2.top();
		}
		else if (!s1.empty()) {
			transfer(s1, s2);
			return s2.top();
		}
		else {
			return -1;
		}
	}

	// Return whether the queue is empty.
	bool empty(void) {
		return s1.empty() && s2.empty();
	}
private:
	void transfer(stack<int>& s1, stack<int>& s2) {
		while (!s1.empty()) {
			s2.push(s1.top());
			s1.pop();
		}
	}
};
/*

233. Number of Digit One (Medium)

Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

For example:
Given n = 13,
Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.

Hint:

Beware of overflow.

*/
class Solution {
public:
	int countDigitOne(int n) {
		int res = 0;
		for (long long i = 1; i <= n; i *= 10) {
			res += (n / i + 8) / 10 * i + (n / i % 10 == 1) * (n % i + 1);
		}
		return res;
	}
};
/*

234. Palindrome Linked List (Easy)

Given a singly linked list, determine if it is a palindrome.

*/
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	bool isPalindrome(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return true;
		}
		ListNode *s = head, *f = head;
		while (f->next != NULL && f->next->next != NULL) {
			s = s->next;
			f = f->next->next;
		}
		s->next = reverse(s->next);
		s = s->next;
		while (s != NULL) {
			if (s->val != head->val) {
				return false;
			}
			s = s->next;
			head = head->next;
		}
		return true;
	}
private:
	ListNode* reverse(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *prev = NULL;
		while (head != NULL) {
			ListNode *post = head->next;
			head->next = prev;
			prev = head;
			head = post;
		}
		return prev;
	}
};
/*

235. Lowest Common Ancestor of a Binary Search Tree (Easy)

Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

		_______6______
	   /              \
	___2__          ___8__
   /      \        /      \
   0      _4       7       9
		 /  \
		 3   5
For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

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
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == NULL || root == p || root == q) {
			return root;
		}
		TreeNode *l = lowestCommonAncestor(root->left, p, q), *r = lowestCommonAncestor(root->right, p, q);
		if (l != NULL && r != NULL) {
			return root;
		}
		return l != NULL ? l : r;
	}
};
/*

236. Lowest Common Ancestor of a Binary Tree (Medium)

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

		_______3______
	   /              \
	___5__          ___1__
   /      \        /      \
   6      _2       0       8
		 /  \
		 7   4
For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

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
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == NULL || root == p || root == q) {
			return root;
		}
		TreeNode *l = lowestCommonAncestor(root->left, p, q), *r = lowestCommonAncestor(root->right, p, q);
		if (l != NULL && r != NULL) {
			return root;
		}
		return l != NULL ? l : r;
	}
};
/*

237. Delete Node in a Linked List (Easy)

Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.

Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function.

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	void deleteNode(ListNode* node) {
		if (node == NULL) {
			return;
		}
		node->val = node->next->val;
		node->next = node->next->next;
	}
};
/*

238. Product of Array Except Self (Medium)

Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)

*/
class Solution {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		vector<int> res(nums.size());
		res[0] = 1;
		for (int i = 1; i < res.size(); i++) {
			res[i] = nums[i - 1] * res[i - 1];
		}
		int post = 1;
		for (int i = res.size() - 2; i >= 0; i--) {
			post *= nums[i + 1];
			res[i] *= post;
		}
		return res;
	}
};
/*

239. Sliding Window Maximum (Hard)

Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.

Follow up:
Could you solve it in linear time?

Hint:

How about using a data structure such as deque (double-ended queue)?
The queue size need not be the same as the window’s size.
Remove redundant elements and the queue should store only elements that need to be considered.

*/
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		deque<int> dq;
		vector<int> res;
		for (int i = 0; i < nums.size(); i++) {
			while (!dq.empty() && nums[dq.back()] <= nums[i]) {
				dq.pop_back();
			}
			while (!dq.empty() && i - dq.front() >= k) {
				dq.pop_front();
			}
			dq.push_back(i);
			if (i >= k - 1) {
				res.push_back(nums[dq.front()]);
			}
		}
		return res;
	}
};
/*

240. Search a 2D Matrix II (Medium)

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
For example,

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Given target = 5, return true.

Given target = 20, return false.

*/
class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.empty()) {
			return false;
		}
		int i = 0, j = matrix[0].size() - 1;
		while (i < matrix.size() && j >= 0) {
			if (matrix[i][j] > target) {
				j--;
			}
			else if (matrix[i][j] < target) {
				i++;
			}
			else {
				return true;
			}
		}
		return false;
	}
};
/*

241. Different Ways to Add Parentheses (Medium)

Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.


Example 1
Input: "2-1-1".

((2-1)-1) = 0
(2-(1-1)) = 2
Output: [0, 2]


Example 2
Input: "2*3-4*5"

(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
Output: [-34, -14, -10, -10, 10]

*/
class Solution {
private:
	int _len;
	vector<int> calculate(const string& input, int st, int ed) {
		vector<int> res;
		if (st > ed) return res;
		for (int i = st; i <= ed; i++) {
			if (!isdigit(input[i])) {
				vector<int> l = calculate(input, st, i - 1), r = calculate(input, i + 1, ed);
				for (int j = 0; j < l.size(); j++) {
					for (int k = 0; k < r.size(); k++) {
						switch (input[i]) {
						case '-': res.push_back(l[j] - r[k]); break;
						case '+': res.push_back(l[j] + r[k]); break;
						case '*': res.push_back(l[j] * r[k]); break;
						}
					}
				}
			}
		}
		if (res.empty()) res.push_back(stoi(input.substr(st, ed - st + 1)));
		return res;
	}
public:
	vector<int> diffWaysToCompute(string input) {
		int _len = input.length();
		return calculate(input, 0, _len - 1);
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

243. Shortest Word Distance (Easy)

Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.

Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.

*/
class Solution {
public:
	int shortestDistance(vector<string>& words, string word1, string word2) {
		int p1 = -1, p2 = -1, mindis = INT_MAX;
		for (int k = 0; k < words.size(); k++) {
			if (isMatched(words[k], word1)) {
				p1 = k;
			}
			else if (isMatched(words[k], word2)) {
				p2 = k;
			}
			if (p1 != -1 && p2 != -1) {
				mindis = min(mindis, abs(p1 - p2));
			}
		}
		return mindis;
	}
private:
	bool isMatched(string words, string word1) {
		int len = words.length();
		if (len == word1.length()) {
			int i = 0;
			for (; i < len; i++) {
				if (words[i] != word1[i]) {
					break;
				}
			}
			if (i == len) {
				return true;
			}
		}
		return false;
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

245. Shortest Word Distance III (Medium)

This is a follow up of Shortest Word Distance. The only difference is now word1 could be the same as word2.

Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

word1 and word2 may be the same and they represent two individual words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “makes”, word2 = “coding”, return 1.
Given word1 = "makes", word2 = "makes", return 3.

Note:
You may assume word1 and word2 are both in the list.

*/
class Solution {
public:
	int shortestWordDistance(vector<string>& words, string word1, string word2) {
		int p1 = -1, p2 = -1, mindis = INT_MAX, prep1;
		for (int k = 0; k < words.size(); k++) {
			if (isMatched(words[k], word1)) {
				prep1 = p1;
				p1 = k;
			}
			if (isMatched(words[k], word2)) {
				p2 = k;
			}
			if (p1 != -1 && p2 != -1) {
				if (p1 == p2) {
					if (prep1 != -1) {
						mindis = min(mindis, abs(prep1 - p2));
					}
				}
				else {
					mindis = min(mindis, abs(p1 - p2));
				}
			}
		}
		return mindis;
	}
private:
	bool isMatched(string words, string word1) {
		int len = words.length();
		if (len == word1.length()) {
			int i = 0;
			for (; i < len; i++) {
				if (words[i] != word1[i]) {
					break;
				}
			}
			if (i == len) {
				return true;
			}
		}
		return false;
	}
};
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

247. Strobogrammatic Number II (Medium)

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Find all strobogrammatic numbers that are of length = n.

For example,
Given n = 2, return ["11","69","88","96"].

Hint:

Try to use recursion and notice that it should recurse with n - 2 instead of n - 1.

*/
class Solution {
public:
	vector<string> findStrobogrammatic(int n) {
		return findStrobogrammatic(n, n);
	}
private:
	vector<string> findStrobogrammatic(int n, const int& m) {
		if (n == 0) {
			return{ "" };
		}
		if (n == 1) {
			return{ "0", "1", "8" };
		}
		vector<string> res_sub = findStrobogrammatic(n - 2, m), res;
		for (string s : res_sub) {
			if (n != m) {
				res.push_back("0" + s + "0");
			}
			res.push_back("1" + s + "1");
			res.push_back("6" + s + "9");
			res.push_back("8" + s + "8");
			res.push_back("9" + s + "6");
		}
		return res;
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

250. Count Univalue Subtrees (Medium)

Given a binary tree, count the number of uni-value subtrees.

A Uni-value subtree means all nodes of the subtree have the same value.

For example:
Given binary tree,
			  5
			 / \
			1   5
		   / \   \
		  5   5   5
return 4.

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
	int countUnivalSubtrees(TreeNode* root) {
		int res = 0;
		countUnivalSubtrees(root, res);
		return res;
	}
private:
	bool countUnivalSubtrees(TreeNode* root, int& res) {
		if (root == NULL) {
			return true;
		}
		else if (root->left == NULL && root->right == NULL) {
			res++;
			return true;
		}
		bool l = countUnivalSubtrees(root->left, res), r = countUnivalSubtrees(root->right, res);
		if (l && r && (root->left == NULL || root->val == root->left->val) && (root->right == NULL || root->val == root->right->val)) {
			res++;
			return true;
		}
		return false;
	}
};
/*

251. Flatten 2D Vector (Medium)

Implement an iterator to flatten a 2d vector.

For example,
Given 2d vector =

[
  [1,2],
  [3],
  [4,5,6]
]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].

Hint:

How many variables do you need to keep track?
Two variables is all you need. Try with x and y.
Beware of empty rows. It could be the first few rows.
To write correct code, think about the invariant to maintain. What is it?
The invariant is x and y must always point to a valid point in the 2d vector. Should you maintain your invariant ahead of time or right when you need it?
Not sure? Think about how you would implement hasNext(). Which is more complex?
Common logic in two different places should be refactored into a common method.
Follow up:
As an added challenge, try to code it using only iterators in C++ or iterators in Java.

*/
class Vector2D {
public:
	Vector2D(vector<vector<int>>& vec2d) {
		b = vec2d.begin();
		e = vec2d.end();
	}

	int next() {
		hasNext();
		return (*b)[j++];
	}

	bool hasNext() {
		while (b != e && j == (*b).size()) {
			b++, j = 0;
		}
		return b != e;
	}
private:
	vector<vector<int>>::iterator b, e;
	int j = 0;
};
/**
* Your Vector2D object will be instantiated and called as such:
* Vector2D i(vec2d);
* while (i.hasNext()) cout << i.next();
*/
/*

252. Meeting Rooms (Easy)

Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return false.

*/
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Comp {
public:
	bool operator()(Interval i1, Interval i2) {
		return i1.start < i2.start;
	}
}comp;
class Solution {
public:
	bool canAttendMeetings(vector<Interval>& intervals) {
		if (intervals.empty()) {
			return true;
		}
		sort(intervals.begin(), intervals.end(), comp);
		for (int i = 0; i < intervals.size() - 1; i++) {
			if (intervals[i].end > intervals[i + 1].start) {
				return false;
			}
		}
		return true;
	}
};
/*

254. Factor Combinations (Medium)

Numbers can be regarded as product of its factors. For example,

8 = 2 x 2 x 2;
  = 2 x 4.
Write a function that takes an integer n and return all possible combinations of its factors.

Note:
You may assume that n is always positive.
Factors should be greater than 1 and less than n.
Examples:
input: 1
output:
[]
input: 37
output:
[]
input: 12
output:
[
  [2, 6],
  [2, 2, 3],
  [3, 4]
]
input: 32
output:
[
  [2, 16],
  [2, 2, 8],
  [2, 2, 2, 4],
  [2, 2, 2, 2, 2],
  [2, 4, 4],
  [4, 8]
]

*/
class Solution {
public:
	vector<vector<int>> getFactors(int n) {
		vector<vector<int>> res;
		vector<int> res_sub;
		getFactors(2, n, res, res_sub, sqrt(n));
		return res;
	}
private:
	void getFactors(int start, int n, vector<vector<int>>& res, vector<int>& res_sub, int upper) {
		if (n == 1) {
			if (res_sub.size() > 1) {
				res.push_back(res_sub);
			}
			return;
		}
		for (int i = start; i <= n; i++) {
			if (i > upper) {
				i = n;
			}
			if (n % i == 0) {
				res_sub.push_back(i);
				getFactors(i, n / i, res, res_sub, sqrt(n / i));
				res_sub.pop_back();
			}
		}
	}
};
/*

255. Verify Preorder Sequence in Binary Search Tree (Medium)

Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.

You may assume each number in the sequence is unique.

Follow up:
Could you do it using only constant space complexity?

*/
class Solution {
public:
	bool verifyPreorder(vector<int>& preorder) {
		int i = 0;
		verifyPreorder(preorder, i, INT_MIN, INT_MAX);
		return i >= preorder.size() ? true : false;
	}
private:
	void verifyPreorder(vector<int>& nums, int& i, int low, int high) {
		if (i >= nums.size() || nums[i] > high || nums[i] < low) return;
		int cur = nums[i++];
		verifyPreorder(nums, i, low, cur);
		verifyPreorder(nums, i, cur, high);
		return;
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

258. Add Digits (Easy)

Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.

For example:

Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it.

Follow up:

Could you do it without any loop/recursion in O(1) runtime?

*/
class Solution {
public:
	int addDigits(int num) {
		return 1 + (num - 1) % 9;
	}
};
/*

259. 3Sum Smaller (Medium)

Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

For example, given nums = [-2, 0, 1, 3], and target = 2.

Return 2. Because there are two triplets which sums are less than 2:

[-2, 0, 1]
[-2, 0, 3]
Follow up:
Could you solve it in O(n2) runtime?

*/
class Solution {
public:
	int threeSumSmaller(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		if (nums.size() < 3) {
			return 0;
		}
		int res = 0;
		for (int i = 0; i < nums.size() - 2; i++) {
			if (nums[i] + nums[i + 1] + nums[i + 2] >= target) {
				return res;
			}
			int j = i + 1, k = nums.size() - 1;
			while (j < k) {
				if (nums[i] + nums[j] + nums[k] < target) {
					res += k - j;
					j++;
				}
				else {
					k--;
				}
			}
		}
		return res;
	}
};
/*

260. Single Number III (Medium)

Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:
The order of the result is not important. So in the above example, [5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?


*/
class Solution {
public:
	vector<int> singleNumber(vector<int>& nums) {
		int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
		diff &= -diff;
		vector<int> res(2, 0);
		for (int& num : nums) {
			if (diff & num) {
				res[0] ^= num;
			}
			else {
				res[1] ^= num;
			}
		}
		return res;
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
According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”
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

263. Ugly Number (Easy)

Write a program to check whether a given number is an ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.

Note that 1 is typically treated as an ugly number.

*/
class Solution {
public:
	bool isUgly(int num) {
		if (num == 0)
			return false;
		if (num == 1)
			return true;
		if (num % 2 == 0)
			return isUgly(num / 2);
		if (num % 3 == 0)
			return isUgly(num / 3);
		if (num % 5 == 0)
			return isUgly(num / 5);
		return false;
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

267. Palindrome Permutation II (Medium)

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
		int t[256] = { 0 };
		for (char cha : s) {
			t[cha]++;
		}
		string str, c;
		bool odd = false;
		for (int i = 0; i < 256; i++) {
			if (t[i] & 1) {
				if (odd == true) {
					return{};
				}
				c = (char)i;
				odd = true;
			}
			str += string(t[i] / 2, (char)i);
		}
		vector<string> res;
		helper(res, str, 0, c);
		return res;
	}
private:
	void helper(vector<string>& res, string& str, int index, const string& c) {
		if (index == str.size()) {
			string temp = str;
			reverse(temp.begin(), temp.end());
			res.push_back(str + c + temp);
			return;
		}
		unordered_set<char> s;
		for (int i = index; i < str.size(); i++) {
			if (s.find(str[i]) == s.end()) {
				s.insert(str[i]);
				swap(str[i], str[index]);
				helper(res, str, index + 1, c);
				swap(str[i], str[index]);
			}
		}
	}
};
/*

268. Missing Number (Medium)

Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

For example,
Given nums = [0, 1, 3] return 2.

Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?

*/
class Solution {
public:
	int missingNumber(vector<int>& nums) {
		int res = 0;
		for (int num : nums) {
			res ^= num;
		}
		for (int i = 0; i <= nums.size(); i++) {
			res ^= i;
		}
		return res;
	}
};
/*

270. Closest Binary Search Tree Value

Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.

Note:
Given target value is a floating point.
You are guaranteed to have only one unique value in the BST that is closest to the target.

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
	int closestValue(TreeNode* root, double target) {
		int res = root->val;
		while (root != NULL) {
			if (abs(root->val - target) < abs(res - target)) {
				res = root->val;
			}
			if (root->val < target) {
				root = root->right;
			}
			else {
				root = root->left;
			}
		}
		return res;
	}
};
/*

271. Encode and Decode Strings (medium)

Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

Machine 1 (sender) has the function:

string encode(vector<string> strs) {
  // ... your code
  return encoded_string;
}
Machine 2 (receiver) has the function:
vector<string> decode(string s) {
  //... your code
  return strs;
}
So Machine 1 does:

string encoded_string = encode(strs);
and Machine 2 does:

vector<string> strs2 = decode(encoded_string);
strs2 in Machine 2 should be the same as strs in Machine 1.

Implement the encode and decode methods.

Note:
The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.
Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.

*/
class Codec {
public:

	// Encodes a list of strings to a single string.
	string encode(vector<string>& strs) {
		string res = "";
		for (string str : strs) {
			res += to_string(str.size()) + "/" + str;
		}
		return res;
	}

	// Decodes a single string to a list of strings.
	vector<string> decode(string s) {
		vector<string> res;
		for (int i = 0; i < s.size(); i++) {
			int j = s.find_first_of('/', i);
			int len = stoi(s.substr(i, j - i));
			res.push_back(s.substr(j + 1, len));
			i = j + len;
		}
		return res;
	}
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
/*

272. Closest Binary Search Tree Value II (Hard)

Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:
Given target value is a floating point.
You may assume k is always valid, that is: k ≤ total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

Hint:

Consider implement these two helper functions:
getPredecessor(N), which returns the next smaller node to N.
getSuccessor(N), which returns the next larger node to N.
Try to assume that each node has a parent pointer, it makes the problem much easier.
Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
You would need two stacks to track the path in finding predecessor and successor node separately.

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
	vector<int> closestKValues(TreeNode* root, double target, int k) {
		stack<TreeNode*> suc, pre;
		vector<int> res;
		iniPreSta(root, target, pre);
		iniSucSta(root, target, suc);
		if (!suc.empty() && !pre.empty() && suc.top()->val == pre.top()->val) {
			getNextPredecessor(pre);
		}
		while (k-- > 0) {
			if (suc.empty()) {
				res.push_back(getNextPredecessor(pre));
			}
			else if (pre.empty()) {
				res.push_back(getNextSuccessor(suc));
			}
			else {
				if (abs((double)pre.top()->val - target) < abs((double)suc.top()->val - target)) {
					res.push_back(getNextPredecessor(pre));
				}
				else {
					res.push_back(getNextSuccessor(suc));
				}
			}
		}
		return res;
	}
private:
	void iniPreSta(TreeNode* root, double target, stack<TreeNode*>& pre) {
		while (root != NULL) {
			if (root->val < target) {
				pre.push(root);
				root = root->right;
			}
			else if (root->val > target) {
				root = root->left;
			}
			else {
				pre.push(root);
				break;
			}
		}
	}
	void iniSucSta(TreeNode* root, double target, stack<TreeNode*>& suc) {
		while (root != NULL) {
			if (root->val > target) {
				suc.push(root);
				root = root->left;
			}
			else if (root->val < target) {
				root = root->right;
			}
			else {
				suc.push(root);
				break;
			}
		}
	}
	int getNextSuccessor(stack<TreeNode*>& suc) {
		TreeNode* cur = suc.top();
		suc.pop();
		int res = cur->val;
		cur = cur->right;
		while (cur != NULL) {
			suc.push(cur);
			cur = cur->left;
		}
		return res;
	}
	int getNextPredecessor(stack<TreeNode*>& pre) {
		TreeNode* cur = pre.top();
		pre.pop();
		int res = cur->val;
		cur = cur->left;
		while (cur != NULL) {
			pre.push(cur);
			cur = cur->right;
		}
		return res;
	}
};
/*

273. Integer to English Words (Hard)

Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.

For example,
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Hint:

Did you see a pattern in dividing the number into chunk of words? For example, 123 and 123000.
Group the number by thousands (3 digits). You can write a helper function that takes a number less than 1000 and convert just that chunk to words.
There are many edge cases. What are some good test cases? Does your code work with input such as 0? Or 1000010? (middle chunk is zero and should not be printed out)

*/
class Solution {
public:
	string numberToWords(int num) {
		if (num == 0) {
			return "Zero";
		}
		vector<string> unit = { "", "Thousand", "Million", "Billion" };
		vector<string> less20 = { "", "One", "Two", "Three","Four","Five","Six","Seven","Eight","Nine", "Ten", "Eleven", "Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
		vector<string> ten2 = { "", "Ten", "Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
		string res;
		int bit = 0;
		while (num != 0) {
			if (num % 1000 > 0) {
				res = numberToWords2(num % 1000, less20, ten2) + " " + unit[bit] + " " + res;
			}
			num /= 1000;
			bit++;
		}
		while (res.back() == ' ') {
			res.pop_back();
		}
		return res;
	}
private:
	string numberToWords2(int num, const vector<string>& less20, const vector<string>& ten2) {
		if (num == 0) {
			return "";
		}
		if (num < 20) {
			return less20[num];
		}
		else if (num < 100) {
			if (num % 10) {
				return ten2[num / 10] + " " + less20[num % 10];
			}
			return ten2[num / 10];
		}
		else {
			if (num % 100) {
				return less20[num / 100] + " Hundred " + numberToWords2(num % 100, less20, ten2);
			}
			return less20[num / 100] + " Hundred";
		}
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

275. H-Index II (Medium)

Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm?

Hint:

Expected runtime complexity is in O(log n) and the input is sorted.

*/
class Solution {
public:
	int hIndex(vector<int>& citations) {
		if (citations.empty()) return 0;
		int _size = citations.size();
		int l = 0, r = _size - 1;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (citations[mid] < _size - mid) l = mid + 1;
			else if (citations[mid] > _size - mid) r = mid - 1;
			else return citations[mid];
		}
		return _size - l;
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

277. Find the Celebrity (Medium)

Suppose you are at a party with n people (labeled from 0 to n - 1) and among them, there may exist one celebrity. The definition of a celebrity is that all the other n - 1 people know him/her but he/she does not know any of them.

Now you want to find out who the celebrity is or verify that there is not one. The only thing you are allowed to do is to ask questions like: "Hi, A. Do you know B?" to get information of whether A knows B. You need to find out the celebrity (or verify there is not one) by asking as few questions as possible (in the asymptotic sense).

You are given a helper function bool knows(a, b) which tells you whether A knows B. Implement a function int findCelebrity(n), your function should minimize the number of calls to knows.

Note: There will be exactly one celebrity if he/she is in the party. Return the celebrity's label if there is a celebrity in the party. If there is no celebrity, return -1.

*/
// Forward declaration of the knows API.
bool knows(int a, int b);

class Solution {
public:
	int findCelebrity(int n) {
		int l = 0, r = n - 1;
		while (l < r) {
			if (knows(l, r)) {
				l++;
			}
			else {
				r--;
			}
		}
		for (int i = 0; i < n; i++) {
			if (i == l || knows(i, l) && !knows(l, i)) {
				continue;
			}
			else {
				return -1;
			}
		}
		return l;
	}
};
/*

278. First Bad Version (easy)

You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

*/
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);
class Solution {
public:
	int firstBadVersion(int n) {
		int l = 1, r = n;
		while (l < r) {
			int mid = l + (r - l) / 2;
			if (isBadVersion(mid)) {
				r = mid;
			}
			else {
				l = mid + 1;
			}
		}
		return l;
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

280. Wiggle Sort (Medium)

Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].

*/
class Solution {
public:
	void wiggleSort(vector<int>& nums) {
		for (int i = 1; i < nums.size(); i++) {
			if ((i % 2 == 1 && nums[i] < nums[i - 1]) || (i % 2 == 0 && nums[i] > nums[i - 1])) {
				swap(nums[i], nums[i - 1]);
			}
		}
	}
};
class Solution {
public:
	void wiggleSort(vector<int>& nums) {
		if (nums.empty()) {
			return;
		}
		sort(nums.begin(), nums.end());
		swap(nums.back(), nums[nums.size() / 2]);
		if (nums.size() & 1) {
			wiggleSort(nums, 0, nums.size() - 2);
		}
		else {
			wiggleSort(nums, 0, nums.size() - 1);
		}
	}
private:
	void wiggleSort(vector<int>& nums, int l, int r) {
		if (l >= r - 1) {
			return;
		}
		int _size = r - l + 1;
		int i = l + _size / 4, j = l + _size * 3 / 4, mid = l + _size / 2;
		reverse(nums.begin() + i, nums.begin() + mid);
		reverse(nums.begin() + mid, nums.begin() + j);
		reverse(nums.begin() + i, nums.begin() + j);
		wiggleSort(nums, l, l + 2 * (i - l) - 1);
		wiggleSort(nums, l + 2 * (i - l), r);
	}
};
/*

281. Zigzag Iterator (Medium)

Given two 1d vectors, implement an iterator to return their elements alternately.

For example, given two 1d vectors:

v1 = [1, 2]
v2 = [3, 4, 5, 6]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].

Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

Clarification for the follow up question - Update (2015-09-18):
The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases. If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For example, given the following input:

[1,2,3]
[4,5,6,7]
[8,9]
It should return [1,4,8,2,5,9,3,6,7].

*/
class ZigzagIterator {
public:
	ZigzagIterator(vector<int>& v1, vector<int>& v2) {
		b[0] = v1.begin();
		b[1] = v2.begin();
		e[0] = v1.end();
		e[1] = v2.end();
	}

	int next() {
		int elem;
		if (b[0] == e[0]) {
			elem = *b[1]++;
		}
		else if (b[1] == e[1]) {
			elem = *b[0]++;
		}
		else {
			elem = *b[cnt % 2]++;
			cnt++;
		}
		return elem;
	}

	bool hasNext() {
		return b[0] != e[0] || b[1] != e[1];
	}
private:
	vector<int>::iterator b[2], e[2];
	int cnt = 0;
};
/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */
 /*

 283. Move Zeroes (Easy)

 Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

 For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

 Note:
 You must do this in-place without making a copy of the array.
 Minimize the total number of operations.

 */
class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		for (int i = 0, j = 0; j < nums.size(); j++) {
			if (nums[j] != 0) {
				swap(nums[i++], nums[j]);
			}
		}
	}
};
/*

284. Peeking Iterator (Medium)

Given an Iterator class interface with methods: next() and hasNext(), design and implement a PeekingIterator that support the peek() operation -- it essentially peek() at the element that will be returned by the next call to next().

Here is an example. Assume that the iterator is initialized to the beginning of the list: [1, 2, 3].

Call next() gets you 1, the first element in the list.

Now you call peek() and it returns 2, the next element. Calling next() after that still return 2.

You call next() the final time and it returns 3, the last element. Calling hasNext() after that should return false.

Hint:

Think of "looking ahead". You want to cache the next element.
Is one variable sufficient? Why or why not?
Test your design with call order of peek() before next() vs next() before peek().
For a clean implementation, check out Google's guava library source code.
Follow up: How would you extend your design to be generic and work with all types, not just integer?

*/
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
	struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};
class PeekingIterator : public Iterator {
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
		// Initialize any member here.
		// **DO NOT** save a copy of nums and manipulate it directly.
		// You should only use the Iterator interface methods.

	}

	// Returns the next element in the iteration without advancing the iterator.
	int peek() {
		return Iterator(*this).next();
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
		return Iterator::next();
	}

	bool hasNext() const {
		return Iterator::hasNext();
	}
};
/*

285. Inorder Successor in BST (Medium)

Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null.

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
	TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
		stack<TreeNode*> s;
		iniSucSta(root, p, s);
		if (!s.empty() && s.top() == p) {
			getNextSuccessor(s);
		}
		return getNextSuccessor(s);
	}
private:
	void iniSucSta(TreeNode* root, TreeNode* p, stack<TreeNode*>& s) {
		while (root != NULL) {
			if (root->val > p->val) {
				s.push(root);
				root = root->left;
			}
			else if (root->val < p->val) {
				root = root->right;
			}
			else {
				s.push(root);
				break;
			}
		}
	}
	TreeNode* getNextSuccessor(stack<TreeNode*>& s) {
		if (s.empty()) {
			return NULL;
		}
		TreeNode* cur = s.top();
		s.pop();
		TreeNode* temp = cur;
		cur = cur->right;
		while (cur != NULL) {
			s.push(cur);
			cur = cur->left;
		}
		return temp;
	}
};
/*

287. Find the Duplicate Number (Hard)

Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n2).
There is only one duplicate number in the array, but it could be repeated more than once.

*/
class Solution {
public:
	int findDuplicate(vector<int>& nums) {
		int s = 0, f = 0;
		int finder = 0;
		while (true) {
			s = nums[s];
			f = nums[nums[f]];
			if (s == f) {
				break;
			}
		}
		while (true) {
			s = nums[s];
			finder = nums[finder];
			if (s == finder) {
				return s;
			}
		}
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

289. Game of Life (Medium)

According to the Wikipedia's article: "The Game of Life, also known simply as Life,
is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live (1) or dead (0).
Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the
following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
Write a function to compute the next state (after one update) of the board given its current state.

Follow up:
Could you solve it in-place? Remember that the board needs to be updated at the same time:
You cannot update some cells first and then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In principle, the board is infinite,
which would cause problems when the active area encroaches the border of the array. How would you address these problems?

*/
class Solution {
public:
	void gameOfLife(vector<vector<int>>& board) {
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[0].size(); j++) {
				int cnt = lives(board, i, j);
				if (cnt == 3 || (cnt == 2 && board[i][j] == 1)) {
					board[i][j] += 10;
				}
			}
		}
		update(board);
	}
	int lives(vector<vector<int>>& board, int i, int j) {
		int cnt = 0;
		for (int row = max(0, i - 1); row <= min((int)board.size() - 1, i + 1); row++) {
			for (int col = max(0, j - 1); col <= min((int)board[0].size() - 1, j + 1); col++) {
				if (row != i || col != j) {
					cnt += board[row][col] % 10;
				}
			}
		}
		return cnt;
	}
	void update(vector<vector<int>>& board) {
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[0].size(); j++) {
				board[i][j] = board[i][j] / 10;
			}
		}
	}
};
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

292. Nim Game (Easy)

You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones.

Both of you are very clever and have optimal strategies for the game. Write a function to determine whether you can win the game given the number of stones in the heap.

For example, if there are 4 stones in the heap, then you will never win the game: no matter 1, 2, or 3 stones you remove, the last stone will always be removed by your friend.

Hint:

If there are 5 stones in the heap, could you figure out a way to remove the stones such that you will always be the winner?

*/
class Solution {
public:
	bool canWinNim(int n) {
		return n % 4;
	}
};
/*

293. Flip Game (Easy)

You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to compute all possible states of the string after one valid move.

For example, given s = "++++", after one move, it may become one of the following states:

[
  "--++",
  "+--+",
  "++--"
]
If there is no valid move, return an empty list [].

*/
class Solution {
public:
	vector<string> generatePossibleNextMoves(string s) {
		vector<string> res;
		for (int i = 0; i < (int)s.size() - 1; i++) {
			if (s[i] == '+' && s[i + 1] == '+') {
				s[i] = s[i + 1] = '-';
				res.push_back(s);
				s[i] = s[i + 1] = '+';
			}
		}
		return res;
	}
};
/*

294. Flip Game II (Medium)

You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to determine if the starting player can guarantee a win.

For example, given s = "++++", return true. The starting player can guarantee a win by flipping the middle "++" to become "+--+".

Follow up:
Derive your algorithm's runtime complexity.

*/
class Solution {
public:
	bool canWin(string s) {
		for (int i = 0; i < (int)s.size() - 1; i++) {
			if (s[i] == '+' && s[i + 1] == '+') {
				s[i] = s[i + 1] = '-';
				if (canWin(s) == false) {
					return true;
				}
				s[i] = s[i + 1] = '+';
			}
		}
		return false;
	}
};
/*

295. Find Median from Data Stream (Hard)

Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

Examples:
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.
For example:

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2

*/
class min_h {
public:
	bool operator()(int num1, int num2) {
		return num1 > num2;
	}
};
class MedianFinder {
public:
	priority_queue<int, vector<int>, min_h> pr;
	priority_queue<int, vector<int>> pl;
	// Adds a number into the data structure.
	void addNum(int num) {
		if (pl.size() == pr.size()) {
			if (pl.empty() || num < pl.top()) {
				pl.push(num);
			}
			else {
				pr.push(num);
			}
		}
		else if (pl.size() < pr.size()) {
			pr.push(num);
			pl.push(pr.top());
			pr.pop();
		}
		else {
			pl.push(num);
			pr.push(pl.top());
			pl.pop();
		}
	}
	// Returns the median of current data stream
	double findMedian() {
		if (pr.size() == pl.size()) {
			if (pr.empty()) {
				return (double)0;
			}
			return (double)(pr.top() + pl.top()) / 2;
		}
		else if (pr.size() > pl.size()) {
			return (double)pr.top();
		}
		return (double)pl.top();
	}
};
// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();
/*

297. Serialize and Deserialize Binary Tree (Hard)

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

	1
   / \
  2   3
	 / \
	4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

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
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream out;
		serialize(root, out);
		return out.str();
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream in(data);
		return deserialize(in);
	}
private:
	void serialize(TreeNode* root, ostringstream& out) {
		if (root != NULL) {
			out << root->val << ' ';
			serialize(root->left, out);
			serialize(root->right, out);
		}
		else {
			out << "# ";
		}
	}
	TreeNode* deserialize(istringstream& in) {
		string val;
		in >> val;
		if (val == "#") {
			return NULL;
		}
		TreeNode* root = new TreeNode(stoi(val));
		root->left = deserialize(in);
		root->right = deserialize(in);
		return root;
	}
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
/*

298. Binary Tree Longest Consecutive Sequence (Medium)

Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).

For example,
   1
	\
	 3
	/ \
   2   4
		\
		 5
Longest consecutive sequence path is 3-4-5, so return 3.
   2
	\
	 3
	/
   2
  /
 1
Longest consecutive sequence path is 2-3,not3-2-1, so return 2.

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
	int longestConsecutive(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}
		int res = 0;
		longestConsecutive(root, res, 0, root->val);
		return res;
	}
private:
	void longestConsecutive(TreeNode* root, int& res, int cur, int tar) {
		if (root == NULL) {
			return;
		}
		else if (root->val == tar) {
			cur++;
		}
		else {
			cur = 1;
		}
		res = max(res, cur);
		longestConsecutive(root->left, res, cur, root->val + 1);
		longestConsecutive(root->right, res, cur, root->val + 1);
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

313. Super Ugly Number (Medium)

Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k. For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32] is the sequence of the first 12 super ugly numbers given primes = [2, 7, 13, 19] of size 4.

Note:
(1) 1 is a super ugly number for any given primes.
(2) The given numbers in primes are in ascending order.
(3) 0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
(4) The nth super ugly number is guaranteed to fit in a 32-bit signed integer.

*/
class Solution {
public:
	int nthSuperUglyNumber(int n, vector<int>& primes) {
		vector<int> index(primes.size(), 0);
		vector<int> t(n, INT_MAX);
		t[0] = 1;
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < index.size(); j++) {
				t[i] = min(t[i], primes[j] * t[index[j]]);
			}
			for (int j = 0; j < index.size(); j++) {
				if (t[i] % primes[j] == 0) {
					index[j]++;
				}
			}
		}
		return t.back();
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

315. Count of Smaller Numbers After Self (Hard)

You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

Given nums = [5, 2, 6, 1]

To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Return the array [2, 1, 1, 0].

*/
class Solution {
public:
	vector<int> countSmaller(vector<int>& nums) {
		vector<int> index(nums.size()), count(nums.size(), 0);
		for (int i = 0; i < index.size(); i++) {
			index[i] = i;
		}
		mergesort(nums, index, 0, nums.size() - 1, count);
		return count;
	}
private:
	void mergesort(const vector<int>& nums, vector<int>& index, int l, int r, vector<int>& count) {
		if (r <= l) {
			return;
		}
		int mid = l + (r - l) / 2;
		mergesort(nums, index, l, mid, count);
		mergesort(nums, index, mid + 1, r, count);
		merge(nums, index, l, r, mid, count);
	}
	void merge(const vector<int>& nums, vector<int>& index, int l, int r, int mid, vector<int>& count) {
		int i = l, j = mid + 1, rightcount = 0, k = 0;
		vector<int> newindex(r - l + 1);
		while (i <= mid && j <= r) {
			if (nums[index[j]] < nums[index[i]]) {
				newindex[k++] = index[j++];
				rightcount++;
			}
			else {
				newindex[k++] = index[i];
				count[index[i++]] += rightcount;
			}
		}
		while (i <= mid) {
			newindex[k++] = index[i];
			count[index[i++]] += rightcount;
		}
		while (j <= r) {
			newindex[k++] = index[j++];
		}
		for (int i = l; i <= r; i++) {
			index[i] = newindex[i - l];
		}
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

318. Maximum Product of Word Lengths (Medium)

Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:
Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
Return 16
The two words can be "abcw", "xtfn".

Example 2:
Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
Return 4
The two words can be "ab", "cd".

Example 3:
Given ["a", "aa", "aaa", "aaaa"]
Return 0
No such pair of words.

*/
class Solution {
public:
	int maxProduct(vector<string>& words) {
		if (words.size() < 2) {
			return 0;
		}
		vector<int> t(words.size());
		for (int i = 0; i < words.size(); i++) {
			int mask = 0;
			for (char cha : words[i]) {
				mask |= (1 << cha);
			}
			t[i] = mask;
		}
		int res = 0;
		for (int i = 0; i < words.size() - 1; i++) {
			for (int j = i + 1; j < words.size(); j++) {
				if ((t[i] & t[j]) == 0 && words[i].size() * words[j].size() > res) {
					res = words[i].size() * words[j].size();
				}
			}
		}
		return res;
	}
};
/*

319. Bulb Switcher (Medium)

There are n bulbs that are initially off. You first turn on all the bulbs. Then, you turn off every second bulb. On the third round, you toggle every third bulb (turning on if it's off or turning off if it's on). For the ith round, you toggle every i bulb. For the nth round, you only toggle the last bulb. Find how many bulbs are on after n rounds.

Example:

Given n = 3.

At first, the three bulbs are [off, off, off].
After first round, the three bulbs are [on, on, on].
After second round, the three bulbs are [on, off, on].
After third round, the three bulbs are [on, off, off].

So you should return 1, because there is only one bulb is on.

*/
class Solution {
public:
	int bulbSwitch(int n) {
		return sqrt(n);
	}
};
/*

320. Generalized Abbreviation (Medium)

Write a function to generate the generalized abbreviations of a word.

Example:
Given word = "word", return the following list (order does not matter):
["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]

*/
class Solution {
public:
	vector<string> generateAbbreviations(string word) {
		vector<string> res;
		generateAbbreviations(res, word, "", 0, 0);
		return res;
	}
private:
	void generateAbbreviations(vector<string>& res, string word, string cur, int index, int cnt) {
		if (index == word.size()) {
			if (cnt > 0) {
				cur += to_string(cnt);
			}
			res.push_back(cur);
			return;
		}
		generateAbbreviations(res, word, cur, index + 1, cnt + 1);
		generateAbbreviations(res, word, cur + (cnt > 0 ? to_string(cnt) : "") + word.substr(index, 1), index + 1, 0);
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

324. Wiggle Sort II (Medium)

Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example:
(1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is [1, 4, 1, 5, 1, 6].
(2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is [2, 3, 1, 3, 1, 2].

Note:
You may assume all input has valid answer.

Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?

*/
class Solution {
public:
	vector<int> wiggleSort(vector<int>& nums) {
		int n = nums.size();
		auto midptr = nums.begin() + n / 2;
		nth_element(nums.begin(), midptr, nums.end());
		int mid = *midptr;
		show(nums);
		cout << endl;
#define A(i) nums[(1+2*(i)) % (n|1)]
		int i = 0, j = 0, k = n - 1;
		while (j <= k) {
			if (A(j) > mid) {
				swap(A(i++), A(j++));
				show(nums);
				cout << endl;
			}
			else if (A(j) < mid) {
				swap(A(j), A(k--));
				show(nums);
				cout << endl;
			}
			else {
				j++;
			}
		}
		return nums;
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

326. Power of Three (Easy)

Given an integer, write a function to determine if it is a power of three.

Follow up:
Could you do it without using any loop / recursion?

*/
class Solution {
public:
	bool isPowerOfThree(int n) {
		return n > 0 && 1162261467 % n == 0;
	}
};
/*

328. Odd Even Linked List (Medium)

Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

Example:
Given 1->2->3->4->5->NULL,
return 1->3->5->2->4->NULL.

Note:
The relative order inside both the even and odd groups should remain as it was in the input.
The first node is considered odd, the second node even and so on ...

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* oddEvenList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *odd = head, *even = head->next;
		ListNode *p = even;
		while (p != NULL && p->next != NULL) {
			odd->next = p->next;
			p->next = odd->next->next;
			odd = odd->next;
			p = p->next;
		}
		odd->next = even;
		return head;
	}
};
/*

331. Verify Preorder Serialization of a Binary Tree (Medium)

One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as #.

	 _9_
	/   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.

Each comma separated value in the string must be either an integer or a character '#' representing null pointer.

You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".

Example 1:
"9,3,4,#,#,1,#,#,2,#,6,#,#"
Return true

Example 2:
"1,#"
Return false

Example 3:
"9,#,#,1"
Return false

*/
class Solution {
public:
	bool isValidSerialization(string preorder) {
		string s = "";
		for (int i = 0; i < preorder.length(); i++) {
			if (preorder[i] != '#') {
				s += 'n';
				while (preorder[i] != ',' && i < preorder.length()) i++;
			}
			else {
				s += '#';
				while (s.length() >= 2 && s.back() == '#' && s[s.length() - 2] == '#') {
					if (s.length() == 2) return false;
					s.pop_back();
					s.pop_back();
					s.pop_back();
					s += '#';
				}
				i++;
			}
		}
		return s == "#";
	}
};
/*

333. Largest BST Subtree (Medium)

Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.

Note:
A subtree must include all of its descendants.
Here's an example:
	10
	/ \
   5  15
  / \   \
 1   8   7
The Largest BST Subtree in this case is the highlighted one.
The return value is the subtree's size, which is 3.
Hint:

You can recursively use algorithm similar to 98. Validate Binary Search Tree at each node of the tree, which will result in O(nlogn) time complexity.
Follow up:
Can you figure out ways to solve it with O(n) time complexity?

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
	int largestBSTSubtree(TreeNode* root) {
		int res = 0;
		largestBSTSubtree(root, res);
		return res;
	}
private:
	vector<int> largestBSTSubtree(TreeNode *root, int& res) {
		if (root == NULL) {
			return{ 0,0,0 };
		}
		vector<int> l = largestBSTSubtree(root->left, res), r = largestBSTSubtree(root->right, res);
		if (l[0] == -1 || r[0] == -1) {
			return{ -1, 0, 0 };
		}
		if ((l[0] == 0 || root->val > l[2]) && (r[0] == 0 || root->val < r[1])) {
			res = max(res, l[0] + r[0] + 1);
			int small = l[1] == 0 ? root->val : l[1], large = r[2] == 0 ? root->val : r[2];
			return{ l[0] + r[0] + 1, small, large };
		}
		return{ -1,0,0 };
	}
};
/*

335. Self Crossing (Hard)

You are given an array x of n positive numbers. You start at point (0,0) and moves x[0] metres to the north, then x[1] metres to the west, x[2] metres to the south, x[3] metres to the east and so on. In other words, after each move your direction changes counter-clockwise.

Write a one-pass algorithm with O(1) extra space to determine, if your path crosses itself, or not.

Example 1:
Given x =
[2, 1, 1, 2]
,
┌───┐
│   │
└───┼──>
│

Return true (self crossing)
Example 2:
Given x =
[1, 2, 3, 4]
,
┌──────┐
│      │
│
│
└────────────>

Return false (not self crossing)
Example 3:
Given x =
[1, 1, 1, 1]
,
┌───┐
│   │
└───┼>

Return true (self crossing)

*/
class Solution {
public:
	bool isSelfCrossing(vector<int>& x) {
		int l = x.size();
		if (l < 4) {
			return false;
		}
		for (int i = 3; i < l; i++) {
			if (x[i] >= x[i - 2] && x[i - 1] <= x[i - 3]) {
				return true;
			}
			if (i >= 4) {
				if (x[i - 1] == x[i - 3] && x[i] + x[i - 4] >= x[i - 2]) {
					return true;
				}
			}
			if (i >= 5) {
				if (x[i - 2] - x[i - 4] >= 0 && x[i] >= x[i - 2] - x[i - 4] && x[i - 1] >= x[i - 3] - x[i - 5] && x[i - 1] <= x[i - 3]) {
					return true;
				}
			}
		}
		return false;
	}
};
/*

337. House Robber III (Medium)

The thief has found himself a new place for his thievery again. There is only one entrance to this area, called the "root." Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that "all houses in this place forms a binary tree". It will automatically contact the police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:
	 3
	/ \
   2   3
	\   \
	 3   1
Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:
	 3
	/ \
   4   5
  / \   \
 1   3   1
Maximum amount of money the thief can rob = 4 + 5 = 9.

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
	int rob(TreeNode* root) {
		int l = 0, r = 0;
		return rob(root, l, r);
	}
private:
	int rob(TreeNode* root, int& l, int& r) {
		if (root == NULL) {
			return 0;
		}
		int ll = 0, lr = 0, rl = 0, rr = 0;
		l = rob(root->left, ll, lr);
		r = rob(root->right, rl, rr);
		return max(root->val + ll + lr + rl + rr, l + r);
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

339. Nested List Weight Sum (Easy)

Given a nested list of integers, return the sum of all integers in the list weighted by their depth.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]], return 10. (four 1's at depth 2, one 2 at depth 1)

Example 2:
Given the list [1,[4,[6]]], return 27. (one 1 at depth 1, one 4 at depth 2, and one 6 at depth 3; 1 + 4*2 + 6*3 = 27)

*/
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
	int depthSum(vector<NestedInteger>& nestedList) {
		return depthSum(nestedList, 1);
	}
private:
	int depthSum(const vector<NestedInteger>& nestedList, int deepth) {
		int res = 0;
		for (auto element : nestedList) {
			if (element.isInteger() == true) {
				res += deepth * element.getInteger();
			}
			else {
				res += depthSum(element.getList(), deepth + 1);
			}
		}
		return res;
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

341. Flatten Nested List Iterator (Medium)

Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].

Example 2:
Given the list [1,[4,[6]]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].

*/
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
public:
	stack<NestedInteger> sta;
	NestedIterator(vector<NestedInteger> &nestedList) {
		for (int i = nestedList.size() - 1; i >= 0; i--) {
			sta.push(nestedList[i]);
		}
	}

	int next() {
		int result = sta.top().getInteger();
		sta.pop();
		return result;
	}

	bool hasNext() {
		while (!sta.empty()) {
			if (sta.top().isInteger() == true) {
				return true;
			}
			NestedInteger curr = sta.top();
			sta.pop();
			vector<NestedInteger>& adjs = curr.getList();
			for (int i = adjs.size() - 1; i >= 0; i--) {
				sta.push(adjs[i]);
			}
		}
		return false;
	}
};
/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
 /*

 342. Power of Four (Easy)

 Given an integer (signed 32 bits), write a function to check whether it is a power of 4.

 Example:
 Given num = 16, return true. Given num = 5, return false.

 Follow up: Could you solve it without loops/recursion?

 */
class Solution {
public:
	bool isPowerOfFour(int num) {
		return num > 0 && (num & (num - 1)) == 0 && (num & 0x55555555) != 0;
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

344. Reverse String (Easy)

Write a function that takes a string as input and returns the string reversed.

Example:
Given s = "hello", return "olleh".

*/
class Solution {
public:
	string reverseString(string s) {
		if (s.size() < 2) {
			return s;
		}
		int i = 0, j = s.size() - 1;
		while (i < j) {
			swap(s[i++], s[j--]);
		}
		return s;
	}
};
/*

345. Reverse Vowels of a String (Easy)

Write a function that takes a string as input and reverse only the vowels of a string.

Example 1:
Given s = "hello", return "holle".

Example 2:
Given s = "leetcode", return "leotcede".

*/
class Solution {
public:
	string reverseVowels(string s) {
		string v = "aeiouAEIOU";
		int i = 0, j = s.size() - 1;
		while (i < j) {
			while (v.find(s[i]) == -1 && i < j) {
				i++;
			}
			while (v.find(s[j]) == -1 && i < j) {
				j--;
			}
			if (i >= j) {
				break;
			}
			swap(s[i++], s[j--]);
		}
		return s;
	}
};
/*

346. Moving Average from Data Stream (Easy)

Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

For example,
MovingAverage m = new MovingAverage(3);
m.next(1) = 1
m.next(10) = (1 + 10) / 2
m.next(3) = (1 + 10 + 3) / 3
m.next(5) = (10 + 3 + 5) / 3

*/
class MovingAverage {
public:
	/** Initialize your data structure here. */
	int _size = 0, sum = 0;
	deque<int> d;
	MovingAverage(int size) {
		_size = size;
	}

	double next(int val) {
		while (d.size() >= _size) {
			sum -= d.front();
			d.pop_front();
		}
		sum += val;
		d.push_back(val);
		return (double)sum / d.size();
	}
};
/**
* Your MovingAverage object will be instantiated and called as such:
* MovingAverage obj = new MovingAverage(size);
* double param_1 = obj.next(val);
*/
/*

347. Top K Frequent Elements (Medium)

Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size

*/
class Solution {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		vector<int> res;
		unordered_map<int, int> mapping;
		for (auto i : nums) {
			mapping[i]++;
		}
		priority_queue<pair<int, int>> q;
		for (auto i = mapping.begin(); i != mapping.end(); i++) {
			q.push(make_pair(i->second, i->first));
			if (q.size() > (int)mapp.size() - k) {
				res.push_back(q.top().second);
				q.pop();
			}
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

360. Sort Transformed Array (Medium)

Given a sorted array of integers nums and integer values a, b and c. Apply a function of the form f(x) = ax2 + bx + c to each element x in the array.

The returned array must be in sorted order.

Expected time complexity: O(n)

Example:
nums = [-4, -2, 2, 4], a = 1, b = 3, c = 5,

Result: [3, 9, 15, 33]

nums = [-4, -2, 2, 4], a = -1, b = 3, c = 5

Result: [-23, -5, 1, 7]

*/
class Solution {
public:
	vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
		vector<int> res(nums.size());
		int i = 0, j = nums.size() - 1, index = a >= 0 ? nums.size() - 1 : 0;
		while (i <= j) {
			int l = quad(nums[i], a, b, c), r = quad(nums[j], a, b, c);
			if (a >= 0) {
				if (l >= r) {
					res[index--] = l;
					i++;
				}
				else {
					res[index--] = r;
					j--;
				}
			}
			else {
				if (l >= r) {
					res[index++] = r;
					j--;
				}
				else {
					res[index++] = l;
					i++;
				}
			}
		}
		return res;
	}
private:
	int quad(const int& x, const int& a, const int& b, const int& c) {
		return a * x * x + b * x + c;
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

362. Design Hit Counter (Medium)

Design a hit counter which counts the number of hits received in the past 5 minutes.

Each function accepts a timestamp parameter (in seconds granularity) and you may assume that calls are being made to the system in chronological order (ie, the timestamp is monotonically increasing). You may assume that the earliest timestamp starts at 1.

It is possible that several hits arrive roughly at the same time.

Example:
HitCounter counter = new HitCounter();

// hit at timestamp 1.
counter.hit(1);

// hit at timestamp 2.
counter.hit(2);

// hit at timestamp 3.
counter.hit(3);

// get hits at timestamp 4, should return 3.
counter.getHits(4);

// hit at timestamp 300.
counter.hit(300);

// get hits at timestamp 300, should return 4.
counter.getHits(300);

// get hits at timestamp 301, should return 3.
counter.getHits(301);
Follow up:
What if the number of hits per second could be very large? Does your design scale?

*/
class HitCounter {
public:
	/** Initialize your data structure here. */
	HitCounter() {
		num = 0;
	}

	/** Record a hit.
	@param timestamp - The current timestamp (in seconds granularity). */
	void hit(int timestamp) {
		num++;
		if (!q.empty() && q.back().first == timestamp) {
			q.back().second++;
		}
		else {
			q.push(make_pair(timestamp, 1));
		}
	}

	/** Return the number of hits in the past 5 minutes.
	@param timestamp - The current timestamp (in seconds granularity). */
	int getHits(int timestamp) {
		while (!q.empty() && timestamp - q.front().first >= 300) {
			num -= q.front().second;
			q.pop();
		}
		return num;
	}
private:
	queue<pair<int, int>> q;
	int num;
};
/**
* Your HitCounter object will be instantiated and called as such:
* HitCounter obj = new HitCounter();
* obj.hit(timestamp);
* int param_2 = obj.getHits(timestamp);
*/
/*

364. Nested List Weight Sum II (Medium)

Given a nested list of integers, return the sum of all integers in the list weighted by their depth.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Different from the previous question where weight is increasing from root to leaf, now the weight is defined from bottom up. i.e., the leaf level integers have weight 1, and the root level integers have the largest weight.

Example 1:
Given the list [[1,1],2,[1,1]], return 8. (four 1's at depth 1, one 2 at depth 2)

Example 2:
Given the list [1,[4,[6]]], return 17. (one 1 at depth 3, one 4 at depth 2, and one 6 at depth 1; 1*3 + 4*2 + 6*1 = 17)

*/
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
	int depthSumInverse(vector<NestedInteger>& nestedList) {
		int unweighted = 0, weighted = 0;
		while (!nestedList.empty()) {
			vector<NestedInteger> nextLevel;
			for (NestedInteger ni : nestedList) {
				if (ni.isInteger()) {
					unweighted += ni.getInteger();
				}
				else {
					for (NestedInteger ni : ni.getList()) {
						nextLevel.push_back(ni);
					}
				}
			}
			weighted += unweighted;
			nestedList = nextLevel;
		}
		return weighted;
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
private:
	int findLeaves(TreeNode* root, vector<vector<int>>& res) {
		if (root == NULL) {
			return 0;
		}
		int l = findLeaves(root->left, res), r = findLeaves(root->right, res);
		int height = max(l, r) + 1;
		if (res.size() < height) {
			res.push_back(vector<int>());
		}
		res[height - 1].push_back(root->val);
		return height;
	}
};
/*

367. Valid Perfect Square (Medium)

Given a positive integer num, write a function which returns True if num is a perfect square else False.

Note: Do not use any built-in library function such as sqrt.

Example 1:

Input: 16
Returns: True
Example 2:

Input: 14
Returns: False

*/
class Solution {
public:
	bool isPerfectSquare(int num) {
		int l = 1, r = num;
		while (l < r - 1) {
			int mid = l + (r - l) / 2;
			if (mid * mid == num) {
				return true;
			}
			else if (num / mid < mid) {
				r = mid;
			}
			else {
				l = mid;
			}
		}
		return l * l == num || r * r == num;
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

369. Plus One Linked List (Medium)

Given a non-negative integer represented as non-empty a singly linked list of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.

Example:
Input:
1->2->3

Output:
1->2->4

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* plusOne(ListNode* head) {
		int carry = helper(head);
		if (carry != 0) {
			ListNode* newhead = new ListNode(carry);
			newhead->next = head;
			return newhead;
		}
		return head;
	}
private:
	int helper(ListNode* head) {
		if (head == NULL) {
			return 1;
		}
		int val = head->val + helper(head->next);
		head->val = val % 10;
		return val / 10;
	}
};
/*

370. Range Addition (Medium)

Assume you have an array of length n initialized with all 0's and are given k update operations.

Each operation is represented as a triplet: [startIndex, endIndex, inc] which increments each element of subarray A[startIndex ... endIndex] (startIndex and endIndex inclusive) with inc.

Return the modified array after all k operations were executed.

Example:

Given:

	length = 5,
	updates = [
		[1,  3,  2],
		[2,  4,  3],
		[0,  2, -2]
	]

Output:

	[-2, 0, 3, 5, 3]
Explanation:

Initial state:
[ 0, 0, 0, 0, 0 ]

After applying operation [1, 3, 2]:
[ 0, 2, 2, 2, 0 ]

After applying operation [2, 4, 3]:
[ 0, 2, 5, 5, 3 ]

After applying operation [0, 2, -2]:
[-2, 0, 3, 5, 3 ]
Hint:

Thinking of using advanced data structures? You are thinking it too complicated.
For each update operation, do you really need to update all elements between i and j?
Update only the first and end element is sufficient.
The optimal time complexity is O(k + n) and uses O(1) extra space.

*/
class Solution {
public:
	vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
		vector<int> res(length, 0);
		for (vector<int> v : updates) {
			res[v[0]] += v[2];
			if (v[1] < length - 1) {
				res[v[1] + 1] -= v[2];
			}
		}
		for (int i = 1; i < length; i++) {
			res[i] += res[i - 1];
		}
		return res;
	}
};
/*

371. Sum of Two Integers (Easy)

Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example:
Given a = 1 and b = 2, return 3.

*/
class Solution {
public:
	int getSum(int a, int b) {
		int sum = 0;
		while (b != 0) {
			sum = a ^ b;
			b = (a & b) << 1;
			a = sum;
		}
		return sum;
	}
};
/*

372. Super Pow (Medium)

Your task is to calculate ab mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.

Example1:

a = 2
b = [3]

Result: 8
Example2:

a = 2
b = [1,0]

Result: 1024

*/
class Solution {
public:
	int superPow(int a, vector<int>& b) {
		if (a % 1337 == 0) return 0;
		int p = 0;
		for (int i : b)
			p = (p * 10 + i) % 1140;
		if (p == 0) p += 1140;
		return power(a, p, 1337);
	}
	int power(int x, int n, int mod) {
		int ret = 1;
		for (x %= mod; n; x = x * x % mod, n >>= 1)
			if (n & 1) ret = ret * x % mod;
		return ret;
	}
};
/*

373. Find K Pairs with Smallest Sums (Medium)

You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.

Define a pair (u,v) which consists of one element from the first array and one element from the second array.

Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:
Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3

Return: [1,2],[1,4],[1,6]

The first 3 pairs are returned from the sequence:
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
Example 2:
Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2

Return: [1,1],[1,1]

The first 2 pairs are returned from the sequence:
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
Example 3:
Given nums1 = [1,2], nums2 = [3],  k = 3

Return: [1,3],[2,3]

All possible pairs are returned from the sequence:
[1,3],[2,3]

*/
class Comp {
public:
	bool operator()(pair<int, int>& p1, pair<int, int>& p2) {
		return p1.first + p1.second < p2.first + p2.second;
	}
};
class Solution {
public:
	vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
		vector<pair<int, int>> res;
		priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> pq;
		int m = min((int)nums1.size(), k), n = min((int)nums2.size(), k);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (pq.size() < k) {
					pq.push(make_pair(nums1[i], nums2[j]));
				}
				else if (nums1[i] + nums2[j] < pq.top().first + pq.top().second) {
					pq.push(make_pair(nums1[i], nums2[j]));
					pq.pop();
				}
			}
		}
		while (!pq.empty()) {
			res.push_back(pq.top());
			pq.pop();
		}
		return res;
	}
};
/*

374. Guess Number Higher or Lower (Easy)

We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I'll tell you whether the number is higher or lower.

You call a pre-defined API guess(int num) which returns 3 possible results (-1, 1, or 0):

-1 : My number is lower
 1 : My number is higher
 0 : Congrats! You got it!
Example:
n = 10, I pick 6.

Return 6.

*/
// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
	int guessNumber(int n) {
		int left = 1, right = n;
		while (left != right) {
			int mid = left / 2 + right / 2;
			switch (guess(mid)) {
			case 1: left = mid + 1; break;
			case -1: right = mid - 1; break;
			case 0: return mid;
			}
		}
		return left;
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

378. Kth Smallest Element in a Sorted Matrix (Medium)

Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.
Note:
You may assume k is always valid, 1 ≤ k ≤ n2.

*/
class Solution {
public:
	int kthSmallest(vector<vector<int>>& matrix, int k) {
		int l = matrix[0][0], r = matrix.back().back();
		while (l < r) {
			int mid = l + (r - l) / 2;
			int num = 0;
			for (int i = 0; i < matrix.size(); i++) {
				num += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
			}
			if (num < k) {
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}
		return l;
	}
};
class Comp {
public:
	bool operator()(pair<int, pair<int, int>> p1, pair<int, pair<int, int>> p2) {
		return p1.first > p2.first;
	}
};
class Solution {
public:
	int kthSmallest(vector<vector<int>>& matrix, int k) {
		priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, Comp> pq;
		vector<vector<bool>> t(matrix.size(), vector<bool>(matrix[0].size(), false));
		pq.push(make_pair(matrix[0][0], make_pair(0, 0)));
		t[0][0] = true;
		while (1) {
			pair<int, pair<int, int>> p = pq.top();
			pq.pop();
			if (k == 1) {
				return p.first;
			}
			k--;
			// k--;
			// if (k == 0) {
			// return p.first;
			// }
			int row = p.second.first, col = p.second.second;
			if (row < matrix.size() - 1 && t[row + 1][col] == false) {
				t[row + 1][col] = true;
				pq.push(make_pair(matrix[row + 1][col], make_pair(row + 1, col)));
			}
			if (col < matrix[0].size() - 1 && t[row][col + 1] == false) {
				t[row][col + 1] = true;
				pq.push(make_pair(matrix[row][col + 1], make_pair(row, col + 1)));
			}
		}
		return 0;
	}
};
/*

379. Design Phone Directory (Medium)

Design a Phone Directory which supports the following operations:

get: Provide a number which is not assigned to anyone.
check: Check if a number is available or not.
release: Recycle or release a number.
Example:

// Init a phone directory containing a total of 3 numbers: 0, 1, and 2.
PhoneDirectory directory = new PhoneDirectory(3);

// It can return any available phone number. Here we assume it returns 0.
directory.get();

// Assume it returns 1.
directory.get();

// The number 2 is available, so return true.
directory.check(2);

// It returns 2, the only number that is left.
directory.get();

// The number 2 is no longer available, so return false.
directory.check(2);

// Release number 2 back to the pool.
directory.release(2);

// Number 2 is available again, return true.
directory.check(2);

*/
class PhoneDirectory {
public:
	queue<int> q;
	unordered_set<int> s;
	int max;
	/** Initialize your data structure here
	@param maxNumbers - The maximum numbers that can be stored in the phone directory. */
	PhoneDirectory(int maxNumbers) {
		for (int i = 0; i < maxNumbers; i++) {
			q.push(i);
			max = maxNumbers;
		}
	}

	/** Provide a number which is not assigned to anyone.
	@return - Return an available number. Return -1 if none is available. */
	int get() {
		if (q.empty()) {
			return -1;
		}
		int res = q.front();
		q.pop();
		s.insert(res);
		return res;
	}

	/** Check if a number is available or not. */
	bool check(int number) {
		if (number >= max || number < 0) {
			return false;
		}
		return s.find(number) == s.end();
	}

	/** Recycle or release a number. */
	void release(int number) {
		if (s.find(number) != s.end())
			q.push(number);
		s.erase(number);
	}
};
/**
* Your PhoneDirectory object will be instantiated and called as such:
* PhoneDirectory obj = new PhoneDirectory(maxNumbers);
* int param_1 = obj.get();
* bool param_2 = obj.check(number);
* obj.release(number);
*/
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

382. Linked List Random Node (Medium)

Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.

Follow up:
What if the linked list is extremely large and its length is unknown to you? Could you solve this efficiently without using extra space?

Example:

// Init a singly linked list [1,2,3].
ListNode head = new ListNode(1);
head.next = new ListNode(2);
head.next.next = new ListNode(3);
Solution solution = new Solution(head);

// getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.
solution.getRandom();

*/
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	/** @param head The linked list's head.
	Note that the head is guaranteed to be not null, so it contains at least one node. */
	Solution(ListNode* head) {
		p = head;
	}

	/** Returns a random node's value. */
	int getRandom() {
		ListNode* q = p;
		int res, num = 1;
		while (q != NULL) {
			if (num == rand() % num + 1) {
				res = q->val;
			}
			num++;
			q = q->next;
		}
		return res;
	}
private:
	ListNode* p = NULL;
};
/**
* Your Solution object will be instantiated and called as such:
* Solution obj = new Solution(head);
* int param_1 = obj.getRandom();
*/
/*

383. Ransom Note (Easy)


Given an arbitrary ransom note string and another string containing letters from all the magazines, write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

Note:
You may assume that both strings contain only lowercase letters.

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true

*/
class Solution {
public:
	bool canConstruct(string ransomNote, string magazine) {
		int t[256] = { 0 };
		for (char cha : magazine) {
			t[cha]++;
		}
		for (char cha : ransomNote) {
			if (t[cha]-- == 0) {
				return false;
			}
		}
		return true;
	}
};
/*

384. Shuffle an Array (Medium)

Shuffle a set of numbers without duplicates.

Example:

// Init an array with set 1, 2, and 3.
int[] nums = {1,2,3};
Solution solution = new Solution(nums);

// Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3] must equally likely to be returned.
solution.shuffle();

// Resets the array back to its original configuration [1,2,3].
solution.reset();

// Returns the random shuffling of array [1,2,3].
solution.shuffle();

*/
class Solution {
public:
	vector<int> original, shuffled;
	Solution(vector<int> nums) {
		original = nums;
		shuffled = nums;
	}
	/** Resets the array to its original configuration and return it. */
	vector<int> reset() {
		return original;
	}
	/** Returns a random shuffling of the array. */
	vector<int> shuffle() {
		for (int i = 0; i < shuffled.size(); i++) {
			int index = rand() % (shuffled.size() - i);
			swap(shuffled[i], shuffled[i + index]);
		}
		return shuffled;
	}
};
/**
* Your Solution object will be instantiated and called as such:
* Solution obj = new Solution(nums);
* vector<int> param_1 = obj.reset();
* vector<int> param_2 = obj.shuffle();
*/
/*

386. Lexicographical Numbers (medium)

Given an integer n, return 1 - n in lexicographical order.

For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].

Please optimize your algorithm to use less time and space. The input size may be as large as 5,000,000.

*/
class Solution {
public:
	vector<int> lexicalOrder(int n) {
		vector<int> res;
		int cur = 1;
		for (int i = 1; i <= n; i++) {
			res.push_back(cur);
			if (cur * 10 <= n) {
				cur *= 10;
			}
			else if (cur % 10 != 9 && cur + 1 <= n) {
				cur++;
			}
			else {
				while ((cur / 10) % 10 == 9) {
					cur /= 10;
				}
				cur = cur / 10 + 1;
			}
		}
		return res;
	}
};
/*

387. First Unique Character in a String (Easy)

Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.

*/
class Solution {
public:
	int firstUniqChar(string s) {
		int t[26] = { 0 };
		for (char cha : s) {
			t[cha - 'a']++;
		}
		for (int i = 0; i < s.size(); i++) {
			if (t[s[i] - 'a'] == 1) {
				return i;
			}
		}
		return -1;
	}
};
/*

388. Longest Absolute File Path (Medium)

Suppose we abstract our file system by a string in the following manner:

The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:

dir
subdir1
subdir2
file.ext
The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a file file.ext.

The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:

dir
subdir1
file1.ext
subsubdir1
subdir2
subsubdir2
file2.ext
The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1. subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.

We are interested in finding the longest (number of characters) absolute path to a file within our file system. For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not including the double quotes).

Given a string representing the file system in the above format, return the length of the longest absolute path to file in the abstracted file system. If there is no file in the system, return 0.

Note:
The name of a file contains at least a . and an extension.
The name of a directory or sub-directory will not contain a ..
Time complexity required: O(n) where n is the size of the input string.

Notice that a/aa/aaa/file1.txt is not the longest file path, if there is another path aaaaaaaaaaaaaaaaaaaaa/sth.png.

*/
class Solution {
public:
	int lengthLongestPath(string input) {
		int res = 0, n = input.size(), level = 0;
		unordered_map<int, int> m{ { 0, 0 } };
		for (int i = 0; i < n; i++) {
			int start = i;
			while (i < n && input[i] != '\n' && input[i] != '\t') {
				i++;
			}
			if (i >= n || input[i] == '\n') {
				string t = input.substr(start, i - start);
				if (t.find('.') != string::npos) {
					res = max(res, m[level] + (int)t.size());
				}
				else {
					level++;
					m[level] = m[level - 1] + (int)t.size() + 1;
				}
				level = 0;
			}
			else {
				level++;
			}
		}
		return res;
	}
};
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

394. Decode String (Medium)

Given an encoded string, return it's decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".

*/
class Solution {
public:
	string decodeString(string s) {
		string res;
		int i = 0;
		while (i < s.size()) {
			if (isalpha(s[i])) {
				res += s[i++];
			}
			else {
				int num = 0;
				while (isdigit(s[i])) {
					num = num * 10 + s[i++] - '0';
				}
				int start = ++i;
				for (int l = 1, r = 0; l != r; i++) {
					l += s[i] == '[';
					r += s[i] == ']';
				}
				string temp = decodeString(s.substr(start, i - start - 1));
				for (int j = 0; j < num; j++) {
					res += temp;
				}
			}
		}
		return res;
	}
};
/*

396. Rotate Function (Easy)

Given an array of integers A and let n to be its length.

Assume Bk to be an array obtained by rotating the array A k positions clock-wise, we define a "rotation function" F on A as follow:

F(k) = 0 * Bk[0] + 1 * Bk[1] + ... + (n-1) * Bk[n-1].

Calculate the maximum value of F(0), F(1), ..., F(n-1).

Note:
n is guaranteed to be less than 10^5.

Example:

A = [4, 3, 2, 6]

F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26

So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.

*/
class Solution {
public:
	int maxRotateFunction(vector<int>& A) {
		if (A.empty()) {
			return 0;
		}
		int sum = 0, res = INT_MIN, temp = 0;
		for (int i = 0; i < A.size(); i++) {
			sum += A[i];
			temp += i* A[i];
		}
		res = temp;
		for (int i = 1; i < A.size(); i++) {
			temp += sum - A.size() * A[A.size() - i];
			res = max(res, temp);
		}
		return res;
	}
};
/*

397. Integer Replacement (Easy)

Given a positive integer n and you can do operations as follow:

If n is even, replace n with n/2.
If n is odd, you can replace n with either n + 1 or n - 1.
What is the minimum number of replacements needed for n to become 1?

Example 1:

Input:
8

Output:
3

Explanation:
8 -> 4 -> 2 -> 1
Example 2:

Input:
7

Output:
4

Explanation:
7 -> 8 -> 4 -> 2 -> 1
or
7 -> 6 -> 3 -> 2 -> 1

*/
class Solution {
public:
	int integerReplacement(int n) {
		int res = 0;
		unsigned m = n;
		while (m > 3) {
			if (!(m & 1)) {
				m >>= 1;
			}
			else if (m & 2) {
				m++;
			}
			else {
				m--;
			}
			res++;
		}
		return res + m - 1;
	}
};
/*

398. Random Pick Index (medium)

Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.

Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

Example:

int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);

// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);

*/
class Solution {
public:
	Solution(vector<int> nums) {
		t = nums;
	}

	int pick(int target) {
		int cnt = 0, res = -1;
		for (int i = 0; i < t.size(); i++) {
			if (t[i] != target) {
				continue;
			}
			cnt++;
			if (cnt == rand() % cnt + 1) {
				res = i;
			}
		}
		return res;
	}
private:
	vector<int> t;
};
/**
* Your Solution object will be instantiated and called as such:
* Solution obj = new Solution(nums);
* int param_1 = obj.pick(target);
*/
/*

399. Evaluate Division (Medium)

Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0.
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ].
The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.

*/
class Solution {
public:
	vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
		unordered_map<string, unordered_map<string, double>> pairs;
		for (int i = 0; i < equations.size(); i++) {
			pairs[equations[i].first][equations[i].second] = values[i];
			pairs[equations[i].second][equations[i].first] = 1 / values[i];
		}
		vector<double> res(queries.size());
		for (int i = 0; i < queries.size(); i++) {
			if (pairs.count(queries[i].first) && pairs.count(queries[i].second)) {
				if (queries[i].first == queries[i].second) {
					res[i] = 1.0;
				}
				else {
					unordered_set<string> visited;
					res[i] = dfs(queries[i].first, queries[i].second, pairs, visited, 1.0);
				}
			}
			else {
				res[i] = -1.0;
			}
		}
		return res;
	}
private:
	double dfs(const string& start, const string& end, unordered_map<string, unordered_map<string, double>> pairs, unordered_set<string>& visited, double value) {
		if (pairs[start].find(end) != pairs[start].end()) {
			return value * pairs[start][end];
		}
		for (pair<string, double> p : pairs[start]) {
			string str = p.first;
			if (visited.find(str) == visited.end()) {
				visited.insert(str);
				double cur = dfs(str, end, pairs, visited, value * p.second);
				if (cur != -1.0) {
					return cur;
				}
			}
		}
		return -1.0;
	}
};
/*

400. Nth Digit (Easy)

Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...

Note:
n is positive and will fit within the range of a 32-bit signed integer (n < 231).

Example 1:

Input:
3

Output:
3
Example 2:

Input:
11

Output:
0

Explanation:
The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.

*/
class Solution {
public:
	int findNthDigit(int n) {
		int d = 1, len = 1;
		while ((long long)9 * len * d - n < 0) {
			n -= 9 * len * d++;
			len *= 10;
		}
		int num = --n / d + len;
		for (int i = 1; i < d - n % d; i++) {
			num /= 10;
		}
		return num % 10;
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
/*

402. Remove K Digits (Medium)

Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.

*/
class Solution {
public:
	string removeKdigits(string num, int k) {
		int digits = num.size() - k;
		string res(num.size(), ' ');
		int top = 0;
		for (int i = 0;i < num.size(); i++) {
			while (top > 0 && res[top - 1] > num[i] && k > 0) {
				top--;
				k--;
			}
			res[top++] = num[i];
		}
		int index = 0;
		while (index < digits && res[index] == '0') {
			index++;
		}
		return index == digits ? "0" : res.substr(index, digits - index);
	}
};
/*

404. Sum of Left Leaves (Easy)

Find the sum of all left leaves in a given binary tree.

Example:

	3
   / \
  9  20
	/  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.

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
	int sumOfLeftLeaves(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}
		int l = sumOfLeftLeaves(root->left), r = sumOfLeftLeaves(root->right);
		if (root->left != NULL && root->left->left == NULL && root->left->right == NULL) {
			return root->left->val + l + r;
		}
		return l + r;
	}
};
/*

405. Convert a Number to Hexadecimal (Easy)

Given an integer, write an algorithm to convert it to hexadecimal. For negative integer, two’s complement method is used.

Note:

All letters in hexadecimal (a-f) must be in lowercase.
The hexadecimal string must not contain extra leading 0s. If the number is zero, it is represented by a single zero character '0'; otherwise, the first character in the hexadecimal string will not be the zero character.
The given number is guaranteed to fit within the range of a 32-bit signed integer.
You must not use any method provided by the library which converts/formats the number to hex directly.
Example 1:

Input:
26

Output:
"1a"
Example 2:

Input:
-1

Output:
"ffffffff"

*/
class Solution {
public:
	string toHex(int num) {
		if (num == 0) {
			return "0";
		}
		string res;
		int cnt = 0;
		while (num != 0 && cnt++ < 8) {
			int temp = num & 15;
			if (temp < 10) {
				res += temp + '0';
			}
			else {
				res += temp - 10 + 'a';
			}
			num >>= 4;
		}
		reverse(res.begin(), res.end());
		return res;
	}
};
/*

406. Queue Reconstruction by Height (Medium)

Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers (h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100.

Example

Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

*/
class Comp {
public:
	bool operator()(pair<int, int> p1, pair<int, int> p2) {
		return p1.first > p2.first || p1.first == p2.first && p1.second < p2.second;
	}
}comp;
class Solution {
public:
	vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
		sort(people.begin(), people.end(), comp);
		vector<pair<int, int>> res;
		for (pair<int, int> p : people) {
			res.insert(res.begin() + p.second, p);
		}
		return res;
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

408. Valid Word Abbreviation (Easy)

Given a non-empty string s and an abbreviation abbr, return whether the string matches with the given abbreviation.

A string such as "word" contains only the following valid abbreviations:

["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
Notice that only the above abbreviations are valid abbreviations of the string "word". Any other string is not a valid abbreviation of "word".

Note:
Assume s contains only lowercase letters and abbr contains only lowercase letters and digits.

Example 1:
Given s = "internationalization", abbr = "i12iz4n":

Return true.
Example 2:
Given s = "apple", abbr = "a2e":

Return false.

*/
class Solution {
public:
	bool validWordAbbreviation(string word, string abbr) {
		return validWordAbbreviation(word, 0, abbr, 0);
	}
private:
	bool validWordAbbreviation(const string& word, int i, const string& abbr, int j) {
		if (i == word.size() && j == abbr.size()) {
			return true;
		}
		else if (i >= word.size() || j >= abbr.size()) {
			return false;
		}
		if (isdigit(abbr[j]) == true) {
			if (abbr[j] == '0') {
				return false;
			}
			int step = 0;
			while (j < abbr.size() && isdigit(abbr[j])) {
				step = 10 * step + abbr[j++] - '0';
			}
			return validWordAbbreviation(word, i + step, abbr, j);
		}
		else {
			if (word[i] == abbr[j]) {
				return validWordAbbreviation(word, i + 1, abbr, j + 1);
			}
			return false;
		}
		return true;
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

412. Fizz Buzz (Easy)

Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.

Example:

n = 15,

Return:
[
"1",
"2",
"Fizz",
"4",
"Buzz",
"Fizz",
"7",
"8",
"Fizz",
"Buzz",
"11",
"Fizz",
"13",
"14",
"FizzBuzz"
]

*/
class Solution {
public:
	vector<string> fizzBuzz(int n) {
		vector<string> res(n);
		for (int i = 1; i <= n; i++) {
			if (i % 3 != 0 && i % 5 != 0) {
				res[i - 1] = to_string(i);
			}
			else if (i % 3 == 0 && i % 5 == 0) {
				res[i - 1] = "FizzBuzz";
			}
			else if (i % 3 == 0) {
				res[i - 1] = "Fizz";
			}
			else {
				res[i - 1] = "Buzz";
			}
		}
		return res;
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

414. Third Maximum Number (Easy)

Given a non-empty array of integers, return the third maximum number in this array. If it does not exist, return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.

*/
class Solution {
public:
	int thirdMax(vector<int>& nums) {
		int count = 0, max = INT_MIN, mid = INT_MIN, small = INT_MIN;
		for (int num : nums) {
			if (count > 0 && num == max || count > 1 && num == mid) {
				continue;
			}
			count++;
			if (num > max) {
				small = mid;
				mid = max;
				max = num;
			}
			else if (num > mid) {
				small = mid;
				mid = num;
			}
			else if (num > small) {
				small = num;
			}
		}
		return count < 3 ? max : small;
	}
};
/*

415. Add Strings (Easy)

Given two non-negative numbers num1 and num2 represented as string, return the sum of num1 and num2.

Note:

The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.

*/
class Solution {
public:
	string addStrings(string num1, string num2) {
		string res;
		int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
		while (i >= 0 || j >= 0 || carry > 0) {
			if (i >= 0) {
				carry += num1[i--] - '0';
			}
			if (j >= 0) {
				carry += num2[j--] - '0';
			}
			res += carry % 10 + '0';
			carry /= 10;
		}
		reverse(res.begin(), res.end());
		return res;
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

419. Battleships in a Board (Medium)

Given an 2D board, count how many different battleships are in it. The battleships are represented with 'X's, empty slots are represented with '.'s. You may assume the following rules:

You receive a valid board, made of only battleships or empty slots.
Battleships can only be placed horizontally or vertically. In other words, they can only be made of the shape 1xN (1 row, N columns) or Nx1 (N rows, 1 column), where N can be of any size.
At least one horizontal or vertical cell separates between two battleships - there are no adjacent battleships.
Example:
X..X
...X
...X
In the above board there are 2 battleships.
Invalid Example:
...X
XXXX
...X
This is an invalid board that you will not receive - as battleships will always have a cell separating between them.
Follow up:
Could you do it in one-pass, using only O(1) extra memory and without modifying the value of the board?

*/
class Solution {
public:
	int countBattleships(vector<vector<char>>& board) {
		if (board.empty()) {
			return 0;
		}
		int row = board.size(), col = board[0].size(), cnt = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cnt += board[i][j] == 'X' && (i == 0 || board[i - 1][j] != 'X') && (j == 0 || board[i][j - 1] != 'X');
			}
		}
		return cnt;
	}
};
/*

422. Valid Word Square (Easy)

Given a sequence of words, check whether it forms a valid word square.

A sequence of words forms a valid word square if the kth row and column read the exact same string, where 0 ≤ k < max(numRows, numColumns).

Note:
The number of words given is at least 1 and does not exceed 500.
Word length will be at least 1 and does not exceed 500.
Each word contains only lowercase English alphabet a-z.
Example 1:

Input:
[
  "abcd",
  "bnrt",
  "crmy",
  "dtye"
]

Output:
true

Explanation:
The first row and first column both read "abcd".
The second row and second column both read "bnrt".
The third row and third column both read "crmy".
The fourth row and fourth column both read "dtye".

Therefore, it is a valid word square.
Example 2:

Input:
[
  "abcd",
  "bnrt",
  "crm",
  "dt"
]

Output:
true

Explanation:
The first row and first column both read "abcd".
The second row and second column both read "bnrt".
The third row and third column both read "crm".
The fourth row and fourth column both read "dt".

Therefore, it is a valid word square.
Example 3:

Input:
[
  "ball",
  "area",
  "read",
  "lady"
]

Output:
false

Explanation:
The third row reads "read" while the third column reads "lead".

Therefore, it is NOT a valid word square.

*/
class Solution {
public:
	bool validWordSquare(vector<string>& words) {
		for (int i = 0; i < words.size(); i++) {
			for (int j = 0; j < words[i].size(); j++) {
				if (j >= words.size() || i >= words[j].size() || words[i][j] != words[j][i]) {
					return false;
				}
			}
		}
		return true;
	}
};
/*

434. Number of Segments in a String (Easy)

Count the number of segments in a string, where a segment is defined to be a contiguous sequence of non-space characters.

Please note that the string does not contain any non-printable characters.

Example:

Input: "Hello, my name is John"
Output: 5

*/
class Solution {
public:
	int countSegments(string s) {
		int res = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] != ' ' && (i + 1 == s.size() || s[i + 1] == ' ')) {
				res++;
			}
		}
		return res;
	}
};
/*

437. Path Sum III (Easy)

You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

	  10
	 /  \
	5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11

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
	int pathSum(TreeNode* root, int sum) {
		unordered_map<int, int> mapping;
		mapping[0] = 1;
		return pathSum(root, sum, mapping, 0);
	}
private:
	int pathSum(TreeNode* root, const int& target, unordered_map<int, int>& mapping, int sum) {
		if (root == NULL) {
			return 0;
		}
		sum += root->val;
		int res = mapping[sum - target];
		mapping[sum]++;
		res += pathSum(root->left, target, mapping, sum) + pathSum(root->right, target, mapping, sum);
		mapping[sum]--;
		return res;
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

441. Arranging Coins (Easy)

You have a total of n coins that you want to form in a staircase shape, where every k-th row must have exactly k coins.

Given n, find the total number of full staircase rows that can be formed.

n is a non-negative integer and fits within the range of a 32-bit signed integer.

Example 1:

n = 5

The coins can form the following rows:
¤
¤ ¤
¤ ¤

Because the 3rd row is incomplete, we return 2.
Example 2:

n = 8

The coins can form the following rows:
¤
¤ ¤
¤ ¤ ¤
¤ ¤

Because the 4th row is incomplete, we return 3.

*/
class Solution {
public:
	int arrangeCoins(int n) {
		int l = 1, r = n;
		while (l < r) {
			long mid = l + (r - l + 1) / 2;
			if (mid * (mid + 1) / 2 <= n) {
				l = mid;
			}
			else {
				r = mid - 1;
			}
		}
		return r;
	}
};
/*

442. Find All Duplicates in an Array (Medium)

Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements that appear twice in this array.

Could you do it without extra space and in O(n) runtime?

Example:
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]

*/
class Solution {
public:
	vector<int> findDuplicates(vector<int>& nums) {
		vector<int> res;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[abs(nums[i]) - 1] < 0) {
				res.push_back(abs(nums[i]));
			}
			nums[abs(nums[i]) - 1] *= -1;
		}
		return res;
	}
};
/*

445. Add Two Numbers II (Medium)

You are given two linked lists representing two non-negative numbers. The most significant digit comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

Example:

Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		if (l1 == NULL || l2 == NULL) {
			return l1 == NULL ? l2 : l1;
		}
		extend(l1, l2);
		ListNode *temp = add(l1, l2);
		return temp->val == 0 ? l1 : temp;
	}
private:
	int getLength(ListNode* l) {
		int res = 0;
		while (l != NULL) {
			res++;
			l = l->next;
		}
		return res;
	}
	void extend(ListNode*& l1, ListNode*& l2) {
		int len1 = getLength(l1), len2 = getLength(l2);
		while (len1 > len2) {
			ListNode *n = new ListNode(0);
			n->next = l2;
			l2 = n;
			len1--;
		}
		while (len1 < len2) {
			ListNode *n = new ListNode(0);
			n->next = l1;
			l1 = n;
			len2--;
		}
	}
	ListNode* add(ListNode* l1, ListNode* l2) {
		if (l1 == NULL) {
			return new ListNode(0);
		}
		l1->val += l2->val + add(l1->next, l2->next)->val;
		ListNode *tmp = new ListNode(l1->val / 10);
		l1->val %= 10;
		tmp->next = l1;
		return tmp;
	}
};
class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		if (l1 == NULL || l2 == NULL) {
			return l1 == NULL ? l2 : l1;
		}
		stack<int> s1, s2;
		while (l1 != NULL) {
			s1.push(l1->val);
			l1 = l1->next;
		}
		while (l2 != NULL) {
			s2.push(l2->val);
			l2 = l2->next;
		}
		ListNode *newhead = new ListNode(-1);
		int sum = 0;
		while (!s1.empty() || !s2.empty() || sum > 0) {
			int num1 = 0, num2 = 0;
			if (!s1.empty()) {
				num1 = s1.top();
				s1.pop();
			}
			if (!s2.empty()) {
				num2 = s2.top();
				s2.pop();
			}
			sum += num1 + num2;
			ListNode *node = new ListNode(sum % 10);
			node->next = newhead->next;
			newhead->next = node;
			sum /= 10;
		}
		return newhead->next;
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

448. Find All Numbers Disappeared in an Array (Easy)

Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements of [1, n] inclusive that do not appear in this array.

Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:

Input:
[4,3,2,7,8,2,3,1]

Output:
[5,6]

*/
class Solution {
public:
	vector<int> findDisappearedNumbers(vector<int>& nums) {
		vector<int> res;
		for (int i = 0; i < nums.size(); i++) {
			int index = abs(nums[i]) - 1;
			if (nums[index] > 0) {
				nums[index] = -nums[index];
			}
		}
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] > 0) {
				res.push_back(i + 1);
			}
		}
		return res;
	}
};
/*

449. Serialize and Deserialize BST (Medium)

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary search tree can be serialized to a string and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

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
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream out;
		serialize(root, out);
		return out.str();
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream in(data);
		return deserialize(in);
	}
private:
	void serialize(TreeNode* root, ostringstream& out) {
		if (root) {
			out << root->val << ' ';
			serialize(root->left, out);
			serialize(root->right, out);
		}
		else {
			out << "# ";
		}
	}
	TreeNode* deserialize(istringstream& in) {
		string val;
		in >> val;
		if (val == "#")
			return nullptr;
		TreeNode* root = new TreeNode(stoi(val));
		root->left = deserialize(in);
		root->right = deserialize(in);
		return root;
	}
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
/*

450. Delete Node in a BST (Medium)

Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.
Note: Time complexity should be O(height of tree).

Example:

root = [5,3,6,2,4,null,7]
key = 3

	5
   / \
  3   6
 / \   \
2   4   7

Given key to delete is 3. So we find the node with value 3 and delete it.

One valid answer is [5,4,6,2,null,null,7], shown in the following BST.

	5
   / \
  4   6
 /     \
2       7

Another valid answer is [5,2,6,null,4,null,7].

	5
   / \
  2   6
   \   \
	4   7

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
	TreeNode* deleteNode(TreeNode* root, int key) {
		if (root == NULL) {
			return root;
		}
		else if (root->val < key) {
			root->right = deleteNode(root->right, key);
		}
		else if (root->val > key) {
			root->left = deleteNode(root->left, key);
		}
		else {
			if (root->left == NULL || root->right == NULL) {
				return root->left == NULL ? root->right : root->left;
			}
			else {
				root->val = findSmallest(root->right);
				root->right = deleteNode(root->right, root->val);
			}
		}
		return root;
	}
private:
	int findSmallest(TreeNode* root) {
		while (root->left != NULL) {
			root = root->left;
		}
		return root->val;
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

453. Minimum Moves to Equal Array Elements (Easy)

Given a non-empty integer array of size n, find the minimum number of moves required to make all array elements equal, where a move is incrementing n - 1 elements by 1.

Example:

Input:
[1,2,3]

Output:
3

Explanation:
Only three moves are needed (remember each move increments two elements):

[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]

*/
class Solution {
public:
	int minMoves(vector<int>& nums) {
		int m = nums[0], res = 0;
		for (int i = 1; i < nums.size(); i++) {
			m = min(m, nums[i]);
		}
		for (int num : nums) {
			res += num - m;
		}
		return res;
	}
};
/*

455. Assign Cookies (Easy)

Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie. Each child i has a greed factor gi, which is the minimum size of a cookie that the child will be content with; and each cookie j has a size sj. If sj >= gi, we can assign the cookie j to the child i, and the child i will be content. Your goal is to maximize the number of your content children and output the maximum number.

Note:
You may assume the greed factor is always positive.
You cannot assign more than one cookie to one child.

Example 1:
Input: [1,2,3], [1,1]

Output: 1

Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3.
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.
Example 2:
Input: [1,2], [1,2,3]

Output: 2

Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2.
You have 3 cookies and their sizes are big enough to gratify all of the children,
You need to output 2.

*/
class Solution {
public:
	int findContentChildren(vector<int>& g, vector<int>& s) {
		sort(g.begin(), g.end());
		sort(s.begin(), s.end());
		int i = 0, j = 0;
		while (i < g.size() && j < s.size()) {
			if (g[i] > s[j]) {
				j++;
			}
			else {
				i++;
				j++;
			}
		}
		return i;
	}
};
/*

459. Repeated Substring Pattern (Easy)

Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.

Example 1:
Input: "abab"

Output: True

Explanation: It's the substring "ab" twice.
Example 2:
Input: "aba"

Output: False
Example 3:
Input: "abcabcabcabc"

Output: True

Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)

*/
class Solution {
public:
	bool repeatedSubstringPattern(string s) {
		vector<int> t(s.size(), 0);
		for (int i = 1; i < s.size(); i++) {
			int j = t[i - 1];
			while (j > 0 && s[i] != s[j]) {
				j = t[j - 1];
			}
			t[i] = (j += s[i] == s[j]);
		}
		return t.back() && t.back() % (s.size() - t.back()) == 0;
	}
};
/*

461. Hamming Distance (Easy)

The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, calculate the Hamming distance.

Note:
0 ≤ x, y < 231.

Example:

Input: x = 1, y = 4

Output: 2

Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
	   ↑   ↑

The above arrows point to positions where the corresponding bits are different.

*/
class Solution {
public:
	int hammingDistance(int x, int y) {
		int res = 0;
		x ^= y;
		while (x != 0) {
			res++;
			x &= x - 1;
		}
		return res;
	}
};
/*

462. Minimum Moves to Equal Array Elements II (Medium)

Given a non-empty integer array, find the minimum number of moves required to make all array elements equal, where a move is incrementing a selected element by 1 or decrementing a selected element by 1.

You may assume the array's length is at most 10,000.

Example:

Input:
[1,2,3]

Output:
2

Explanation:
Only two moves are needed (remember each move increments or decrements one element):

[1,2,3]  =>  [2,2,3]  =>  [2,2,2]

*/
class Solution {
public:
	int minMoves2(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int res = 0, i = 0, j = nums.size() - 1;
		while (i < j) {
			res += nums[j--] - nums[i++];
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

475. Heaters (Easy)

Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.

Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.

So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.

Note:
Numbers of houses and heaters you are given are non-negative and will not exceed 25000.
Positions of houses and heaters you are given are non-negative and will not exceed 10^9.
As long as a house is in the heaters' warm radius range, it can be warmed.
All the heaters follow your radius standard and the warm radius will the same.
Example 1:
Input: [1,2,3],[2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
Example 2:
Input: [1,2,3,4],[1,4]
Output: 1
Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.

*/
class Solution {
public:
	int findRadius(vector<int>& houses, vector<int>& heaters) {
		sort(houses.begin(), houses.end());
		sort(heaters.begin(), heaters.end());
		int i = 0, res = 0;
		for (int house : houses) {
			while (i < heaters.size() - 1 && heaters[i] + heaters[i + 1] <= house * 2) {
				i++;
			}
			res = max(res, abs(heaters[i] - house));
		}
		return res;
	}
};
/*

476. Number Complement (Easy)

Given a positive integer, output its complement number. The complement strategy is to flip the bits of its binary representation.

Note:
The given integer is guaranteed to fit within the range of a 32-bit signed integer.
You could assume no leading zero bit in the integer’s binary representation.
Example 1:
Input: 5
Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
Example 2:
Input: 1
Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.

*/
class Solution {
public:
	int findComplement(int num) {
		unsigned int mask = ~0;
		while (mask & num) {
			mask <<= 1;
		}
		return ~mask & ~num;
	}
};
/*

477. Total Hamming Distance (Medium)

The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Now your job is to find the total Hamming distance between all pairs of the given numbers.

Example:
Input: 4, 14, 2

Output: 6

Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case). So the answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
Note:
Elements of the given array are in the range of 0 to 10^9
Length of the array will not exceed 10^4.

*/
class Solution {
public:
	int totalHammingDistance(vector<int>& nums) {
		int res = 0, n = nums.size();
		for (int j = 0;j < 32;j++) {
			int bitCount = 0;
			for (int i = 0;i < n;i++) {
				bitCount += (nums[i] >> j) & 1;
			}
			res += bitCount * (n - bitCount);
		}
		return res;
	}
};
/*

481. Magical String (Medium)

A magical string S consists of only '1' and '2' and obeys the following rules:

The string S is magical because concatenating the number of contiguous occurrences of characters '1' and '2' generates the string S itself.

The first few elements of string S is the following: S = "1221121221221121122……"

If we group the consecutive '1's and '2's in S, it will be:

1 22 11 2 1 22 1 22 11 2 11 22 ......

and the occurrences of '1's or '2's in each group are:

1 2	2 1 1 2 1 2 2 1 2 2 ......

You can see that the occurrence sequence above is the S itself.

Given an integer N as input, return the number of '1's in the first N number in the magical string S.

Note: N will not exceed 100,000.

Example 1:
Input: 6
Output: 3
Explanation: The first 6 elements of magical string S is "12211" and it contains three 1's, so return 3.

*/
class Solution {
public:
	int magicalString(int n) {
		string s = "122";
		int i = 2;
		while (s.size() < n) {
			s += string(s[i++] - '0', s.back() ^ 3);
		}
		return count(s.begin(), s.begin() + n, '1');
	}
};
/*

482. License Key Formatting (Medium)

Now you are given a string S, which represents a software license key which we would like to format. The string S is composed of alphanumerical characters and dashes. The dashes split the alphanumerical characters within the string into groups. (i.e. if there are M dashes, the string is split into M+1 groups). The dashes in the given string are possibly misplaced.

We want each group of characters to be of length K (except for possibly the first group, which could be shorter, but still must contain at least one character). To satisfy this requirement, we will reinsert dashes. Additionally, all the lower case letters in the string must be converted to upper case.

So, you are given a non-empty string S, representing a license key to format, and an integer K. And you need to return the license key formatted according to the description above.

Example 1:
Input: S = "2-4A0r7-4k", K = 4

Output: "24A0-R74K"

Explanation: The string S has been split into two parts, each part has 4 characters.
Example 2:
Input: S = "2-4A0r7-4k", K = 3

Output: "24-A0R-74K"

Explanation: The string S has been split into three parts, each part has 3 characters except the first part as it could be shorter as said above.
Note:
The length of string S will not exceed 12,000, and K is a positive integer.
String S consists only of alphanumerical characters (a-z and/or A-Z and/or 0-9) and dashes(-).
String S is non-empty.

*/
class Solution {
public:
	string licenseKeyFormatting(string S, int K) {
		string res = "";
		for (int i = S.size() - 1; i >= 0; i--) {
			if (S[i] != '-') {
				if (res.size() % (K + 1) - K == 0) {
					res += '-';
				}
				res += toupper(S[i]);
			}
		}
		reverse(res.begin(), res.end());
		return res;
	}
};
/*

485. Max Consecutive Ones (Easy)

Given a binary array, find the maximum number of consecutive 1s in this array.

Example 1:
Input: [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s.
	The maximum number of consecutive 1s is 3.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000

*/
class Solution {
public:
	int findMaxConsecutiveOnes(vector<int>& nums) {
		int res = 0, cur = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] == 1) {
				cur++;
				res = max(res, cur);
			}
			else {
				cur = 0;
			}
		}
		return res;
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

487. Max Consecutive Ones II (Medium)

Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most one 0.

Example 1:
Input: [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
	After flipping, the maximum number of consecutive 1s is 4.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
Follow up:
What if the input numbers come in one by one as an infinite stream? In other words, you can't store all numbers coming from the stream as it's too large to hold in memory. Could you solve it efficiently?

*/
class Solution {
public:
	int findMaxConsecutiveOnes(vector<int>& nums) {
		int res = 0, l = 0, r = 0;
		bool one = false;
		while (r < nums.size()) {
			if (nums[r] == 0 && one == true) {
				while (nums[l] != 0) {
					l++;
				}
				one = false;
				l++;
			}
			res = max(res, r - l + 1);
			if (nums[r] == 0) {
				one = true;
			}
			r++;
		}
		return res;
	}
};
/*

492. Construct the Rectangle (Easy)

For a web developer, it is very important to know how to design a web page's size. So, given a specific rectangular web page’s area, your job by now is to design a rectangular web page, whose length L and width W satisfy the following requirements:

1. The area of the rectangular web page you designed must equal to the given target area.

2. The width W should not be larger than the length L, which means L >= W.

3. The difference between length L and width W should be as small as possible.
You need to output the length L and the width W of the web page you designed in sequence.
Example:
Input: 4
Output: [2, 2]
Explanation: The target area is 4, and all the possible ways to construct it are [1,4], [2,2], [4,1].
But according to requirement 2, [1,4] is illegal; according to requirement 3,  [4,1] is not optimal compared to [2,2]. So the length L is 2, and the width W is 2.
Note:
The given area won't exceed 10,000,000 and is a positive integer
The web page's width and length you designed must be positive integers.

*/
class Solution {
public:
	vector<int> constructRectangle(int area) {
		int w = sqrt(area);
		while (area % w != 0) {
			w--;
		}
		return{ area / w, w };
	}
};
/*

496. Next Greater Element I (Easy)

You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2. Find all the next greater numbers for nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, output -1 for this number.

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
	For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
	For number 1 in the first array, the next greater number for it in the second array is 3.
	For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
	For number 2 in the first array, the next greater number for it in the second array is 3.
	For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
Note:
All elements in nums1 and nums2 are unique.
The length of both nums1 and nums2 would not exceed 1000.

*/
class Solution {
public:
	vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
		vector<int> res(findNums.size());
		unordered_map<int, int> mapping;
		stack<int> sta;
		for (const int& num : nums) {
			while (!sta.empty() && sta.top() < num) {
				mapping[sta.top()] = num;
				sta.pop();
			}
			sta.push(num);
		}
		for (int i = 0; i < res.size(); i++) {
			res[i] = mapping.find(findNums[i]) == mapping.end() ? -1 : mapping[findNums[i]];
		}
		return res;
	}
};
/*

498. Diagonal Traverse (Medium)

Given a matrix of M x N elements (M rows, N columns), return all elements of the matrix in diagonal order as shown in the below image.

Example:
Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output:  [1,2,4,7,5,3,6,8,9]
Explanation:

Note:
The total number of elements of the given matrix will not exceed 10,000.

*/
class Solution {
public:
	vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
		if (matrix.empty()) {
			return{};
		}
		vector<int> res;
		int m = matrix.size(), n = matrix[0].size();
		int i = 0, j = 0;
		bool up = true;
		while (i < m && j < n) {
			res.push_back(matrix[i][j]);
			if (up) {
				if (j == n - 1) {
					i++;
					up = false;
				}
				else if (i == 0) {
					j++;
					up = false;
				}
				else {
					i--;
					j++;
				}
			}
			else {
				if (i == m - 1) {
					j++;
					up = true;
				}
				else if (j == 0) {
					i++;
					up = true;
				}
				else {
					i++;
					j--;
				}
			}
		}
		return res;
	}
};
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

501. Find Mode in Binary Search Tree (Easy)

Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
For example:
Given BST [1,null,2,2],
   1
	\
	 2
	/
   2
return [2].

Note: If a tree has more than one mode, you can return them in any order.

Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).

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
	vector<int> findMode(TreeNode* root) {
		unordered_map<int, int> mapping;
		vector<int> res;
		int modevalue = findMode(root, mapping);
		for (auto i = mapping.begin(); i != mapping.end(); i++) {
			if (i->second == modevalue) {
				res.push_back(i->first);
			}
		}
		return res;
	}
private:
	int findMode(TreeNode* root, unordered_map<int, int>& mapping) {
		if (root == NULL) {
			return 0;
		}
		mapping[root->val]++;
		int l = findMode(root->left, mapping), r = findMode(root->right, mapping);
		return max(mapping[root->val], max(l, r));
	}
};
/*

504. Base 7 (Easy)

Given an integer, return its base 7 string representation.

Example 1:
Input: 100
Output: "202"
Example 2:
Input: -7
Output: "-10"
Note: The input will be in range of [-1e7, 1e7].

*/
class Solution {
public:
	string convertToBase7(int num) {
		if (num == 0) {
			return "0";
		}
		string res = "";
		bool sign = num < 0;
		num = abs(num);
		while (num != 0) {
			res += num % 7 + '0';
			num /= 7;
		}
		reverse(res.begin(), res.end());
		return sign ? "-" + res : res;
	}
};
/*

506. Relative Ranks (Easy)

Given scores of N athletes, find their relative ranks and the people with the top three highest scores, who will be awarded medals: "Gold Medal", "Silver Medal" and "Bronze Medal".

Example 1:
Input: [5, 4, 3, 2, 1]
Output: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]
Explanation: The first three athletes got the top three highest scores, so they got "Gold Medal", "Silver Medal" and "Bronze Medal".
For the left two athletes, you just need to output their relative ranks according to their scores.
Note:
N is a positive integer and won't exceed 10,000.
All the scores of athletes are guaranteed to be unique.

*/
class Comp {
public:
	bool operator()(pair<int, int> p1, pair<int, int> p2) {
		return p1.first > p2.first;
	}
}comp;
class Solution {
public:
	vector<string> findRelativeRanks(vector<int>& nums) {
		vector<string> res(nums.size());
		vector<pair<int, int>> v;
		for (int i = 0; i < nums.size(); i++) {
			v.push_back(make_pair(nums[i], i));
		}
		sort(v.begin(), v.end(), comp);
		for (int i = 0; i < v.size(); i++) {
			if (i == 0) {
				res[v[0].second] = "Gold Medal";
			}
			else if (i == 1) {
				res[v[1].second] = "Silver Medal";
			}
			else if (i == 2) {
				res[v[2].second] = "Bronze Medal";
			}
			else {
				res[v[i].second] = to_string(i + 1);
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
/*

520. Detect Capital (Easy)

Given a word, you need to judge whether the usage of capitals in it is right or not.

We define the usage of capitals in a word to be right when one of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital if it has more than one letter, like "Google".
Otherwise, we define that this word doesn't use capitals in a right way.
Example 1:
Input: "USA"
Output: True
Example 2:
Input: "FlaG"
Output: False
Note: The input will be a non-empty word consisting of uppercase and lowercase latin letters.

*/
class Solution {
public:
	bool detectCapitalUse(string word) {
		int num = 0;
		for (char cha : word) {
			if (isupper(cha)) {
				num++;
			}
		}
		return num == 0 || num == word.size() || num == 1 && isupper(word[0]);
	}
};
/*

530. Minimum Absolute Difference in BST (Easy)

Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

Example:

Input:

   1
	\
	 3
	/
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
Note: There are at least two nodes in this BST.

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
	int getMinimumDifference(TreeNode* root) {
		TreeNode* pre = NULL;
		int res = INT_MAX;
		getMinimumDifference(root, res, pre);
		return res;
	}
private:
	void getMinimumDifference(TreeNode* root, int& res, TreeNode*& pre) {
		if (root == NULL) {
			return;
		}
		getMinimumDifference(root->left, res, pre);
		if (pre != NULL) {
			res = min(res, root->val - pre->val);
		}
		pre = root;
		getMinimumDifference(root->right, res, pre);
	}
};