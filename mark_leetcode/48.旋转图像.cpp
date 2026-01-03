/*
 * @lc app=leetcode.cn id=48 lang=cpp
 *
 * [48] 旋转图像
 */
#include <vector>

using std::vector;
// @lc code=start
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        // 这道题要记住：
        // 1. 实现一个交换元素的函数
        // 2. 实现一个交换行的函数
        // 3. 镜像两行交换位置
        // 4. 对角元素交换位置

        // 模拟一下：
        // 1 2 3 4 5
        // 6 7 8 9 10
        // 11 12 13 14 15
        // 16 17 18 19 20
        // 21 22 23 24 25

        // 镜像两行交换
        // 21 22 23 24 25
        // 16 17 18 19 20
        // 11 12 13 14 15
        // 6 7 8 9 10
        // 1 2 3 4 5

        // 对角元素交换
        // 21 [16 11 6 1]
        // 22 17 [12 7 2]
        // 23 18 13 [8 3]
        // 24 19 14 9 [4]
        // 25 20 15 10 5

        // 完成

        int n = matrix.size();

        if (n == 1) return;

        // 交换镜像两行
        int start = 0, last = n - 1;
        while (start < last) {
            swapLine(matrix[start], matrix[last]);

            start++;
            last--;
        }

        // 交换对角元素
        // 按行遍历
        for (int i = 0; i < n - 1; i++) {
            // 遍历元素
            for (int j = i + 1; j < n; j++) {
                // 交换对角元素
                swapElement(matrix[i][j], matrix[j][i]);
            }
        }
    }

private:
    void swapLine(vector<int>& a, vector<int>& b) {
        vector<int> tmp{a};
        a = b;
        b = tmp;
    }

    void swapElement(int &a, int &b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
};
// @lc code=end
