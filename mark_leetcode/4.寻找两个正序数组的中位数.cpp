/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个正序数组的中位数
 */
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    double findKthElementByTwoSortedArray(const vector<int>& nums1, const vector<int>& nums2, int k) {
        int len1 = nums1.size(), len2 = nums2.size();
        int index1 = 0, index2 = 0;

        while (index1 < len1 || index2 < len2) {
            // 1. 判断数组下标和数组大小，如果有一个数组遍历完了，则直接返回另一个数组的第k个元素
            if (index1 == len1) return nums2[index2 + (k - 1)];
            if (index2 == len2) return nums1[index1 + (k - 1)];

            // 2. 若 k == 1，则直接返回nums1 或 nums2 中小的值
            if (k == 1) return min(nums1[index1], nums2[index2]);

            // 3. 二分法，将k值二分，两个数组分别获得新索引值
            int newIndex1 = min(len1 - 1, index1 + (k / 2 - 1));
            int newIndex2 = min(len2 - 1, index2 + (k / 2 - 1));

            // 4. 判断两个数组第 索引+k/2 的大小，跳过值小的部分
            if (nums1[newIndex1] < nums2[newIndex2]) {
                // 5. k值减少
                k -= newIndex1 - index1 + 1;
                // 6. 移动值小的数组索引
                index1 = newIndex1 + 1;
            } else {
                k -= newIndex2 - index2 + 1;
                index2 = newIndex2 + 1;
            }
        }
        return -1;
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int total_size = nums1.size() + nums2.size();

        if (total_size & 1) {
            // 奇数
            return findKthElementByTwoSortedArray(nums1, nums2, total_size / 2 + 1);
        } else {
            // 偶数
            return (findKthElementByTwoSortedArray(nums1, nums2, total_size / 2) + findKthElementByTwoSortedArray(nums1, nums2, total_size / 2 + 1)) / 2.0;
        }
    }
};
// @lc code=end

