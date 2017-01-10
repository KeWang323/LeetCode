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
		int l = 0, r = nums.size() - 1;
		while (l < r) {
			int mid = l + (r - l) / 2;
			if (nums[mid] < nums[r]) {
				r = mid;
			}
			else {
				l = mid + 1;
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
		for (int i = 0, j = 0; j < nums.size(); j++) {
			if (nums[j] != 0) {
				swap(nums[i++], nums[j]);
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