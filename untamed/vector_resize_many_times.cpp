/*
 * @Descripttion: vector 一直resize会发生什么
 * @Author: jev
 * @Date: 2026-02-08
 */
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void printVector(const vector<int>& arr) {
    size_t len = arr.size();
    cout << "arr = [";
    for (int i = 0; i < len; i++) {
        cout << arr[i];
        if (i != len - 1) { cout << ','; }
    }
    cout << "]" << endl;
}

void printVectorCap(const vector<int>& arr) {
    cout << "arr.capacity = " << arr.capacity() << endl;
    cout << "arr.size = " << arr.size() << endl;
}

void testResize(int size, vector<int>& arr) {
    arr.resize(size);
    printVector(arr);
    printVectorCap(arr);
}

int main() {
    // 尝试一直resize
    vector<int> arr{1, 2, 3, 4, 5};

    // capacity = 5, size = 5, arr = [1,2,3,4,5]
    testResize(5, arr);

    // capacity = 5, size = 2, arr = [1,2]
    testResize(2, arr);

    // capacity = 5, size = 3, arr = [1,2,0]
    testResize(3, arr);

    // capacity = 5, size = 5, arr = [1,2,0,0]
    testResize(4, arr);

    // capacity >= 6, size = 6, arr = [1,2,0,0,0,0]
    testResize(6, arr);

    // capacity >= 9, size = 9, arr = [1,2,0,0,0,0,0,0,0,0]
    testResize(9, arr);

    return 0;
}