/*
 * @lc app=leetcode.cn id=79 lang=cpp
 *
 * [79] 单词搜索
 */
#include <string>
#include <vector>

using std::string;
using std::vector;
// @lc code=start
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        // dfs，利用

        raw_ = board.size();
        col_ = board[0].size();

        mark_.assign(raw_, vector<bool>(col_, false));

        for (int i = 0; i < raw_; i++) {
            for (int j = 0; j < col_; j++) {
                if (dfs(0, i, j, board, word)) { return true; }
            }
        }

        return false;
    }

private:
    vector<vector<bool>> mark_;  // 用来标记位置是否已经选择，剪枝用
    int raw_;
    int col_;

    /**
     * @descripttion:
     * @param {int} cur  当前遍历到的 word 索引
     * @param {int} r  当前遍历到 board 横坐标
     * @param {int} c  当前遍历到的 baord 纵坐标
     * @param {vector<vector<char>>} &board
     * @param {string&} word
     * @return {*}
     */
    bool dfs(int cur, int r, int c, const vector<vector<char>>& board, const string& word) {

        // 边界检查
        // 是否使用检查
        // 元素是否相等检查
        if (r < 0 || c < 0 || r >= raw_ || c >= col_ || mark_[r][c] || board[r][c] != word[cur]) {
            return false;
        }

        // 元素找完了
        if (cur == word.size() - 1) { return true; }

        mark_[r][c] = true;

        // 递归4个方向
        if (dfs(cur + 1, r - 1, c, board, word) || dfs(cur + 1, r + 1, c, board, word) ||
            dfs(cur + 1, r, c - 1, board, word) || dfs(cur + 1, r, c + 1, board, word)) {
            return true;
        }

        // 撤销标记
        mark_[r][c] = false;

        return false;
    }
};
// @lc code=end
