/*
 * @lc app=leetcode.cn id=49 lang=cpp
 *
 * [49] 字母异位词分组
 */
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;
// @lc code=start
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 使用一个数组暂存，然后将每个字符串进行排序
        // 用一个map管理相同的字符的字符串 <字符串, <索引数组>>
        // 拼接结果
        vector<vector<string>> res;
        vector<string> tmp_strs = strs;
        unordered_map<string, vector<int>> ans_map;
        for (auto& s : tmp_strs) { std::sort(s.begin(), s.end()); }

        for (int i = 0; i < tmp_strs.size(); i++) {
            string tmp_s = tmp_strs[i];

            if (ans_map.find(tmp_s) == ans_map.end()) {
                // 元素不存在
                ans_map[tmp_s] = std::vector<int>{};
            }
            ans_map[tmp_s].push_back(i);
        }

        for (auto kv : ans_map) {
            vector<string> tmp_res = {};

            for (auto index : kv.second) { tmp_res.push_back(strs[index]); }

            res.push_back(tmp_res);
        }

        return res;
    }
};
// @lc code=end
