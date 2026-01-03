/*
 * @lc app=leetcode.cn id=50 lang=cpp
 *
 * [50] Pow(x, n)
 */
#include <limits.h>
// @lc code=start
class Solution {
public:
    double myPow(double x, int n) {
        // 快速幂
        // x^n = ?
        // x^n * (res * ?)
        // x^(n/2) * (res * x^2)
        // ...

        if (n == INT_MIN) {
            if (x == 1 || x == -1) return 1;
            return 0;
        }

        double res = 1;

        if (n < 0) {
            x = 1 / x;
            n = -n;
        }

        while (n > 0) {
            if (n & 1) {
                // 奇数，记录结果
                res *= x;
            }

            x *= x;
            n >>= 1;
        }

        return res;
    }
};
// @lc code=end
