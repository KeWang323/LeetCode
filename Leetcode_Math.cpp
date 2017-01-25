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

263. Ugly Number (Easy)

Write a program to check whether a given number is an ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.

Note that 1 is typically treated as an ugly number.

*/
class Solution {
public:
	bool isUgly(int num) {
		if (num == 0) {
			return false;
		}
		else if (num == 1) {
			return true;
		}
		else if (num % 2 == 0) {
			return isUgly(num / 2);
		}
		else if (num % 3 == 0) {
			return isUgly(num / 3);
		}
		else if (num % 5 == 0) {
			return isUgly(num / 5);
		}
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
		for (int i = 1; i < d - n % d; i++) num /= 10;
		return num % 10;
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