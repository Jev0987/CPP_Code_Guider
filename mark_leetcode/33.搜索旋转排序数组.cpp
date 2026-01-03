/*
 * @lc app=leetcode.cn id=33 lang=cpp
 *
 * [33] 搜索旋转排序数组
 */
#include <vector>

using std::vector;
// @lc code=start
class Solution {
public:
    int search(vector<int>& nums, int target) {
        // 二分查找

        int n = nums.size();

        int left = 0, right = n - 1;

        // 注意点1: <= 闭区间
        while (left <= right) {
            int mid = left + ((right - left) >> 1);

            if (target == nums[mid]) return mid;

            // 注意点2: <= 
            if (nums[0] <= nums[mid]) {
                // 如果中间的值比第一个数值大, 说明从 0 .. mid 都是递增的
                // 4 5 6 7 1 2 3
                // 注意点3: 元素比较
                if (target < nums[mid] && target >= nums[0]) {
                    // 目标值小于 nums[mid] , 并且目标值大于首个元素. 缩小右指针,在左半部分找
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }

            } else {
                // 如果中间的值比第一个数值小, 说明从 mid ... n - 1 都是递增的
                // 4 5 6 0 1 2 3
                if (target > nums[mid] && target <= nums[n - 1]) {
                    // 目标值大于 nums[mid], 并且目标值小于最后一个元素, 放大左指针,在右半部分找
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};
// @lc code=end
