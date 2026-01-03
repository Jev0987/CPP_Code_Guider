/*
 * @lc app=leetcode.cn id=34 lang=cpp
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */
#include <vector>

using std::vector;

// @lc code=start
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        // 二分查找

        int left = findTarget(nums, target, true);

        int right = findTarget(nums, target, false);

        return {left, right};
    }

private:
    int findTarget(const vector<int>& nums, int target, bool is_left_bound) {
        // 二分查找
        // 找到边界后返回
        // 找到元素后，找到其左边界和有边界
        int n = nums.size();

        int left = 0, right = n - 1;

        // 闭区间
        // 5 7 7 8 8 8 10, target = 8
        // l     m     r
        // l m r
        //     lr
        //     mr l
        while (left <= right) {
            int mid = left + ((right - left) >> 1);

            if (target == nums[mid]) {
                // 找到元素后，继续往边界移动
                if (is_left_bound) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else if (target < nums[mid]) {
                right = mid - 1;
            } else if (target > nums[mid]) {
                left = mid + 1;
            }
        }

        if (is_left_bound) {
            if (left < 0 || left >= nums.size()) return -1;
            else return nums[left] == target ? left : -1;
        } else {
            if (right < 0 || right >= nums.size()) return -1;
            else return nums[right] == target ? right : -1;
        }

        // no-use
        return -1;
    }

};
// @lc code=end

