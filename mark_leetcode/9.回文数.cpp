/*
 * @lc app=leetcode.cn id=9 lang=cpp
 *
 * [9] 回文数
 */
#include <vector>
// @lc code=start
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        if (x == 0) return true;

        int digit = 0;
        vector<int> temp_str;

        while (x > 0) {
            int num = x % 10;
            x /= 10;
            temp_str.emplace_back(num);
            digit++;
        }

        if (temp_str.size() == 1) return true;

        int i = 0, j = temp_str.size() - 1;

        while (i < j) {
            if (temp_str[i] == temp_str[j]) {
                i++;
                j--;
            } else {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end
