/*
 * @lc app=leetcode.cn id=24 lang=cpp
 *
 * [24] 两两交换链表中的节点
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
    ListNode* swapPairs(ListNode* head) {

        if (head == nullptr || head->next == nullptr) return head;

        dummy_node->next = head;
        ListNode* cur = dummy_node.get();

        while (cur != nullptr && cur->next != nullptr && cur->next->next != nullptr) {
            ListNode* n1 = cur->next;
            ListNode* n2 = cur->next->next;

            cur->next = swapListNode(n1, n2);

            cur = n1;
        }

        return dummy_node->next;
    }

private:
    std::shared_ptr<ListNode> dummy_node = std::make_shared<ListNode>();

    // 交换 node1 -> node2 之间的节点
    ListNode* swapListNode(ListNode* node1, ListNode* node2) {

        // n1 -> n2 -> n3 -> n4
        // n1 -> n3
        // n2 -> n1
        // return n2

        ListNode* n2_next = node2->next;

        node1->next = n2_next;

        node2->next = node1;

        return node2;
    }
};
// @lc code=end
