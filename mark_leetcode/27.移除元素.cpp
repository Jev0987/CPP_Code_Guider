/*
 * @lc app=leetcode.cn id=27 lang=cpp
 *
 * [27] 移除元素
 */
#include <vector>

using std::vector;
// @lc code=start
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        // 快慢指针
        // 慢指针指向需要交换的位置
        // 快指针往后遍历，将满足条件的值往前移
        int n = nums.size();

        int slow = 0, fast = 0;

        while (fast < n) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }

        return slow;
    }
};
// @lc code=end
