/*
 * @lc app=leetcode.cn id=28 lang=cpp
 *
 * [28] 找出字符串中第一个匹配项的下标
 */
#include <string>
#include <vector>

using std::vector;
using std::string;
// @lc code=start
class Solution {
public:
    int strStr(string haystack, string needle) {
        // 学习使用 KMP算法
        
        int n = haystack.size();
        int m = needle.size();
        
        // KMP算法精髓： 构造next数组
        vector<int> next = buildNextArray(needle);

        int j = 0;

        for (int i = 0; i < n; i++) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }

            if (haystack[i] == needle[j]) {
                j++;
            }

            if (j == m) {
                // 匹配成功，返回结果
                // result.push_back(i - m + 1);
                // j = next[j - 1];
                return i - m + 1;
            }
        }

        return -1;
    }

private:
    vector<int> buildNextArray(const string& pattern) {
        
        int n = pattern.size();
        vector<int> next(n, 0);  // next 数组，当前索引下匹配的状态
        int j = 0;  // 状态

        for (int i = 1; i < n; i++) {

            // 字符不匹配时，回退上一个状态
            while (j > 0 && pattern[i] != pattern[j]) {
                j = next[j - 1];
            }

            if (pattern[i] == pattern[j]) {
                j++;
            }

            next[i] = j;
        }

        return next;
    }
};
// @lc code=end
