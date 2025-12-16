/*
 * @lc app=leetcode.cn id=1094 lang=cpp
 *
 * [1094] 拼车
 */
#include <algorithm>
#include <csignal>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // 利用路线上人员的数量来判断是否满足要求
        // 若大于汽车可载人容量，则说明不满足条件

        // 获取最大的距离
        int to_max = 0;
        for (const auto& single_trip : trips) { to_max = max(to_max, single_trip[2]); }

        vector<int> diff(to_max + 1);
        for (const auto& single_trip : trips) {
            diff[single_trip[1]] += single_trip[0];
            diff[single_trip[2]] -= single_trip[0];
        }

        int counts = 0;
        for (int i = 0; i < to_max; i++) {
            counts += diff[i];

            if (counts > capacity) return false;
        }

        return true;
    }
};
// @lc code=end
