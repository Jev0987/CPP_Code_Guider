/*
 * @Descripttion: 从两个有序数组中找到第k个元素
 * @Author: jev
 * @Date: 2025-12-01
 */

#include <iostream>
#include <vector>

int findKthElementByTwoArray(const std::vector<int>& nums1, const std::vector<int>& nums2, int k) {
    int len1 = nums1.size(), len2 = nums2.size();

    int index1 = 0, index2 = 0;

    while (index1 < len1 || index2 < len2) {
        // 如果 k - 1 == 0, 返回两个数组中最小的值
        if (k == 1) return std::min(nums1[index1], nums2[index2]);
        // 如果数组1遍历完了，返回数组2中 index2 - (k - 1) 的元素。反之亦然
        if (index1 == len1) return nums2[index2 - (k - 1)];
        if (index2 == len2) return nums1[index1 - (k - 1)];

        int newIndex1 = std::min(len1, index1 + (k / 2 - 1));
        int newIndex2 = std::min(len2, index2 + (k / 2 - 1));

        if (nums1[newIndex1] < nums2[newIndex2]) {
            k -= newIndex1 - index1 + 1;
            index1 = newIndex1 + 1;
        } else {
            k -= newIndex2 - index2 + 1;
            index2 = newIndex2 + 1;
        }
    }

    return 0;
}