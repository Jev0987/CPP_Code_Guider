/*
 * @lc app=leetcode.cn id=8 lang=cpp
 *
 * [8] 字符串转换整数 (atoi)
 */
#include <iostream>
#include <limits.h>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int myAtoi(string s) {
        int i = 0;
        bool is_neg = false;

        // 去除前导空格
        while (s[i] == ' ') i++;

        // 检查正负号
        if (s[i] == '-') {
            is_neg = true;
            i++;
        }

        if (s[i] == '+') {
            if (is_neg) return 0;
            i++;
        }

        // 跳过前置0
        while (s[i] == '0') i++;

        // 处理数字
        int res = 0;
        while (s[i] >= '0' && s[i] <= '9') {
            int cur_num = s[i] - '0';
            if (res > INT_MAX / 10 || (res == INT_MAX / 10) && cur_num > 7) { return INT_MAX; }
            if (res < INT_MIN / 10 || (res == INT_MIN / 10) && cur_num > 8) { return INT_MIN; }
            if (!is_neg) {
                res = res * 10 + cur_num;
            } else {
                res = res * 10 - cur_num;
            }
            i++;
        }

        return res;
    }
};
// @lc code=end
