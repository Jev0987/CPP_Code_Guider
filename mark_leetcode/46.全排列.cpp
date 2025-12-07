/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] 全排列
 */
#include <set>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        dfs(nums, 0);
        return final_res;
    }

private:
    vector<int> track;
    vector<vector<int>> final_res;
    set<int> alreay_used_index;
    void dfs(const vector<int>& nums, int index) {
        // 退出条件
        if (index == nums.size()) {
            if (track.empty()) return;
            final_res.emplace_back(track);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            // 已经选择过了，跳过
            if (alreay_used_index.find(i) != alreay_used_index.end()) { continue; }

            // track add node
            track.push_back(nums[i]);
            alreay_used_index.insert(i);

            // search another node
            dfs(nums, index + 1);

            // track erase node
            track.pop_back();
            alreay_used_index.erase(i);
        }
    }
};
// @lc code=end
