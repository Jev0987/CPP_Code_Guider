/*
 * @Descripttion: 两数之和
 * @Author: jev
 * @Date: 2025-11-26
 */
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
public:
    // 返回满足两数之和数组下标
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> target_num;
        int ans1 = 0, ans2 = 0;
        // 遍历元素
        for (int i = 0; i < nums.size(); ++i) {
            if (target_num.find(target - nums[i]) != target_num.end()) {
                // 找到元素，直接返回结果
                return {target_num[target - nums[i]], i};
            }

            // 插入元素及其下标到 map 中
            target_num.insert(std::make_pair(nums[i], i));
        }
        return {ans1, ans2};
    }
};

int main() {
    Solution solution;
    std::vector<int> test1{1, 2, 3, 4, 5, 63};
    int target = 8;

    std::vector<int> ans = solution.twoSum(test1, target);
    std::cout << "index is : ";
    for (int i = 0; i < ans.size(); i++) { std::cout << ans[i] << " "; }
    std::cout << std::endl;
}
