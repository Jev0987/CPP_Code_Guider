/*
 * @Descripttion: 无重复最长子串
 * @Author: jev
 * @Date: 2025-12-01
 */

#include <iostream>
#include <string>
#include <unordered_set>
std::string LengthOfLongestSubString(const std::string& s) {
    // 滑动窗口
    int len = s.size();
    int maxL = 0, begin = 0;
    std::unordered_set<char> mp;
    int left = 0;
    for (int right = left; right < len; right++) {
        while (mp.find(s[right]) != mp.end()) {
            mp.erase(s[left]);
            left++;
        }

        mp.insert(s[right]);

        if (maxL < right - left + 1) {
            maxL = right - left + 1;
            begin = left;
        }
    }

    return s.substr(begin, maxL);
}