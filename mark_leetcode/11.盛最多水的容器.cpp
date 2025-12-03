/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        // 双指针
        // 从两边到中间

        int len = height.size();
        int left = 0, right = len - 1;

        int ans = 0;

        while (left < right) {
            int W = right - left;  // 宽
            int H = min(height[right], height[left]); // 高
            ans = max(ans, W * H);

            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return ans;
    }
};
// @lc code=end

