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
class Comp {
public:
	bool operator()(Interval in1, Interval in2) {
		return in1.start < in2.start;
	}
}comp;
class Solution {
public:
	vector<Interval> merge(vector<Interval>& intervals) {
		if (intervals.empty()) {
			return{};
		}
		sort(intervals.begin(), intervals.end(), comp);
		vector<Interval> res = { intervals[0] };
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

147. Insertion Sort List (Medium)

Sort a linked list using insertion sort.

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
	ListNode* insertionSortList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *head_new = new ListNode(-1);
		head_new->next = head;
		while (head->next != NULL) {
			ListNode *post = head->next;
			if (post->val < head->val) {
				head->next = post->next;
				ListNode *prev = head_new;
				ListNode *p = head_new->next;
				while (p->val < post->val) {
					prev = prev->next;
					p = p->next;
				}
				prev->next = post;
				post->next = p;
			}
			else {
				head = head->next;
			}
		}
		return head_new->next;
	}
};
/*

148. Sort List (Medium)

Sort a linked list in O(n log n) time using constant space complexity.

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
	ListNode* sortList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *newhead = split(head);
		return sort_combine(sortList(head), sortList(newhead));
	}
private:
	ListNode* split(ListNode* head) {
		ListNode *s = head, *f = head;
		while (f->next != NULL && f->next->next != NULL) {
			s = s->next;
			f = f->next->next;
		}
		f = s->next;
		s->next = NULL;
		return f;
	}
	ListNode* sort_combine(ListNode* head, ListNode* s) {
		ListNode *head_new = new ListNode(-1), *p = head_new;
		while (head != NULL || s != NULL) {
			if (head == NULL || s != NULL && head->val > s->val) {
				p->next = s;
				s = s->next;
			}
			else {
				p->next = head;
				head = head->next;
			}
			p = p->next;
		}
		return head_new->next;
	}
};
/*

164. Maximum Gap (Hard)

Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Try to solve it in linear time/space.

Return 0 if the array contains less than 2 elements.

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.

*/
class Solution {
public:
	int maximumGap(vector<int>& nums) {
		if (nums.empty()) {
			return 0;
		}
		int minnum = nums[0], maxnum = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			minnum = min(minnum, nums[i]);
			maxnum = max(maxnum, nums[i]);
		}
		int gap = (int)ceil((double)(maxnum - minnum) / (nums.size() - 1));
		vector<int> bucketmin(nums.size() - 1, INT_MAX);
		vector<int> bucketmax(nums.size() - 1, INT_MIN);
		for (int num : nums) {
			if (num == minnum || num == maxnum) {
				continue;
			}
			int idx = (num - minnum) / gap;
			bucketmin[idx] = min(num, bucketmin[idx]);
			bucketmax[idx] = max(num, bucketmax[idx]);
		}
		int maxGap = INT_MIN, pre = minnum;
		for (int i = 0; i < nums.size() - 1; i++) {
			if (bucketmin[i] == INT_MAX && bucketmax[i] == INT_MIN) {
				continue;
			}
			maxGap = max(maxGap, bucketmin[i] - pre);
			pre = bucketmax[i];
		}
		maxGap = max(maxGap, maxnum - pre);
		return maxGap;
	}
};
/*

179. Largest Number (Medium)

Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.

*/
class Comp {
public:
	bool operator()(int i, int j) {
		return to_string(i) + to_string(j) > to_string(j) + to_string(i);
	}
}comp;
class Solution {
public:
	string largestNumber(vector<int>& nums) {
		if (nums.empty()) {
			return "";
		}
		sort(nums.begin(), nums.end(), comp);
		if (nums[0] == 0) {
			return "0";
		}
		string res;
		for (int num : nums) {
			res += to_string(num);
		}
		return res;
	}
};
/*

242. Valid Anagram (Easy)

Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?

*/
class Solution {
public:
	bool isAnagram(string s, string t) {
		if (s.size() != t.size()) {
			return false;
		}
		int a[256] = { 0 };
		for (char cha : s) {
			a[cha]++;
		}
		for (char cha : t) {
			if (a[cha] == 0) {
				return false;
			}
			a[cha]--;
		}
		return true;
	}
};
/*

252. Meeting Rooms (Easy)

Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return false.

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
class Comp {
public:
	bool operator()(Interval i1, Interval i2) {
		return i1.end < i2.end;
	}
} comp;
class Solution {
public:
	bool canAttendMeetings(vector<Interval>& intervals) {
		if (intervals.empty()) {
			return true;
		}
		sort(intervals.begin(), intervals.end(), comp);
		for (int i = 0; i < intervals.size() - 1; i++) {
			if (intervals[i].end > intervals[i + 1].start) {
				return false;
			}
		}
		return true;
	}
};
/*

274. H-Index (Medium)

Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.

Note: If there are several possible values for h, the maximum one is taken as the h-index.

Hint:

An easy approach is to sort the array first.
What are the possible values of h-index?
A faster approach is to use extra space.

*/
class Solution {
public:
	int hIndex(vector<int>& citations) {
		sort(citations.begin(), citations.end());
		int _size = citations.size();
		for (int i = 0; i < _size; i++) {
			if (citations[i] >= _size - i) {
				return _size - i;
			}
		}
		return 0;
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