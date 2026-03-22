/*
 * @lc app=leetcode.cn id=85 lang=cpp
 *
 * [85] 最大矩形
 */
#include <stack>
#include <vector>

using std::stack;
using std::vector;
// @lc code=start
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        // 把 matrix 按行处理，做成多个 “柱状图”
        // 利用 84.柱状图中的最大矩形 来解决这个问题

        int n = matrix.size();
        int m = matrix[0].size();

        vector<vector<int>> nRectangle(n, vector<int>(m, 0));

        // 创建 n 行的矩形图
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == '1') {
                    nRectangle[i][j] = 1;
                    if (i > 0) { nRectangle[i][j] += nRectangle[i - 1][j]; }
                }
            }
        }

        // 利用单调栈解决这个问题
        int res = 0;
        for (int i = 0; i < n; i++) { res = std::max(res, maxRectangle(nRectangle[i], m)); }

        return res;
    }

private:
    int maxRectangle(const vector<int>& rectangles, int n) {
        // 单调栈处理矩形问题
        int res = 0;
        stack<int> sk;

        for (int i = 0; i < n; i++) {
            // 处理单调栈，保持栈内元素始终单调递增
            while (!sk.empty() && rectangles[i] <= rectangles[sk.top()]) {
                // 当前元素 小于 栈顶元素 的高度
                // 计算当前这根柱子左边所有柱子中形成的矩形大小

                // 获取右边柱子的高度
                int h_r = rectangles[sk.top()];
                sk.pop();

                // 计算长度
                int w = i;
                if (!sk.empty()) { w = i - sk.top() - 1; }

                // 计算面积
                res = std::max(res, h_r * w);
            }
            sk.push(i);
        }

        while (!sk.empty()) {
            int h_r = rectangles[sk.top()];
            sk.pop();

            int w = n;
            if (!sk.empty()) { w = n - sk.top() - 1; }

            res = std::max(res, h_r * w);
        }

        return res;
    }
};
// @lc code=end
