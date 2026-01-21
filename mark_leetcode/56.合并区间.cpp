/*
 * @lc app=leetcode.cn id=56 lang=cpp
 *
 * [56] 合并区间
 */
#include <algorithm>
#include <vector>
using std::vector;
// @lc code=start
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // 1. 按照第一个元素排序
        // 2. 遍历

        int n = intervals.size();

        if (n <= 1) return intervals;

        std::sort(intervals.begin(), intervals.end(),
                  [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

        vector<vector<int>> res;
        res.emplace_back(intervals[0]);

        for (int i = 1; i < n; i++) {
            if (intervals[i][0] <= res.back()[1]) {
                res.back()[1] = std::max(intervals[i][1], res.back()[1]);
            } else {
                res.emplace_back(intervals[i]);
            }
        }

        return res;
    }
};
// @lc code=end
