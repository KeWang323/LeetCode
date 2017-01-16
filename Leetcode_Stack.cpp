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
			if (token == "." || token == "") continue;
			else if (token == "..") {
				if (!pos.empty())  pos.pop_back();
			}
			else pos.push_back(token);
		}
		if (pos.empty()) return "/";
		for (string i : pos)
			res = res + '/' + i;
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
		vector<vector<int>> res;
		if (!root) return res;
		queue<TreeNode*> q;
		q.push(root);
		int level = 0;
		while (!q.empty()) {
			vector<int> lev;
			int _size = q.size();
			for (int i = 0; i < _size; i++) {
				TreeNode *temp = q.front();
				q.pop();
				lev.push_back(temp->val);
				if (temp->left) q.push(temp->left);
				if (temp->right) q.push(temp->right);
			}
			if (level % 2) reverse(lev.begin(), lev.end());
			res.push_back(lev);
			level++;
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
		stack<TreeNode*> s;
		TreeNode *pre = NULL;
		s.push(root);
		while (!s.empty()) {
			TreeNode *cur = s.top();
			if (pre == NULL || pre->left == cur || pre->right == cur) {
				if (cur->left != NULL) {
					s.push(cur->left);
				}
				else if (cur->right != NULL) {
					s.push(cur->right);
				}
				else {
					res.push_back(cur->val);
					s.pop();
				}
			}
			else if (pre == cur->left) {
				if (cur->right != NULL) {
					s.push(cur->right);
				}
				else {
					res.push_back(cur->val);
					s.pop();
				}
			}
			else {
				res.push_back(cur->val);
				s.pop();
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
	stack<int> s1;
	stack<int> s2;
	// Push element x to the back of queue.
	void push(int x) {
		s1.push(x);
	}

	// Removes the element from in front of queue.
	void pop(void) {
		if (!s2.empty())
			s2.pop();
		else if (s1.empty())
			return;
		else {
			while (!s1.empty()) {
				int temp = s1.top();
				s1.pop();
				s2.push(temp);
			}
			s2.pop();
		}
	}

	// Get the front element.
	int peek(void) {
		if (!s2.empty())
			return s2.top();
		else if (s1.empty())
			return -1;
		else {
			while (!s1.empty()) {
				int temp = s1.top();
				s1.pop();
				s2.push(temp);
			}
		}
		return s2.top();
	}

	// Return whether the queue is empty.
	bool empty(void) {
		return  s1.empty() && s2.empty();
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
You may assume k is always valid, that is: k ¡Ü total nodes.
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