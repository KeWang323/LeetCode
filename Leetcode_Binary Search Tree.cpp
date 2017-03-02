/*

220. Contains Duplicate III (Medium)

Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.

*/
class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		if (k < 1 || t < 0) {
			return false;
		}
		unordered_map<long, long> mapping;
		for (int i = 0; i < nums.size(); i++) {
			long remappedNum = (long)nums[i] - INT_MIN, bucket = remappedNum / ((long)t + 1);
			if (mapping.count(bucket)
				|| mapping.count(bucket - 1) && remappedNum - mapping[bucket - 1] <= t
				|| mapping.count(bucket + 1) && mapping[bucket + 1] - remappedNum <= t) {
				return true;
			}
			if (mapping.size() >= k) {
				long lastBucket = ((long)nums[i - k] - INT_MIN) / ((long)t + 1);
				mapping.erase(lastBucket);
			}
			mapping[bucket] = remappedNum;
		}
		return false;
	}
};
/*

315. Count of Smaller Numbers After Self (Hard)

You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

Given nums = [5, 2, 6, 1]

To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Return the array [2, 1, 1, 0].

*/
class Solution {
public:
	vector<int> countSmaller(vector<int>& nums) {
		vector<int> index(nums.size()), count(nums.size(), 0);
		for (int i = 0; i < index.size(); i++) {
			index[i] = i;
		}
		mergesort(nums, index, 0, nums.size() - 1, count);
		return count;
	}
private:
	void mergesort(const vector<int>& nums, vector<int>& index, int l, int r, vector<int>& count) {
		if (r <= l) {
			return;
		}
		int mid = l + (r - l) / 2;
		mergesort(nums, index, l, mid, count);
		mergesort(nums, index, mid + 1, r, count);
		merge(nums, index, l, r, mid, count);
	}
	void merge(const vector<int>& nums, vector<int>& index, int l, int r, int mid, vector<int>& count) {
		int i = l, j = mid + 1, rightcount = 0, k = 0;
		vector<int> newindex(r - l + 1);
		while (i <= mid && j <= r) {
			if (nums[index[j]] < nums[index[i]]) {
				newindex[k++] = index[j++];
				rightcount++;
			}
			else {
				newindex[k++] = index[i];
				count[index[i++]] += rightcount;
			}
		}
		while (i <= mid) {
			newindex[k++] = index[i];
			count[index[i++]] += rightcount;
		}
		while (j <= r) {
			newindex[k++] = index[j++];
		}
		for (int i = l; i <= r; i++) {
			index[i] = newindex[i - l];
		}
	}
};
/*

530. Minimum Absolute Difference in BST (Easy)

Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

Example:

Input:

   1
	\
	 3
	/
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
Note: There are at least two nodes in this BST.

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
	int getMinimumDifference(TreeNode* root) {
		TreeNode* pre = NULL;
		int res = INT_MAX;
		getMinimumDifference(root, res, pre);
		return res;
	}
private:
	void getMinimumDifference(TreeNode* root, int& res, TreeNode*& pre) {
		if (root == NULL) {
			return;
		}
		getMinimumDifference(root->left, res, pre);
		if (pre != NULL) {
			res = min(res, root->val - pre->val);
		}
		pre = root;
		getMinimumDifference(root->right, res, pre);
	}
};