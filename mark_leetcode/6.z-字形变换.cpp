/*
 * @lc app=leetcode.cn id=6 lang=cpp
 *
 * [6] Z 字形变换
 */

// @lc code=start
#include <iostream>
#include <string>

using namespace std;
class Solution {
public:
    string convert(string s, int numRows) {
        // 第0行跳跃的值为 2*(3 - 0) - 2
        // 第0行跳跃的值为 2*(4 - 0) - 2
        // 第i行的跳跃值为 2*(row - i) - 2
        // 若i>0,则需要继续跳跃： 2*(row - row + i + 1)) = 2*(i + 1)

        // 若row=4,则
        // 第0行：2*(4 - 0) - 2 = 6, 2*(0 + 1) - 2 = 0
        // 第1行：2*(4 - 1) - 2 = 4, 2*(1 + 1) - 2 = 2
        // 第2行：2*(4 - 2) - 2 = 2, 2*(2 + 1) - 2 = 4
        // 第3行：2*(4 - 3) - 2 = 0, 2*(3 + 1) - 2 = 6

        int len = s.size();
        string res = "";

        if (numRows == 1 || numRows > len) {
            return s;
        }

        auto first_dump = [&](int row_i) {
            int jump_index = 2 * (numRows - row_i) - 2;
            if (jump_index == 0) return 2 * (row_i + 1) - 2;
            return jump_index;
        };

        auto second_dump = [&](int row_i) {
            int jump_index = 2 * (row_i + 1) - 2;
            if (jump_index == 0) return 2 * (numRows - row_i) - 2;
            return jump_index;
        };

        // PAYPALISHIRING
        for (int row_i = 0; row_i < numRows; row_i++) {
            int index = row_i;
            bool change_flag = true;
            while (index < len) {
                res += s[index];  // PINALSIGYAHRPI
                if (change_flag) {
                    index += first_dump(row_i);
                    change_flag = false;
                } else {
                    index += second_dump(row_i);
                    change_flag = true;
                }
            }
        }

        return res;
    }
};
// @lc code=end