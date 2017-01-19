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