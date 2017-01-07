/*

2. Add Two Numbers (Medium)

You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

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
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode *dummy = new ListNode(-1), *p = dummy;
		int carry = 0;
		while (carry != 0 || l1 != NULL || l2 != NULL) {
			int a = l1 == NULL ? 0 : l1->val, b = l2 == NULL ? 0 : l2->val;
			carry += a + b;
			p->next = new ListNode(carry % 10);
			p = p->next;
			carry /= 10;
			l1 = l1 == NULL ? NULL : l1->next;
			l2 = l2 == NULL ? NULL : l2->next;
		}
		return dummy->next;
	}
};
/*

19. Remove Nth Node From End of List (Easy)

Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.

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
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		if (head == NULL) {
			return head;
		}
		ListNode *p = head, *q = head, *q_prev = NULL;
		for (int i = 0; i < n - 1; i++) {
			p = p->next;
		}
		while (p->next != NULL) {
			p = p->next;
			q_prev = q;
			q = q->next;
		}
		if (!q_prev) {
			return head->next;
		}
		q_prev->next = q->next;
		return head;
	}
};
/*

21. Merge Two Sorted Lists (Easy)

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

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
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* dummy = new ListNode(-1);
		for (ListNode* p = dummy; l1 != NULL || l2 != NULL; p = p->next) {
			if (l1 == NULL || l2 != NULL && l2->val < l1->val) {
				p->next = l2;
				l2 = l2->next;
			}
			else {
				p->next = l1;
				l1 = l1->next;
			}
		}
		return dummy->next;
	}
};
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
	bool operator()(pair<ListNode*, int> p1, pair<ListNode*, int> p2) {
		return p1.first->val > p2.first->val;
	}
};
class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		priority_queue<pair<ListNode*, int>, vector<pair<ListNode*, int>>, Comp> pq;
		ListNode *dummy = new ListNode(-1);
		ListNode *cur = dummy;
		for (int i = 0; i < lists.size();i++) {
			if (lists[i] != NULL) {
				pq.push(make_pair(lists[i], i));
			}
		}
		while (!pq.empty()) {
			pair<ListNode*, int> p = pq.top();
			pq.pop();
			cur->next = p.first;
			cur = cur->next;
			lists[p.second] = lists[p.second]->next;
			if (lists[p.second] != NULL) {
				pq.push(make_pair(lists[p.second], p.second));
			}
		}
		return dummy->next;
	}
};
/*

24. Swap Nodes in Pairs (Easy)

Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.

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
	ListNode* swapPairs(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode* temp = head->next;
		head->next = swapPairs(temp->next);
		temp->next = head;
		return temp;
	}
};
/*

25. Reverse Nodes in k-Group (Hard)

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

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
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *node = head;
		int index = 1;
		while (index < k) {
			node = node->next;
			if (node == NULL) {
				return head;
			}
			index++;
		}
		ListNode *next = head->next;
		head->next = reverseKGroup(node->next, k);
		index = 1;
		while (index < k) {
			ListNode *post = next->next;
			next->next = head;
			head = next;
			next = post;
			index++;
		}
		return node;
	}
};
/*

61. Rotate List (Medium)

Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

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
	ListNode* rotateRight(ListNode* head, int k) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		int len = 1;
		ListNode *p = head, *q = head;
		while (p->next != NULL) {
			p = p->next;
			len++;
		}
		k %= len;
		p = head;
		for (int i = 0; i < k; i++) {
			p = p->next;
		}
		while (p->next != NULL) {
			p = p->next;
			q = q->next;
		}
		p->next = head;
		ListNode *newh = q->next;
		q->next = NULL;
		return newh;
	}
};
class Solution {
public:
	ListNode* rotateRight(ListNode* head, int k) {
		if (!head) {
			return head;
		}
		int len = 1;
		ListNode *p = head;
		while (p->next != NULL) {
			len++;
			p = p->next;
		}
		p->next = head;
		k %= len;
		for (int i = 0; i < len - k; i++, p = p->next) {
		}
		ListNode *head_new = p->next;
		p->next = NULL;
		return head_new;
	}
};
/*

82. Remove Duplicates from Sorted List II (Medium)

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.

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
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *dummy = new ListNode(-1);
		dummy->next = head;
		ListNode *p = dummy;
		while (head != NULL) {
			ListNode *post = head->next;
			if (post != NULL && post->val == head->val) {
				while (post != NULL && post->val == head->val) {
					post = post->next;
				}
				head = post;
				p->next = head;
			}
			else {
				p = head;
				head = head->next;
			}
		}
		return dummy->next;
	}
};
/*

83. Remove Duplicates from Sorted List (Easy)

Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.

*/
/**
 * Definition for singly-linked list.`
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (head != NULL || head->next != NULL) {
			return head;
		}
		ListNode *p = head;
		while (p != NULL && p->next != NULL) {
			if (p->val == p->next->val) {
				p->next = p->next->next;
			}
			else {
				p = p->next;
			}
		}
		return head;
	}
};
/*

86. Partition List (Medium)

Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.

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
	ListNode* partition(ListNode* head, int x) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *s = new ListNode(-1), *g = new ListNode(-1);
		ListNode *p = s, *q = g;
		while (head != NULL) {
			if (head->val < x) {
				p->next = head;
				p = p->next;
			}
			else {
				q->next = head;
				q = q->next;
			}
			head = head->next;
		}
		p->next = g->next;
		q->next = NULL;
		return s->next;
	}
};
/*

92. Reverse Linked List II (Medium)

Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list.

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
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		ListNode *head_new = new ListNode(0);
		head_new->next = head;
		ListNode *p = head_new;
		int i = 1;
		while (i < n) {
			if (i++ < m) {
				p = head;
				head = head->next;
			}
			else {
				ListNode *post = head->next;
				head->next = head->next->next;
				post->next = p->next;
				p->next = post;
			}
		}
		return head_new->next;
	}
};
/*

109. Convert Sorted List to Binary Search Tree (Medium)

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
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
	TreeNode* sortedListToBST(ListNode* head) {
		TreeNode *fake = new TreeNode(-1);
		if (head == NULL) {
			return fake->left;
		}
		else if (head->next == NULL) {
			fake->val = head->val;
			return fake;
		}
		ListNode *fast = head, *slow = head, *slow_prev = NULL;
		while (fast->next != NULL && fast->next->next != NULL) {
			slow_prev = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		fake->val = slow->val;
		if (slow_prev != NULL) {
			slow_prev->next = NULL;
			fake->left = sortedListToBST(head);
		}
		fake->right = sortedListToBST(slow->next);
		return fake;
	}
};
/*

138. Copy List with Random Pointer (Hard)

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

*/
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
	RandomListNode *copyRandomList(RandomListNode *head) {
		if (head == NULL) {
			return NULL;
		}
		RandomListNode *newhead = new RandomListNode(head->label);
		RandomListNode *cur = newhead;
		unordered_map<RandomListNode*, RandomListNode*> mapping;
		mapping[head] = newhead;
		while (head != NULL) {
			if (head->next != NULL) {
				if (mapping.find(head->next) == mapping.end()) {
					RandomListNode *next = new RandomListNode(head->next->label);
					mapping[head->next] = next;
				}
				cur->next = mapping[head->next];
			}
			if (head->random != NULL) {
				if (mapping.find(head->random) == mapping.end()) {
					RandomListNode *random = new RandomListNode(head->random->label);
					mapping[head->random] = random;
				}
				cur->random = mapping[head->random];
			}
			head = head->next;
			cur = cur->next;
		}
		return newhead;
	}
};
/*

141. Linked List Cycle (Easy)

Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?

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
	bool hasCycle(ListNode *head) {
		if (head == NULL) {
			return false;
		}
		ListNode *s = head, *f = head;
		while (f->next != NULL && f->next->next != NULL) {
			s = s->next;
			f = f->next->next;
			if (s == f) {
				return true;
			}
		}
		return false;

	}
};
/*

142. Linked List Cycle II (Medium)

Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?

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
	ListNode *detectCycle(ListNode *head) {
		if (head == NULL || head->next == NULL) {
			return NULL;
		}
		ListNode *s = head, *f = head;
		while (f != NULL && f->next != NULL) {
			s = s->next;
			f = f->next->next;
			if (s == f) break;
		}
		if (s != f) return NULL;
		while (head != s) {
			head = head->next;
			s = s->next;
		}
		return head;
	}
};
/*

143. Reorder List (Medium)

Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.

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
	void reorderList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return;
		}
		ListNode *s = head, *f = head;
		while (f->next != NULL && f->next->next != NULL) {
			s = s->next;
			f = f->next->next;
		}
		ListNode *newhead = reverse(s->next);
		s->next = NULL;
		s = head;
		while (newhead != NULL) {
			ListNode *newheadpos = newhead->next;
			newhead->next = s->next;
			s->next = newhead;
			s = s->next->next;
			newhead = newheadpos;
		}
	}
private:
	ListNode* reverse(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *newhead = reverse(head->next);
		head->next->next = head;
		head->next = NULL;
		return newhead;
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

160. Intersection of Two Linked Lists (Easy)

Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:          a1 → a2
				   ↘
					 c1 → c2 → c3
				   ↗
B:     b1 → b2 → b3
begin to intersect at node c1.


Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.

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
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		if (headA == NULL || headB == NULL) {
			return NULL;
		}
		ListNode *headA1 = headA, *headB1 = headB;
		int flag1 = 0, flag2 = 0;
		while (flag1 + flag2 <= 2) {
			if (headA1->val != headB1->val) {
				if (!headA1->next) {
					headA1 = headB;
					flag1++;
				}
				else {
					headA1 = headA1->next;
				}
				if (!headB1->next) {
					headB1 = headA;
					flag2++;
				}
				else {
					headB1 = headB1->next;
				}
			}
			else {
				return headA1;
			}
		}
		return NULL;
	}
};
/*

203. Remove Linked List Elements (Easy)

Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5

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
	ListNode* removeElements(ListNode* head, int val) {
		ListNode *dummy = new ListNode(-1), *p = dummy;
		dummy->next = head;
		while (p != NULL) {
			if (p->next != NULL && p->next->val == val) {
				p->next = p->next->next;
			}
			else {
				p = p->next;
			}
		}
		return dummy->next;
	}
};
/*

206. Reverse Linked List (Easy)

Reverse a singly linked list.

click to show more hints.

Hint:

A linked list can be reversed either iteratively or recursively. Could you implement both?

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
	ListNode* reverseList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *p = head, *prev = NULL;
		while (head != NULL) {
			ListNode *post = head->next;
			head->next = prev;
			prev = head;
			head = post;
		}
		return prev;
	}
};
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *newhead = reverseList(head->next);
		head->next->next = head;
		head->next = NULL;
		return newhead;
	}
};
/*

234. Palindrome Linked List (Easy)

Given a singly linked list, determine if it is a palindrome.

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
	bool isPalindrome(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return true;
		}
		ListNode *mid = head, *last = head;
		while (last->next && last->next->next) {
			mid = mid->next;
			last = last->next->next;
		}
		mid->next = reverse(mid->next);
		mid = mid->next;
		while (mid != NULL) {
			if (mid->val != head->val) {
				return false;
			}
			mid = mid->next;
			head = head->next;
		}
		return true;
	}
private:
	ListNode* reverse(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *p = head, *prev = NULL;
		while (head != NULL) {
			ListNode *post = head->next;
			head->next = prev;
			prev = head;
			head = post;
		}
		return prev;
	}
};
/*

237. Delete Node in a Linked List (Easy)

Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.

Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function.

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
	void deleteNode(ListNode* node) {
		if (node == NULL) {
			return;
		}
		node->val = node->next->val;
		node->next = node->next->next;
	}
};
/*

328. Odd Even Linked List (Medium)

Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

Example:
Given 1->2->3->4->5->NULL,
return 1->3->5->2->4->NULL.

Note:
The relative order inside both the even and odd groups should remain as it was in the input.
The first node is considered odd, the second node even and so on ...

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
	ListNode* oddEvenList(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *o = head, *eh = head->next, *e = head->next;
		while (o->next && e->next) {
			o->next = e->next;
			o = e->next;
			e->next = o->next;
			e = o->next;
		}
		o->next = eh;
		return head;
	}
};
/*

369. Plus One Linked List (Medium)

Given a non-negative number represented as a singly linked list of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.

Example:
Input:
1->2->3

Output:
1->2->4

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
	ListNode* plusOne(ListNode* head) {
		if (head == NULL) {
			return head;
		}
		ListNode *newhead = reverse(head);
		int carry = 1;
		for (ListNode *p = newhead; p != NULL && carry != 0; p = p->next) {
			int value = p->val + carry;
			p->val = value % 10;
			carry = value / 10;
		}
		head = reverse(newhead);
		if (carry > 0) {
			ListNode *p = new ListNode(1);
			p->next = head;
			return p;
		}
		return head;
	}
private:
	ListNode* reverse(ListNode* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}
		ListNode *pre = NULL;
		while (head != NULL) {
			ListNode *post = head->next;
			head->next = pre;
			pre = head;
			head = post;
		}
		return pre;
	}
};
/*

445. Add Two Numbers II (Medium)

You are given two linked lists representing two non-negative numbers. The most significant digit comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

Example:

Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7

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
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		if (l1 == NULL || l2 == NULL) {
			return l1 == NULL ? l2 : l1;
		}
		extend(l1, l2);
		ListNode *temp = add(l1, l2);
		return temp->val == 0 ? l1 : temp;
	}
private:
	int getLength(ListNode* l) {
		int res = 0;
		while (l != NULL) {
			res++;
			l = l->next;
		}
		return res;
	}
	void extend(ListNode*& l1, ListNode*& l2) {
		int len1 = getLength(l1), len2 = getLength(l2);
		while (len1 > len2) {
			ListNode *n = new ListNode(0);
			n->next = l2;
			l2 = n;
			len1--;
		}
		while (len1 < len2) {
			ListNode *n = new ListNode(0);
			n->next = l1;
			l1 = n;
			len2--;
		}
	}
	ListNode* add(ListNode* l1, ListNode* l2) {
		if (l1 == NULL) {
			return new ListNode(0);
		}
		l1->val += l2->val + add(l1->next, l2->next)->val;
		ListNode *tmp = new ListNode(l1->val / 10);
		l1->val %= 10;
		tmp->next = l1;
		return tmp;
	}
};