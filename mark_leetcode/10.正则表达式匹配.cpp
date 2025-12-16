/*
 * @lc app=leetcode.cn id=10 lang=cpp
 *
 * [10] 正则表达式匹配
 */
#include <string>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    bool isMatch(string s, string p) {
        // 动态规划
        // dp[i][j] 表示 s[0 .. i] 和 p[0 ... j] 是否匹配
        // 若 p 出现 *，则只需要判断上一个元素是否相等即可

        int n = s.size(), m = p.size();

        // 注意 dp 数组大小，i-1才表示的是数组第i个元素
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1));

        dp[0][0] = true;

        // 处理出现*的情况，每次都跳过2个位置来判断
        for (int j = 2; j <= m; j += 2) {
            dp[0][j] = p[j - 1] == '*' ? dp[0][j - 2] : false;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <=m; j++) {
                // 判断 s[i - 1] 和 p[j - 1] 元素是否相等
                // 若元素相等，或者出现 .
                if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    // 如果p[j - 1]是 * 则需要根据不同状态进行判断：

                    // 1. s[0 .. i - 2] 和 p[0 ... j - 1]匹配
                    // 并且，s[i - 1] (当前元素) 与上一个模式元素 p[j - 2] 相同
                    if (dp[i - 1][j] && s[i - 1] == p[j - 2]) dp[i][j] = true;

                    // 2. s[0 .. i - 2] 和 p[0 ... j - 1]匹配
                    // 并且，上一个模式元素 p[j - 1] 是 . 表示为可以匹配任意字符
                    if (dp[i - 1][j] && p[j - 2] == '.') dp[i][j] = true;

                    // 3. s[0 ... i - 1] 和 p[0 ... j - 3] 的匹配《状态》为true，
                    // 将p[j - 1] 这个元素设置为0个，也能满足匹配
                    if (dp[i][j - 2]) dp[i][j] = true;
                }

            }
        }

        return dp[n][m];

    }
};
// @lc code=end
