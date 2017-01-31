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
		int l = 1, r = n;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			int g = guess(mid);
			if (g == 1) {
				l = mid + 1;
			}
			else if (g == -1) {
				r = mid - 1;
			}
			else {
				return mid;
			}
		}
		return -1;
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