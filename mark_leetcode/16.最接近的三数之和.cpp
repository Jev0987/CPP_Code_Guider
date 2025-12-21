/*
 * @lc app=leetcode.cn id=16 lang=cpp
 *
 * [16] 最接近的三数之和
 */
#include <algorithm>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int final_res;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        final_res = nums[0] + nums[1] + nums[2];

        for (int i = 0; i < n; i++) {
            int j = i + 1;
            int k = n - 1;

            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];

                // 如果有相等的直接返回
                if (sum == target) return target;

                int remainder = abs(target - sum);
                final_res = remainder < abs(final_res - target) ? sum : final_res;
                if (sum < target) {
                    j++;
                } else {
                    k--;
                }
            }
        }

        return final_res;
    }
};
// @lc code=end
