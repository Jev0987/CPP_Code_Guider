/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 */
#include <string>
#include <unordered_set>
using namespace std;
// @lc code=start
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // 滑动窗口
        int len = s.size();
        int left = 0;
        int res = 0;
        unordered_set<char> mp;

        for (int right = 0; right < len; right++) {
            while (mp.find(s[right]) != mp.end()) {
                mp.erase(s[left]);
                left++;
            }
            mp.insert(s[right]);
            res = max(res, right - left + 1);
        }

        return res;
    }
};
// @lc code=end

