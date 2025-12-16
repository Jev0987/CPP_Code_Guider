/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] 合并两个有序链表
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
class Solution {

private:
    std::unique_ptr<ListNode> dummy_node = std::make_unique<ListNode>(-1);

public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *ptr1 = list1, *ptr2 = list2;
        ListNode* cur = dummy_node.get();

        while (ptr1 != nullptr && ptr2 != nullptr) {
            if (ptr1->val <= ptr2->val) {
                cur->next = ptr1;
                ptr1 = ptr1->next;
            } else {
                cur->next = ptr2;
                ptr2 = ptr2->next;
            }
            cur = cur->next;
        }

        if (ptr1 != nullptr) { cur->next = ptr1; }

        if (ptr2 != nullptr) { cur->next = ptr2; }

        return dummy_node->next;
    }
};
// @lc code=end
