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
// struct ListNode {
//     int val;
//     ListNode* next;
// };
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {

        // 翻转长度为1，直接返回
        if (k == 1) return head;
        // 使用 dummy_node 来记录链表头
        dummy_node->next = head;

        ListNode* cur = dummy_node.get();
        // x -> 1 -> 2 -> 3 -> 4 -> 5
        while (cur != nullptr && cur->next != nullptr) {
            ListNode* node1 = cur->next;
            ListNode* node2 = cur;
            for (int i = 0; i < k; i++) {
                if (node2 == nullptr) { break; }
                node2 = node2->next;
            }

            cur->next = reverseNode(node1, node2);
            cur = node1;
        }

        return dummy_node->next;
    }

private:
    std::shared_ptr<ListNode> dummy_node = std::make_shared<ListNode>();

    // 将 node1 -> node2 之间的节点进行翻转
    ListNode* reverseNode(ListNode* head, ListNode* tail) {

        // tail节点为nullptr，直接返回，此时不满足按k翻转的要求
        if (tail == nullptr) return head;

        // pre -> cur -> tmp
        ListNode *pre = head, *cur = head->next;

        // head->next 为nullptr， 不满足按k(k > 1)翻转的要求，直接返回
        if (cur == nullptr) return cur;

        // head的next指针指向最后一个节点(tail)的next节点
        // head -> a -> b -> tail -> c
        pre->next = tail->next;

        while (pre != tail) {

            ListNode* tmp = cur->next;

            cur->next = pre;

            pre = cur;

            cur = tmp;
        }

        return pre;
    }
};
// @lc code=end
