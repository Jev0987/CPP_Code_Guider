/*
 * @lc app=leetcode.cn id=26 lang=cpp
 *
 * [26] 删除有序数组中的重复项
 */
#include <vector>

using std::vector;
// @lc code=start
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // 双指针，快慢指针
        // 从 下标1 开始
        // 快指针对比后一项，若出现不同，就给slow位置赋值，赋值后slow + 1
        int n = nums.size();
        int slow = 1, fast = 1;

        // 1 1 1 2 3 3 4
        // 1 2 3 4
        while (fast < n) {
            if (nums[fast] != nums[fast - 1]) {
                nums[slow] = nums[fast];
                slow++;
            }

            fast++;
        }

        return slow;
    }
};
// @lc code=end
