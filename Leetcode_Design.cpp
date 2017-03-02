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

170. Two Sum III - Data structure design (Easy)

Design and implement a TwoSum class. It should support the following operations: add and find.

add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,
add(1); add(3); add(5);
find(4) -> true
find(7) -> false

*/
class TwoSum {
public:
	/** Initialize your data structure here. */
	unordered_map<int, int> mapping;
	TwoSum() {
		mapping.clear();
	}

	/** Add the number to an internal data structure.. */
	void add(int number) {
		mapping[number]++;
	}

	/** Find if there exists any pair of numbers which sum is equal to the value. */
	bool find(int value) {
		for (auto i = mapping.begin(); i != mapping.end(); i++) {
			if (mapping.find(value - i->first) != mapping.end() && (i->first != value - i->first || mapping[i->first] > 1)) {
				return true;
			}
		}
		return false;
	}
};
/**
* Your TwoSum object will be instantiated and called as such:
* TwoSum obj = new TwoSum();
* obj.add(number);
* bool param_2 = obj.find(value);
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

244. Shortest Word Distance II (Medium)

his is a follow up of Shortest Word Distance. The only difference is now you are given the list of words and your method will be called repeatedly many times with different parameters. How would you optimize it?

Design a class which receives a list of words in the constructor, and implements a method that takes two words word1 and word2 and return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = ¡°coding¡±, word2 = ¡°practice¡±, return 3.
Given word1 = "makes", word2 = "coding", return 1.

Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.

*/
class WordDistance {
public:
	WordDistance(vector<string> words) {
		for (int i = 0; i < words.size(); i++) {
			mapping[words[i]].push_back(i);
		}
	}

	int shortest(string word1, string word2) {
		int i = 0, j = 0, res = INT_MAX;
		while (i < mapping[word1].size() && j < mapping[word2].size()) {
			res = min(res, abs(mapping[word1][i] - mapping[word2][j]));
			mapping[word1][i] < mapping[word2][j] ? i++ : j++;
		}
		return res;
	}
private:
	unordered_map<string, vector<int>> mapping;
};
/**
* Your WordDistance object will be instantiated and called as such:
* WordDistance obj = new WordDistance(words);
* int param_1 = obj.shortest(word1,word2);
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

288. Unique Word Abbreviation (Medium)

An abbreviation of a word follows the form <first letter><number><last letter>. Below are some examples of word abbreviations:

a) it                      --> it    (no abbreviation)

	 1
b) d|o|g                   --> d1g

			  1    1  1
	 1---5----0----5--8
c) i|nternationalizatio|n  --> i18n

			  1
	 1---5----0
d) l|ocalizatio|n          --> l10n
Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary. A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.

Example:
Given dictionary = [ "deer", "door", "cake", "card" ]

isUnique("dear") ->
false

isUnique("cart") ->
true

isUnique("cane") ->
false

isUnique("make") ->
true

*/
class ValidWordAbbr {
public:
	ValidWordAbbr(vector<string> dictionary) {
		for (string& str : dictionary) {
			string abbr = str[0] + to_string(str.size()) + str.back();
			mapping[abbr].insert(str);
		}
	}

	bool isUnique(string word) {
		string abbr = word[0] + to_string(word.size()) + word.back();
		return mapping[abbr].count(word) == mapping[abbr].size();
	}
private:
	unordered_map<string, unordered_set<string>> mapping;
};
/**
* Your ValidWordAbbr object will be instantiated and called as such:
* ValidWordAbbr obj = new ValidWordAbbr(dictionary);
* bool param_1 = obj.isUnique(word);
*/
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
		if (root != NULL) {
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
		if (val == "#") {
			return NULL;
		}
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
/*

362. Design Hit Counter (Medium)

Design a hit counter which counts the number of hits received in the past 5 minutes.

Each function accepts a timestamp parameter (in seconds granularity) and you may assume that calls are being made to the system in chronological order (ie, the timestamp is monotonically increasing). You may assume that the earliest timestamp starts at 1.

It is possible that several hits arrive roughly at the same time.

Example:
HitCounter counter = new HitCounter();

// hit at timestamp 1.
counter.hit(1);

// hit at timestamp 2.
counter.hit(2);

// hit at timestamp 3.
counter.hit(3);

// get hits at timestamp 4, should return 3.
counter.getHits(4);

// hit at timestamp 300.
counter.hit(300);

// get hits at timestamp 300, should return 4.
counter.getHits(300);

// get hits at timestamp 301, should return 3.
counter.getHits(301);
Follow up:
What if the number of hits per second could be very large? Does your design scale?

*/
class HitCounter {
public:
	/** Initialize your data structure here. */
	HitCounter() {
		num = 0;
	}

	/** Record a hit.
	@param timestamp - The current timestamp (in seconds granularity). */
	void hit(int timestamp) {
		num++;
		if (!q.empty() && q.back().first == timestamp) {
			q.back().second++;
		}
		else {
			q.push(make_pair(timestamp, 1));
		}
	}

	/** Return the number of hits in the past 5 minutes.
	@param timestamp - The current timestamp (in seconds granularity). */
	int getHits(int timestamp) {
		while (!q.empty() && timestamp - q.front().first >= 300) {
			num -= q.front().second;
			q.pop();
		}
		return num;
	}
private:
	queue<pair<int, int>> q;
	int num;
};
/**
* Your HitCounter object will be instantiated and called as such:
* HitCounter obj = new HitCounter();
* obj.hit(timestamp);
* int param_2 = obj.getHits(timestamp);
*/
/*

379. Design Phone Directory (Medium)

Design a Phone Directory which supports the following operations:

get: Provide a number which is not assigned to anyone.
check: Check if a number is available or not.
release: Recycle or release a number.
Example:

// Init a phone directory containing a total of 3 numbers: 0, 1, and 2.
PhoneDirectory directory = new PhoneDirectory(3);

// It can return any available phone number. Here we assume it returns 0.
directory.get();

// Assume it returns 1.
directory.get();

// The number 2 is available, so return true.
directory.check(2);

// It returns 2, the only number that is left.
directory.get();

// The number 2 is no longer available, so return false.
directory.check(2);

// Release number 2 back to the pool.
directory.release(2);

// Number 2 is available again, return true.
directory.check(2);

*/
class PhoneDirectory {
public:
	queue<int> q;
	unordered_set<int> s;
	int max;
	/** Initialize your data structure here
	@param maxNumbers - The maximum numbers that can be stored in the phone directory. */
	PhoneDirectory(int maxNumbers) {
		for (int i = 0; i < maxNumbers; i++) {
			q.push(i);
			max = maxNumbers;
		}
	}

	/** Provide a number which is not assigned to anyone.
	@return - Return an available number. Return -1 if none is available. */
	int get() {
		if (q.empty()) {
			return -1;
		}
		int res = q.front();
		q.pop();
		s.insert(res);
		return res;
	}

	/** Check if a number is available or not. */
	bool check(int number) {
		if (number >= max || number < 0) {
			return false;
		}
		return s.find(number) == s.end();
	}

	/** Recycle or release a number. */
	void release(int number) {
		if (s.find(number) != s.end())
			q.push(number);
		s.erase(number);
	}
};
/**
* Your PhoneDirectory object will be instantiated and called as such:
* PhoneDirectory obj = new PhoneDirectory(maxNumbers);
* int param_1 = obj.get();
* bool param_2 = obj.check(number);
* obj.release(number);
*/
/*

380. Insert Delete GetRandom O(1) (Medium)

Design a data structure that supports all following operations in average O(1) time.

insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
Example:

// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();

// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);

// Returns false as 2 does not exist in the set.
randomSet.remove(2);

// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);

// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();

// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);

// 2 was already in the set, so return false.
randomSet.insert(2);

// Since 2 is the only number in the set, getRandom always return 2.
randomSet.getRandom();

*/
class RandomizedSet {
public:
	/** Initialize your data structure here. */
	RandomizedSet() {

	}

	/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
	bool insert(int val) {
		if (mapping.find(val) == mapping.end()) {
			mapping[val] = t.size();
			t.push_back(val);
			return true;
		}
		return false;
	}

	/** Removes a value from the set. Returns true if the set contained the specified element. */
	bool remove(int val) {
		if (mapping.find(val) != mapping.end()) {
			mapping[t.back()] = mapping[val];
			t[mapping[val]] = t.back();
			t.pop_back();
			mapping.erase(val);
			return true;
		}
		return false;
	}

	/** Get a random element from the set. */
	int getRandom() {
		return t[rand() % t.size()];
	}
private:
	unordered_map<int, int> mapping;
	vector<int> t;
};
/**
* Your RandomizedSet object will be instantiated and called as such:
* RandomizedSet obj = new RandomizedSet();
* bool param_1 = obj.insert(val);
* bool param_2 = obj.remove(val);
* int param_3 = obj.getRandom();
*/