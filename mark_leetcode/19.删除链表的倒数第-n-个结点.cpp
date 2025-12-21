/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第 N 个结点
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <memory>

// struct ListNode {
//     int val;
//     ListNode* next;
// };
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        
        ListNode *slow = dummy_node.get(), *fast = dummy_node.get();
        dummy_node->next = head;

        while (n > 0 && fast != nullptr) {
            fast = fast->next;
            n--;
        }

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }

        if (slow->next != nullptr) {
            slow->next = slow->next->next;
        }

        return dummy_node->next;
    }

private:
    std::unique_ptr<ListNode> dummy_node = std::make_unique<ListNode>();
};
// @lc code=end
