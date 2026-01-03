/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */
#include <algorithm>
#include <stack>
#include <vector>
using std::stack;
using std::vector;

// @lc code=start
class Solution {
public:
    int trap(vector<int>& height) {
        // 单调栈
        // 栈里存放数组下标：用于计算宽度
        // 遇到比栈顶大的值：开始计算
        // 遇到比栈顶小的值：入栈
        int n = height.size();

        stack<int> sk;

        int cur = 0;
        int res = 0;

        while (cur < n) {
            while (!sk.empty() && height[cur] > height[sk.top()]) {
                // 记录层级高度
                int layer_i = sk.top();
                int layer_height = height[layer_i];
                sk.pop();

                // 如果为空，退出判断
                if (sk.empty()) break;

                // 记录左半部分柱子高度
                int left_i = sk.top();
                int left_height = height[left_i];

                // 计算面积
                // 注意点1：高度差计算时，需要获取两边最小的长度
                int h = std::min(height[cur], left_height) - layer_height;
                int w = cur - left_i - 1;
                res += h * w;
            }

            sk.push(cur);
            cur++;
        }

        return res;
    }
};
// @lc code=end
