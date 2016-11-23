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
			while (r < _size - 1 && s[r] == s[r + 1]) r++;
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
		if (str[i] == '-' || str[i] == '+') {
			sign = 1 - 2 * (str[i++] == '-');
		}
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