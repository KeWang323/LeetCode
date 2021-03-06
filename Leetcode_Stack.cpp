/*

20. Valid Parentheses (Easy)

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

*/
class Solution {
public:
	bool isValid(string s) {
		stack<char> sta;
		for (char cha : s) {
			if (cha == '(' || cha == '{' || cha == '[') {
				sta.push(cha);
			}
			else if (sta.empty() || cha == ')' && sta.top() != '(' || cha == '}' && sta.top() != '{' || cha == ']' && sta.top() != '[') {
				return false;
			}
			else {
				sta.pop();
			}
		}
		return sta.empty();
	}
};
/*

42. Trapping Rain Water (Hard)

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.


The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!

*/
class Solution {
public:
	int trap(vector<int>& height) {
		if (height.size() < 3) {
			return 0;
		}
		int res = 0, i = 0, j = height.size() - 1;
		while (i < j - 1) {
			int bar = min(height[i], height[j]);
			for (int k = i + 1; k < j; k++) {
				if (height[k] < bar) {
					res += bar - height[k];
					height[k] = bar;
				}
			}
			while (height[i] == bar) {
				i++;
			}
			while (height[j] == bar) {
				j--;
			}
		}
		return res;
	}
};
/*

71. Simplify Path (Medium)

Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
click to show corner cases.

Corner Cases:

Did you consider the case where path = "/../"?
In this case, you should return "/".

Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
In this case, you should ignore redundant slashes and return "/home/foo".

*/
class Solution {
public:
	string simplifyPath(string path) {
		string res = "", token;
		stringstream ss(path);
		vector<string> pos;
		while (getline(ss, token, '/')) {
			if (token == "." || token == "") {
				continue;
			}
			else if (token == "..") {
				if (!pos.empty()) {
					pos.pop_back();
				}
			}
			else {
				pos.push_back(token);
			}
		}
		if (pos.empty()) {
			return "/";
		}
		for (string str : pos) {
			res += '/' + str;
		}
		return res;
	}
};
/*

84. Largest Rectangle in Histogram (Hard)

Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given heights = [2,1,5,6,2,3],
return 10.

*/
class Solution {
public:
	int largestRectangleArea(vector<int>& heights) {
		stack<int> s;
		int res = 0;
		for (int i = 0; i <= heights.size(); i++) {
			int cur = i == heights.size() ? 0 : heights[i];
			while (!s.empty() && cur <= heights[s.top()]) {
				int height = heights[s.top()];
				s.pop();
				int left = s.empty() ? 0 : s.top() + 1;
				res = max(res, height * (i - left));
			}
			s.push(i);
		}
		return res;
	}
};
/*

85. Maximal Rectangle (Hard)

Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 6.

*/
class Solution {
public:
	int maximalRectangle(vector<vector<char>>& matrix) {
		if (matrix.empty()) {
			return 0;
		}
		int maxRec = 0;
		vector<int> height(matrix[0].size());
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				height[j] = matrix[i][j] == '0' ? 0 : height[j] + 1;
			}
			maxRec = max(maxRec, largestRectangleArea(height));
		}
		return maxRec;
	}
private:
	int largestRectangleArea(const vector<int>& heights) {
		stack<int> s;
		int maxSize = 0;
		for (int i = 0; i <= heights.size(); i++) {
			int cur = i == heights.size() ? 0 : heights[i];
			while (!s.empty() && heights[s.top()] >= cur) {
				int height = heights[s.top()];
				s.pop();
				int left = s.empty() ? 0 : s.top() + 1;
				maxSize = max(maxSize, (i - left) * height);
			}
			s.push(i);
		}
		return maxSize;
	}
};
/*

94. Binary Tree Inorder Traversal (Medium)

Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree [1,null,2,3],
   1
	\
	 2
	/
   3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

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
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		inorderTraversal(root, res);
		return res;
	}
private:
	void inorderTraversal(TreeNode* root, vector<int>& res) {
		if (root) {
			inorderTraversal(root->left, res);
			res.push_back(root->val);
			inorderTraversal(root->right, res);
		}
	}
};
class Solution {
public:
	vector<int> inorderTraversal(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		stack<TreeNode*> sta;
		vector<int> res;
		while (root != NULL || !sta.empty()) {
			if (root != NULL) {
				sta.push(root);
				root = root->left;
			}
			else {
				root = sta.top();
				sta.pop();
				res.push_back(root->val);
				root = root->right;
			}
		}
		return res;
	}
};
/*

103. Binary Tree Zigzag Level Order Traversal (Medium)

Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
	3
   / \
  9  20
	/  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]

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
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<vector<int>> res;
		deque<TreeNode*> dq;
		dq.push_back(root);
		bool odd = true;
		while (!dq.empty()) {
			int _size = dq.size();
			vector<int> res_sub;
			if (odd == true) {
				for (int i = 0; i < _size; i++) {
					res_sub.push_back(dq.front()->val);
					if (dq.front()->left != NULL) {
						dq.push_back(dq.front()->left);
					}
					if (dq.front()->right != NULL) {
						dq.push_back(dq.front()->right);
					}
					dq.pop_front();
				}
			}
			else {
				for (int i = 0; i < _size; i++) {
					res_sub.push_back(dq.back()->val);
					if (dq.back()->right != NULL) {
						dq.push_front(dq.back()->right);
					}
					if (dq.back()->left != NULL) {
						dq.push_front(dq.back()->left);
					}
					dq.pop_back();
				}
			}
			odd = !odd;
			res.push_back(res_sub);
		}
		return res;
	}
};
/*

144. Binary Tree Preorder Traversal (Medium)

Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
	\
	 2
	/
   3
return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?

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
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> res;
		traversal(root, res);
		return res;
	}
	void traversal(TreeNode* root, vector<int>& res) {
		if (root) {
			res.push_back(root->val);
			traversal(root->left, res);
			traversal(root->right, res);
		}
	}
};
class Solution {
public:
	vector<int> preorderTraversal(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<int> res;
		stack<TreeNode*> sta;
		sta.push(root);
		while (!sta.empty()) {
			TreeNode *node = sta.top();
			sta.pop();
			res.push_back(node->val);
			if (node->right != NULL) {
				sta.push(node->right);
			}
			if (node->left != NULL) {
				sta.push(node->left);
			}
		}
		return res;
	}
};
/*

145. Binary Tree Postorder Traversal (Hard)

Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
	\
	 2
	/
   3
return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?

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
	vector<int> postorderTraversal(TreeNode* root) {
		if (root == NULL) {
			return{};
		}
		vector<int> res;
		stack<TreeNode*> sta;
		TreeNode *pre = NULL;
		sta.push(root);
		while (!sta.empty()) {
			TreeNode *cur = sta.top();
			if (pre == NULL || pre->left == cur || pre->right == cur) {
				if (cur->left != NULL) {
					sta.push(cur->left);
				}
				else if (cur->right != NULL) {
					sta.push(cur->right);
				}
				else {
					res.push_back(cur->val);
					sta.pop();
				}
			}
			else if (cur->left == pre) {
				if (cur->right != NULL) {
					sta.push(cur->right);
				}
				else {
					res.push_back(cur->val);
					sta.pop();
				}
			}
			else {
				res.push_back(cur->val);
				sta.pop();
			}
			pre = cur;
		}
		return res;
	}
};
/*

150. Evaluate Reverse Polish Notation (Medium)

Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:
["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

*/
class Solution {
public:
	int evalRPN(vector<string>& tokens) {
		stack<int> sta;
		for (string t : tokens) {
			if (t == "+" || t == "-" || t == "*" || t == "/") {
				int b = sta.top();
				sta.pop();
				int a = sta.top();
				sta.pop();
				if (t == "+") {
					sta.push(a + b);
				}
				else if (t == "-") {
					sta.push(a - b);
				}
				else if (t == "*") {
					sta.push(a * b);
				}
				else {
					sta.push(a / b);
				}
			}
			else {
				sta.push(stoi(t));
			}
		}
		return sta.top();
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
				int temp = q2.front();
				q2.pop();
				q1.push(temp);
			}
		}
		else {
			q2.push(x);
			while (!q1.empty()) {
				int temp = q1.front();
				q1.pop();
				q2.push(temp);
			}
		}
	}

	// Removes the element on top of the stack.
	void pop() {
		if (!q1.empty())
			q1.pop();
		if (!q2.empty())
			q2.pop();
	}

	// Get the top element.
	int top() {
		if (!q1.empty())
			return q1.front();
		if (!q2.empty())
			return q2.front();
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

255. Verify Preorder Sequence in Binary Search Tree (Medium)

Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.

You may assume each number in the sequence is unique.

Follow up:
Could you do it using only constant space complexity?

*/
class Solution {
public:
	bool verifyPreorder(vector<int>& preorder) {
		int i = 0;
		verifyPreorder(preorder, i, INT_MIN, INT_MAX);
		return i >= preorder.size() ? true : false;
	}
private:
	void verifyPreorder(vector<int>& nums, int& i, int low, int high) {
		if (i >= nums.size() || nums[i] > high || nums[i] < low) return;
		int cur = nums[i++];
		verifyPreorder(nums, i, low, cur);
		verifyPreorder(nums, i, cur, high);
		return;
	}
};
/*

272. Closest Binary Search Tree Value II (Hard)

Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:
Given target value is a floating point.
You may assume k is always valid, that is: k �� total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

Hint:

Consider implement these two helper functions:
getPredecessor(N), which returns the next smaller node to N.
getSuccessor(N), which returns the next larger node to N.
Try to assume that each node has a parent pointer, it makes the problem much easier.
Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
You would need two stacks to track the path in finding predecessor and successor node separately.

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
	vector<int> closestKValues(TreeNode* root, double target, int k) {
		stack<TreeNode*> suc, pre;
		vector<int> res;
		iniPreSta(root, target, pre);
		iniSucSta(root, target, suc);
		if (!suc.empty() && !pre.empty() && suc.top()->val == pre.top()->val) {
			getNextPredecessor(pre);
		}
		while (k-- > 0) {
			if (suc.empty()) {
				res.push_back(getNextPredecessor(pre));
			}
			else if (pre.empty()) {
				res.push_back(getNextSuccessor(suc));
			}
			else {
				if (abs((double)pre.top()->val - target) < abs((double)suc.top()->val - target)) {
					res.push_back(getNextPredecessor(pre));
				}
				else {
					res.push_back(getNextSuccessor(suc));
				}
			}
		}
		return res;
	}
private:
	void iniPreSta(TreeNode* root, double target, stack<TreeNode*>& pre) {
		while (root != NULL) {
			if (root->val < target) {
				pre.push(root);
				root = root->right;
			}
			else if (root->val > target) {
				root = root->left;
			}
			else {
				pre.push(root);
				break;
			}
		}
	}
	void iniSucSta(TreeNode* root, double target, stack<TreeNode*>& suc) {
		while (root != NULL) {
			if (root->val > target) {
				suc.push(root);
				root = root->left;
			}
			else if (root->val < target) {
				root = root->right;
			}
			else {
				suc.push(root);
				break;
			}
		}
	}
	int getNextSuccessor(stack<TreeNode*>& suc) {
		TreeNode* cur = suc.top();
		suc.pop();
		int res = cur->val;
		cur = cur->right;
		while (cur != NULL) {
			suc.push(cur);
			cur = cur->left;
		}
		return res;
	}
	int getNextPredecessor(stack<TreeNode*>& pre) {
		TreeNode* cur = pre.top();
		pre.pop();
		int res = cur->val;
		cur = cur->left;
		while (cur != NULL) {
			pre.push(cur);
			cur = cur->right;
		}
		return res;
	}
};
/*

316. Remove Duplicate Letters (Hard)

Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example:
Given "bcabc"
Return "abc"

Given "cbacdcbc"
Return "acdb"

*/
class Solution {
public:
	string removeDuplicateLetters(string s) {
		int cnt[256] = { 0 };
		bool visited[256] = { false };
		string res = "0";
		for (char cha : s) {
			cnt[cha]++;
		}
		for (char cha : s) {
			cnt[cha]--;
			if (visited[cha] == true) {
				continue;
			}
			while (cha < res.back() && cnt[res.back()] > 0) {
				visited[res.back()] = false;
				res.pop_back();
			}
			res += cha;
			visited[cha] = true;
		}
		return res.substr(1);
	}
};
/*

331. Verify Preorder Serialization of a Binary Tree (Medium)

One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as #.

	 _9_
	/   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.

Each comma separated value in the string must be either an integer or a character '#' representing null pointer.

You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".

Example 1:
"9,3,4,#,#,1,#,#,2,#,6,#,#"
Return true

Example 2:
"1,#"
Return false

Example 3:
"9,#,#,1"
Return false

*/
class Solution {
public:
	bool isValidSerialization(string preorder) {
		string s = "";
		for (int i = 0; i < preorder.length(); i++) {
			if (preorder[i] != '#') {
				s += 'n';
				while (preorder[i] != ',' && i < preorder.length()) i++;
			}
			else {
				s += '#';
				while (s.length() >= 2 && s.back() == '#' && s[s.length() - 2] == '#') {
					if (s.length() == 2) return false;
					s.pop_back();
					s.pop_back();
					s.pop_back();
					s += '#';
				}
				i++;
			}
		}
		return s == "#";
	}
};
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

394. Decode String (Medium)

Given an encoded string, return it's decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".

*/
class Solution {
public:
	string decodeString(string s) {
		string res;
		int i = 0;
		while (i < s.size()) {
			if (isalpha(s[i])) {
				res += s[i++];
			}
			else {
				int num = 0;
				while (isdigit(s[i])) {
					num = num * 10 + s[i++] - '0';
				}
				int start = ++i;
				for (int l = 1, r = 0; l != r; i++) {
					l += s[i] == '[';
					r += s[i] == ']';
				}
				string temp = decodeString(s.substr(start, i - start - 1));
				for (int j = 0; j < num; j++) {
					res += temp;
				}
			}
		}
		return res;
	}
};
/*

402. Remove K Digits (Medium)

Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be �� k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.

*/
class Solution {
public:
	string removeKdigits(string num, int k) {
		int digits = num.size() - k;
		string res(num.size(), ' ');
		int top = 0;
		for (int i = 0;i < num.size(); i++) {
			while (top > 0 && res[top - 1] > num[i] && k > 0) {
				top--;
				k--;
			}
			res[top++] = num[i];
		}
		int index = 0;
		while (index < digits && res[index] == '0') {
			index++;
		}
		return index == digits ? "0" : res.substr(index, digits - index);
	}
};
/*

496. Next Greater Element I (Easy)

You are given two arrays (without duplicates) nums1 and nums2 where nums1��s elements are subset of nums2. Find all the next greater numbers for nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, output -1 for this number.

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
	For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
	For number 1 in the first array, the next greater number for it in the second array is 3.
	For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
	For number 2 in the first array, the next greater number for it in the second array is 3.
	For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
Note:
All elements in nums1 and nums2 are unique.
The length of both nums1 and nums2 would not exceed 1000.

*/
class Solution {
public:
	vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
		vector<int> res(findNums.size());
		unordered_map<int, int> mapping;
		stack<int> sta;
		for (const int& num : nums) {
			while (!sta.empty() && sta.top() < num) {
				mapping[sta.top()] = num;
				sta.pop();
			}
			sta.push(num);
		}
		for (int i = 0; i < res.size(); i++) {
			res[i] = mapping.find(findNums[i]) == mapping.end() ? -1 : mapping[findNums[i]];
		}
		return res;
	}
};