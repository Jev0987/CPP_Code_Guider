/*
 * @Descripttion:  模拟内存泄漏的场景，使用 asan 检测
 * @Author: jev
 * @Date: 2026-02-24
 */

#include <iostream>
#include <vector>

// 1. 直接泄漏
void trigger_direct_leak() {
    // 动态分配 100个 int 的数组在堆上
    int* orphaned_array = new int[10];

    // 函数结束，没有调用 delete[] orphaned_array。
    // 此时，局部变量 orphaned_array（指针本身）随着栈帧一起销毁了。
    // 堆上的那 400 字节彻底失去了指针引用，成为“死区”。
}

// 2. 间接泄漏
struct Node {
    int* data;
};

void trigger_indirect_leak() {
    Node* root = new Node;
    root->data = new int(42);  // 内部又分配了一块内存

    // 只释放了外层，忘记释放内层。
    // root->data 依然是一块未释放的内存，且再也找不到它了。
    // 这种被称为间接泄漏，LSan 同样能敏锐捕捉。
}

int main() {
    std::cout << "[Demo] 执行内存泄漏测试...\n";
    trigger_direct_leak();
    trigger_indirect_leak();

    std::cout << "程序即将正常退出。LSan 会在此时开始清点账目...\n";
    return 0;
}
