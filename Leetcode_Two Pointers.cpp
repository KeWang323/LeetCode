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