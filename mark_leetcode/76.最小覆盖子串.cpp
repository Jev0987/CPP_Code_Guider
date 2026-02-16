/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 */
#include <climits>
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>
using std::string;
using std::unordered_map;
using std::vector;

// @lc code=start
class Solution {
public:
    string minWindow(string s, string t) {

        // 滑动窗口
        // 一个 need，一个 window
        // 还需要一个记录匹配个数的 valid

        size_t m = s.size();
        size_t n = t.size();

        if (n > m) return "";

        unordered_map<char, int> need, window;

        for (char c : t) { need[c]++; }

        int slow = 0, fast = 0;

        int start = 0;
        int minL = INT_MAX;
        int valid = 0;  // 记录匹配的个数 - need.size()

        while (fast < m) {
            char c = s[fast];

            // 窗口数据更新
            if (need.find(c) != need.end()) {
                // 找到元素
                window[c]++;

                if (need[c] == window[c]) { valid++; }
            }

            // 判断是否需要缩小窗口
            while (valid == need.size()) {
                // 记录结果
                if (fast - slow + 1 < minL) {
                    minL = fast - slow + 1;
                    start = slow;
                }

                // 缩小窗口
                char d = s[slow];

                if (need.find(d) != need.end()) {
                    // 找到元素，先判断匹配个数是否和need数组的相同
                    // 如果相同则使 valid--
                    if (need[d] == window[d]) { valid--; }

                    // 缩小窗口
                    window[d]--;
                }

                slow++;
            }

            fast++;
        }

        // 长度没变，则说明没有找到
        return minL == INT_MAX ? "" : s.substr(start, minL);
    }
};
// @lc code=end
