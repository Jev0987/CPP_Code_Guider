/*
 * @lc app=leetcode.cn id=70 lang=cpp
 *
 * [70] 爬楼梯
 */
#include <algorithm>
#include <vector>

using std::vector;
// @lc code=start
class Solution {
public:
    int climbStairs(int n) {
        // 动态规划
        // dp[i] 表示当前位置的方法数量
        // dp[0] 表示楼梯 1阶时，有1种方式
        // dp[1] 表示楼梯 2阶时，有2种方式
        // dp[2] = dp[0] + dp[1], 楼梯为 3阶时，在 1阶 跨 2层； 在 2阶 跨 1层；
        // 考虑 最后一阶楼梯，可能跨了1步，也可能跨了2步，所以得出如下式子：
        // dp[i] = dp[i - 1] + dp[i - 2]  表示 （i - 1）阶时，把它前两阶的方式加起来即可

        // 1 2 3 4
        // 1 2 3
        vector<int> dp(n);

        if (n == 1) return 1;
        if (n == 2) return 2;

        dp[0] = 1;
        dp[1] = 2;

        for (int i = 2; i < n; i++) { dp[i] = dp[i - 1] + dp[i - 2]; }

        return dp[n - 1];
    }
};
// @lc code=end
