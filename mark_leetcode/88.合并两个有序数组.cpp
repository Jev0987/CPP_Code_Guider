/*
 * @lc app=leetcode.cn id=88 lang=cpp
 *
 * [88] 合并两个有序数组
 */
#include <vector>
using std::vector;

// @lc code=start
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (n == 0) return;

        if (m == 0) {
            nums1 = nums2;
            return;
        }

        // 逆向双指针
        // 把数字大的放到后面

        int i = m - 1;
        int j = n - 1;
        int p = n + m - 1;

        while (i >= 0 && j >= 0) {
            nums1[p--] = nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
            // if (nums1[i] > nums2[j]) {
            //     nums1[p] = nums1[i];
            //     i--;
            // } else {
            //     nums1[p] = nums2[j];
            //     j--;
            // }
            // p--;
        }

        // 处理数组2剩余的元素，
        // 不用处理数组1, 原因数组1本身就按顺序存放了
        while (j >= 0) {
            nums1[p--] = nums2[j--];
            // p--;
            // j--;
        }
    }
};
// @lc code=end
