/*
 * @lc app=leetcode.cn id=39 lang=cpp
 *
 * [39] 组合总和
 */
#include <vector>

using std::vector;

// @lc code=start
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        dfs(candidates, 0, target);

        return final_res;
    }

private:
    vector<vector<int>> final_res;
    vector<int> track;
    int tmp_res = 0;

    void dfs(const vector<int>& nums, int index, int target) {
        // 若 target <= 0 记录结果，返回
        if (target <= 0) {
            if (target == 0) final_res.emplace_back(track);

            return;
        }
        for (int i = index; i < nums.size(); i++) {
            track.emplace_back(nums[i]);
            
            // 继续遍历
            dfs(nums, i, target - nums[i]);
            track.pop_back();
        }
    }
};
// @lc code=end
