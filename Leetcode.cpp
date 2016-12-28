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
			if (mapping.count(gap)) {
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
/*

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
		int carry = 0;
		ListNode *dummy = new ListNode(-1), *p = dummy;
		for (ListNode *pa = l1, *pb = l2; pa || pb; p = p->next) {
			int ai = pa != NULL ? pa->val : 0;
			int bi = pb != NULL ? pb->val : 0;
			carry = ai + bi + carry;
			p->next = new ListNode(carry % 10);
			carry /= 10;
			pa = pa != NULL ? pa->next : NULL;
			pb = pb != NULL ? pb->next : NULL;
		}
		if (carry) {
			p->next = new ListNode(carry);
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
		int start = 0, max_len = 0;
		vector<int> last_position(255, -1);
		for (int i = 0; i < s.size(); i++) {
			if (last_position[s[i]] >= start) {
				max_len = max(i - start, max_len);
				start = last_position[s[i]] + 1;
			}
			last_position[s[i]] = i;
		}
		return max((int)s.size() - start, max_len);
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
		double res;
		if (sum % 2) {
			res = findKth(nums1, nums2, 0, 0, sum / 2 + 1);
		}
		else {
			res = (findKth(nums1, nums2, 0, 0, sum / 2) + findKth(nums1, nums2, 0, 0, sum / 2 + 1)) / 2.0;
		}
		return res;
	}
private:
	double findKth(vector<int>& nums1, vector<int>& nums2, int s1, int s2, int k) {
		if (s1 >= nums1.size()) {
			return nums2[s2 + k - 1];
		}
		else if (s2 >= nums2.size()) {
			return nums1[s1 + k - 1];
		}
		if (k == 1) {
			return min(nums1[s1], nums2[s2]);
		}
		int mid1 = s1 + k / 2 - 1 >= nums1.size() ? INT_MAX : nums1[s1 + k / 2 - 1];
		int mid2 = s2 + k / 2 - 1 >= nums2.size() ? INT_MAX : nums2[s2 + k / 2 - 1];
		if (mid1 < mid2) {
			return findKth(nums1, nums2, s1 + k / 2, s2, k - k / 2);
		}
		else {
			return findKth(nums1, nums2, s1, s2 + k / 2, k - k / 2);
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
		string res;
		int _size = s.length(), l_max = 0, len_max = 0, l, r;
		for (int i = 0; i < _size && _size - i > len_max / 2;) {
			l = r = i;
			while (r < _size - 1 && s[r] == s[r + 1]) {
				r++;
			}
			i = r + 1;
			while (l > 0 && r < _size - 1 && s[l - 1] == s[r + 1]) {
				l--;
				r++;
			}
			if (r - l + 1 > len_max) {
				len_max = r - l + 1;
				l_max = l;
			}
		}
		return s.substr(l_max, len_max);
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
		if (numRows == 1) return s;
		string res;
		int delta1 = 2 * numRows - 2;
		for (int i = 0; i < numRows; i++) {
			int j = i, delta2 = delta1 - 2 * i;
			while (j < s.size()) {
				res += s[j];
				if (delta2 == 0 || delta2 == delta1) j += delta1;
				else {
					j += delta2;
					if (j >= s.size()) break;
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
		long long num_rev = 0;
		while (x) {
			num_rev = num_rev * 10 + x % 10;
			x /= 10;
		}
		if (num_rev < INT_MIN || num_rev > INT_MAX) {
			return 0;
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
		long long num = 0;
		int i = 0, sign = 1;
		for (; str[i] == ' '; i++) {
		}
		if (str[i] == '-' || str[i] == '+') sign = 1 - 2 * (str[i++] == '-');
		for (; i < str.length(); i++) {
			if (isdigit(str[i])) {
				num = num * 10 + (str[i] - '0');
				if (num > INT_MAX) {
					return sign > 0 ? INT_MAX : INT_MIN;
				}
			}
			else break;
		}
		return (int)num * sign;
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
		for (; x / len >= 10; len *= 10) {
		}
		while (x != 0) {
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

11. Container With Most Water (Medium)

Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container.

*/
class Solution {
public:
	int maxArea(vector<int>& height) {
		int water = 0, i = 0, j = height.size() - 1;
		while (i < j) {
			int h_min = min(height[i], height[j]);
			water = max(water, h_min * (j - i));
			while (height[j] <= h_min && i < j) {
				j--;
			}
			while (height[i] <= h_min && i < j) {
				i++;
			}
		}
		return water;
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
		int num = ChatoNum(s[0]);
		for (int i = 1; i < s.length(); i++) {
			if (ChatoNum(s[i]) > ChatoNum(s[i - 1])) {
				num += ChatoNum(s[i]) - 2 * ChatoNum(s[i - 1]);
			}
			else {
				num += ChatoNum(s[i]);
			}
		}
		return num;
	}
	int ChatoNum(char cha) {
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
		if (strs.empty()) return "";
		int len = strs[0].length();
		int i, j;
		for (i = 1; i < strs.size(); i++) {
			for (j = 0; j < len; j++) {
				if (strs[i - 1][j] != strs[i][j]) {
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
		vector<vector<int>> res;
		int _size = nums.size();
		if (_size < 3) {
			return res;
		}
		sort(nums.begin(), nums.end());
		for (int i = 0; i < _size - 2; i++) {
			if (i > 0 && nums[i - 1] == nums[i] || nums[i] + nums[_size - 1] + nums[_size - 2] < 0) {
				continue;
			}
			if (nums[i] + nums[i + 1] + nums[i + 2] > 0) {
				break;
			}
			int j = i + 1, k = _size - 1;
			while (j < k) {
				int _sum = nums[i] + nums[j] + nums[k];
				if (_sum == 0) {
					res.push_back(vector<int>{nums[i], nums[j], nums[k]});
					do {
						j++;
					} while (nums[j] == nums[j - 1] && j < k);
					do {
						k--;
					} while (nums[k] == nums[k + 1] && j < k);
				}
				else if (_sum > 0) {
					k--;
				}
				else {
					j++;
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
		if (nums.size() < 3) {
			return 0;
		}
		sort(nums.begin(), nums.end());
		int res = nums[0] + nums[1] + nums[2];
		for (int i = 0; i < nums.size() - 2; i++) {
			int j = i + 1, k = nums.size() - 1;
			while (j < k) {
				int _sum = nums[i] + nums[j] + nums[k];
				if (_sum == target) {
					return _sum;
				}
				else if (abs(_sum - target) < abs(res - target)) {
					res = _sum;
				}
				else if (_sum > target) {
					k--;
				}
				else {
					j++;
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
		vector<vector<int>> res;
		int _size = nums.size();
		if (_size < 4) {
			return res;
		}
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
						res.push_back(vector<int>{nums[i], nums[j], nums[k], nums[l]});
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
		if (head == NULL) {
			return head;
		}
		ListNode *p = head, *q = head, *q_prev = NULL;
		for (int i = 0; i < n - 1; i++) {
			p = p->next;
		}
		while (p->next != NULL) {
			p = p->next;
			q_prev = q;
			q = q->next;
		}
		if (!q_prev) {
			return head->next;
		}
		q_prev->next = q->next;
		return head;
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
		stack<char> str;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
				str.push(s[i]);
			}
			else {
				if (str.empty()) return false;
				if ((s[i] == ')' && str.top() != '(') || (s[i] == '}' && str.top() != '{') || (s[i] == ']' && str.top() != '[')) return false;
				str.pop();
			}
		}
		return str.empty();
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
		ListNode* dummy = new ListNode(-1);
		for (ListNode* p = dummy; l1 != NULL || l2 != NULL; p = p->next) {
			if (l1 == NULL || l2 != NULL && l2->val < l1->val) {
				p->next = l2;
				l2 = l2->next;
			}
			else {
				p->next = l1;
				l1 = l1->next;
			}
		}
		return dummy->next;
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
	bool operator()(pair<ListNode*, int> p1, pair<ListNode*, int> p2) {
		return p1.first->val > p2.first->val;
	}
};
class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		priority_queue<pair<ListNode*, int>, vector<pair<ListNode*, int>>, Comp> pq;
		ListNode *dummy = new ListNode(-1);
		ListNode *cur = dummy;
		for (int i = 0; i < lists.size();i++) {
			if (lists[i] != NULL) {
				pq.push(make_pair(lists[i], i));
			}
		}
		while (!pq.empty()) {
			pair<ListNode*, int> p = pq.top();
			pq.pop();
			cur->next = p.first;
			cur = cur->next;
			lists[p.second] = lists[p.second]->next;
			if (lists[p.second] != NULL) {
				pq.push(make_pair(lists[p.second], p.second));
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
		ListNode* temp = head->next;
		head->next = swapPairs(temp->next);
		temp->next = head;
		return temp;
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
		while (index < k) {
			node = node->next;
			if (node == NULL) {
				return head;
			}
			index++;
		}
		ListNode *next = head->next;
		head->next = reverseKGroup(node->next, k);
		index = 1;
		while (index < k) {
			ListNode *post = next->next;
			next->next = head;
			head = next;
			next = post;
			index++;
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
class Solution {
public:
	int removeElement(vector<int>& nums, int val) {
		return distance(nums.begin(), remove(nums.begin(), nums.end(), val));
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
		if (!dividend) {
			return 0;
		}
		if (!divisor || dividend == INT_MIN && divisor == -1) {
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
		for (string str : words) {
			mapping[str]++;
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
					while (mapping[str] < mapping2[str]) {
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
		int i = nums.size() - 1, j = i;
		for (; i > 0; i--) {
			if (nums[i] > nums[i - 1]) {
				break;
			}
		}
		if (i == 0) {
			sort(nums.begin(), nums.end());
			return;
		}
		for (; j > i; j--) {
			if (nums[j] > nums[i - 1]) {
				break;
			}

		}
		swap(nums[i - 1], nums[j]);
		sort(nums.begin() + i, nums.end());
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
		for (int i = 0; i < s.length(); ++i) {
			if (s[i] == '(') {
				sta.push(i);
			}
			else if (s[i] == ')' && !sta.empty()) {
				t[i] = true;
				t[sta.top()] = true;
				sta.pop();
			}
		}
		int max_len = 0, cur_len = 0;
		for (int i = 0; i < s.size(); i++) {
			if (t[i] == true) {
				cur_len++;
			}
			else {
				cur_len = 0;
			}
			max_len = max(max_len, cur_len);
		}
		return max_len;
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
		int l = 0, r = nums.size() - 1;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			if (nums[mid] == target) {
				return mid;
			}
			else if (nums[l] <= nums[mid]) {
				if (nums[l] <= target && target < nums[mid]) {
					r = mid - 1;
				}
				else {
					l = mid + 1;
				}
			}
			else {
				if (nums[mid] < target && target <= nums[r]) {
					l = mid + 1;
				}
				else {
					r = mid - 1;
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
		vector<int> res(2, -1);
		while (l <= r) {
			int mid = l + (r - l) / 2;
			if (nums[mid] < target) {
				l = mid + 1;
			}
			else if (target < nums[mid]) {
				r = mid - 1;
			}
			else {
				while (nums[l] != target) {
					l++;
				}
				while (nums[r] != target) {
					r--;
				}
				res[0] = l;
				res[1] = r;
				return res;
			}
		}
		return res;
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
		for (int i = 0; i < 9; i++) {
			unordered_map<char, bool> mapping1;
			unordered_map<char, bool> mapping2;
			unordered_map<char, bool> mapping3;
			for (int j = 0; j < 9; j++) {
				if (board[i][j] != '.') {
					if (mapping1[board[i][j]] == true) {
						return false;
					}
					else {
						mapping1[board[i][j]] = true;
					}
				}
				if (board[j][i] != '.') {
					if (mapping2[board[j][i]] == true) {
						return false;
					}
					else {
						mapping2[board[j][i]] = true;
					}
				}
				if (board[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3] != '.') {
					if (mapping3[board[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3]] == true) {
						return false;
					}
					else {
						mapping3[board[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3]] = true;
					}
				}
			}
		}
		return true;
	}
};
class Solution {
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		int mapping1[9][9] = { 0 };
		int mapping2[9][9] = { 0 };
		int mapping3[9][9] = { 0 };
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (board[i][j] != '.') {
					int num = board[i][j] - '0' - 1, k = i / 3 * 3 + j / 3;
					if (mapping1[i][num] || mapping2[j][num] || mapping3[k][num]) {
						return false;
					}
					mapping1[i][num] = mapping2[j][num] = mapping3[k][num] = 1;
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
		string res = "";
		if (n == 1) res = "1";
		if (n - 1) {
			string str = countAndSay(n - 1) + "*";
			int cnt = 1;
			for (int i = 0; i < str.length() - 1; i++) {
				if (str[i] == str[i + 1]) cnt++;
				else {
					res.push_back(cnt + '0');
					res.push_back(str[i]);
					cnt = 1;
				}
			}
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

42. Trapping Rain Water (Hard)

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.


The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!

*/
class Solution {
public:
	int trap(vector<int>& height) {
		if (height.size() < 3) {
			return 0;
		}
		int res = 0, i = 0, j = height.size() - 1;
		while (i < j - 1) {
			int bar = min(height[i], height[j]);
			for (int k = i + 1; k < j; k++) {
				if (height[k] < bar) {
					res += bar - height[k];
					height[k] = bar;
				}
			}
			while (height[i] == bar) {
				i++;
			}
			while (height[j] == bar) {
				j--;
			}
		}
		return res;
	}
};
/*

43. Multiply Strings (Medium)

Given two numbers represented as strings, return multiplication of the numbers as a string.

Note:
The numbers can be arbitrarily large and are non-negative.
Converting the input string to integer is NOT allowed.
You should NOT use internal library such as BigInteger.

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
		while (j <= i) {
			for (int k = 0; k <= j; k++) {
				if (s1 >= k && s2 >= (j - k)) {
					carry += (num1[s1 - k] - '0') * (num2[s2 - (j - k)] - '0');
				}
			}
			res = char(carry % 10 + '0') + res;
			carry /= 10;
			j++;
		}
		while (carry) {
			res = char(carry % 10 + '0') + res;
			carry /= 10;
		}
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
		for (int i = 0; i < (n + 2) / 2; i++) {
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
		vector<vector<string>> res;
		vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107 };
		unordered_map<long, int> mapping;
		int pos = 0;
		for (auto s : strs) {
			long temp = 1;
			if (s != "") {
				for (auto cha : s) {
					temp *= primes[cha - 'a'];
				}
			}
			else {
				temp = 107;
			}
			if (mapping.find(temp) == mapping.end()) {
				mapping[temp] = pos++;
				res.push_back(vector<string>{s});
			}
			else {
				res[mapping[temp]].push_back(s);
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
			return 1;
		}
		if (n < 0) {
			if (n == INT_MIN) {
				return 1 / x * myPow(x, n + 1);
			}
			x = 1 / x;
			n = -n;
		}
		double temp = myPow(x, n / 2);
		return n % 2 ? x * temp * temp : temp * temp;
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
		int _sum = INT_MIN, prev = 0;
		for (int i = 0; i < nums.size(); i++) {
			prev = max(prev + nums[i], nums[i]);
			_sum = max(_sum, prev);
		}
		return _sum;
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
		vector<int> res;
		if (matrix.empty()) {
			return res;
		}
		int m = matrix.size() - 1, n = matrix[0].size() - 1, h = 0, l = 0;
		while (true) {
			for (int col = l; col <= n; col++) {
				res.push_back(matrix[h][col]);
			}
			if (++h > m) {
				break;
			}
			for (int row = h; row <= m; row++) {
				res.push_back(matrix[row][n]);
			}
			if (--n < l) {
				break;
			}
			for (int col = n; col >= l; col--) {
				res.push_back(matrix[m][col]);
			}
			if (--m < h) {
				break;
			}
			for (int row = m; row >= h; row--) {
				res.push_back(matrix[row][l]);
			}
			if (++l > n) {
				break;
			}
		}
		return res;
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
			if (steps <= nums[i]) steps = nums[i];
			if (steps >= _size - 1 - i) return true;
			if (--steps < 0) return false;
		}
		return false;
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
class Solution {
public:
	vector<Interval> merge(vector<Interval>& intervals) {
		if (intervals.empty()) {
			return{};
		}
		sort(intervals.begin(), intervals.end(), [](Interval a, Interval b) {return a.start < b.start;});
		vector<Interval> res;
		res.push_back(intervals[0]);
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
		bool flag = false;
		for (Interval inter : intervals) {
			if (flag) {
				res.push_back(inter);
			}
			else {
				if (newInterval.end < inter.start) {
					res.push_back(newInterval);
					flag = true;
					res.push_back(inter);
				}
				else if (inter.end < newInterval.start) {
					res.push_back(inter);
				}
				else {
					newInterval.start = min(newInterval.start, inter.start);
					newInterval.end = max(newInterval.end, inter.end);
				}
			}
		}
		if (!flag) {
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
		int len = s.length() - 1, res = 0;
		while (len > -1) {
			if (s[len] != ' ') res++;
			else if (res) return res;
			len--;
		}
		return res;
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
		if (n < 1) {
			return{};
		}
		vector<vector<int>> res(n, vector<int>(n));
		int i = n - 1, j = n - 1, k = 1, h = 0, l = 0;
		while (k <= n * n) {
			for (int col = l; col <= j; col++) {
				res[h][col] = k++;
			}
			if (++h > i) {
				break;
			}
			for (int row = h; row <= i; row++) {
				res[row][j] = k++;
			}
			if (--j < l) {
				break;
			}
			for (int col = j; col >= l; col--) {
				res[i][col] = k++;
			}
			if (--i < h) {
				break;
			}
			for (int row = i; row >= h; row--) {
				res[row][l] = k++;
			}
			if (++l > j) {
				break;
			}
		}
		return res;
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
		int i, j, f = 1;
		string s(n, '0');
		for (i = 1;i <= n;i++) {
			f *= i;
			s[i - 1] += i;
		}
		for (i = 0, k--; i < n; i++) {
			f /= n - i;
			j = i + k / f;
			char c = s[j];
			for (;j > i;j--) {
				s[j] = s[j - 1];
			}
			k %= f;
			s[i] = c;
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
		int len = 1;
		ListNode *p = head, *q = head;
		while (p->next != NULL) {
			p = p->next;
			len++;
		}
		k %= len;
		p = head;
		for (int i = 0; i < k; i++) {
			p = p->next;
		}
		while (p->next != NULL) {
			p = p->next;
			q = q->next;
		}
		p->next = head;
		ListNode *newh = q->next;
		q->next = NULL;
		return newh;
	}
};
class Solution {
public:
	ListNode* rotateRight(ListNode* head, int k) {
		if (!head) {
			return head;
		}
		int len = 1;
		ListNode *p = head;
		while (p->next != NULL) {
			len++;
			p = p->next;
		}
		p->next = head;
		k %= len;
		for (int i = 0; i < len - k; i++, p = p->next) {
		}
		ListNode *head_new = p->next;
		p->next = NULL;
		return head_new;
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
		if (m == 0 || n == 0) {
			return 0;
		}
		vector<int> res(n, 1);
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				res[j] = res[j - 1] + res[j];
			}
		}
		return res[n - 1];
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
		if (obstacleGrid.empty()) {
			return 0;
		}
		int _size = obstacleGrid[0].size();
		vector<int> res(_size, 0);
		res[0] = 1;
		for (int i = 0; i < obstacleGrid.size(); i++) {
			for (int j = 0; j < _size; j++) {
				if (obstacleGrid[i][j] == 1) {
					res[j] = 0;
				}
				else if (j > 0) {
					res[j] = res[j - 1] + res[j];
				}
			}
		}
		return res[_size - 1];
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
		int _size = grid[0].size();
		vector<int> res(_size, INT_MAX);
		res[0] = 0;
		for (int i = 0; i < grid.size(); i++) {
			res[0] += grid[i][0];
			for (int j = 1; j < _size; j++) {
				res[j] = min(res[j - 1], res[j]) + grid[i][j];
			}
		}
		return res[_size - 1];
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
		int flag = 1;
		for (int i = 0; i < digits.size(); i++) {
			digits[i] += flag;
			flag = digits[i] / 10;
			digits[i] %= 10;
		}
		if (flag) {
			digits.push_back(1);
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
		int i = a.size(), j = b.size(), carry = 0;
		string res;
		while (i > 0 || j > 0 || carry > 0) {
			int num1 = i > 0 ? a[(i--) - 1] - '0' : 0, num2 = j > 0 ? b[(j--) - 1] - '0' : 0;
			carry += num1 + num2;
			res = char(carry % 2 + '0') + res;
			carry /= 2;
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
		if (n < 4) return n;
		int i = 4, prev1 = 2, prev2 = 3;
		while (i <= n) {
			int temp = prev2;
			prev2 += prev1;
			prev1 = temp;
			i++;
		}
		return prev2;
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
			if (token == "." || token == "") continue;
			else if (token == "..") {
				if (!pos.empty())  pos.pop_back();
			}
			else pos.push_back(token);
		}
		if (pos.empty()) return "/";
		for (string i : pos)
			res = res + '/' + i;
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
		int row = word1.size(), col = word2.size();
		vector<vector<int>> t(row + 1, vector<int>(col + 1, 0));
		for (int i = 0; i < row + 1; i++) {
			for (int j = 0; j < col + 1; j++) {
				if (i == 0) {
					t[i][j] = j;
				}
				else if (j == 0) {
					t[i][j] = i;
				}
				else if (word1[i - 1] == word2[j - 1]) {
					t[i][j] = t[i - 1][j - 1];
				}
				else {
					t[i][j] = min(min(t[i - 1][j - 1], t[i][j - 1]), t[i - 1][j]) + 1;
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
				if (matrix[i][0] == 0 || matrix[0][j] == 0) {
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
				swap(nums[k], nums[j--]);
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
		unordered_map<char, int> mapping;
		for (char cha : t) {
			mapping[cha]++;
		}
		int i = 0, len = s.size() + 1;
		int slow = 0, fast = 0, cnt = mapping.size();
		while (fast < s.size()) {
			if (mapping.find(s[fast]) != mapping.end()) {
				if (--mapping[s[fast]] == 0) {
					cnt--;
				}
				while (cnt == 0 && (mapping.find(s[slow]) == mapping.end() || mapping[s[slow]] < 0)) {
					slow++;
					if (mapping.find(s[slow - 1]) != mapping.end()) {
						mapping[s[slow - 1]]++;
					}
				}
			}
			if (cnt == 0) {
				if (len > fast - slow) {
					i = slow;
					len = fast - slow + 1;
				}
			}
			fast++;
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
			if (search(board, w + 1, i + 1, j) || search(board, w + 1, i - 1, j) || search(board, w + 1, i, j - 1) || search(board, w + 1, i, j + 1))
				return true;
			board[i][j] = t;
		}
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

Write a function to determine if a given target is in the array.

*/
class Solution {
public:
	bool search(vector<int>& nums, int target) {
		int l = 0, r = nums.size() - 1;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			if (nums[mid] == target) return true;
			else if (nums[l] < nums[mid]) {
				if (nums[l] <= target && target < nums[mid]) r = mid - 1;
				else l = mid + 1;
			}
			else if (nums[l] > nums[mid]) {
				if (nums[mid] < target && target <= nums[r]) l = mid + 1;
				else r = mid - 1;
			}
			else l++;
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
		ListNode *dummy = new ListNode(-1);
		dummy->next = head;
		ListNode *p = dummy;
		while (head != NULL) {
			ListNode *post = head->next;
			if (post != NULL && post->val == head->val) {
				while (post != NULL && post->val == head->val) {
					post = post->next;
				}
				head = post;
				p->next = head;
			}
			else {
				p = head;
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
 * Definition for singly-linked list.`
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (head != NULL || head->next != NULL) {
			return head;
		}
		ListNode *p = head;
		while (p != NULL && p->next != NULL) {
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
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *s = new ListNode(-1), *g = new ListNode(-1);
		ListNode *p = s, *q = g;
		while (head != NULL) {
			if (head->val < x) {
				p->next = head;
				p = p->next;
			}
			else {
				q->next = head;
				q = q->next;
			}
			head = head->next;
		}
		p->next = g->next;
		q->next = NULL;
		return s->next;
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
		int i = m - 1, j = n - 1, k = m + n - 1;
		while (j >= 0) {
			if (i >= 0 && nums1[i] > nums2[j]) {
				nums1[k--] = nums1[i--];
			}
			else {
				nums1[k--] = nums2[j--];
			}
		}
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
		if (s.empty() || s[0] == '0') return 0;
		int _size = s.length();
		int t1 = 1, t2 = 1;
		for (int i = 2; i <= _size; i++) {
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
		vector<int> table(n + 1, 0);
		table[0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++)
				table[i] += table[j - 1] * table[i - j];
		}
		return table[n];
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
		TreeNode* prev = NULL;
		return validate(root, prev);
	}
private:
	bool validate(TreeNode* root, TreeNode* &prev) {
		if (root == NULL) {
			return true;
		}
		else if (!validate(root->left, prev)) {
			return false;
		}
		else if (prev != NULL && prev->val >= root->val) {
			return false;
		}
		prev = root;
		return validate(root->right, prev);
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
		if (!p || !q) {
			if (p || q) return false;
			return true;
		}
		return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
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
		if (!root) return true;
		return check(root->left, root->right);
	}
	bool check(TreeNode* L, TreeNode* R) {
		if (!L || !R) {
			if (L || R) return false;
			return true;
		}
		return L->val == R->val && check(L->left, R->right) && check(L->right, R->left);
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
		vector<vector<int>> res;
		if (!root) return res;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			vector<int> lev;
			int _size = q.size();
			for (int i = 0; i < _size; i++) {
				TreeNode *temp = q.front();
				q.pop();
				lev.push_back(temp->val);
				if (temp->left) q.push(temp->left);
				if (temp->right) q.push(temp->right);
			}
			res.push_back(lev);
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
		vector<vector<int>> res;
		if (!root) return res;
		queue<TreeNode*> q;
		q.push(root);
		int level = 0;
		while (!q.empty()) {
			vector<int> lev;
			int _size = q.size();
			for (int i = 0; i < _size; i++) {
				TreeNode *temp = q.front();
				q.pop();
				lev.push_back(temp->val);
				if (temp->left) q.push(temp->left);
				if (temp->right) q.push(temp->right);
			}
			if (level % 2) reverse(lev.begin(), lev.end());
			res.push_back(lev);
			level++;
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
		if (!root) return 0;
		int res = 0;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			int _size = q.size();
			res++;
			for (int i = 0; i < _size; i++) {
				TreeNode *temp = q.front();
				q.pop();
				if (temp->left) q.push(temp->left);
				if (temp->right) q.push(temp->right);
			}
		}
		return res;
	}
};
class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (!root) return 0;
		else if (!(root->left) && !(root->right)) return 1;
		int depth_L = maxDepth(root->left);
		int depth_R = maxDepth(root->right);
		return depth_L > depth_R ? depth_L + 1 : depth_R + 1;
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
		return BT(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
	}
	TreeNode* BT(vector<int>& preorder, int pl, int pr, vector<int>& inorder, int il, int ir) {
		if (il > ir) {
			return NULL;
		}
		int val = preorder[pl];
		TreeNode *root = new TreeNode(val);
		int i = il;
		for (; i < ir; i++) {
			if (val == inorder[i]) {
				break;
			}
		}
		root->left = BT(preorder, pl + 1, pl + i - il, inorder, il, i - 1);
		root->right = BT(preorder, pl + i - il + 1, pr, inorder, i + 1, ir);
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
		int val = postorder[pr];
		TreeNode *root = new TreeNode(val);
		int i = il;
		for (; i < ir; i++) {
			if (val == inorder[i]) {
				break;
			}
		}
		root->left = BT(inorder, il, i - 1, postorder, pl, pl - il + i - 1);
		root->right = BT(inorder, i + 1, ir, postorder, pl - il + i, pr - 1);
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
		vector<vector<int>> res;
		if (!root) return res;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			vector<int> lev;
			int _size = q.size();
			for (int i = 0; i < _size; i++) {
				TreeNode *temp = q.front();
				q.pop();
				lev.push_back(temp->val);
				if (temp->left) q.push(temp->left);
				if (temp->right) q.push(temp->right);
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
	TreeNode* sortedArrayToBST(vector<int>& nums, int l, int r) {
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
		if (!root) return true;
		else if (abs(depth(root->left) - depth(root->right)) > 1) return false;
		else return isBalanced(root->left) && isBalanced(root->right);
	}
	int depth(TreeNode* root) {
		if (!root) return 0;
		else if (!(root->left) && !(root->right)) return 1;
		int depth_L = depth(root->left);
		int depth_R = depth(root->right);
		return depth_L > depth_R ? depth_L + 1 : depth_R + 1;
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
		if (!root) return 0;
		else if (!root->left && !root->right) return 1;
		else {
			int depth_L, depth_R;
			if (root->left) depth_L = minDepth(root->left);
			else depth_L = INT_MAX;
			if (root->right) depth_R = minDepth(root->right);
			else depth_R = INT_MAX;
			return min(depth_L, depth_R) + 1;
		}
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
		else if (root->left == NULL && root->right == NULL && sum == root->val) {
			res_sub.push_back(root->val);
			res.push_back(res_sub);
			res_sub.pop_back();
			return;
		}
		if (root->left != NULL) {
			res_sub.push_back(root->val);
			pathSum(root->left, res, res_sub, sum - root->val);
			res_sub.pop_back();
		}
		if (root->right != NULL) {
			res_sub.push_back(root->val);
			pathSum(root->right, res, res_sub, sum - root->val);
			res_sub.pop_back();
		}

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
	void flatten(TreeNode *root) {
		while (root) {
			if (root->left && root->right) {
				TreeNode* t = root->left;
				while (t->right) {
					t = t->right;
				}
				t->right = root->right;
			}
			if (root->left) {
				root->right = root->left;
			}
			root->left = NULL;
			root = root->right;
		}
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
		vector<vector<int>> vec;
		if (numRows <= 0) {
			return vec;
		}
		vec.push_back(vector<int>(1, 1));
		for (int i = 1; i < numRows; i++) {
			vector<int> res(1, 1);
			for (int j = 0, k = 1; k < vec[i - 1].size(); j++, k++) {
				res.push_back(vec[i - 1][j] + vec[i - 1][k]);
			}
			res.push_back(1);
			vec.push_back(res);
		}
		return vec;
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
		vector<int> res(1, 1);
		if (rowIndex == 0) {
			return res;
		}
		for (int i = 1; i <= rowIndex; i++) {
			vector<int> tmp = res;
			res.clear();
			res.push_back(1);
			for (int i = 0; i < tmp.size() - 1; i++) {
				res.push_back(tmp[i] + tmp[i + 1]);
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
		vector<int> res = triangle.back();
		for (int i = triangle.size() - 2; i >= 0; i--) {
			for (int j = 0; j < triangle[i].size(); j++) {
				res[j] = min(res[j], res[j + 1]) + triangle[i][j];
			}
		}
		return res[0];
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
		if (!prices.size()) {
			return 0;
		}
		int pro, low = prices[0];
		for (int i = 0; i < prices.size(); i++) {
			if (low > prices[i]) {
				low = prices[i];
			}
			else {
				pro = max(prices[i] - low, pro);
			}
		}
		return pro;
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
			res += max(prices[i] - prices[i - 1], 0);
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
		vector<int> pro(prices.size());
		pro[0] = 0;
		int buy = prices[0];
		for (int i = 1; i < prices.size(); i++) {
			pro[i] = max(pro[i - 1], prices[i] - buy);
			buy = min(buy, prices[i]);
		}
		int sell = prices.back(), best = 0;
		for (int i = prices.size() - 2; i >= 0; i--) {
			best = max(best, sell - prices[i] + pro[i]);
			sell = max(sell, prices[i]);
		}
		return best;
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
	int maxPathSum(TreeNode* root, int& max) {
		if (root == NULL) {
			return 0;
		}
		int l = maxPathSum(root->left, max), r = maxPathSum(root->right, max);
		l = l < 0 ? 0 : l;
		r = r < 0 ? 0 : r;
		max = max > l + r + root->val ? max : l + r + root->val;
		return l > r ? l + root->val : r + root->val;
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
		int left = 0, right = s.length() - 1;
		while (left < right) {
			while (!isalnum(s[left]) && left < right)
				left++;
			while (!isalnum(s[right]) && left < right)
				right--;
			if (tolower(s[left++]) != tolower(s[right--]))
				return false;
		}
		return true;
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
		vector<int> nums;
		int num = 0;
		sumNumber(root, nums, num);
		num = 0;
		for (int i : nums) {
			num += i;
		}
		return num;
	}
private:
	void sumNumber(TreeNode* root, vector<int>& nums, int& num) {
		if (root == NULL) {
			nums.push_back(0);
			return;
		}
		num = 10 * num + root->val;
		if (root->left == NULL && root->right == NULL) {
			nums.push_back(num);
			num /= 10;
			return;
		}
		if (root->left != NULL) {
			sumNumber(root->left, nums, num);
		}
		if (root->right != NULL) {
			sumNumber(root->right, nums, num);
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
				if (s[i] == s[j] && (j - i < 2 || t[i + 1][j - 1])) {
					t[i][j] = true;
					t2[j + 1] = min(t2[j + 1], 1 + t2[i]);
				}
			}
		}
		return t2.back();
	}
};
class Solution {
public:
	int minCut(string s) {
		int _size = s.size();
		vector<int> t(_size + 1);
		for (int i = 0; i <= _size; i++) {
			t[i] = i - 1;
		}
		for (int i = 1; i < _size; i++) {
			for (int j = 0; i - j >= 0 && i + j < _size && s[i - j] == s[i + j]; j++) {
				t[i + j + 1] = min(t[i + j + 1], 1 + t[i - j]);
			}
			for (int j = 0; i - j - 1 >= 0 && i + j < _size && s[i - j - 1] == s[i + j]; j++) {
				t[i + j + 1] = min(t[i + j + 1], 1 + t[i - j - 1]);
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
		UndirectedGraphNode *newhead = new UndirectedGraphNode(node->label);
		mapping[node->label] = newhead;
		queue<UndirectedGraphNode*> q;
		q.push(node);
		while (!q.empty()) {
			UndirectedGraphNode *node1 = q.front();
			q.pop();
			for (UndirectedGraphNode* nei : node1->neighbors) {
				if (mapping.find(nei->label) == mapping.end()) {
					mapping[nei->label] = new UndirectedGraphNode(nei->label);
					q.push(nei);
				}
				mapping[node1->label]->neighbors.push_back(mapping[nei->label]);
			}
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
		int a = 0, b = 0;
		for (int c : nums) {
			int ta = (~a&b&c) | (a&~b&~c);
			b = (~a&~b&c) | (~a&b&~c);
			a = ta;
		}
		return a | b;
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
		RandomListNode *newhead = new RandomListNode(head->label);
		RandomListNode *cur = newhead;
		unordered_map<RandomListNode*, RandomListNode*> mapping;
		mapping[head] = newhead;
		while (head != NULL) {
			if (head->next != NULL) {
				if (mapping.find(head->next) == mapping.end()) {
					RandomListNode *next = new RandomListNode(head->next->label);
					mapping[head->next] = next;
				}
				cur->next = mapping[head->next];
			}
			if (head->random != NULL) {
				if (mapping.find(head->random) == mapping.end()) {
					RandomListNode *random = new RandomListNode(head->random->label);
					mapping[head->random] = random;
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
	bool wordBreak(string s, unordered_set<string>& wordDict) {
		vector<bool> t(s.size() + 1, false);
		t[0] = true;
		for (int i = 1; i <= s.size(); i++) {
			for (int j = i - 1; j >= 0; j--) {
				if (t[j]) {
					if (wordDict.find(s.substr(j, i - j)) != wordDict.end()) {
						t[i] = true;
						break;
					}
				}
			}
		}
		return t.back();
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
		if (head == NULL) {
			return false;
		}
		ListNode *s = head, *f = head;
		while (f->next != NULL && f->next->next != NULL) {
			s = s->next;
			f = f->next->next;
			if (s == f) {
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
			if (s == f) break;
		}
		if (s != f) return NULL;
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
			s = s->next;
			f = f->next->next;
		}
		ListNode *newhead = reverse(s->next);
		s->next = NULL;
		s = head;
		while (newhead != NULL) {
			ListNode *newheadpos = newhead->next;
			newhead->next = s->next;
			s->next = newhead;
			s = s->next->next;
			newhead = newheadpos;
		}
	}
private:
	ListNode* reverse(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *newhead = reverse(head->next);
		head->next->next = head;
		head->next = NULL;
		return newhead;
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
		stack<TreeNode*> s;
		TreeNode *pre = NULL;
		s.push(root);
		while (!s.empty()) {
			TreeNode *cur = s.top();
			if (pre == NULL || pre->left == cur || pre->right == cur) {
				if (cur->left != NULL) {
					s.push(cur->left);
				}
				else if (cur->right != NULL) {
					s.push(cur->right);
				}
				else {
					res.push_back(cur->val);
					s.pop();
				}
			}
			else if (pre == cur->left) {
				if (cur->right != NULL) {
					s.push(cur->right);
				}
				else {
					res.push_back(cur->val);
					s.pop();
				}
			}
			else {
				res.push_back(cur->val);
				s.pop();
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
	KeyValue *next;
	KeyValue(int key, int value) {
		next = NULL;
		this->key = key;
		this->value = value;
	}
	KeyValue() {
		this->next = NULL;
		this->key = 0;
		this->value = 0;
	}
};
class LRUCache {
public:
	unordered_map<int, KeyValue*> mapping;
	KeyValue *head, *tail;
	int capacity, size;
	LRUCache(int capacity) {
		this->head = new KeyValue(0, 0);
		this->tail = head;
		this->capacity = capacity;
		this->size = 0;
		mapping.clear();
	}

	int get(int key) {
		if (mapping.find(key) == mapping.end()) {
			return -1;
		}
		moveToTail(mapping[key]);
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
	void moveToTail(KeyValue *prev) {
		if (prev->next == tail) {
			return;
		}
		KeyValue *node = prev->next;
		prev->next = node->next;
		if (node->next != NULL) {
			mapping[node->next->key] = prev;
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
		ListNode *head_new = new ListNode(-1);
		head_new->next = head;
		while (head->next != NULL) {
			ListNode *post = head->next;
			if (post->val < head->val) {
				head->next = post->next;
				ListNode *prev = head_new;
				ListNode *p = head_new->next;
				while (p->val < post->val) {
					prev = prev->next;
					p = p->next;
				}
				prev->next = post;
				post->next = p;
			}
			else {
				head = head->next;
			}
		}
		return head_new->next;
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
		stack<int> s;
		for (auto t : tokens) {
			if (t == "+" || t == "-" || t == "*" || t == "/") {
				int num2 = s.top();
				s.pop();
				int num1 = s.top();
				s.pop();
				if (t == "+") s.push(num1 + num2);
				if (t == "-") s.push(num1 - num2);
				if (t == "*") s.push(num1 * num2);
				if (t == "/") s.push(num1 / num2);
			}
			else s.push(stoi(t));
		}
		return s.top();
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
		while (ss >> temp) s = temp + ' ' + s;
		return;
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
		int cur_max = nums[0], cur_min = nums[0], maxProduct = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			int prev_min = cur_min, prev_max = cur_max;
			cur_max = max(nums[i], max(prev_max * nums[i], prev_min * nums[i]));
			cur_min = min(nums[i], min(prev_max * nums[i], prev_min * nums[i]));
			maxProduct = max(cur_max, maxProduct);
		}
		return maxProduct;
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
		int left = 0, right = nums.size() - 1;
		while (left < right) {
			int mid = (left + right) / 2;
			if (nums[mid] < nums[right]) right = mid;
			else left = mid + 1;
		}
		return nums[left];
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
	stack<int> s, min;
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		s.push(x);
		if (min.empty() || x <= min.top()) {
			min.push(x);
		}
	}

	void pop() {
		if (s.top() == min.top()) {
			min.pop();
		}
		s.pop();
	}

	int top() {
		return s.top();
	}

	int getMin() {
		return min.top();
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
		ListNode *headA1 = headA, *headB1 = headB;
		int flag1 = 0, flag2 = 0;
		while (flag1 + flag2 <= 2) {
			if (headA1->val != headB1->val) {
				if (!headA1->next) {
					headA1 = headB;
					flag1++;
				}
				else {
					headA1 = headA1->next;
				}
				if (!headB1->next) {
					headB1 = headA;
					flag2++;
				}
				else {
					headB1 = headB1->next;
				}
			}
			else {
				return headA1;
			}
		}
		return NULL;
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
		vector<int> ver1 = split(version1, '.');
		vector<int> ver2 = split(version2, '.');
		int size_min = min(ver1.size(), ver2.size()), index = 0;
		for (index; index < size_min; index++) {
			if (ver1[index] > ver2[index])
				return 1;
			if (ver1[index] < ver2[index])
				return -1;
		}
		if (ver1.size() > ver2.size()) {
			while (!ver1[index] && index < ver1.size())
				index++;
			if (index < ver1.size())
				return 1;
		}
		if (ver1.size() < ver2.size()) {
			while (!ver2[index] && index < ver2.size())
				index++;
			if (index < ver2.size())
				return -1;
		}
		return 0;
	}
	vector<int> split(string s, char sign) {
		vector<int> res;
		stringstream str(s);
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
		if (!numerator) {
			return "0";
		}
		string res;
		if (numerator < 0 ^ denominator < 0) {
			res += "-";
		}
		long n_l_abs = labs(long(numerator)), d_l_abs = labs(long(denominator));
		res += to_string(n_l_abs / d_l_abs);
		if (!(n_l_abs %= d_l_abs)) {
			return res;
		}
		res += ".";
		unordered_map<int, int> mapping;
		int i = res.size() - 1;
		while (n_l_abs) {
			if (mapping.count(n_l_abs)) {
				res.insert(mapping[n_l_abs], "(");
				res += ")";
				return res;
			}
			mapping[n_l_abs] = ++i;
			res += to_string((n_l_abs *= 10) / d_l_abs);
			n_l_abs %= d_l_abs;
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
		if (numbers.size() < 2) {
			return{ -1, -1 };
		}
		for (int i = 0; i < numbers.size() - 1; i++) {
			if (numbers[i] + numbers[i + 1] > target) {
				break;
			}
			int l = i + 1, r = numbers.size() - 1;
			while (l <= r) {
				int mid = l + (r - l) / 2;
				if (numbers[mid] > target - numbers[i]) {
					r = mid - 1;
				}
				else if (numbers[mid] < target - numbers[i]) {
					l = mid + 1;
				}
				else {
					return{ i + 1, mid + 1 };
				}
			}
		}
		return{ -1, -1 };
	}
};
class Solution {
public:
	vector<int> twoSum(vector<int>& numbers, int target) {
		if (numbers.size() < 2) {
			return{ -1, -1 };
		}
		int l = 0, r = numbers.size() - 1;
		while (l < r) {
			if (numbers[l] + numbers[r] > target) {
				r--;
			}
			else if (numbers[l] + numbers[r] < target) {
				l++;
			}
			else {
				return{ ++l, ++r };
			}
		}
		return{ -1, -1 };
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
		string res = "";
		while (n) {
			res = char((n - 1) % 26 + 'A') + res;
			n = (n - 1) / 26;
		}
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
		if (nums.size() == 1) {
			return nums[0];
		}
		int cnt = 0, majority;
		for (int i = 0; i < nums.size(); i++) {
			if (cnt == 0) {
				majority = nums[i];
				cnt++;
			}
			else {
				majority == nums[i] ? cnt++ : cnt--;
				if (cnt > nums.size() / 2) {
					return majority;
				}
			}
		}
		return majority;
	}
};
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
		for (int i = 0; i < s.length(); i++) {
			res = res * 26 + (s[i] - '@');
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
	stack<int> s;
	void traversal(TreeNode* root, stack<int>& s) {
		if (root) {
			traversal(root->right, s);
			s.push(root->val);
			traversal(root->left, s);
		}
	}
public:
	BSTIterator(TreeNode *root) {
		traversal(root, s);
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !s.empty();
	}

	/** @return the next smallest number */
	int next() {
		int num = s.top();
		s.pop();
		return num;
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
class Solution {
public:
	string largestNumber(vector<int>& nums) {
		string res;
		sort(nums.begin(), nums.end(), comp);
		if (nums[0] == 0) return "0";
		for (int num : nums)
			res += to_string(num);
		return res;
	}
	static bool comp(int i, int j) {
		return to_string(i) + to_string(j) > to_string(j) + to_string(i);
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
		unordered_map<int, int> mapping;
		vector<string> res;
		for (int t = 0, i = 0; i < s.size(); i++) {
			if (mapping[t = t << 3 & 0x3FFFFFFF | s[i] & 7]++ == 1) {
				res.push_back(s.substr(i - 9, 10));
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
		int n = nums.size();
		if (n <= 1) {
			return;
		}
		k %= n;
		reverse(nums.begin(), nums.begin() + (n - k));
		reverse(nums.begin() + (n - k), nums.end());
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
		int index = 31;
		while (n > 0) {
			res |= (n & 0x1) << index;
			n >>= 1;
			index--;
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
		int res;
		while (n > 0) {
			res += n & 0x1;
			n = n >> 1;
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
		int n = nums.size();
		switch (n) {
		case 0: return 0; break;
		case 1: return nums[0]; break;
		}
		vector<int> res(n, 0);
		res[0] = nums[0];
		res[1] = max(nums[0], nums[1]);
		for (int i = 2; i < n; i++) {
			res[i] = max(nums[i] + res[i - 2], res[i - 1]);
		}
		return res[n - 1];
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
class Solution {
public:
	vector<int> rightSideView(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<int> res;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			int _size = q.size();
			for (int i = 0; i < _size; i++) {
				TreeNode* node = q.front();
				q.pop();
				if (node->left != NULL) {
					q.push(node->left);
				}
				if (node->right != NULL) {
					q.push(node->right);
				}
				if (i == _size - 1) {
					res.push_back(node->val);
				}
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
	int cal(int n) {
		int temp = 0;
		while (n) {
			temp += pwo(n % 10, 2);
			n /= 10;
		}
		return temp;
	}
	bool isHappy(int n) {
		unordered_map<int, bool> mapping;
		int sum = cal(n);
		while (sum != 1) {
			if (mapping[sum]) {
				return false;
			}
			else {
				mapping[sum] = true;
				sum = cal(sum);
			}
		}
		return true;
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
		ListNode *dummy = new ListNode(-1), *p = dummy;
		dummy->next = head;
		while (p != NULL) {
			if (p->next != NULL && p->next->val == val) {
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
		if (n <= 1) return 0;
		vector<int> prime(n, 0);
		int cnt = 0;
		for (int i = 2; i < n; i++) {
			if (prime[i] == 0) {
				cnt++;
				for (int j = 2; i * j < n; j++) {
					prime[i * j] = 1;
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
		if (s.length() == 0) {
			return true;
		}
		unordered_map<char, char> mapping;
		set<char> Set;
		for (int i = 0; i < s.length(); i++) {
			char s1 = s[i], t1 = t[i];
			if (mapping.find(s1) != mapping.end()) {
				if (mapping[s1] != t1) return false;
			}
			else {
				if (Set.count(t1) == 1) {
					return false;
				}
				else {
					mapping[s1] = t1;
					Set.insert(t1);
				}
			}
		}
		return true;
	}
};
class Solution {
public:
	bool isIsomorphic(string s, string t) {
		int cs[128] = { 0 }, ct[128] = { 0 };
		for (int i = 0; i < s.size(); i++) {
			if (cs[s[i]] != ct[t[i]]) {
				return false;
			}
			else if (!cs[s[i]]) {
				cs[s[i]] = i + 1;
				ct[t[i]] = i + 1;
			}
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
		ListNode *p = head, *prev = NULL;
		while (head != NULL) {
			ListNode *post = head->next;
			head->next = prev;
			prev = head;
			head = post;
		}
		return prev;
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
		int l = 0, r = 0, _sum = 0, _size = nums.size(), len_min = _size + 1;
		while (r < _size) {
			while (r < _size && _sum < s) {
				_sum += nums[r++];
			}
			while (_sum >= s) {
				_sum -= nums[l++];
			}
			len_min = min(len_min, r - l + 1);
		}
		return len_min > _size ? 0 : len_min;
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
		int _size = nums.size();
		if (_size < 2) return _size ? nums[0] : 0;
		return max(robber(nums, 0, _size - 2), robber(nums, 1, _size - 1));
	}
	int robber(vector<int>& nums, int l, int r) {
		int pre = 0, cur = 0;
		for (int i = l; i <= r; i++) {
			int temp = max(pre + nums[i], cur);
			pre = cur;
			cur = temp;
		}
		return cur;
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
class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		sort(nums.begin(), nums.end(), greater<int>());
		return nums[k - 1];
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
		unordered_map<int, bool> mapping;
		for (int i : nums) {
			if (mapping[i]) {
				return true;
			}
			mapping[i] = true;
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
		for (int i = 0; i < nums.size(); ++i) {
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
		if (nums.size() < 2) return false;
		vector<pair<long, int>> withIndex;
		for (int i = 0; i < nums.size(); i++)
			withIndex.emplace_back(nums[i], i);
		sort(withIndex.begin(), withIndex.end(), [](const pair<long, int>& a, const pair<long, int>&b) { return a.first < b.first; });
		for (int i = 0; i < nums.size(); i++) {
			int j = i + 1;
			while (j < nums.size()) {
				if (withIndex[j].first - withIndex[i].first > t) break;
				if (abs(withIndex[j].second - withIndex[i].second) <= k) return true;
				j++;
			}
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
		int row = matrix.size(), col = matrix[0].size();
		vector<vector<int>> t(row, vector<int>(col, 0));
		int cur = 0;
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				if (i == 0 || j == 0) {
					t[i][j] = matrix[i][j] - '0';
				}
				else if (matrix[i][j] == '1') {
					t[i][j] = min(min(t[i - 1][j - 1], t[i][j - 1]), t[i - 1][j]) + 1;
				}
				cur = max(cur, t[i][j]);
			}
		}
		return cur * cur;
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
		int are = (C - A) * (D - B) + (G - E) * (H - F);
		if (E >= C || G <= A || F >= D || H <= B) {
			return are;
		}
		else {
			are -= (min(C, G) - max(A, E)) * (min(D, H) - max(B, F));
		}
		return are;
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
		if (!root || !(root->left) && !(root->right))
			return root;
		else {
			swap(root->left, root->right);
			invertTree(root->left);
			invertTree(root->right);
		}
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
		vector<string> res;
		int lower = 0;
		nums.push_back(INT_MAX);
		for (int i = 1; i < nums.size(); i++) {
			if (nums[i] > nums[i - 1] + 1) {
				res.push_back(subrange(nums[lower], nums[i - 1]));
				lower = i;
			}
		}
		return res;
	}
	string subrange(int lower, int higher) {
		return lower == higher ? to_string(lower) : to_string(lower) + "->" + to_string(higher);
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
		vector<int> res;
		int res1, res2, num1 = 0, num2 = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (res1 == nums[i]) {
				num1++;
			}
			else if (res2 == nums[i]) {
				num2++;
			}
			else if (num1 == 0) {
				res1 = nums[i];
				num1++;
			}
			else if (num2 == 0) {
				res2 = nums[i];
				num2++;
			}
			else {
				num1--;
				num2--;
			}
		}
		num1 = 0;
		num2 = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (res1 == nums[i]) {
				num1++;
			}
			else if (res2 == nums[i]) {
				num2++;
			}
		}
		if (num1 > nums.size() / 3) res.push_back(res1);
		if (num2 > nums.size() / 3) res.push_back(res2);
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
		while (!s2.empty()) {
			s1.push(s2.top());
			s2.pop();
		}
		s1.push(x);
		while (!s1.empty()) {
			s2.push(s1.top());
			s1.pop();
		}
	}

	// Removes the element from in front of queue.
	void pop(void) {
		s2.pop();
	}

	// Get the front element.
	int peek(void) {
		return s2.top();
	}

	// Return whether the queue is empty.
	bool empty(void) {
		return s2.empty();
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
		ListNode *mid = head, *last = head;
		while (last->next && last->next->next) {
			mid = mid->next;
			last = last->next->next;
		}
		mid->next = reverse(mid->next);
		mid = mid->next;
		while (mid != NULL) {
			if (mid->val != head->val) {
				return false;
			}
			mid = mid->next;
			head = head->next;
		}
		return true;
	}
private:
	ListNode* reverse(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *p = head, *prev = NULL;
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
		if (min(p->val, q->val) < root->val && max(p->val, q->val) > root->val)
			return root;
		else if (root->val < min(p->val, q->val))
			return lowestCommonAncestor(root->right, p, q);
		else if (root->val > max(p->val, q->val))
			return lowestCommonAncestor(root->left, p, q);
		else
			return root;
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
		else if (l != NULL) {
			return l;
		}
		else if (r != NULL) {
			return r;
		}
		return NULL;
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
		int _size = nums.size(), temp = 1;
		vector<int> res(_size);
		res[0] = 1;
		for (int i = 1; i < _size; i++) {
			res[i] = res[i - 1] * nums[i - 1];
		}
		for (int i = _size - 2; i >= 0; i--) {
			res[i] *= (temp *= nums[i + 1]);
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
		int r = matrix.size() - 1, c = matrix[0].size() - 1;
		int i = 0, j = c;
		while (i <= r && j >= 0) {
			if (matrix[i][j] > target) j--;
			else if (matrix[i][j] < target) i++;
			else return true;
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
		if (s.empty() != t.empty() || s.length() != t.length()) {
			return false;
		}
		if (s.empty() && t.empty()) {
			return true;
		}
		unordered_map<char, int> mapping;
		for (auto cha : s) {
			mapping[cha] += 1;
		}
		for (auto cha : t) {
			if (mapping[cha] == 0) {
				return false;
			}
			else {
				mapping[cha]--;
			}
		}
		return true;
	}
};
class Solution {
public:
	bool isAnagram(string s, string t) {
		if (s.empty() != t.empty() || s.length() != t.length()) {
			return false;
		}
		if (s.empty() && t.empty()) {
			return true;
		}
		vector<int> cnt(26, 0);
		for (int i = 0; i < s.size(); i++) {
			cnt[s[i] - 'a']++;
		}
		for (int i = 0; i < t.size(); i++) {
			if (cnt[t[i] - 'a'] == 0) return false;
			cnt[t[i] - 'a']--;
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
		unordered_map <char, char> mapping = { {'0', '0'}, {'1', '1'}, { '6', '9'}, {'8', '8'}, {'9', '6'} };
		int i = 0, j = num.size() - 1;
		while (i <= j) {
			if (mapping[num[i]] != num[j]) {
				return false;
			}
			i++;
			j--;
		}
		return true;
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
		cout(root, res);
		return res;
	}
private:
	int cout(TreeNode* root, int& res) {
		if (root == NULL) {
			return 0;
		}
		else if (root->left == NULL && root->right == NULL) {
			res++;
			return 1;
		}
		int l = cout(root->left, res), r = cout(root->right, res);
		if (l == 1 && r == 1) {
			if (root->val == root->left->val && root->val == root->right->val) {
				res += 1;
				return 1;
			}
		}
		else if (l == -1 || r == -1) {
			return -1;
		}
		else if (l != 0 && root->val == root->left->val) {
			res += 1;
			return 1;
		}
		else if (r != 0 && root->val == root->right->val) {
			res += 1;
			return 1;
		}
		return -1;
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
		return num - (num - 1) / 9 * 9;
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

Note that 1 is typically treated as an ugly number.

Hint:

The naive approach is to call isUgly for every number until you reach the nth one. Most numbers are not ugly. Try to focus your effort on generating only the ugly ones.
An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly number.
The key is how to maintain the order of the ugly numbers. Try a similar approach of merging from three sorted lists: L1, L2, and L3.
Assume you have Uk, the kth ugly number. Then Uk+1 must be Min(L1 * 2, L2 * 3, L3 * 5).

*/
class Solution {
public:
	int nthUglyNumber(int n) {
		if (!n) return 0;
		static vector<int> table(1, 1);
		static int i2 = 0, i3 = 0, i5 = 0;
		int k(table.size());
		for (; k < n; k++) {
			int tmp = min(table[i2] * 2, min(table[i3] * 3, table[i5] * 5));
			if (!(tmp % 2)) i2++;
			if (!(tmp % 3)) i3++;
			if (!(tmp % 5)) i5++;
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
		int _sum = nums.size() * (nums.size() + 1) / 2;
		for (int i : nums) {
			_sum -= i;
		}
		return _sum;
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
		sort(citations.begin(), citations.end());
		int _size = citations.size();
		for (int i = 0; i < _size; i++) {
			if (citations[i] >= _size - i) {
				return _size - i;
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
		int left = 1, right = n;
		while (left != right) {
			int mid = left / 2 + right / 2;
			if (isBadVersion(mid))
				right = mid;
			else
				left = mid + 1;
		}
		return left;
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
		if (n <= 0) return 0;
		static vector<int> table{ (0) };
		while (table.size() <= n) {
			int _size = table.size();
			int temp = INT_MAX;
			for (int i = 1; i * i <= _size; i++)
				temp = min(temp, table[_size - i * i] + 1);
			table.push_back(temp);
		}
		return table[n];
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
		if (nums.size() % 2) {
			wiggleSort(nums, 0, nums.size() - 2);
		}
		else {
			wiggleSort(nums, 0, nums.size() - 1);
		}
	}
private:
	void wiggleSort(vector<int>& nums, int l, int r) {
		if (l < r - 1) {
			int _size = r - l + 1, i = l + _size / 4, mid = l + _size / 2, j = l + 3 * _size / 4;
			reverse(nums.begin() + i, nums.begin() + mid);
			reverse(nums.begin() + mid, nums.begin() + j);
			reverse(nums.begin() + i, nums.begin() + j);
			wiggleSort(nums, l, l + 2 * (i - l) - 1);
			wiggleSort(nums, l + 2 * (i - l), r);
		}
	}
};
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
		for (int i = 0, j = 0; i < nums.size(); i++) {
			if (nums[i]) {
				swap(nums[i], nums[j++]);
			}
		}
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
		if (s.empty()) {
			return{};
		}
		vector<string> res;
		for (int i = 0; i < s.size() - 1; i++) {
			if (s[i] == '+' && s[i + 1] == '+') {
				s[i] = '-';
				s[i + 1] = '-';
				res.push_back(s);
				s[i] = '+';
				s[i + 1] = '+';
			}
		}
		return res;
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

add(1)
add(2)
findMedian() -> 1.5
add(3)
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
		if (root->val == tar) {
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
		vector<int> res;
		for (int i : nums) {
			auto it = lower_bound(res.begin(), res.end(), i);
			if (it == res.end()) res.push_back(i);
			else *it = i;
		}
		return res.size();
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
	vector<int> table;
	NumArray(vector<int> &nums) {
		int sum = 0;
		for (int i : nums) {
			sum += i;
			table.push_back(sum);
		}
	}

	int sumRange(int i, int j) {
		if (!i) return table[j];
		return table[j] - table[i - 1];
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

319. Bulb Switcher (Easy)

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
		vector<int> table(amount + 1, INT_MAX - 1);
		table[0] = 0;
		for (int i = 0; i < coins.size(); i++) {
			for (int j = coins[i]; j <= amount; j++) {
				table[j] = min(table[j], table[j - coins[i]] + 1);
			}
		}
		return (table[amount] == INT_MAX - 1 ? -1 : table[amount]);
	}
};
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		sort(coins.begin(), coins.end());
		return coinChange(coins, amount, coins.size() - 1, 0, *(new int(INT_MAX)));
	}
	int coinChange(vector<int>&coins, int amount, int idx, int cur, int &cand) {
		if (!amount) return cand = cur;
		if (idx < 0)return -1;
		int flag = 0, n = amount / coins[idx];
		if (n + cur >= cand) return -1;
		for (int i = n; i >= 0; i--)
			if (coinChange(coins, amount - i*coins[idx], idx - 1, cur + i, cand) != -1) flag = 1;
		if (flag) return cand;
		return -1;
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
		if (n <= 0)
			return false;
		if (n == 1)
			return true;
		if (n % 3 == 0)
			return isPowerOfThree(n / 3);
		return false;
	}
};
class Solution {
public:
	bool isPowerOfThree(int n) {
		if (n > 0)
			return 1162261467 % n == 0;
		else
			return false;
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
		ListNode *o = head, *eh = head->next, *e = head->next;
		while (o->next && e->next) {
			o->next = e->next;
			o = e->next;
			e->next = o->next;
			e = o->next;
		}
		o->next = eh;
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
	vector<int> largestBSTSubtree(TreeNode* root, int& res) {
		if (root == NULL) {
			return{ 0,0,0 };
		}
		else if (root->left == NULL && root->right == NULL) {
			res = max(res, 1);
			return{ 1, root->val, root->val };
		}
		vector<int> l = largestBSTSubtree(root->left, res), r = largestBSTSubtree(root->right, res);
		if (l[0] != -1 && r[0] != -1) {
			if ((l[0] == 0 || root->val > l[2]) && (r[0] == 0 || root->val < r[1])) {
				res = max(res, l[0] + r[0] + 1);
				int small = l[1] == 0 ? root->val : l[1], large = r[2] == 0 ? root->val : r[2];
				return{ l[0] + r[0] + 1, small, large };
			}
		}
		return{ -1,0,0 };
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
		vector<int> table(num + 1);
		for (int i = 1; i <= num; i++)
			table[i] = 1 + table[i & (i - 1)];
		return table;
	}
};
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
		return num > 0 && !(num & (num - 1)) && (num & 0x55555555) == num;
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
		reverse(s.begin(), s.end());
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
		string vowels = "aeiouAEIOU";
		int left = 0, right = s.length() - 1;
		while (left < right) {
			while (vowels.find(s[left]) == -1 && left < right) {
				left++;
			}
			while (vowels.find(s[right]) == -1 && left < right) {
				right--;
			}
			swap(s[right--], s[left++]);
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
		vector<int> result;
		if (nums1.empty() || nums2.empty()) return result;
		unordered_map<int, bool> mapping;
		for (auto i : nums1) {
			mapping[i] = true;
		}
		for (auto i : nums2) {
			if (mapping[i]) {
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
		vector<int> result;
		if (nums1.empty() || nums2.empty()) return result;
		unordered_map<int, int> mapping;
		for (auto val : nums1) {
			mapping[val]++;
		}
		for (auto val : nums2) {
			if (mapping[val]-- > 0) {
				result.push_back(val);
			}
		}
		return result;
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

	int findLeaves(TreeNode* root, vector<vector<int>>& res) {
		if (root == NULL) {
			return 0;
		}
		int value = root->val, height = max(findLeaves(root->left, res), findLeaves(root->right, res)) + 1;
		if (height > res.size()) {
			vector<int> res_sub;
			res_sub.push_back(value);
			res.push_back(res_sub);
		}
		else {
			res[height - 1].push_back(value);
		}
		return height;
	}
};
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
		if (root == NULL) {
			return{};
		}
		vector<vector<int>> res;
		while (root->right != NULL || root->left != NULL) {
			vector<int> res_sub = helper(root);
			res.push_back(res_sub);
		}
		res.push_back({ root->val });
		return res;
	}
private:
	vector<int> helper(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<int> res_sub, l, r;
		if (root->left != NULL && root->left->left == NULL && root->left->right == NULL) {
			res_sub.push_back(root->left->val);
			root->left = NULL;
		}
		else {
			l = helper(root->left);
		}
		if (root->right != NULL && root->right->left == NULL && root->right->right == NULL) {
			res_sub.push_back(root->right->val);
			root->right = NULL;
		}
		else {
			r = helper(root->right);
		}
		for (int i : l) {
			res_sub.push_back(i);
		}
		for (int i : r) {
			res_sub.push_back(i);
		}
		return res_sub;
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
			int mid = (l + r) / 2;
			if (mid * mid == num) return true;
			else if (mid > num / mid) r = mid;
			else l = mid;
		}
		if ((l * l == num) || (r * r == num))  return true;
		return false;
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

Given a non-negative number represented as a singly linked list of digits, plus one to the number.

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
		if (head == NULL) {
			return head;
		}
		ListNode *newhead = reverse(head);
		int carry = 1;
		for (ListNode *p = newhead; p != NULL && carry != 0; p = p->next) {
			int value = p->val + carry;
			p->val = value % 10;
			carry = value / 10;
		}
		head = reverse(newhead);
		if (carry > 0) {
			ListNode *p = new ListNode(1);
			p->next = head;
			return p;
		}
		return head;
	}
private:
	ListNode* reverse(ListNode* head) {
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
		while (b) {
			int x = a ^ b, y = (a & b) << 1;
			a = x; b = y;
		}
		return a;
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
		vector<int> table(target + 1);
		table[0] = 1;
		for (int i = 1; i <= target; i++) {
			for (int j : nums) {
				if (i - j >= 0) table[i] += table[i - j];
			}
		}
		return table.back();
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
		int r = matrix.size() - 1, min = matrix[0][0], max = matrix[r][r];
		while (min < max) {
			int cnt = 0, mid = (min + max) / 2;
			for (int i = 0; i <= r && matrix[i][0] <= mid; i++)
				cnt += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
			k <= cnt ? max = mid : min = mid + 1;
		}
		return min;
	}
};
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
		for (auto cha_r : ransomNote) {
			auto cha_m = magazine.find(cha_r);
			if (cha_m == string::npos) return false;
			magazine.erase(cha_m, 1);
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
			swap(shuffled[i], shuffled[index + i]);
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
		for (int i = 0;i < s.size();i++) {
			t[s[i] - 'a']++;
		}
		for (int i = 0;i < s.size();i++) {
			if (t[s[i] - 'a'] == 1) {
				return i;
			}
		}
		return -1;
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
class Solution {
public:
	char findTheDifference(string s, string t) {
		unordered_map<char, int> mapping;
		for (char c : s) {
			mapping[c] += 1;
		}
		for (char c : t) {
			mapping[c] -= 1;
			if (mapping[c] == -1) {
				return c;
			}
		}
		return ' ';
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
			temp += i * A[i];
		}
		res = temp;
		for (int i = 1; i < A.size(); i++) {
			temp = sum - A.size() * A[A.size() - i] + temp;
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
			//...?0 even
			if (!(m & 1)) m >>= 1;
			//...11
			else if (m & 2) m++;
			//...01
			else m--;
			res++;
		}
		return res + m - 1;
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
		int d = 1, base = 1;
		while ((long long)9 * base * d - n < 0) {
			n -= 9 * base * d++;
			base *= 10;
		}
		int num = --n / d + base;
		for (int i = 1; i < d - n % d; i++) {
			num /= 10;
		}
		return num % 10;
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
		int res = 0;
		sumOfLeftLeaves(root, NULL, res);
		return res;
	}
private:
	void sumOfLeftLeaves(TreeNode* root, TreeNode* pre, int& res) {
		if (root == NULL) {
			return;
		}
		else if (pre == NULL) {
			sumOfLeftLeaves(root->left, root, res);
			sumOfLeftLeaves(root->right, root, res);
		}
		else if (root->left == NULL && root->right == NULL && pre->left == root) {
			res += root->val;
			return;
		}
		else {
			sumOfLeftLeaves(root->left, root, res);
			sumOfLeftLeaves(root->right, root, res);
		}

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
		int cnt = 0;
		string res;
		while (num != 0 && cnt < 8) {
			int temp = num & 15;
			if (temp < 10) {
				res += temp + '0';
			}
			else {
				res += temp - 10 + 'a';
			}
			num = num >> 4;
			cnt++;
		}
		reverse(res.begin(), res.end());
		return res;
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
		int table[58] = { 0 };
		int res = 0;
		bool flag = false;
		for (char cha : s) {
			table[cha - 'A']++;
		}
		for (auto i : table) {
			res += i / 2 * 2;
			if (i % 2 == 1) {
				flag = true;
			}
		}
		return flag == true ? res + 1 : res;
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
		set<int> s;
		for (int i = 0; i < nums.size(); ++i) {
			s.insert(nums[i]);
			if (s.size() > 3) {
				s.erase(s.begin());
			}
		}
		if (s.size() < 3) {
			return *(--s.end());
		}
		return *s.begin();
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
		int i = num1.length() - 1, j = num2.length() - 1;
		long carry = 0;
		while (i >= 0 || j >= 0 || carry > 0) {
			if (i >= 0) {
				carry = (num1[i--] - '0') + carry;
			}
			if (j >= 0) {
				carry = (num2[j--] - '0') + carry;
			}
			res += to_string(carry % 10);
			carry /= 10;
		}
		reverse(res.begin(), res.end());
		return res;
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
		return pathSum(root, 0, sum, mapping);
	}
private:
	int pathSum(TreeNode* root, int sum, const int& target, unordered_map<int, int>& mapping) {
		if (root == NULL) {
			return 0;
		}
		sum += root->val;
		int res = mapping.find(sum - target) != mapping.end() ? mapping[sum - target] : 0;
		mapping[sum]++;
		res += pathSum(root->left, sum, target, mapping) + pathSum(root->right, sum, target, mapping);
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
		if (s.length() < p.length()) {
			return{};
		}
		vector<int> res;
		int mapping[26] = { 0 };
		for (char cha : p) {
			mapping[cha - 'a']++;
		}
		int cnt = p.size(), i = 0, j = 0;
		while (j < s.length()) {
			if (j - i == p.length() && mapping[s[i++] - 'a']++ >= 0) {
				cnt++;
			}
			if (--mapping[s[j++] - 'a'] >= 0) {
				cnt--;
			}
			if (cnt == 0) {
				res.push_back(i);
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
		if (n == 0) {
			return 0;
		}
		int l = 1, r = n;
		while (l < r) {
			long mid = l + (r - l + 1) / 2;
			if (mid * (mid + 1) / 2.0 <= n) {
				l = mid;
			}
			else if (mid * (mid + 1) / 2 > n) {
				r = mid - 1;
			}
		}
		return r;
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
		else if (root->val > key) {
			root->left = deleteNode(root->left, key);
		}
		else if (root->val < key) {
			root->right = deleteNode(root->right, key);
		}
		else {
			if (root->right == NULL || root->left == NULL) {
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