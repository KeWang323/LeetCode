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

264. Ugly Number II (Medium)

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number.

Hint:

The naive approach is to call isUgly for every number until you reach the nth one. Most numbers are not ugly. Try to focus your effort on generating only the ugly ones.
An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly number.
The key is how to maintain the order of the ugly numbers. Try a similar approach of merging from three sorted lists: L1, L2, and L3.
Assume you have Uk, the kth ugly number. Then Uk+1 must be Min(L1 * 2, L2 * 3, L3 * 5).

*/
class Solution {
public:
	int nthUglyNumber(int n) {
		if (!n) return 0;
		static vector<int> table(1, 1);
		static int i2 = 0, i3 = 0, i5 = 0;
		int k(table.size());
		for (; k < n; k++) {
			int tmp = min(table[i2] * 2, min(table[i3] * 3, table[i5] * 5));
			if (!(tmp % 2)) i2++;
			if (!(tmp % 3)) i3++;
			if (!(tmp % 5)) i5++;
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

add(1)
add(2)
findMedian() -> 1.5
add(3)
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
		int r = matrix.size() - 1, min = matrix[0][0], max = matrix[r][r];
		while (min < max) {
			int cnt = 0, mid = (min + max) / 2;
			for (int i = 0; i <= r && matrix[i][0] <= mid; i++)
				cnt += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
			k <= cnt ? max = mid : min = mid + 1;
		}
		return min;
	}
};