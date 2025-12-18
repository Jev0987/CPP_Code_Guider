/*
 * @lc app=leetcode.cn id=12 lang=cpp
 *
 * [12] 整数转罗马数字
 */
#include <functional>
#include <map>
#include <string>
using namespace std;

// @lc code=start
class Solution {
public:
    string intToRoman(int num) {
        string res;
        map<int, string, greater<int>> mp{
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"},
            {40, "XL"},  {10, "X"},   {9, "IX"},  {5, "V"},    {4, "IV"},  {1, "I"}};

        for (const auto& kv : mp) {
            while (num >= kv.first) {
                res += kv.second;
                num -= kv.first;
            }

            if (num == 0) { break; }
        }

        return res;
    }
};
// @lc code=end
