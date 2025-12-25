/*
 * @Descripttion: 记录下KMP算法
 * @Author: jev
 * @Date: 2025-12-25
 */
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<int> buildNextArray(const string& pattern) {
    int m = pattern.size();
    vector<int> next(m, 0);

    int j = 0;

    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) { j = next[j - 1]; }

        if (pattern[i] == pattern[j]) { j++; }

        next[i] = j;
    }

    return next;
}

vector<int> KMPSerach(const string& str, const string& pattern) {
    int n = str.size();
    int m = pattern.size();

    vector<int> next = buildNextArray(pattern);
    vector<int> result;
    int j = 0;

    for (int i = 0; i < n; i++) {
        while (j > 0 && str[i] != pattern[j]) { j = next[j - 1]; }

        if (str[i] == pattern[j]) { j++; }

        if (j == m) {
            // 匹配成功
            result.emplace_back(i - m + 1);
            j = next[j - 1];  // 继续查找，切回上一个状态
        }
    }

    return result;
}

int main() {
    string str = "abababcddfgaadsf";
    string pattern = "abab";

    vector<int> result = KMPSerach(str, pattern);

    for (int i = 0; i < result.size(); i++) { cout << result[i] << ' '; }
    cout << endl;
}