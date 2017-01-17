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
		for (int i = start; i < nums.size(); i++) {
			res_sub.push_back(nums[i]);
			res.push_back(res_sub);
			generate(nums, i + 1, res, res_sub);
			res_sub.pop_back();
		}
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