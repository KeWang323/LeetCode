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

12. Integer to Roman (Medium)

Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.

*/
class Solution {
public:
	string intToRoman(int num) {
		string res;
		char* c[4][10] = {
			{ "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" },
			{ "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" },
			{ "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" },
			{ "", "M", "MM", "MMM" }
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

28. Implement strStr() (Easy)

Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

*/
class Solution {
public:
	int strStr(string haystack, string needle) {
		if (haystack.size() < needle.size()) {
			return -1;
		}
		for (int i = 0; i <= haystack.size() - needle.size(); i++) {
			if (haystack.substr(i, needle.size()) == needle) {
				return i;
			}
		}
		return -1;
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
				glo = max(glo, ++cur);
			}
			else {
				cur = 0;
			}
		}
		return glo;
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