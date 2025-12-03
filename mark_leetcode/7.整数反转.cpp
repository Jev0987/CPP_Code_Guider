/*
 * @lc app=leetcode.cn id=7 lang=cpp
 *
 * [7] 整数反转
 */
#include <limits.h>
// @lc code=start
class Solution {
public:
    int reverse(int x) {
        // 1. 对10取余得到末位数字
        // 2. 处以10移除末位
        // 3. 正数溢出检查：reversed * 10 + digit > INT_MAX(2147483647)
        // 4. 负数溢出检查：reversed * 10 + digit < INT_MIN(-2147483648)
        int reversed = 0;

        // 1. 核心循环，当x不为0时开始
        while (x != 0) {

            // 2. 取余得到末位数字
            int digit = x % 10;

            // 3. 乘10前判断大小
            if (reversed > INT_MAX / 10 || (reversed == INT_MAX / 10 && digit > 7)) {
                return 0;
            }

            if (reversed < INT_MIN / 10 || (reversed == INT_MIN / 10 && digit < -8)) {
                return 0;
            }

            // 4. 结果乘10 且 加上末位
            reversed = reversed * 10 + digit;

            // 5. 原数字除以10, 丢弃末位
            x /= 10;
        }

        return reversed;
        
    }
};
// @lc code=end

