/*
 * @lc app=leetcode.cn id=84 lang=cpp
 *
 * [84] 柱状图中最大的矩形
 */
#include <algorithm>
#include <stack>
#include <vector>
using std::stack;
using std::vector;
// @lc code=start
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // 单调栈
        // 维护一个递增的单调栈
        // 如果遇到比当前长度小的柱子，处理单调栈

        int res = 0;
        int n = heights.size();
        stack<int> st;

        for (int i = 0; i < n; i++) {
            // 如果单调栈不为空，且当前枚举柱子长度小于等于栈顶元素
            // 计算单调栈内柱子的面积
            while (!st.empty() && heights[i] < heights[st.top()]) {
                // 获取当前柱子左边第一根柱子
                int index = st.top();
                int rh = heights[index];
                st.pop();

                // 默认宽度， [0, i - 1], 即当前柱子左边范围
                int w = i;

                if (!st.empty()) {
                    // 栈顶有元素时，重新计算宽度，表示为 [sk.top() + 1, i - 1]
                    w = i - st.top() - 1;
                }

                // 计算面积
                res = std::max(res, rh * w);
            }

            st.push(i);
        }

        // 如果栈不为空，说明柱子是按序放的，如(1,2,3,4,5)
        // 计算每个栈顶元素柱子的的面积
        while (!st.empty()) {
            int top = st.top();
            int rh = heights[top];
            st.pop();

            // 默认宽度，是整个数组长度
            int w = n;

            if (!st.empty()) {
                // 栈不为空，则重新计算长度
                // 因为当前栈顶柱子长度大于栈内其他元素的柱子
                w = n - st.top() - 1;
            }

            res = std::max(res, rh * w);
        }

        return res;
    }
};
// @lc code=end
