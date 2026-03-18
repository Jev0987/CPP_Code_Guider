/*
 * @lc app=leetcode.cn id=86 lang=cpp
 *
 * [86] 分隔链表
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
//     ListNode()
//         : val(0)
//         , next(nullptr) {}
//     ListNode(int x)
//         : val(x)
//         , next(nullptr) {}
//     ListNode(int x, ListNode* next)
//         : val(x)
//         , next(next) {}
// };
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        // 分开维护两个链表：小链表和大链表
        // 最后串起来

        // 例如 1 4 3 2 5 2
        // 小链表 1 2 2
        // 大链表 4 3 5

        small_dummy_ = std::make_shared<ListNode>(0);
        large_dummy_ = std::make_shared<ListNode>(0);

        ListNode* small_ptr = small_dummy_.get();
        ListNode* large_ptr = large_dummy_.get();

        ListNode* cur = head;

        while (cur != nullptr) {
            if (cur->val < x) {
                small_ptr->next = cur;
                small_ptr = small_ptr->next;
            } else {
                large_ptr->next = cur;
                large_ptr = large_ptr->next;
            }
            cur = cur->next;
        }

        // 处理大链表结尾
        large_ptr->next = nullptr;

        // 将小链表和大链表串起来
        small_ptr->next = large_dummy_->next;

        ListNode* result = small_dummy_->next;

        return result;
    }

private:
    std::shared_ptr<ListNode> small_dummy_;
    std::shared_ptr<ListNode> large_dummy_;
};
// @lc code=end
