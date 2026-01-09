/*
 * @lc app=leetcode.cn id=51 lang=cpp
 *
 * [51] N 皇后
 */
#include <string>
#include <unordered_set>
#include <vector>
using std::string;
using std::unordered_set;
using std::vector;
// @lc code=start
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        // 回溯法
        // 1. 按行遍历，按列摆放
        // 2. 列不重复
        // 3. 左上到右下斜对角线不重复
        // 关键：（横坐标 - 纵坐标）值相等，表示在同一个左上到右下对角线
        // 4. 左下到右上写对角线不重复
        // 关键：（横坐标 + 纵坐标）值相等，表示在同一个左下到右上对角线

        dfs(0, n);
        return final_res;
    }

private:
    unordered_set<int> col;
    unordered_set<int> duijiaoxian1;
    unordered_set<int> duijiaoxian2;

    vector<int> track;
    vector<vector<string>> final_res;

    void dfs(int row, int board_size) {
        if (row == board_size) {
            vector<string> tmp_res = putInBoard(track);
            final_res.emplace_back(tmp_res);
            return;
        }

        for (int i = 0; i < board_size; i++) {
            if (col.find(i) != col.end()) { continue; }

            if (duijiaoxian1.find(row - i) != duijiaoxian1.end()) { continue; }

            if (duijiaoxian2.find(row + i) != duijiaoxian2.end()) { continue; }

            col.insert(i);
            duijiaoxian1.insert(row - i);
            duijiaoxian2.insert(row + i);
            track.push_back(i);

            dfs(row + 1, board_size);

            col.erase(i);
            duijiaoxian1.erase(row - i);
            duijiaoxian2.erase(row + i);
            track.pop_back();
        }
    }

    vector<string> putInBoard(const vector<int>& record_index) {
        int n = record_index.size();
        vector<string> res(n, string(n, '.'));

        
        for (int i = 0; i < n; i++) {
            res[i].at(record_index[i]) = 'Q';
        }

        return res;
    }
};
// @lc code=end
