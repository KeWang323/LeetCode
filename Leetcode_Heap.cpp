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

239. Sliding Window Maximum (Hard)

Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.

Follow up:
Could you solve it in linear time?

Hint:

How about using a data structure such as deque (double-ended queue)?
The queue size need not be the same as the window’s size.
Remove redundant elements and the queue should store only elements that need to be considered.

*/
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		deque<int> dq;
		vector<int> res;
		for (int i = 0; i < nums.size(); i++) {
			while (!dq.empty() && nums[dq.back()] <= nums[i]) {
				dq.pop_back();
			}
			while (!dq.empty() && i - dq.front() >= k) {
				dq.pop_front();
			}
			dq.push_back(i);
			if (i >= k - 1) {
				res.push_back(nums[dq.front()]);
			}
		}
		return res;
	}
};
/*

264. Ugly Number II (Medium)

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number, and n does not exceed 1690.

Hint:

The naive approach is to call isUgly for every number until you reach the nth one. Most numbers are not ugly. Try to focus your effort on generating only the ugly ones.
An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly number.
The key is how to maintain the order of the ugly numbers. Try a similar approach of merging from three sorted lists: L1, L2, and L3.
Assume you have Uk, the kth ugly number. Then Uk+1 must be Min(L1 * 2, L2 * 3, L3 * 5).

*/
class Solution {
public:
	int nthUglyNumber(int n) {
		if (n < 0) {
			return 0;
		}
		vector<int> table(1, 1);
		int i2 = 0, i3 = 0, i5 = 0;
		for (int k = 1; k < n; k++) {
			int tmp = min(table[i2] * 2, min(table[i3] * 3, table[i5] * 5));
			if (tmp % 2 == 0) {
				i2++;
			}
			if (tmp % 3 == 0) {
				i3++;
			}
			if (tmp % 5 == 0) {
				i5++;
			}
			table.push_back(tmp);
		}
		return table[n - 1];
	}
};
/*

295. Find Median from Data Stream (Hard)

Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

Examples:
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.
For example:

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2

*/
class min_h {
public:
	bool operator()(int num1, int num2) {
		return num1 > num2;
	}
};
class MedianFinder {
public:
	priority_queue<int, vector<int>, min_h> pr;
	priority_queue<int, vector<int>> pl;
	// Adds a number into the data structure.
	void addNum(int num) {
		if (pl.size() == pr.size()) {
			if (pl.empty() || num < pl.top()) {
				pl.push(num);
			}
			else {
				pr.push(num);
			}
		}
		else if (pl.size() < pr.size()) {
			pr.push(num);
			pl.push(pr.top());
			pr.pop();
		}
		else {
			pl.push(num);
			pr.push(pl.top());
			pl.pop();
		}
	}
	// Returns the median of current data stream
	double findMedian() {
		if (pr.size() == pl.size()) {
			if (pr.empty()) {
				return (double)0;
			}
			return (double)(pr.top() + pl.top()) / 2;
		}
		else if (pr.size() > pl.size()) {
			return (double)pr.top();
		}
		return (double)pl.top();
	}
};
// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();
/*

347. Top K Frequent Elements (Medium)

Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size

*/
class Comp {
public:
	bool operator()(pair<int, int> p1, pair<int, int> p2) {
		return p1.second > p2.second;
	}
};
class Solution {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> mapping;
		for (int num : nums) {
			mapping[num]++;
		}
		priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> pq;
		for (auto i = mapping.begin(); i != mapping.end(); i++) {
			pq.push(make_pair(i->first, i->second));
			if (pq.size() > k) {
				pq.pop();
			}
		}
		vector<int> res(k, 0);
		for (int i = k - 1; i >= 0; i--) {
			res[i] = pq.top().first;
			pq.pop();
		}
		return res;
	}
};
/*

355. Design Twitter (Medium)

Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:

postTweet(userId, tweetId): Compose a new tweet.
getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
follow(followerId, followeeId): Follower follows a followee.
unfollow(followerId, followeeId): Follower unfollows a followee.
Example:

Twitter twitter = new Twitter();

// User 1 posts a new tweet (id = 5).
twitter.postTweet(1, 5);

// User 1's news feed should return a list with 1 tweet id -> [5].
twitter.getNewsFeed(1);

// User 1 follows user 2.
twitter.follow(1, 2);

// User 2 posts a new tweet (id = 6).
twitter.postTweet(2, 6);

// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.getNewsFeed(1);

// User 1 unfollows user 2.
twitter.unfollow(1, 2);

// User 1's news feed should return a list with 1 tweet id -> [5],
// since user 1 is no longer following user 2.
twitter.getNewsFeed(1);

*/
class Twitter {
	struct Tweet
	{
		int time;
		int id;
		Tweet(int time, int id) : time(time), id(id) {}

	};
	unordered_map<int, vector<Tweet>> tweets;
	unordered_map<int, set<int>> following;
	int time;
public:
	/** Initialize your data structure here. */
	Twitter() : time(0) {}

	/** Compose a new tweet. */
	void postTweet(int userId, int tweetId) {
		tweets[userId].emplace_back(time++, tweetId);
	}

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
	vector<int> getNewsFeed(int userId) {
		vector<pair<Tweet*, Tweet*>> h;
		for (auto& u : following[userId]) {
			auto& t = tweets[u];
			if (t.size()) h.emplace_back(t.data(), t.data() + t.size() - 1);
		}
		auto& t = tweets[userId];
		if (t.size()) h.emplace_back(t.data(), t.data() + t.size() - 1);
		auto f = [](const pair<Tweet*, Tweet*>& x, const pair<Tweet*, Tweet*>& y) {
			return x.second->time < y.second->time;
		};
		make_heap(h.begin(), h.end(), f);

		const int n = 10;
		vector<int> o;
		o.reserve(n);
		for (int i = 0; i < n && !h.empty(); i++) {
			pop_heap(h.begin(), h.end(), f);
			auto& hb = h.back();
			o.push_back(hb.second->id);
			if (hb.first == hb.second--) h.pop_back();
			else push_heap(h.begin(), h.end(), f);
		}
		return o;
	}

	/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
	void follow(int followerId, int followeeId) {
		if (followerId != followeeId) following[followerId].insert(followeeId);
	}

	/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
	void unfollow(int followerId, int followeeId) {
		if (followerId != followeeId) following[followerId].erase(followeeId);
	}
};
/**
* Your Twitter object will be instantiated and called as such:
* Twitter obj = new Twitter();
* obj.postTweet(userId,tweetId);
* vector<int> param_2 = obj.getNewsFeed(userId);
* obj.follow(followerId,followeeId);
* obj.unfollow(followerId,followeeId);
*/
/*

373. Find K Pairs with Smallest Sums (Medium)

You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.

Define a pair (u,v) which consists of one element from the first array and one element from the second array.

Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:
Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3

Return: [1,2],[1,4],[1,6]

The first 3 pairs are returned from the sequence:
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
Example 2:
Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2

Return: [1,1],[1,1]

The first 2 pairs are returned from the sequence:
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
Example 3:
Given nums1 = [1,2], nums2 = [3],  k = 3

Return: [1,3],[2,3]

All possible pairs are returned from the sequence:
[1,3],[2,3]

*/
class Comp {
public:
	bool operator()(pair<int, int>& p1, pair<int, int>& p2) {
		return p1.first + p1.second < p2.first + p2.second;
	}
};
class Solution {
public:
	vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
		vector<pair<int, int>> res;
		priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> pq;
		int m = min((int)nums1.size(), k), n = min((int)nums2.size(), k);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (pq.size() < k) {
					pq.push(make_pair(nums1[i], nums2[j]));
				}
				else if (nums1[i] + nums2[j] < pq.top().first + pq.top().second) {
					pq.push(make_pair(nums1[i], nums2[j]));
					pq.pop();
				}
			}
		}
		while (!pq.empty()) {
			res.push_back(pq.top());
			pq.pop();
		}
		return res;
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
class Solution {
public:
	int kthSmallest(vector<vector<int>>& matrix, int k) {
		int l = matrix[0][0], r = matrix.back().back();
		while (l < r) {
			int mid = l + (r - l) / 2;
			int num = 0;
			for (int i = 0; i < matrix.size(); i++) {
				num += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
			}
			if (num < k) {
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}
		return l;
	}
};
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

407. Trapping Rain Water II (Hard)

Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.

Note:
Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.

Example:

Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

Return 4.

*/
class Cell {
public:
	int row, col, height;
	Cell(int r, int c, int h) : row(r), col(c), height(h) {}
};
class Comp {
public:
	bool operator()(Cell* c1, Cell* c2) {
		return c1->height > c2->height;
	}
};
class Solution {
public:
	int trapRainWater(vector<vector<int>>& heightMap) {
		if (heightMap.empty()) {
			return 0;
		}
		int m = heightMap.size(), n = heightMap[0].size();
		priority_queue<Cell*, vector<Cell*>, Comp> pq;
		vector<vector<bool>> t(heightMap.size(), vector<bool>(heightMap[0].size(), false));
		for (int i = 0; i < m; i++) {
			t[i][0] = true;
			t[i][n - 1] = true;
			pq.push(new Cell(i, 0, heightMap[i][0]));
			pq.push(new Cell(i, n - 1, heightMap[i][n - 1]));
		}
		for (int i = 1; i < n - 1; i++) {
			t[0][i] = true;
			t[m - 1][i] = true;
			pq.push(new Cell(0, i, heightMap[0][i]));
			pq.push(new Cell(m - 1, i, heightMap[m - 1][i]));
		}
		int res = 0;
		vector<pair<int, int>> nei = { make_pair(-1, 0), make_pair(1, 0), make_pair(0, -1), make_pair(0, 1) };
		while (!pq.empty()) {
			Cell *c = pq.top();
			pq.pop();
			for (pair<int, int> p : nei) {
				int row = c->row + p.first, col = c->col + p.second;
				if (row >= 0 && row < m && col >= 0 && col < n && t[row][col] == false) {
					t[row][col] = true;
					res += max(0, c->height - heightMap[row][col]);
					pq.push(new Cell(row, col, max(c->height, heightMap[row][col])));
				}
			}
		}
		return res;
	}
};
/*

451. Sort Characters By Frequency (Medium)

Given a string, sort it in decreasing order based on the frequency of characters.

Example 1:

Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
Example 2:

Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.
Example 3:

Input:
"Aabb"

Output:
"bbAa"

Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.

*/
class Solution {
public:
	string frequencySort(string s) {
		string res;
		int t[256] = { 0 };
		vector<string> bucket(s.size() + 1);
		for (char cha : s) {
			t[cha]++;
		}
		for (int i = 0; i < 256; i++) {
			if (t[i] > 0) {
				bucket[t[i]].append(t[i], (char)i);
			}
		}
		for (int i = bucket.size() - 1; i >= 0; i--) {
			if (!bucket[i].empty()) {
				res += bucket[i];
			}
		}
		return res;
	}
};