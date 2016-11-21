/*

146. LRU Cache (Hard)

Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

*/
class KeyValue {
public:
    int key, value;
    KeyValue *next;
    KeyValue (int key, int value) {
        next = NULL;
        this->key = key;
        this->value = value;
    }
    KeyValue() {
        this->next = NULL;
        this->key = 0;
        this->value = 0;
    }
};
class LRUCache{
public:
    unordered_map<int, KeyValue*> mapping;
    KeyValue *head, *tail;
    int capacity, size;
    LRUCache(int capacity) {
        this->head = new KeyValue(0, 0);
        this->tail = head;
        this->capacity = capacity;
        this->size = 0;
        mapping.clear();
    }

    int get(int key) {
        if (mapping.find(key) == mapping.end()) {
            return -1;
        }
        moveToTail(mapping[key]);
        return mapping[key]->next->value;
    }

    void set(int key, int value) {
        if (mapping.find(key) != mapping.end()) {
            mapping[key]->next->value = value;
            moveToTail(mapping[key]);
        } else {
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
    void moveToTail(KeyValue *prev) {
        if (prev->next == tail) {
            return;
        }
        KeyValue *node = prev->next;
        prev->next = node->next;
        if (node->next != NULL) {
            mapping[node->next->key] = prev;
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
	stack<int> s, min;
    /** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		s.push(x);
		if (min.empty() || x <= min.top()) {
			min.push(x);
        }
    }

    void pop() {
        if (s.top() == min.top()) {
            min.pop();
        }
        s.pop();
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return min.top();
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
  stack<int> s;
  void traversal(TreeNode* root, stack<int>& s) {
     if (root) {
        traversal(root -> right, s);
        s.push(root -> val);
        traversal(root -> left, s);
    }
}
public:
  BSTIterator(TreeNode *root) {
     traversal(root, s);
 }

    /** @return whether we have a next smallest number */
 bool hasNext() {
     return !s.empty();
 }

    /** @return the next smallest number */
 int next() {
     int num = s.top();
     s.pop();
     return num;
 }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
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
    queue<int> q1,q2;
    // Push element x onto stack.
    void push(int x) {
        if (q1.empty()) {
            q1.push(x);
            while (!q2.empty()) {
                q1.push(q2.front());
                q2.pop();
            }
        } else {
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
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
        s1.push(x);
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
    }

    // Removes the element from in front of queue.
    void pop(void) {
        s2.pop();
    }

    // Get the front element.
    int peek(void) {
        return s2.top();
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return s2.empty();
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
		Tweet(int time, int id): time(time), id(id) {}
		
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
			return x.second -> time < y.second -> time;
		};
		make_heap(h.begin(), h.end(), f);

		const int n = 10;
		vector<int> o;
		o.reserve(n);
		for (int i = 0; i < n && !h.empty(); i++) {
			pop_heap(h.begin(), h.end(), f);
			auto& hb = h.back();
			o.push_back(hb.second -> id);
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