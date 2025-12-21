/*
 * @lc app=leetcode.cn id=23 lang=cpp
 *
 * [23] 合并 K 个升序链表
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
#include <queue>
#include <vector>
using std::priority_queue;
using std::shared_ptr;
using std::vector;

// struct ListNode {
//     int val;
//     ListNode* next;
// };

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return dummy_node->next;

        ListNode* cur = dummy_node.get();

        // 1. struct bool operator
        struct com {
            bool operator()(const ListNode* a, const ListNode* b) const { return a->val > b->val; }
        };
        priority_queue<ListNode*, std::vector<ListNode*>, com> q;

        // 2. lambda
        // auto com = [](const ListNode* a, const ListNode* b) { return a->val > b->val; };
        // priority_queue<ListNode*, vector<ListNode*>, decltype(com)> q2(com);

        for (auto* head : lists) {
            if (head != nullptr) q.push(head);
        }

        while (!q.empty()) {
            auto* node = q.top();
            q.pop();
            if (node->next != nullptr) q.push(node->next);

            cur->next = node;
            cur = cur->next;
        }

        return dummy_node->next;
    }

private:
    shared_ptr<ListNode> dummy_node = std::make_shared<ListNode>();
};
// @lc code=end
