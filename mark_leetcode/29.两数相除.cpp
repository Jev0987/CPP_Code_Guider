/*
 * @lc app=leetcode.cn id=29 lang=cpp
 *
 * [29] 两数相除
 */
#include <limits.h>
// @lc code=start
class Solution {
public:
    // 实现整数除法，不使用乘法、除法和取模运算符
    int divide(int dividend, int divisor) {
        // 被除数为0时，结果为0
        if (dividend == 0) return 0;

        // 处理被除数为INT_MIN的特殊情况
        // INT_MIN是-2147483648，其绝对值超出int正数范围
        if (dividend == INT_MIN) {
            if (divisor == 1) return INT_MIN;  // INT_MIN ÷ 1 = INT_MIN
            if (divisor == -1)
                return INT_MAX;  // INT_MIN ÷ (-1) 应该等于2147483648，但int最大值为2147483647
        }

        // 处理除数为INT_MIN的特殊情况
        if (divisor == INT_MIN) {
            if (dividend == INT_MIN) return 1;  // INT_MIN ÷ INT_MIN = 1
            return 0;  // 任何非INT_MIN的数除以INT_MIN，结果都是0（向下取整）
        }

        // 记录结果是否需要取反（异号得负）
        bool reverse = false;

        // 将被除数和除数都转换为负数处理
        // 这样做的原因：INT_MIN转换为正数会溢出，所以统一用负数运算
        if (dividend > 0) {
            dividend = -dividend;  // 正数转负数
            reverse = !reverse;    // 符号取反
        }
        if (divisor > 0) {
            divisor = -divisor;  // 正数转负数
            reverse = !reverse;  // 符号取反
        }

        // 快速乘法函数（实际上是累加判断）
        // 功能：判断 divisor * n >= dividend 是否成立（注意都是负数）
        // 对于负数：|divisor * n| <= |dividend| 等价于 divisor * n >= dividend
        auto quickMul = [&](int divisor, int n, int dividend) -> bool {
            int res = 0;        // 累加结果
            int add = divisor;  // 当前累加值，初始为divisor

            while (n > 0) {
                // 如果n是奇数，将add加到res中
                if (n & 1) {
                    // 检查是否溢出：对于负数，需要确保 res + add >= dividend
                    // 等价于检查 res < dividend - add（因为都是负数）
                    if (res < dividend - add) return false;
                    res += add;
                }

                // 如果不是最后一位，将add翻倍（相当于左移一位）
                if (n != 1) {
                    // 检查add翻倍是否溢出
                    if (add < dividend - add) return false;
                    add += add;  // add翻倍，相当于乘以2
                }

                n >>= 1;  // n右移一位
            }
            return true;  // divisor * n >= dividend 成立
        };

        // 二分查找的边界
        // left从1开始，因为除数不为0，商至少为1（如果|dividend| >= |divisor|）
        int left = 1, right = INT_MAX;  // 商的最大可能值是INT_MAX
        int ans = 0;                    // 存储最终结果

        // 二分查找最大的n，使得 divisor * n >= dividend
        while (left <= right) {
            // 防止溢出的中点计算
            int mid = left + ((right - left) >> 1);

            // 如果 divisor * mid >= dividend
            if (quickMul(divisor, mid, dividend)) {
                ans = mid;  // 更新当前可行解

                // 如果已经达到最大值，提前结束
                if (mid == INT_MAX) break;

                left = mid + 1;  // 尝试更大的值
            } else {
                right = mid - 1;  // 尝试更小的值
            }
        }

        // 根据原始符号决定最终结果的符号
        return reverse ? -ans : ans;
    }
};
// @lc code=end
