/*

220. Contains Duplicate III (Medium)

Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.

*/
class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		if (nums.size() < 2) return false;
		vector<pair<long, int>> withIndex;
		for (int i = 0; i < nums.size(); i++)
			withIndex.emplace_back(nums[i], i);
		sort(withIndex.begin(), withIndex.end(), [](const pair<long, int>& a, const pair<long, int>&b) { return a.first < b.first; });
		for (int i = 0; i < nums.size(); i++) {
			int j = i + 1;
			while (j < nums.size()) {
				if (withIndex[j].first - withIndex[i].first > t) break;
				if (abs(withIndex[j].second - withIndex[i].second) <= k) return true;
				j++;
			}
		}
		return false;
	}
};