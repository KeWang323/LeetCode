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