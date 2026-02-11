/*
 * @lc app=leetcode.cn id=75 lang=cpp
 *
 * [75] 颜色分类
 */
#include <vector>

using std::vector;
// @lc code=start
class Solution {
public:
    void sortColors(vector<int>& nums) {
        // 左右指针维护区域
        // p0 维护 左边为0的区域，具体而言表示为 [0, p1 - 1] 范围的值都为0
        // p2 维护 右边为2的区域，具体而言表示为 [p2 + 1, n - 1] 范围的值都为2

        int len = nums.size();

        if (len < 2) return;

        int p0 = 0, p2 = len - 1;

        int cur = 0;

        // 注意，cur <= p2，因为 p2 指向的位置也是待处理的一部分
        while (cur <= p2) {
            if (nums[cur] == 0) {
                swapNum(nums[cur], nums[p0]);
                p0++;
                cur++;
            } else if (nums[cur] == 2) {
                swapNum(nums[cur], nums[p2]);
                p2--;
            } else {
                cur++;
            }
        }
    }

private:
    void swapNum(int& a, int& b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
};
// @lc code=end
