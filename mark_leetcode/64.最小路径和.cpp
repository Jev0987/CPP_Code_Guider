/*
 * @lc app=leetcode.cn id=64 lang=cpp
 *
 * [64] 最小路径和
 */
#include <algorithm>
#include <vector>
using std::vector;
// @lc code=start
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        // 动态规划
        int n = grid.size();
        int m = grid[0].size();

        // 1 3 1
        // 1 5 1
        // 4 2 1

        // dp
        // 1 4 5
        // 2 7 6
        // 6 8 7

        // 1 3 5  
        // 5 

        vector<vector<int>> dp(n, vector<int>(m));
        dp[0][0] = grid[0][0];

        for (int i = 1; i < n; i++) { dp[i][0] = grid[i][0] + dp[i - 1][0]; }

        for (int j = 1; j < m; j++) { dp[0][j] = grid[0][j] + dp[0][j - 1]; }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }

        return dp[n - 1][m - 1];
    }
};
// @lc code=end
