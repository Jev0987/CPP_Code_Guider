/*
 * @lc app=leetcode.cn id=18 lang=cpp
 *
 * [18] 四数之和
 */
#include <algorithm>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        // 先试试这个方法：选定一个数字，其他的按照三数之和的方式写
        vector<vector<int>> res;
        int n = nums.size();

        sort(nums.begin(), nums.end());

        for (int p = 0; p < n - 3; p++) {
            if (p > 0 && nums[p] == nums[p - 1]) { continue; }

            long tmp_target = (long)target - (long)nums[p];  // 临时结果，后面的走三数之和逻辑

            for (int i = p + 1; i < n - 2; i++) {
                if (i > p + 1 && nums[i] == nums[i - 1]) { continue; }

                int j = i + 1;
                int k = n - 1;

                while (j < k) {
                    // 这里有细节需要注意结果赋值为long并不能解决赋值前的溢出，赋值前计算加上(long)
                    // 后解决问题 (long long)nums[i] + nums[j] + nums[k];   是ok的，nums[j] 和
                    // nums[k] 会逐个被隐式转换为 long (long long)nums[i] + (long long)nums[j] +
                    // (long long)nums[k];  这样写也是ok的 (long long)(nums[i] + nums[j]) + nums[k]
                    // !!!错误， 因为运算已经进行，此时会报错
                    long sum = (long)nums[i] + nums[j] + nums[k];

                    if (sum == tmp_target) {
                        res.push_back({nums[p], nums[i], nums[j], nums[k]});

                        j++;
                        k--;
                        while (j < k && nums[j] == nums[j - 1]) j++;
                        while (j < k && nums[k] == nums[k + 1]) k--;
                    } else if (sum < tmp_target) {
                        j++;
                        while (j < k && nums[j] == nums[j - 1]) j++;
                    } else if (sum > tmp_target) {
                        k--;
                        while (j < k && nums[k] == nums[k + 1]) k--;
                    }
                }
            }
        }

        return res;
    }
};
// @lc code=end
