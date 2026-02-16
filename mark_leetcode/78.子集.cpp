/*
 * @lc app=leetcode.cn id=78 lang=cpp
 *
 * [78] 子集
 */
#include <vector>

using std::vector;
// @lc code=start
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        // dfs，决策树
        // 横是循环，纵是递归
        //                     空
        //  第一层递归：    1   2  3
        //  第二层递归：   2   3
        //  第三层递归：  3

        // 结果
        // [], [1], [1,2], [1,2,3], [2], [2,3],[3]
        dfs(0, nums);

        return res;
    }

private:
    vector<int> track;
    vector<vector<int>> res;

    void dfs(int index, const vector<int>& nums) {
        // 收集结果
        res.push_back(track);

        // 遍历选择
        for (int i = index; i < nums.size(); i++) {
            // 选择
            track.push_back(nums[i]);

            // 往下进行，不走回头路
            dfs(i + 1, nums);

            // 撤销选择
            track.pop_back();
        }
    }
};
// @lc code=end
