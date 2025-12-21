/*
 * @lc app=leetcode.cn id=14 lang=cpp
 *
 * [14] 最长公共前缀
 */
#include <algorithm>
#include <string>
#include <vector>

using std::string;
using std::vector;
// @lc code=start
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res;

        if (strs.empty()) return res;

        int index = 0;

        // 找到数组中长度最小的字符串
        int min_size = 0;
        string min_str;  // flow
        for (int i = 0; i < strs.size(); i++) {
            if (strs[i].size() < min_size || min_size == 0) {
                min_size = strs[i].size();
                min_str = strs[i];
            }
        }

        // 遍历该字符串，并找到数组中所有字符串元素的相同子串
        while (index < min_size) {
            // 每轮循环都枚举
            for (const auto& s : strs) {
                if (s == min_str) continue;

                // 相等则继续遍历下一个元素
                // 不相等，则返回结果
                if (min_str[index] != s[index]) { return res; }
            }

            res += min_str[index];
            index++;
        }

        return res;
    }
};
// @lc code=end
