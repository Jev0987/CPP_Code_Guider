/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 */
#include <algorithm>
#include <string>
#include <vector>

using std::string;
using std::vector;

// @lc code=start
class Solution {
public:
    int minDistance(string word1, string word2) {
        // 动态规划思想，从末尾看问题
        // 假设有两个指针 i 和 j，分别指向 word1 和 word2 的最后一个字符
        // 此时只关心 word1[i] 和 word2[j] 的状态

        // 如果相等：
        // word1[i] == word2[j], 则不需要任何操作，dp[i][j] = d[i - 1][j - 1]

        // 如果不相等：
        // word1[i] != word2[j], 则 执行一次操作(+1 cost) 来弥补差异
        // 决策：有三种方式
        // 1. replace 替换
        // 把 word1[i] 直接改成 word2[j], 剩下要解决的是 word1[前i - 1个] 和 word2[前 j - 1 个]
        // 代价为 dp[i][j] = dp[i - 1][j - 1] + 1;
        // 2. delete 删除
        // word1[i] 是多余的，把它删掉，剩下要解决的是 word1[前 i - 1 个] (现在的i被删了) 和
        // word2[j] ，j还在 cost dp[i][j] = dp[i - 1][j] + 1;
        // 3. insert 插入
        // word1末尾处插入一个 word2[j], 剩下需要解决的是 word1[前 i 个]（因为这里插了一个word2[j]）
        // 和 word2[前j - 1个] cost dp[i][j] = dp[i][j - 1] + 1;

        // 边界条件
        // 如果 word2 为 空字符串，此时需要删除 word1
        // 如果 word1 为 空字符串，此时需要插入 word2

        size_t len1 = word1.size();
        size_t len2 = word2.size();

        // dp[i][j] 表示 word1 前i个 字符转换到 word2 前j个 字符的距离
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));

        for (int i = 0; i < len1 + 1; i++) { dp[i][0] = i; }

        for (int j = 0; j < len2 + 1; j++) { dp[0][j] = j; }

        for (int i = 1; i < len1 + 1; i++) {
            for (int j = 1; j < len2 + 1; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    // 字符相同，直接参考过去的状态
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                }
            }
        }

        return dp[len1][len2];
    }
};
// @lc code=end
