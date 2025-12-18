/*
 * @lc app=leetcode.cn id=13 lang=cpp
 *
 * [13] 罗马数字转整数
 */
#include <string>
#include <unordered_map>

using namespace std;
// @lc code=start
class Solution {
public:
    int romanToInt(string s) {
        int res = 0;
        int highLevel = 1;
        unordered_map<string, int> mp{{"M", 1000}, {"D", 500}, {"C", 100}, {"L", 50},
                                      {"X", 10},   {"V", 5},   {"I", 1}};

        for (int i = s.size() - 1; i >= 0; i--) {
            string v(1, s[i]);
            int level = mp[v];
            if (level >= highLevel) {
                res += level;
                highLevel = level;
            } else {
                res -= level;
            }
        }
        return res;
    }
};
// @lc code=end
