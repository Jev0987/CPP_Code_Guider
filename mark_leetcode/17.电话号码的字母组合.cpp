/*
 * @lc app=leetcode.cn id=17 lang=cpp
 *
 * [17] 电话号码的字母组合
 */
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        // dfs
        dfs(digits, 0);

        return final_res;
    }

private:
    vector<string> final_res;  // 最终结果
    string track;              // 单次搜索的路径
    std::unordered_map<char, string> num_data{
        {'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
        {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
    };

    // 深度优先搜索
    void dfs(string digits, int index) {
        // 临界值，到树节点末端
        if (index == digits.size()) {
            if (track.empty()) return;
            final_res.emplace_back(track);
            return;
        }

        char c = digits[index];

        for (const auto& num_str : num_data[c]) {
            // track add node
            track.push_back(num_str);

            // trace another option
            dfs(digits, index + 1);

            // track erase node
            track.pop_back();
        }
    }
};
// @lc code=end
