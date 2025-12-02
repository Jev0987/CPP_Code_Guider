/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 */
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    string longestPalindrome(string s) {
        // 动态规划
        // 1. 若 s[i]...s[j] 为回文子串，那么 s[i + 1] ... s[j - 1] 也为回文子串
        // 2. dp[i][j] 表示 s[i] ... s[j] 为回文子串
        // 3. 从回文子串长度开始遍历

        int len = s.size();
        int maxL = 1, begin = 0;
        vector<vector<bool>> dp(len, std::vector<bool>(len));

        // 从长度2开始遍历
        for (int L = 2; L <= len; L++) {
            // 遍历数组中的每个元素
            for (int i = 0; i < len; i++) {
                int j = i + L - 1;
                if (j >= len) break;
                if (s[i] != s[j]) {
                    dp[i][j] = false;
                } else {
                    if (j - i <= 2) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }

                    if (dp[i][j] && maxL < j - i + 1) {
                        maxL = j - i + 1;
                        begin = i;
                    }
                }
            }
        }
        return s.substr(begin, maxL);
    }
};
// @lc code=end

