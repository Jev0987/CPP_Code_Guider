/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 */
#include <string>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        // 全排列，回溯法
        dfs(n, 0, 0);

        return final_res;
    }

private:
    string track;
    vector<string> final_res;

    void dfs(int n, int open, int close) {
        if (track.size() == n * 2) {
            final_res.emplace_back(track);
            return;
        }

        if (open < n) {
            track.push_back('(');

            dfs(n, open + 1, close);

            track.pop_back();
        }

        if (close < open) {
            track.push_back(')');

            dfs(n, open, close + 1);

            track.pop_back();
        }
    }
};
// @lc code=end
