/*
 * @lc app=leetcode.cn id=31 lang=cpp
 *
 * [31] 下一个排列
 */
#include <algorithm>
#include <vector>

using std::vector;
// @lc code=start
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // 1. 从后往前找到需要交换的元素（第一个 nums[i] < nums[i + 1]的）
        // 2. 从后往前找的一个大于 nums[i] 的元素nums[j]
        // 3. 两个进行交换
        // 4. 反转nums[i] 后的元素
        // 5. 如果整个数组是降序，则旋转整个数组

        int n = nums.size();

        int i = n - 2;

        while (i >= 0 && nums[i] >= nums[i + 1]) i--;

        if (i >= 0) {
            int j = n - 1;

            while (i < j && nums[i] >= nums[j]) j--;

            std::swap(nums[i], nums[j]);

            std::reverse(nums.begin() + i + 1, nums.end());
        } else {
            std::reverse(nums.begin(), nums.end());
        }
    }
};
// @lc code=end
