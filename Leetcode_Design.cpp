/*

146. LRU Cache (Hard)

Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

*/
class KeyValue {
public:
	int key, value;
	KeyValue* next;
	KeyValue(int k, int v) : key(k), value(v), next(NULL) {}
};
class LRUCache {
public:
	unordered_map<int, KeyValue*> mapping;//map key the the previous node
	KeyValue *head, *tail;
	int capacity, size;
	LRUCache(int capacity) : capacity(capacity), size(0) {
		this->head = new KeyValue(0, 0);
		this->tail = head;
		mapping.clear();
	}

	int get(int key) {
		if (mapping.find(key) == mapping.end()) {
			return -1;
		}
		moveToTail(mapping[key]);//move this one to the tail
		return mapping[key]->next->value;
	}

	void set(int key, int value) {
		if (mapping.find(key) != mapping.end()) {
			mapping[key]->next->value = value;
			moveToTail(mapping[key]);
		}
		else {
			KeyValue *node = new KeyValue(key, value);
			tail->next = node;
			mapping[key] = tail;
			tail = node;
			size++;
			if (size > capacity) {
				mapping.erase(head->next->key);
				head->next = head->next->next;
				if (head->next != NULL) {
					mapping[head->next->key] = head;
				}
				size--;
			}
		}
	}
private:
	void moveToTail(KeyValue *pre) {
		if (pre->next == tail) {
			return;
		}
		KeyValue *node = pre->next;
		pre->next = node->next;
		if (node->next != NULL) {
			mapping[node->next->key] = pre;
		}
		tail->next = node;
		node->next = NULL;
		mapping[node->key] = tail;
		tail = node;
	}
};
/*

155. Min Stack (Easy)

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.

Example:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

*/
class MinStack {
public:
	stack<int> s, s_min;
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		s.push(x);
		if (s_min.empty() || x <= s_min.top()) {
			s_min.push(x);
		}
	}

	void pop() {
		if (s.top() == s_min.top()) {
			s_min.pop();
		}
		s.pop();
	}

	int top() {
		return s.top();
	}

	int getMin() {
		return s_min.top();
	}
};
/**
* Your MinStack object will be instantiated and called as such:
* MinStack obj = new MinStack();
* obj.push(x);
* obj.pop();
* int param_3 = obj.top();
* int param_4 = obj.getMin();
*/
/*

173. Binary Search Tree Iterator (Medium)

Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.

*/
/**
* Definition for binary tree
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class BSTIterator {
private:
	void postorder(TreeNode* root, stack<int>& s) {
		if (root != NULL) {
			postorder(root->right, s);
			s.push(root->val);
			postorder(root->left, s);
		}
	}
public:
	stack<int> s;
	BSTIterator(TreeNode *root) {
		postorder(root, s);
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !s.empty();
	}

	/** @return the next smallest number */
	int next() {
		int temp = s.top();
		s.pop();
		return temp;
	}
};
/**
* Your BSTIterator will be called like this:
* BSTIterator i = BSTIterator(root);
* while (i.hasNext()) cout << i.next();
*/
/*

208. Implement Trie (Prefix Tree) (Medium)

Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.

*/
class TrieNode {
public:
	TrieNode *next[26];
	bool isWord;
	TrieNode() :isWord(false), next({ NULL }) {}
};
class Trie {
public:
	/** Initialize your data structure here. */
	Trie() {
		root = new TrieNode();
	}

	/** Inserts a word into the trie. */
	void insert(string word) {
		TrieNode *p = root;
		for (int i = 0; i < word.size(); i++) {
			if (p->next[word[i] - 'a'] == NULL) {
				p->next[word[i] - 'a'] = new TrieNode();
			}
			p = p->next[word[i] - 'a'];
		}
		p->isWord = true;
	}

	/** Returns if the word is in the trie. */
	bool search(string word) {
		TrieNode *p = find(word);
		return p != NULL && p->isWord == true;
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		return find(prefix) != NULL;
	}
private:
	TrieNode *root;
	TrieNode* find(string word) {
		TrieNode *p = root;
		for (int i = 0; i < word.size() && p != NULL; i++) {
			p = p->next[word[i] - 'a'];
		}
		return p;
	}
};
/**
* Your Trie object will be instantiated and called as such:
* Trie obj = new Trie();
* obj.insert(word);
* bool param_2 = obj.search(word);
* bool param_3 = obj.startsWith(prefix);
*/
/*

251. Flatten 2D Vector (Medium)

Implement an iterator to flatten a 2d vector.

For example,
Given 2d vector =

[
  [1,2],
  [3],
  [4,5,6]
]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].

Hint:

How many variables do you need to keep track?
Two variables is all you need. Try with x and y.
Beware of empty rows. It could be the first few rows.
To write correct code, think about the invariant to maintain. What is it?
The invariant is x and y must always point to a valid point in the 2d vector. Should you maintain your invariant ahead of time or right when you need it?
Not sure? Think about how you would implement hasNext(). Which is more complex?
Common logic in two different places should be refactored into a common method.
Follow up:
As an added challenge, try to code it using only iterators in C++ or iterators in Java.

*/
class Vector2D {
public:
	Vector2D(vector<vector<int>>& vec2d) {
		b = vec2d.begin();
		e = vec2d.end();
	}

	int next() {
		hasNext();
		return (*b)[j++];
	}

	bool hasNext() {
		while (b != e && j == (*b).size()) {
			b++, j = 0;
		}
		return b != e;
	}
private:
	vector<vector<int>>::iterator b, e;
	int j = 0;
};
/**
* Your Vector2D object will be instantiated and called as such:
* Vector2D i(vec2d);
* while (i.hasNext()) cout << i.next();
*/
/*

281. Zigzag Iterator (Medium)

Given two 1d vectors, implement an iterator to return their elements alternately.

For example, given two 1d vectors:

v1 = [1, 2]
v2 = [3, 4, 5, 6]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].

Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

Clarification for the follow up question - Update (2015-09-18):
The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases. If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For example, given the following input:

[1,2,3]
[4,5,6,7]
[8,9]
It should return [1,4,8,2,5,9,3,6,7].

*/
class ZigzagIterator {
public:
	ZigzagIterator(vector<int>& v1, vector<int>& v2) {
		b[0] = v1.begin();
		b[1] = v2.begin();
		e[0] = v1.end();
		e[1] = v2.end();
	}

	int next() {
		int elem;
		if (b[0] == e[0]) {
			elem = *b[1]++;
		}
		else if (b[1] == e[1]) {
			elem = *b[0]++;
		}
		else {
			elem = *b[cnt % 2]++;
			cnt++;
		}
		return elem;
	}

	bool hasNext() {
		return b[0] != e[0] || b[1] != e[1];
	}
private:
	vector<int>::iterator b[2], e[2];
	int cnt = 0;
};
/**
* Your ZigzagIterator object will be instantiated and called as such:
* ZigzagIterator i(v1, v2);
* while (i.hasNext()) cout << i.next();
*/
/*

297. Serialize and Deserialize Binary Tree (Hard)

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

1
/ \
2   3
/ \
4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

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
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream out;
		serialize(root, out);
		return out.str();
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream in(data);
		return deserialize(in);
	}
private:
	void serialize(TreeNode* root, ostringstream& out) {
		if (root) {
			out << root->val << ' ';
			serialize(root->left, out);
			serialize(root->right, out);
		}
		else {
			out << "# ";
		}
	}
	TreeNode* deserialize(istringstream& in) {
		string val;
		in >> val;
		if (val == "#")
			return nullptr;
		TreeNode* root = new TreeNode(stoi(val));
		root->left = deserialize(in);
		root->right = deserialize(in);
		return root;
	}
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
 /*

 225. Implement Stack using Queues (Easy)

 Implement the following operations of a stack using queues.

 push(x) -- Push element x onto stack.

 pop() -- Removes the element on top of the stack.

 top() -- Get the top element.

 empty() -- Return whether the stack is empty.

 Notes:

 You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.

 Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue.

 You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).

 */
class Stack {
public:
	queue<int> q1, q2;
	// Push element x onto stack.
	void push(int x) {
		if (q1.empty()) {
			q1.push(x);
			while (!q2.empty()) {
				q1.push(q2.front());
				q2.pop();
			}
		}
		else {
			q2.push(x);
			while (!q1.empty()) {
				q2.push(q1.front());
				q1.pop();
			}
		}
	}

	// Removes the element on top of the stack.
	void pop() {
		if (!q1.empty()) {
			q1.pop();
		}
		if (!q2.empty()) {
			q2.pop();
		}
	}

	// Get the top element.
	int top() {
		if (!q1.empty()) {
			return q1.front();
		}
		if (!q2.empty()) {
			return q2.front();
		}
		return -1;
	}

	// Return whether the stack is empty.
	bool empty() {
		return q1.empty() && q2.empty();
	}
};
/*

232. Implement Queue using Stacks (Easy)

Implement the following operations of a queue using stacks.

push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.

Notes:

You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).

*/
class Queue {
public:
	stack<int> s1, s2;
	// Push element x to the back of queue.
	void push(int x) {
		s1.push(x);
	}

	// Removes the element from in front of queue.
	void pop(void) {
		if (!s2.empty()) {
			s2.pop();
		}
		else if (!s1.empty()) {
			transfer(s1, s2);
			s2.pop();
		}
	}

	// Get the front element.
	int peek(void) {
		if (!s2.empty()) {
			return s2.top();
		}
		else if (!s1.empty()) {
			transfer(s1, s2);
			return s2.top();
		}
		else {
			return -1;
		}
	}

	// Return whether the queue is empty.
	bool empty(void) {
		return s1.empty() && s2.empty();
	}
private:
	void transfer(stack<int>& s1, stack<int>& s2) {
		while (!s1.empty()) {
			s2.push(s1.top());
			s1.pop();
		}
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

297. Serialize and Deserialize Binary Tree (Hard)

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

1
/ \
2   3
/ \
4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

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
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream out;
		serialize(root, out);
		return out.str();
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream in(data);
		return deserialize(in);
	}
private:
	void serialize(TreeNode* root, ostringstream& out) {
		if (root) {
			out << root->val << ' ';
			serialize(root->left, out);
			serialize(root->right, out);
		}
		else {
			out << "# ";
		}
	}
	TreeNode* deserialize(istringstream& in) {
		string val;
		in >> val;
		if (val == "#")
			return nullptr;
		TreeNode* root = new TreeNode(stoi(val));
		root->left = deserialize(in);
		root->right = deserialize(in);
		return root;
	}
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
/*

341. Flatten Nested List Iterator (Medium)

Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].

Example 2:
Given the list [1,[4,[6]]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].

*/
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
public:
	stack<NestedInteger> sta;
	NestedIterator(vector<NestedInteger> &nestedList) {
		for (int i = nestedList.size() - 1; i >= 0; i--) {
			sta.push(nestedList[i]);
		}
	}

	int next() {
		int result = sta.top().getInteger();
		sta.pop();
		return result;
	}

	bool hasNext() {
		while (!sta.empty()) {
			if (sta.top().isInteger() == true) {
				return true;
			}
			NestedInteger curr = sta.top();
			sta.pop();
			vector<NestedInteger>& adjs = curr.getList();
			for (int i = adjs.size() - 1; i >= 0; i--) {
				sta.push(adjs[i]);
			}
		}
		return false;
	}
};
/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
 /*

 346. Moving Average from Data Stream (Easy)

 Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

 For example,
 MovingAverage m = new MovingAverage(3);
 m.next(1) = 1
 m.next(10) = (1 + 10) / 2
 m.next(3) = (1 + 10 + 3) / 3
 m.next(5) = (10 + 3 + 5) / 3

 */
class MovingAverage {
public:
	/** Initialize your data structure here. */
	int _size = 0, sum = 0;
	deque<int> d;
	MovingAverage(int size) {
		_size = size;
	}

	double next(int val) {
		while (d.size() >= _size) {
			sum -= d.front();
			d.pop_front();
		}
		sum += val;
		d.push_back(val);
		return (double)sum / d.size();
	}
};
/**
* Your MovingAverage object will be instantiated and called as such:
* MovingAverage obj = new MovingAverage(size);
* double param_1 = obj.next(val);
*/
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

 359. Logger Rate Limiter (Easy)

 Design a logger system that receive stream of messages along with its timestamps, each message should be printed if and only if it is not printed in the last 10 seconds.

 Given a message and a timestamp (in seconds granularity), return true if the message should be printed in the given timestamp, otherwise returns false.

 It is possible that several messages arrive roughly at the same time.

 Example:

 Logger logger = new Logger();

 // logging string "foo" at timestamp 1
 logger.shouldPrintMessage(1, "foo"); returns true;

 // logging string "bar" at timestamp 2
 logger.shouldPrintMessage(2,"bar"); returns true;

 // logging string "foo" at timestamp 3
 logger.shouldPrintMessage(3,"foo"); returns false;

 // logging string "bar" at timestamp 8
 logger.shouldPrintMessage(8,"bar"); returns false;

 // logging string "foo" at timestamp 10
 logger.shouldPrintMessage(10,"foo"); returns false;

 // logging string "foo" at timestamp 11
 logger.shouldPrintMessage(11,"foo"); returns true;

 */
class Logger {
public:
	/** Initialize your data structure here. */
	Logger() {

	}

	/** Returns true if the message should be printed in the given timestamp, otherwise returns false.
	If this method returns false, the message will not be printed.
	The timestamp is in seconds granularity. */
	bool shouldPrintMessage(int timestamp, string message) {
		if (timestamp < mapping[message]) {
			return false;
		}
		mapping[message] = timestamp + 10;
		return true;
	}
private:
	unordered_map<string, int> mapping;
};
/**
* Your Logger object will be instantiated and called as such:
* Logger obj = new Logger();
* bool param_1 = obj.shouldPrintMessage(timestamp,message);
*/