/*
 * @lc app=leetcode.cn id=55 lang=cpp
 *
 * [55] 跳跃游戏
 */
#include <algorithm>
#include <vector>
using std::vector;
// @lc code=start
class Solution {
public:
    bool canJump(vector<int>& nums) {
        // dp 记录当前位置可以跳到的最远下标
        // dp[i] = max(dp[i - 1], nums[i] + i)

        // nums = [2,3,1,1,4]
        // dp = [2,4,4,4,4]

        // nums = [3,2,1,0,4]
        // dp = [3,3,3,3,4]

        int n = nums.size();
        vector<int> dp(n);
        dp[0] = nums[0];

        for (int i = 1; i < n; i++) {
            if (dp[i - 1] < i) { return false; }
            dp[i] = std::max(dp[i - 1], i + nums[i]);
        }
        return true;
    }
};
// @lc code=end
