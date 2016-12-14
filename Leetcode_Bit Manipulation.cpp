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