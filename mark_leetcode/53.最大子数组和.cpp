/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */
#include <vector>
#include <algorithm>

using std::vector;

// @lc code=start
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // [-2,1,-3,4,-1,2,1,-5,4]
        // -2 1 -2 4 3 5 6 1 5

        int n = nums.size();

        vector<int> dp(n);
        int res = nums[0];
        dp[0] = nums[0];

        for (int i = 1; i < n; i++) {
            dp[i] = std::max(nums[i], dp[i - 1] + nums[i]);

            res = std::max(dp[i], res);
        }

        return res;
    }
};
// @lc code=end

