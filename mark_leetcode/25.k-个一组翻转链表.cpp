/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] K 个一组翻转链表
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
struct ListNode {
    int val;
    ListNode* next;
};
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        dummy_node->next = head;
        ListNode* cur = dummy_node.get();
        
        while (cur != nullptr && cur->next != nullptr) { 
            ListNode *node1 = cur->next;
            ListNode *node2 = node1->next;
            for (int i = 0; i < k; i++) {
                if (node2 != nullptr) {

                }

            }
        }

        return dummy_node->next;
    }

private:
    std::shared_ptr<ListNode> dummy_node = std::make_shared<ListNode>();
    ListNode* reverseNode(ListNode* node1, ListNode* node2) {

        ListNode *pre = node1, *cur = node1->next;

        if (cur == nullptr) return cur;

        pre->next = node2->next;

        while (pre != node2) {

            ListNode* tmp = cur->next;

            cur->next = pre;

            pre = cur;

            cur = tmp;
        }

        return pre;
    }
};
// @lc code=end
