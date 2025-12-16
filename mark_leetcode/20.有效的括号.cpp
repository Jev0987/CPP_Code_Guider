/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */
#include <stack>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    bool isValid(string s) {
        stack<char> braket_right_stack;

        for (const auto& c : s) {
            if (c == ')' || c == ']' || c == '}') {
                if (braket_right_stack.empty() || braket_right_stack.top() != c) { return false; }

                braket_right_stack.pop();
            }
            if (c == '(') braket_right_stack.push(')');
            if (c == '[') braket_right_stack.push(']');
            if (c == '{') braket_right_stack.push('}');
        }

        return braket_right_stack.empty();
    }
};
// @lc code=end
