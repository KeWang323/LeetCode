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