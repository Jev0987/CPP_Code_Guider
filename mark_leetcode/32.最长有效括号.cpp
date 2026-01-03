/*
 * @lc app=leetcode.cn id=32 lang=cpp
 *
 * [32] 最长有效括号
 */
#include <string>
#include <stack>

using std::string;
using std::stack;
// @lc code=start
class Solution {
public:
    int longestValidParentheses(string s) {
        // 使用栈来解决
        // 出栈时统计当前下标以及栈顶下标之间的长度大小，记录最大值

        int res = 0;

        stack<int> stk;
        // 初始元素为 - 1, 假设当前 0 1是匹配的括号，那么 1 - (-1) 刚好为长度
        stk.push(-1);

        int cur = 0;

        while (cur < s.size()) {
            if(s[cur] == '(') {
                // 入栈
                stk.push(cur);
            } else {
                stk.pop();
                // 栈已经为空了，说明当前是一个单独的')'，此时push进去作为起始下标
                if (stk.empty()) stk.push(cur);
                else res = std::max(res, cur - stk.top());
            }
            cur++;
        }

        return res;
    }
};
// @lc code=end

