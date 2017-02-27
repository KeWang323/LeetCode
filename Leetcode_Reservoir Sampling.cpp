/*

382. Linked List Random Node (Medium)

Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.

Follow up:
What if the linked list is extremely large and its length is unknown to you? Could you solve this efficiently without using extra space?

Example:

// Init a singly linked list [1,2,3].
ListNode head = new ListNode(1);
head.next = new ListNode(2);
head.next.next = new ListNode(3);
Solution solution = new Solution(head);

// getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.
solution.getRandom();

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
	/** @param head The linked list's head.
	Note that the head is guaranteed to be not null, so it contains at least one node. */
	Solution(ListNode* head) {
		p = head;
	}

	/** Returns a random node's value. */
	int getRandom() {
		ListNode* q = p;
		int res, num = 1;
		while (q != NULL) {
			if (num == rand() % num + 1) {
				res = q->val;
			}
			num++;
			q = q->next;
		}
		return res;
	}
private:
	ListNode* p = NULL;
};
/**
* Your Solution object will be instantiated and called as such:
* Solution obj = new Solution(head);
* int param_1 = obj.getRandom();
*/
/*

398. Random Pick Index (medium)

Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.

Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

Example:

int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);

// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);

*/
class Solution {
public:
	Solution(vector<int> nums) {
		t = nums;
	}

	int pick(int target) {
		int cnt = 0, res = -1;
		for (int i = 0; i < t.size(); i++) {
			if (t[i] != target) {
				continue;
			}
			cnt++;
			if (cnt == rand() % cnt + 1) {
				res = i;
			}
		}
		return res;
	}
private:
	vector<int> t;
};
/**
* Your Solution object will be instantiated and called as such:
* Solution obj = new Solution(nums);
* int param_1 = obj.pick(target);
*/